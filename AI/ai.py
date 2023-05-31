import AI.netctl
import sys


class AI():
    def __init__(self, server_port, server_addr='localhost') -> None:
        self.netctl = AI.netctl.NetCTL()
        self.netctl.connect(server_addr, server_port)
        self.netctl.recv(1024)

