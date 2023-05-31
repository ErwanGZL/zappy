from . import netctl
import sys


class AI():
    def __init__(self, team_name, server_port, server_addr='localhost') -> None:
        self.server_addr = (server_addr, server_port)
        self.netctl = netctl.NetCTL()
        self.conn_hanshake()

    def conn_hanshake(self):
        self.netctl.connect(self.server_addr[0], self.server_addr[1])
        if self.netctl.recv(1024) != b'WELCOME\n':
            raise Exception("Server didn't send WELCOME, received: " + self.netctl.recv(1024).decode())
        self.netctl.send(b'\n')

    def run(self):
        pass
