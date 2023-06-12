from enum import Enum
from . import ai
from typing import Tuple
import subprocess


class Orientation(Enum):
    UP = 1
    RIGHT = 2
    DOWN = 3
    LEFT = 4


class Position:
    def __init__(self, x: int, y: int, map_x: int, map_y: int):
        self.x = x
        self.y = y
        self.map_x = map_x
        self.map_y = map_y

    def __str__(self):
        return "x: " + str(self.x) + " y: " + str(self.y)

    def __eq__(self, other):
        if isinstance(other, Position):
            return self.x == other.x and self.y == other.y
        else:
            return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def get_pos(self):
        return (self.x, self.y)

    def set_pos(self, x: int, y: int):
        self.x = x
        self.y = y

    def go_up(self):
        if self.y == 0:
            self.y = self.map_y - 1
        self.y -= 1

    def go_down(self):
        if self.y == self.map_y - 1:
            self.y = 0
        self.y += 1

    def go_left(self):
        if self.x == 0:
            self.x = self.map_x - 1
        self.x -= 1

    def go_right(self):
        if self.x == self.map_x - 1:
            self.x = 0
        self.x += 1


class Ressouces(Enum):
    FOOD = 0
    LINEMATE = 1
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6


for_level = [
    # nb player, linemate, deraumere, sibur, mendiane, phiras, thystame
    [1, 1, 0, 0, 0, 0, 0],
    [2, 1, 1, 1, 0, 0, 0],
    [2, 2, 0, 1, 0, 2, 0],
    [4, 1, 1, 2, 0, 1, 0],
    [4, 1, 2, 1, 3, 0, 0],
    [6, 1, 2, 3, 0, 1, 0],
    [6, 2, 2, 2, 2, 2, 1],
]


class Inventory:
    def __init__(self):
        self.food = 10
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0

    def add_ressource(self, ressource: Ressouces, amount: int):
        if ressource == Ressouces.FOOD:
            self.food += amount
        elif ressource == Ressouces.LINEMATE:
            self.linemate += amount
        elif ressource == Ressouces.DERAUMERE:
            self.deraumere += amount
        elif ressource == Ressouces.SIBUR:
            self.sibur += amount
        elif ressource == Ressouces.MENDIANE:
            self.mendiane += amount
        elif ressource == Ressouces.PHIRAS:
            self.phiras += amount
        elif ressource == Ressouces.THYSTAME:
            self.thystame += amount
        else:
            raise Exception("Invalid ressource")

    def remove_ressource(self, ressource: Ressouces, amount: int):
        if ressource == Ressouces.FOOD:
            if self.food < amount:
                raise Exception("Not enough food")
            self.food -= amount
        elif ressource == Ressouces.LINEMATE:
            if self.linemate < amount:
                raise Exception("Not enough linemate")
            self.linemate -= amount
        elif ressource == Ressouces.DERAUMERE:
            if self.deraumere < amount:
                raise Exception("Not enough deraumere")
            self.deraumere -= amount
        elif ressource == Ressouces.SIBUR:
            if self.sibur < amount:
                raise Exception("Not enough sibur")
            self.sibur -= amount
        elif ressource == Ressouces.MENDIANE:
            if self.mendiane < amount:
                raise Exception("Not enough mendiane")
            self.mendiane -= amount
        elif ressource == Ressouces.PHIRAS:
            if self.phiras < amount:
                raise Exception("Not enough phiras")
            self.phiras -= amount
        elif ressource == Ressouces.THYSTAME:
            if self.thystame < amount:
                raise Exception("Not enough thystame")
            self.thystame -= amount
        else:
            raise Exception("Invalid ressource")

    def get_ressource(self, ressource: Ressouces):
        if ressource == Ressouces.FOOD:
            return self.food
        elif ressource == Ressouces.LINEMATE:
            return self.linemate
        elif ressource == Ressouces.DERAUMERE:
            return self.deraumere
        elif ressource == Ressouces.SIBUR:
            return self.sibur
        elif ressource == Ressouces.MENDIANE:
            return self.mendiane
        elif ressource == Ressouces.PHIRAS:
            return self.phiras
        elif ressource == Ressouces.THYSTAME:
            return self.thystame
        else:
            raise Exception("Invalid ressource")

    def print_inventory(self):
        print("food: " + str(self.food))
        print("linemate: " + str(self.linemate))
        print("deraumere: " + str(self.deraumere))
        print("sibur: " + str(self.sibur))
        print("mendiane: " + str(self.mendiane))
        print("phiras: " + str(self.phiras))
        print("thystame: " + str(self.thystame))

    def set_ressource(self, item, amount):
        if item == "food":
            self.food = amount
        elif item == "linemate":
            self.linemate = amount
        elif item == "deraumere":
            self.deraumere = amount
        elif item == "sibur":
            self.sibur = amount
        elif item == "mendiane":
            self.mendiane = amount
        elif item == "phiras":
            self.phiras = amount
        elif item == "thystame":
            self.thystame = amount


##class player:


class Player:
    def __init__(self, x, y):
        self.level = 1
        self.inventory = Inventory()
        self.orientation = Orientation.UP
        self.slot = 0
        self.player_conected = 6
        self.command = []
        self.look_content = []
        self.map = [[0 for i in range(x)] for j in range(y)]
        self.pos = Position(0, 0, x, y)

    def add_memory_up(self, content: list):
        lvl = 1
        while lvl <= self.level:
            for i in range(self.pos.x - lvl, self.pos.x + lvl + 1):
                if content[0] == "":
                    content.pop(0)
                    continue
                i = i % self.map_x
                if i < 0:
                    i = self.map_x + i
                vis = self.pos.x - lvl
                vis = vis % self.map_x
                if vis < 0:
                    vis = self.map_x + vis
                if self.map[i][vis] == "":
                    self.map[i][vis] = content.pop(0)
                else:
                    " ".join([self.map[i][vis], content.pop(0)])
            lvl += 1

    def add_memory_down(self, content: list):
        lvl = 1
        while lvl <= self.level:
            for i in range(self.pos.x + lvl, self.pos.x - lvl - 1, -1):
                if content[0] == "":
                    content.pop(0)
                    continue
                i = i % self.map_x
                if i < 0:
                    i = self.map_x + i
                vis = self.pos.x + lvl
                vis = vis % self.map_x
                if vis < 0:
                    vis = self.map_x + vis
                if self.map[i][vis] == "":
                    self.map[i][vis] = content.pop(0)
                else:
                    " ".join([self.map[i][vis], content.pop(0)])
            lvl += 1

    def add_memory_left(self, content: list):
        lvl = 1
        while lvl <= self.level:
            for i in range(self.pos.y - lvl, self.pos.y + lvl + 1):
                if content[0] == "":
                    content.pop(0)
                    continue
                i = i % self.map_y
                if i < 0:
                    i = self.map_y + i
                vis = self.pos.y - lvl
                vis = vis % self.map_y
                if vis < 0:
                    vis = self.map_y + vis
                if self.map[i][vis] == "":
                    self.map[i][vis] = content.pop(0)
                else:
                    " ".join([self.map[i][vis], content.pop(0)])
            lvl += 1

    def add_memory_right(self, content: list):
        lvl = 1
        while lvl <= self.level:
            for i in range(self.pos.y + lvl, self.pos.y - lvl - 1, -1):
                if content[0] == "":
                    content.pop(0)
                    continue
                i = i % self.map_y
                if i < 0:
                    i = self.map_y + i
                vis = self.pos.y + lvl
                vis = vis % self.map_y
                if vis < 0:
                    vis = self.map_y + vis
                if self.map[i][vis] == "":
                    self.map[i][vis] = content.pop(0)
                else:
                    " ".join([self.map[i][vis], content.pop(0)])
            lvl += 1

    def add_memory(self, content: list):
        if self.orientation == Orientation.UP:
            self.add_memory_up(content)
        elif self.orientation == Orientation.DOWN:
            self.add_memory_down(content)
        elif self.orientation == Orientation.LEFT:
            self.add_memory_left(content)
        elif self.orientation == Orientation.RIGHT:
            self.add_memory_right(content)

    def look(self, content: str):
        content = content.split(",")
        content = self.add_memory(content)

    def broadcast(self):
        pass

    def elevation(self):
        pass

    def fork(self):
        pass

    def left(self):
        self.orientation = (self.orientation - 1) % 4
        pass

    def right(self):
        self.orientation = (self.orientation + 1) % 4
        pass

    def forward(self):
        if self.orientation == Orientation.UP:
            self.pos.go_up()
        elif self.orientation == Orientation.DOWN:
            self.pos.go_down()
        elif self.orientation == Orientation.LEFT:
            self.pos.go_left()
        elif self.orientation == Orientation.RIGHT:
            self.pos.go_right()
        pass

    def find_object(self, obj: Ressouces):
        # find the nearest object on the self.map

        pass

    def need_to_elevation(self) -> Ressouces:
        for i in Ressouces:
            if i == Ressouces.FOOD:
                continue
            if self.inventory.get_ressource(i) < for_level[self.level][i.value]:
                return i
        return None

    def go_to(self, obj: Tuple[int, int]):
        pass

    def update_inventory(self, content: str):
        content = content.split(",")
        result = []
        for item in content:
            parts = item.split(" ")
            name = parts[0]
            value = parts[1]
            result.append((name, value))
        for item in result:
            self.inventory.set_ressource(item[0], item[1])
        pass

    def command_interpreter(self, answer: list):
        for i in answer:
            command = i.split("|")
            if command[0] == "Connect_nbr":
                self.player_conected = int(command[1])
            elif command[0] == "Look":
                self.look_content = list(command[1])

    def logic(self, answer: list = []) -> list:
        self.command_interpreter(answer)
        self.command.append("Connect_nbr")
        if self.player_conected < 6:
            subprocess.call(
                [
                    "./zappy_ia",
                    "-p",
                    self.servaddr[1],
                    "-n",
                    self.team_name,
                    "-h",
                    self.servaddr[0],
                ]
            )
            return self.command
        pass
