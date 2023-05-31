import socket


class NetCTL():
    def __init__(self, ip='localhost', port=0) -> None:
        self.address = (ip, port)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.bind(self.address)

    def __del__(self) -> None:
        self.socket.close()

    def connect(self, ip, port):
        self.socket.connect((ip, port))

    def send(self, data):
        self.socket.send(data)

    def recv(self, size) -> bytes:
        return self.socket.recv(size)
