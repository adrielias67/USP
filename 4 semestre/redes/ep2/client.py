import socket
import pacman as pac
import json
import sys
import threading
from time import sleep




class user:
    state = "unlogged"
    character = "none"
    username = "none"
    default_game_map = [list("******.**... .....**.******"),
                        list("******.**.*******.**.******"),
                        list("******.**.*.. ..*.**.******"),
                        list("..... ....*.....*.........."),
                        list("******.**.*.. ..*.**.******")]
    default_pacman_pos = (2, 13)
    default_Lghost_pos = (3, 24)
    default_total_pacdots = 54
    
    last_3_latency = [1, 2, 3]    # [last, last-1, last-2]


    def update_latency(self, latency):
        self.last_3_latency.insert(0, latency)
        self.last_3_latency.pop()

    
    def get_last_3_latency(self):
        return self.last_3_latency
    

    def set_state(self, state):
        self.state = state




class client(user):
    socket_type = "none"
    TCP_socket = None
    UDP_socket = None
    TCP_match_socket_player = None
    TCP_match_socket_ghost = None
    opponent_socket = None
    opponent_addr = None
    server_host = None
    server_port = None
    close_thread = False

    log_options = ["novo", "entra", "lideres", "l", "tchau"]
    menu_options = ["lideres", "senha", "l", "inicia", "desafio", "sai", "tchau"]
    player_options = ["move", "atraso", "encerra"]

    match = None


    def __init__(self, server_host, server_port, connection_type):
        self.server_host = server_host
        self.server_port = server_port
        if connection_type == "TCP":
            self.socket_type = "TCP"
            self.TCP_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.TCP_socket.bind(("localhost", 0))
        elif connection_type == "UDP":
            self.socket_type = "UDP"
            self.UDP_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.UDP_socket.bind(("localhost", 0))
        else:
            print("Erro: tipo de conexao invalido.")
            return


    def send(self, message):
        if self.socket_type == "TCP":
            self.TCP_socket.send(message.encode())
        elif self.socket_type == "UDP":
            self.UDP_socket.sendto(message.encode(), (self.server_host, self.server_port))
        else:
            print("Erro: tipo de conexao invalido.")

    
    def receive(self):
        if self.socket_type == "TCP":
            return self.TCP_socket.recv(1024).decode(), None
        elif self.socket_type == "UDP":
            message, address = self.UDP_socket.recvfrom(1024)
            return message.decode(), address


    def player_send_opponent(self, message):
        self.TCP_match_socket_player.send(message.encode())
    

    def player_receive_opponent(self):
        return self.TCP_match_socket_player.recv(1024).decode()
    

    def ghost_send_opponent(self, message):
        self.TCP_match_socket_ghost.send(message.encode())


    def ghost_receive_opponent(self):
        return self.TCP_match_socket_ghost.recv(1024).decode()
    

    def get_addr(self):
        if self.socket_type == "TCP":
            return self.TCP_socket.getsockname()
        elif self.socket_type == "UDP":
            return self.UDP_socket.getsockname()
        else:
            print("Erro: tipo de conexao invalido.")
            return None


    def connect(self):
        # Connects to the server
        # Returns if the connection was successful
        print("Conectando ao servidor...")
        self.TCP_socket.connect((self.server_host, self.server_port))
        payload = {"type": "connection start"}
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "connection start":
            if response["status"] == "ok":
                print("Conexao estabelecida com o servidor.")
                return True
            else:
                print("Erro de conexao com o servidor.")
                return False
        else:
            print("Erro: resposta invalida do servidor.")
            return False
        
    
    def connect_opponent(self, opponent_addr):
        # Connects to the opponent
        # Returns if the connection was successful
        print("Conectando ao oponente...")
        print(opponent_addr)
        self.TCP_match_socket_ghost.connect(opponent_addr)
        payload = {"type": "connection start"}
        payload = json.dumps(payload)
        self.ghost_send_opponent(payload)
        response, _ = self.ghost_receive_opponent()
        response = json.loads(response)
        if response["type"] == "connection start":
            if response["status"] == "ok":
                if response["accepted"] == "yes":
                    print("Conexao estabelecida com o oponente, lutem!")
                    return True
                elif response["accepted"] == "no":
                    print("Conexao recusada pelo oponente, amarelou!")
                    return False
            else:
                print("Erro de conexao com o oponente.")
                return False
        else:
            print("Erro: resposta invalida do oponente.")
            return False
        

    def unlogged_request(self):
        # Gets a valid unlogged command
        command_input = input()
        if command_input == "":
            return command_input
        command = command_input.split()
        command = command[0]
        if command not in self.log_options:
            if command in self.menu_options:
                print("Comando invalido! Logue em uma conta primeiro.")
            elif command in self.player_options:
                print("Comando invalido! Logue em uma conta e entre em uma partida primeiro.")
            else:
                print("Input invalido! Comando inexistente.")
            print("Comandos disponiveis: novo, entra, lideres, l, tchau")
        return command_input
    

    def menu_request(self):
        # Gets a valid menu command
        command_input = input()
        if command_input == "":
            return command_input
        command = command_input.split()
        command = command[0]
        if command not in self.menu_options:
            if command in self.log_options:
                print("Comando invalido! Deslogue de sua conta primeiro.")
            elif command in self.player_options:
                print("Comando invalido! Entre em uma partida primeiro.")
            else:
                print("Input invalido! Comando inexistente.")
            print("Comandos disponiveis: senha, lideres, l, inicia, desafio, sai, tchau")
        return command_input
    

    def game_request(self):
        # Gets a valid game command
        command_input = input()
        if command_input == "":
            return command_input
        command = command_input.split()
        command = command[0]
        if command not in self.player_options:
            if command in self.log_options:
                print("Comando invalido! Saia da partida e deslogue de sua conta primeiro.")
            elif command in self.menu_options:
                print("Comando invalido! Saia da partida primeiro.")
            else:
                print("Input invalido! Comando inexistente ou nao pode ser usado em partida.")
            print("Comandos disponiveis: move, atraso, encerra")
        return command_input
    

    def make_request(self):
        # Makes a request to the server
        # Returns if the client should keep running
        print("pacman> ", end="")

        match self.state:
            case "unlogged":
                request = self.unlogged_request()
                if request == "":
                    return True
                command = request.split()
                match command[0]:
                    case "novo":
                        if len(command) != 3:
                            print("Erro de comando. Use: novo <nome> <senha>")
                            return True
                        self.new_user_request(command[1], command[2])
                        return True
                    case "entra":
                        if len(command) != 3:
                            print("Erro de comando. Use: entra <nome> <senha>")
                            return True
                        self.login_request(command[1], command[2])
                        return True
                    case "lideres":
                        if len(command) != 1:
                            print("Erro de comando. Use: lideres")
                            return True
                        self.leaderboard_request()
                        return True
                    case "l":
                        if len(command) != 1:
                            print("Erro de comando. Use: l")
                            return True
                        self.logged_users_request()
                        return True
                    case "tchau":
                        if len(command) != 1:
                            print("Erro de comando. Use: tchau")
                            return True
                        self.disconnect_request()
                        return False
                    case default:
                        return True    # Wrong command
                
            case "menu":
                request = self.menu_request()
                if request == "":
                    return True
                command = request.split()
                match command[0]:
                    case "senha":
                        if len(command) != 3:
                            print("Erro de comando. Use: senha <senha antiga> <senha nova>")
                            return True
                        self.change_password_request(command[1], command[2])
                        return True
                    case "lideres":
                        if len(command) != 1:
                            print("Erro de comando. Use: lideres")
                            return True
                        self.leaderboard_request()
                        return True
                    case "l":
                        if len(command) != 1:
                            print("Erro de comando. Use: l")
                            return True
                        self.logged_users_request()
                        return True
                    case "inicia":
                        if len(command) != 1:
                            print("Erro de comando. Use: inicia")
                            return True
                        self.new_match_request()
                        return True
                    case "desafio":
                        if len(command) != 2:
                            print("Erro de comando. Use: desafio <nome do adversario>")
                            return True
                        self.challenge_request(command[1])
                        return True
                    case "sai":
                        if len(command) != 1:
                            print("Erro de comando. Use: sai")
                            return True
                        self.logout_request()
                        return True
                    case "tchau":
                        if len(command) != 1:
                            print("Erro de comando. Use: tchau")
                            return True
                        self.disconnect_request()
                        return False
                    case default:
                        return True    # Wrong command

            case "none":
                print("Erro: estado invalido.")
                return False
            
        return True

    
    def new_user_request(self, username, password):
        # Sends a new user request to the server
        # Returns if the user was created
        payload = {}
        payload["type"] = "new_user"
        payload["username"] = username
        payload["password"] = password
        payload["address"], payload["port"] = self.get_addr()
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "new_user":
            if response["status"] == "ok":
                print("Usuario '" + username + "' criado. Logue para entrar no jogo!")
                return True
            elif response["status"] == "fail":
                print("Nome de usuario ja existe!")
        else:
            print("Erro: resposta invalida do servidor.")
        return False
    
    
    def change_password_request(self, old_password, new_password):
        # Sends a change password request to the server
        # Returns if the password was changed
        payload = {}
        payload["type"] = "change_password"
        payload["username"] = self.username
        payload["old_password"] = old_password
        payload["new_password"] = new_password
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "change_password":
            if response["status"] == "ok":
                print("Senha alterada com sucesso!")
                return True
            elif response["status"] == "fail":
                if response["error"] == "wrong password":
                    print("Senha incorreta!")
                elif response["error"] == "user does not exist":
                    print("Usuario nao existe!")
                else:
                    print("Erro desconhecido!")
        else:
            print("Erro: resposta invalida do servidor.")
        return False
    

    def login_request(self, username, password):
        # Sends a login request to the server
        # Returns if the login was successful
        payload = {}
        payload["type"] = "login"
        payload["username"] = username
        payload["password"] = password
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "login":
            if response["status"] == "ok":
                self.state = "menu"
                self.username = username
                print("Logado com sucesso!")
                return True
            elif response["status"] == "fail":
                if response["error"] == "wrong password":
                    print("Usuario ou senha incorreta!")
                elif response["error"] == "already logged":
                    print("Usuario ja esta logado!")
                elif response["error"] == "user does not exist":
                    print("Usuario nao existe!")
                else:
                    print("Erro desconhecido!")
        else:
            print("Erro: resposta invalida do servidor.")
        return False
    

    def logout_request(self):
        # Sends a logout request to the server
        # Returns if the logout was successful
        payload = {}
        payload["type"] = "logout"
        payload["username"] = self.username
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "logout":
            if response["status"] == "ok":
                self.state = "unlogged"
                self.username = "none"
                print("Deslogado com sucesso!")
                return True
            elif response["status"] == "fail":
                print("Erro ao deslogar!")
        else:
            print("Erro: resposta invalida do servidor.")
        return False


    def disconnect_request(self):
        # Sends a disconnect request to the server
        # Returns if the disconnect was successful
        payload = {}
        payload["type"] = "disconnect"
        payload["username"] = self.username
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "disconnect":
            if response["status"] == "ok":
                print("Desconectado do servidor.")
                if self.socket_type == "TCP": self.TCP_socket.close()
                return True
            elif response["status"] == "fail":
                print("Erro ao desconectar!")
        else:
            print("Erro: resposta invalida do servidor.")
        return False
    

    def leaderboard_request(self):
        # Sends a leaderboard request to the server
        # Returns if the request was successful
        payload = {}
        payload["type"] = "leaderboard"
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "leaderboard":
            print("Lideres:")
            print(response["leaderboard"])
            return True
        else:
            print("Erro: resposta invalida do servidor.")
        return False
    

    def logged_users_request(self):
        # Sends a logged users request to the server
        # Returns if the request was successful
        payload = {}
        payload["type"] = "logged_users"
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "logged_users":
            print("Usuarios logados:")
            print(response["logged_users"])
            return True
        else:
            print("Erro: resposta invalida do servidor.")
        return False
    

    def new_match_request(self):
        # Sends a new match request to the server and plays the match
        payload = {}
        payload["type"] = "new_match"
        payload["username"] = self.username
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "new_match":
            if response["status"] == "ok":
                self.state = "in_game"
                self.match = pac.game(self.default_game_map, self.default_pacman_pos, self.default_Lghost_pos)
                self.TCP_match_socket_player = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.TCP_match_socket_player.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                self.TCP_match_socket_player.bind(("localhost", 0))
                self.TCP_match_socket_player.listen(1)
                self.close_thread = False
                thread = threading.Thread(target=self.Tlisten_opponent)
                thread.start()
                score = self.play_match()
                payload = {}
                payload["type"] = "match_over"
                payload["username"] = self.username
                payload["score"] = score
                payload = json.dumps(payload)
                self.send(payload)
                response, _ = self.receive()
                response = json.loads(response)
                if response["type"] == "match_over":
                    if response["status"] == "ok":
                        print("Partida encerrada!")
                        self.state = "menu"
                        self.match = None
                        return True
                    elif response["status"] == "fail":
                        print("Erro ao encerrar partida!")
                else:
                    print("Erro: resposta invalida do servidor.")
                return True
            elif response["status"] == "fail":
                print("Erro ao iniciar partida!")
        else:
            print("Erro: resposta invalida do servidor.")
        return False
    

    def Tlisten_opponent(self):
        # Listens for opponent until one joins
        print("Esperando oponente...")
        print("IP: " + str(self.get_addr()))
        while not self.close_thread:
            self.opponent_socket, self.opponent_addr = self.TCP_match_socket_player.accept()
            if self.opponent_socket != None:
                break
        print("Oponente encontrado!")
        if self.close_thread:
            self.opponent_socket.close()
            self.opponent_socket = None
            return
        payload = {}
        payload["type"] = "connection start"
        payload["accepted"] = "yes"
        payload = json.dumps(payload)
        self.player_send_opponent(payload)
        response = self.player_receive_opponent()
        response = json.loads(response)
        self.match.set_remote_ghost(response["Lghost_pos"])
    

    def play_match(self):
        # Starts a match
        # Returns the score
        print("Partida iniciada!")
        while True:
            # Draws the game
            if self.match.game_step() == False: break

            # Moves the local ghost
            self.match.local_ghost.rand_ghostmove(self.match)
            sleep(1)

            # Draws the game
            if self.match.game_step() == False: break

            # Gets the opponent input and performs the command
            if self.opponent_socket != None:
                response, _ = self.player_receive_opponent()
                response = json.loads(response)
                if response["type"] == "move":
                    self.match.local_ghost.set_position(response["Lghost_pos"][0], response["Lghost_pos"][1])
                    self.match.pacman.pacmove(response["direction"], self.match)
                elif response["type"] == "latency":
                    self.latency()
                elif response["type"] == "leaving match":
                    self.opponent_socket.close()
                    self.opponent_socket = None
                    self.match.remove_remote_ghost()
            sleep(1)

            # Gets the player input and performs the command
            command = self.game_request()
            stop = False
            while command.split()[0] != "move":
                if command.split()[0] == "atraso":
                    self.latency_request()
                elif command.split()[0] == "encerra":
                    stop = True
                    break
                command = self.game_request()
            if stop: break
            self.match.pacman.pacmove(command, self.match)
            if self.opponent_socket != None:
                payload = {}
                payload["type"] = "move"
                payload["direction"] = command.split()[1]
                payload["Lghost_pos"] = self.match.local_ghost.get_position()
                payload = json.dumps(payload)
                self.player_send_opponent(payload)
        self.state = "menu"
        self.close_thread = True
        score = self.match.pacman.score
        self.match = None
        if self.opponent_socket != None:
            payload = {}
            payload["type"] = "match_over"
            self.player_send_opponent(json.dumps(payload))
            self.opponent_socket.close()
        return score
    

    def latency_request(self):
        print("latencia: au au !")


    def challenge_request(self, opponent):
        # Sends a challenge request to the server
        # Returns if the challenge was successful
        self.TCP_match_socket_ghost = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        payload = {}
        payload["type"] = "challenge"
        payload["username"] = self.username
        payload["challenged_user"] = opponent
        payload = json.dumps(payload)
        self.send(payload)
        response, _ = self.receive()
        response = json.loads(response)
        if response["type"] == "challenge":
            if response["status"] == "ok":
                oponent_addr = (response["address"], response["port"])
                if self.connect_opponent(oponent_addr):
                    self.state = "in_game"
                    self.match = pac.game(response["game_map"], response["pacman_pos"], response["Lghost_pos"])
                    score = self.play_match_opponent()
                    score = self.default_total_pacdots - score
                    return True
                else:
                    return False
            elif response["status"] == "fail":
                if response["error"] == "user does not exist":
                    print("Usuario nao existe!")
                elif response["error"] == "not in game":
                    print("Usuario nao esta em partida!")
                else:
                    print("Erro desconhecido!")
        else:
            print("Erro: resposta invalida do servidor.")
        return False
        

    def play_match_opponent(self):
        # Starts a match
        # Returns the score
        print("Partida iniciada!")
        stop = False
        while True:
            # Draws the game
            if self.match.game_step() == False: break

            # Gets the player input and performs the command
            command = self.game_request()
            while command.split()[0] != "move":
                if command.split()[0] == "atraso":
                    self.latency_request
                elif command.split()[0] == "encerra":
                    stop = True
                    break
                command = self.game_request()
            if stop: break

            # Gets the opponent input and performs the command
            payload = self.ghost_receive_opponent()
            payload = json.loads(payload)
            if payload["type"] == "move":
                self.match.local_ghost.set_position(payload["Lghost_pos"][0], payload["Lghost_pos"][1])
                self.match.pacman.pacmove(payload["direction"], self.match)
            elif payload["type"] == "latency":
                self.latency()
            elif payload["type"] == "match_over":
                break
        if stop:
            payload = {}
            payload["type"] = "leaving match"
            self.ghost_send_opponent(json.dumps(payload))
            self.state = "menu"
            score = self.match.pacman.score
            self.match = None
            return score
        else:
            print("Partida encerrada pelo oponente!")
            self.state = "menu"
            score = self.match.pacman.score
            self.match = None
            return score




if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Erro: numero de argumentos invalido.")
        print("Use: python3 client.py <IP> <porta> <tipo de conexao (TCP ou UDP)>")
        sys.exit(1)

    server_host = sys.argv[1]
    server_port = int(sys.argv[2])
    connecion_type = sys.argv[3]
    
    c = client(server_host, server_port, connecion_type)
    if connecion_type == "TCP":
        c.connect()

    while True:
        if not c.make_request():
            break


