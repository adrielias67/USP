import client
import time
import threading
import socket
import json
import sys


class user_manager:
    # Manages the user related data
    # Responsible for:
    # - creating, editing and logging users  
    # - managing the leaderboard
    # - keeping track of users status

    user_adress = {}        # {username: adress, port}
    user_login_hash = {}    # {username: password}
    user_list_in_game = {}  # {username: is in game}
    leaderboard = {}        # {username: score}
    configs_filename = "configs.json"
    activity_log_filename = "activity_log.txt"


    def __init__(self):
        pass


    def log_configs(self):
        # Logs the configurations of the user manager in a file
        configs = {}
        configs["user_adress"] = self.user_adress
        configs["user_login_hash"] = self.user_login_hash
        configs["user_list_in_game"] = self.user_list_in_game
        configs["leaderboard"] = self.leaderboard
        with open(self.configs_filename, "w") as log_file:
            json.dump(configs, log_file)


    def log_server_activity(self, message):
        # Logs the server activity in a file
        with open(self.activity_log_filename, "a") as log_file:
            log_file.write(message + "\n")


    def create_user(self, username, password, address, port):
        # Creates a user in the user manager
        # Returns if the creation was successful
        if username not in self.user_login_hash:
            self.user_login_hash[username] = password
            self.leaderboard[username] = -1
            self.user_adress[username] = address, port
            self.log_configs()
            return True
        else:
            return False

    
    def change_password(self, username, old_password, new_password):
        # Changes the user password in the user manager
        # Returns 1 if the change was successful
        # Returns 2 if the change was unsuccessful
        # Returns 3 if the user does not exist
        if username not in self.user_login_hash:
            return 3
        elif self.user_login_hash[username] != old_password:
            return 2
        self.user_login_hash[username] = new_password
        self.log_configs()
        return 1
        
    
    def login(self, username, password):
        # Logs the user in the user manager
        # Returns 1 if the login was successful
        # Returns 2 if the login was unsuccessful
        # Returns 3 if the user is already logged in
        # Returns 4 if the user does not exist
        if username in self.user_list_in_game:
            return 3
        elif username not in self.user_login_hash:
            return 4
        elif self.user_login_hash[username] == password:
            self.user_list_in_game[username] = False
            self.log_configs()
            return 1
        else:
            return 2
        
    
    def logout(self, username):
        # Logs the user out of the user manager
        if username in self.user_list_in_game:
            del self.user_list_in_game[username]
            self.log_configs()


    def join_game(self, username):
        # Joins the user in the game (manager)
        self.user_list_in_game[username] = True
        self.log_configs()


    def leave_game(self, username):
        # Leaves the user from the game (manager)
        self.logout(username)
        self.user_list_in_game[username] = False
        self.log_configs()


    def get_leaderboard(self):
        # Returns a string of the leaderboard, sorted by score
        sorted_leaderboard = ""
        for user in sorted(self.leaderboard.items(), key=lambda x: x[1], reverse=True):
            if user[1] >= 0:
                sorted_leaderboard += user[0] + ": " + str(user[1]) + "\n"
            else:
                sorted_leaderboard += user[0] + ": --" + "\n"
        return sorted_leaderboard
    

    def update_leaderboard(self, username, score):
        if score > self.leaderboard[username]:
            self.leaderboard[username] = score
            self.log_configs()
    

    def get_user_list_in_game(self):
        # Returns a string of the users in game, sorted by username
        user_list = ""
        for user in sorted(self.user_list_in_game.items(), key=lambda x: x[0], reverse=False):
            if user[1]:
                user_list += user[0] + ": in game" + "\n"
            else:
                user_list += user[0] + ": menu" + "\n"
        return user_list




class server:
    user_manager = user_manager()

    TCP_socket = None
    UDP_socket = None
    host = None
    port = None


    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.TCP_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.TCP_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.TCP_socket.bind((self.host, self.port))
        self.UDP_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.UDP_socket.bind((self.host, self.port))


    def server_restore(self):
        # Restores the server from the configs file
        try:
            with open(self.user_manager.configs_filename, "r") as log_file:
                configs = json.load(log_file)
                self.user_manager.user_adress = configs["user_adress"]
                self.user_manager.user_login_hash = configs["user_login_hash"]
                self.user_manager.user_list_in_game = configs["user_list_in_game"]
                self.user_manager.leaderboard = configs["leaderboard"]
        except:
            pass

    
    def connect(self):
        try:
            self.TCP_socket.connect((self.host, self.port))
        except Exception as e:
            self.user_manager.log_server_activity(f"Failed to connect: {e}")
        

    def send(self, client_socket, message, type, address, port):
        if type == "TCP":
            client_socket.send(message.encode())
        elif type == "UDP":
            self.UDP_socket.sendto(message.encode(), (address, port))
        else:
            self.user_manager.log_server_activity("Invalid type")
            

    def receive(self, client_socket, type):
        if type == "TCP":
            return client_socket.recv(1024).decode(), None
        elif type == "UDP":
            message, address = self.UDP_socket.recvfrom(1024)
            return message.decode(), address
    
    
    def Thandle_client_TCP(self, client_socket, addr):
        # Thread function for handling a TCP client
        connection_start, _ = self.receive(client_socket, "TCP")
        connection_start = json.loads(connection_start)
        if connection_start["type"] == "connection start":
            frame = {"type": "connection start", "status": "ok"}
            frame = json.dumps(frame)
            self.send(client_socket, frame, "TCP", None, None)
            self.user_manager.log_server_activity("Client connected from " + str(addr))
        else:
            self.user_manager.log_server_activity("Client connection error from " + str(addr))
            return

        while True:
            request, _ = self.receive(client_socket, "TCP")
            request = json.loads(request)
            if self.handle_request(client_socket, request, "TCP", None, None) == False:
                break
        client_socket.close()
        self.user_manager.log_server_activity("Client disconnected from " + str(addr))
       
        
    def Thandle_client_UDP(self):
        # Thread function for handling a UDP client
        while True:
            request, addr = self.receive(None, "UDP")
            request = json.loads(request)
            address = addr[0]
            port = addr[1]
            self.handle_request(None, request, "UDP", address, port)


    def handle_request(self, client_socket, request, type, address, port):
        # Handles a request from a client
        # Returns if the client should keep connected
        match request["type"]:
            case "new_user":
                self.new_user(client_socket, type, request["username"], request["password"], request["address"], request["port"])
                return True
            case "change_password":
                self.change_password(client_socket, type, address, port, request["username"], request["old_password"], request["new_password"])
                return True
            case "login":
                self.login(client_socket, type, address, port, request["username"], request["password"])
                return True
            case "logout":
                self.logout(client_socket, type, address, port, request["username"])
                return True
            case "disconnect":
                self.disconnect(client_socket, type, address, port, request["username"])
                return False
            case "leaderboard":
                self.leaderboard(client_socket, type, address, port)
                return True
            case "logged_users":
                self.logged_users(client_socket, type, address, port)
                return True
            case "new_match":
                self.new_match(client_socket, type, address, port, request["username"])
                return True
            case "match_over":
                self.match_over(client_socket, type, address, port, request["username"], request["score"])
                return True
            case "challenge":
                self.challenge(client_socket, type, address, port, request["username"], request["challenged_user"])
                return True
            
            
    

    def new_user(self, client_socket, type, username, password, adress, port):
        # Creates a new user
        # Writes in the frame if the creation was successful
        if self.user_manager.create_user(username, password, adress, port):
            frame = {}
            frame["type"] = "new_user"
            frame["status"] = "ok"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, adress, port)
            self.user_manager.log_server_activity("New user created: " + username)
        else:
            frame = {}
            frame["type"] = "new_user"
            frame["status"] = "fail"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, adress, port)
            self.user_manager.log_server_activity("New user creation error: " + username)
            
            
    def change_password(self, client_socket, type, address, port, username, old_password, new_password):
        # Changes the user password
        # Writes in the frame if the change was successful
        if self.user_manager.change_password(username, old_password, new_password) == 1:
            frame = {}
            frame["type"] = "change_password"
            frame["status"] = "ok"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("User password changed: " + username)
        elif self.user_manager.change_password(username, old_password, new_password) == 2:
            frame = {}
            frame["type"] = "change_password"
            frame["status"] = "fail"
            frame["error"] = "wrong password"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("User password change error: " + username + " - wrong password")
        elif self.user_manager.change_password(username, old_password, new_password) == 3:
            frame = {}
            frame["type"] = "change_password"
            frame["status"] = "fail"
            frame["error"] = "user does not exist"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("User password change error: " + username + " - user does not exist")

    
    def login(self, client_socket, type, address, port, username, password):
        # Logs the user in
        # Writes in the frame if the login was successful
        if self.user_manager.login(username, password) == 1:
            frame = {}
            frame["type"] = "login"
            frame["status"] = "ok"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("User logged in: " + username)
            return True
        elif self.user_manager.login(username, password) == 2:
            frame = {}
            frame["type"] = "login"
            frame["status"] = "fail"
            frame["error"] = "wrong password"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("User login error: " + username + " - wrong password")
        elif self.user_manager.login(username, password) == 3:
            frame = {}
            frame["type"] = "login"
            frame["status"] = "fail"
            frame["error"] = "already logged"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("User login error: " + username + " - already logged")
        elif self.user_manager.login(username, password) == 4:
            frame = {}
            frame["type"] = "login"
            frame["status"] = "fail"
            frame["error"] = "user does not exist"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("User login error: " + username + " - user does not exist")
        return False
    

    def logout(self, client_socket, type, address, port, username):
        # Logs the user out
        # Writes in the frame if the logout was successful
        self.user_manager.logout(username)
        frame = {}
        frame["type"] = "logout"
        frame["status"] = "ok"
        frame = json.dumps(frame)
        self.send(client_socket, frame, type, address, port)
        self.user_manager.log_server_activity("User logged out: " + username)

    
    def disconnect(self, client_socket, type, address, port, username):
        # Disconnects the user
        # Writes in the frame if the disconnection was successful
        self.user_manager.logout(username)
        frame = {}
        frame["type"] = "disconnect"
        frame["status"] = "ok"
        frame = json.dumps(frame)
        self.send(client_socket, frame, type, address, port)
        if username != "none":
            self.user_manager.log_server_activity("User disconnected: " + username)


    def leaderboard(self, client_socket, type, address, port):
        # Sends the leaderboard to the client
        frame = {}
        frame["type"] = "leaderboard"
        frame["leaderboard"] = self.user_manager.get_leaderboard()
        frame = json.dumps(frame)
        self.send(client_socket, frame, type, address, port)
        if type == "TCP":
            self.user_manager.log_server_activity("Leaderboard sent to client " + str(client_socket.getpeername()))
        elif type == "UDP":
            self.user_manager.log_server_activity("Leaderboard sent to client ('" + str(address) + "', " + str(port) + ")")


    def logged_users(self, client_socket, type, address, port):
        # Sends the logged users to the client
        frame = {}
        frame["type"] = "logged_users"
        frame["logged_users"] = self.user_manager.get_user_list_in_game()
        frame = json.dumps(frame)
        self.send(client_socket, frame, type, address, port)
        if type == "TCP":
            self.user_manager.log_server_activity("Logged users sent to client " + str(client_socket.getpeername()))
        elif type == "UDP":
            self.user_manager.log_server_activity("Logged users sent to client ('" + str(address) + "', " + str(port) + ")")

        
    def new_match(self, client_socket, type, address, port, username):
        # Creates a new match for user
        # Writes in the frame if the creation was successful
        self.user_manager.join_game(username)
        frame = {}
        frame["type"] = "new_match"
        frame["status"] = "ok"
        frame = json.dumps(frame)
        self.send(client_socket, frame, type, address, port)
        self.user_manager.log_server_activity("New match created for user: " + username)

    
    def match_over(self, client_socket, type, address, port, username, score):
        # Ends the match for user
        # Writes in the frame if the ending was successful
        self.user_manager.leave_game(username)
        self.user_manager.update_leaderboard(username, score)
        frame = {}
        frame["type"] = "match_over"
        frame["status"] = "ok"
        frame = json.dumps(frame)
        self.send(client_socket, frame, type, address, port)
        self.user_manager.log_server_activity("Match over for user: " + username + ", leaderboard updated")


    def challenge(self, client_socket, type, address, port, username, challenged_user):
        # Challenges a user
        # Writes in the frame if the challenge was successful
        if self.user_manager.user_list_in_game[challenged_user] == True:
            frame = {}
            frame["type"] = "challenge"
            frame["status"] = "ok"
            frame["address"] = self.user_manager.user_adress[challenged_user][0]
            frame["port"] = self.user_manager.user_adress[challenged_user][1]
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("New challenge: " + challenged_user + "'s address given to user: " + username)
        elif challenged_user not in self.user_manager.user_adress:
            frame = {}
            frame["type"] = "challenge"
            frame["status"] = "fail"
            frame["error"] = "user does not exist"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("Challenge error: " + challenged_user + " does not exist")
        elif self.user_manager.user_list_in_game[challenged_user] == False:
            frame = {}
            frame["type"] = "challenge"
            frame["status"] = "fail"
            frame["error"] = "user not in game"
            frame = json.dumps(frame)
            self.send(client_socket, frame, type, address, port)
            self.user_manager.log_server_activity("Challenge error: " + challenged_user + " not in game")
    

    def run(self, max_clients):
        # Runs the server with a maximum number of clients
        self.TCP_socket.listen(max_clients)

        # Restores the server from the configs file
        self.server_restore()

        # UDP thread
        threading.Thread(target=self.Thandle_client_UDP).start()
        
        # TCP threads
        while True:
            client_socket, client_address = self.TCP_socket.accept()
            threading.Thread(target=self.Thandle_client_TCP, args=(client_socket, client_address)).start()




if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Erro: numero de argumentos invalido.")
        print("Use: python3 server.py <port> <numero maximo de clientes que podem se conectar no servidor>")
        sys.exit(1)

    port = int(sys.argv[1])
    max_clients = int(sys.argv[2])
    s = server("localhost", port)
    s.run(max_clients)