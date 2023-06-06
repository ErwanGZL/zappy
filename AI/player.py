from enum import Enum

class Position():
    def __init__(self, x : int, y : int):
        self.x = x
        self.y = y
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
    def set_pos(self, x : int, y : int):
        self.x = x
        self.y = y
    def go_up(self):
        if self.y == 0:
            self.y = self.map_y - 1
        self.y -= 1

class Ressouces(Enum):
    FOOD = 1
    LINEMATE = 2
    DERAUMERE = 3
    SIBUR = 4
    MENDIANE = 5
    PHIRAS = 6
    THYSTAME = 7

class Inventory:
    def __init__(self):
        self.food = 10
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0
    def add_ressource(self, ressource : Ressouces, amount : int):
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
    def remove_ressource(self, ressource : Ressouces, amount : int):
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
    def get_ressource(self, ressource : Ressouces):
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
##class player:

class Player:
    level : int = 1
    inventory : Inventory = None
    def __init__(self):
        self.level = 1
        self.inventory = Inventory()
    def look(self):
        pass
    def broadcast(self):
        pass
    def elevation(self):
        pass
    def fork(self):
        pass
    def left(self):
        pass
    def right(self):
        pass
    def forward(self):
        pass

for_level = [
#nb player, linemate, deraumere, sibur, mendiane, phiras, thystame
    [1, 1, 0, 0, 0, 0, 0],
    [2, 1, 1, 1, 0, 0, 0],
    [2, 2, 0, 1, 0, 2, 0],
    [4, 1, 1, 2, 0, 1, 0],
    [4, 1, 2, 1, 3, 0, 0],
    [6, 1, 2, 3, 0, 1, 0],
    [6, 2, 2, 2, 2, 2, 1],
]
