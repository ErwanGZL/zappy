import socket

class AI():
    def __init__(self, team_name, port, host='localhost') -> None:
        self.team_name = team_name
        self.servaddr = (host, port)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.pos_in_queue = 0
        self.map_size = (0, 0)
        self.conn_hanshake()

    def conn_hanshake(self):
        self.socket.connect(self.servaddr)
        r = self.socket.recv(1024)
        if r == b"WELCOME\n":
            print("Connection established")
        else:
            print("Connection failed")
        self.socket.send(self.team_name.encode())

    def run(self):
        pass
