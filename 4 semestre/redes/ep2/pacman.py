import random


class character:
    col = 0
    line = 0
    sprite = "0"


    def __init__(self, line, col):
        self.line = line
        self.col = col


    def set_sprite(self, sprite):
        self.sprite = sprite


    def set_position(self, line, col):
        self.line = line
        self.col = col

    def get_position(self):
        return (self.line, self.col)


    def move(self, direction, game):
        # Moves the character in the direction, if possible
        # Returns True if the move was done, False otherwise
        line_now = self.line
        col_now = self.col
        
        match direction:   
            case "up":
                line_now -= 1
            case "down":
                line_now += 1
            case "left":
                col_now -= 1
            case "right":
                col_now += 1
        line_now = line_now % game.height
        col_now = col_now % game.width

        if game.game_map[line_now][col_now] == "*":
            return False
        else:
            self.line = line_now
            self.col = col_now
            return True




class pacman(character):
    score = 0

    def pacmove(self, direction, game):
        direction_dict = {"move w": "up", "move s": "down", "move a": "left", "move d": "right"}
        while direction not in direction_dict:
            print("direcao invalida, opcoes: move w, move s, move a, move d")
            direction = input()
        direction = direction_dict[direction]
        self.move(direction, game)
        if game.game_map[self.line][self.col] == ".":
            game.game_map[self.line][self.col] = " "
            game.pacdots_left -= 1
            self.score += 1




class Rghost(character):
    def get_rand_blank_spot(self, game):
        # Returns a random blank spot (space) in the map
        options = []
        for line in range(game.height):
            for col in range(game.width):
                if game.game_map[line][col] == " ":
                    options.append((line, col))
        return random.choice(options)


    def ghostmove(self, direction, game):
        direction_dict = {"move w": "up", "move s": "down", "move a": "left", "move d": "right"}
        while direction not in direction_dict:
            print("direcao invalida, opcoes: move w, move s, move a, move d")
            direction = input()
        direction = direction_dict[direction]
        self.move(direction, game)




class Lghost(character):
    # Local ghost
    direction = None
    reverse = {"up": "down", "down": "up", "left": "right", "right": "left"}

    def rand_ghostmove(self, game):
        # Moves the ghost in a straight line, and randomly changes direction on intersections
        options = []
        if game.game_map[(self.line-1)%game.height][self.col] != "*":
            options.append("up")
        if game.game_map[(self.line+1)%game.height][self.col] != "*":
            options.append("down")
        if game.game_map[self.line][(self.col-1)%game.width] != "*":
            options.append("left")
        if game.game_map[self.line][(self.col+1)%game.width] != "*":
            options.append("right")
        if self.direction!=None: options.remove(self.reverse[self.direction])
        self.direction = random.choice(options)
        self.move(self.direction, game)




class game:
    game_map = None
    pacdots_left = 0
    pacman = None
    local_ghost = None
    remote_ghost = None
    

    def __init__(self, game_map, pacman_pos, local_ghost_pos):
        self.height = len(game_map)
        self.width = len(game_map[0])
        self.game_map = [list(row) for row in game_map]  # instace copy of the map
        self.pacman = pacman(0, 0)
        self.local_ghost = Lghost(0, 0)

        for line in range(self.height):
            for col in range(self.width):
                if game_map[line][col] == ".":
                    self.pacdots_left += 1

        self.pacman.set_position(pacman_pos[0], pacman_pos[1])
        self.local_ghost.set_position(local_ghost_pos[0], local_ghost_pos[1])
        self.pacman.score = pacman.score
        self.pacman.set_sprite("C")
        self.local_ghost.set_sprite("F")


    def set_remote_ghost(self, remote_ghost_pos):
        self.remote_ghost = Rghost(remote_ghost_pos[0], remote_ghost_pos[1])
        self.remote_ghost.set_sprite("f")

    
    def remove_remote_ghost(self):
        self.remote_ghost = None

    
    def get_draw_map(self, state):
        # Returns a list of strings, each string is a line of the map
        draw_map_list = [list(line) for line in self.game_map]
        draw_map_list[self.pacman.line][self.pacman.col] = self.pacman.sprite
        draw_map_list[self.local_ghost.line][self.local_ghost.col] = self.local_ghost.sprite
        if self.remote_ghost != None:
            if self.remote_ghost.line == self.local_ghost.line and self.remote_ghost.col == self.local_ghost.col:
                draw_map_list[self.local_ghost.line][self.local_ghost.col] = "H"
            else: 
                draw_map_list[self.remote_ghost.line][self.remote_ghost.col] = self.remote_ghost.sprite
        match state:
            case "ongoing":
                pass
            case "lose":
                draw_map_list[self.pacman.line][self.pacman.col] = "X"
            case "win":
                draw_map_list[self.pacman.line][self.pacman.col] = self.pacman.sprite
        draw_map = ""
        for line in draw_map_list:
            draw_map += "".join(line) + "\n"
        return draw_map
         

    def _check_state(self):
        if self.pacman.line == self.local_ghost.line and self.pacman.col == self.local_ghost.col:
            return "lose"
        if self.remote_ghost != None:
            if self.pacman.line == self.remote_ghost.line and self.pacman.col == self.remote_ghost.col:
                return "lose"
        elif self.pacdots_left == 0:
            return "win"
        else:
            return "ongoing"
        

    def game_step(self):
        # In game step for eachstep in turn. Draws the map and checks for win/lose.
        # Returns if the game is still ongoing
        state = self._check_state()
        map = self.get_draw_map(state)
        print(map)
        print()
        if state == "ongoing":
            return True
        elif state == "lose":
            print("You lose! Score: ", self.pacman.score)
            return False
        else:
            print("You win! Score: ", self.pacman.score)
            return False