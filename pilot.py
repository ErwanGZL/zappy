#!/bin/python3

import sys
import socket
import threading
import curses
import curses.ascii
import time


class Tile:
    def __init__(self, content: list) -> None:
        self.food = 0
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0
        self.players = 0

        for item in content:
            if item == "food":
                self.food += 1
            elif item == "linemate":
                self.linemate += 1
            elif item == "deraumere":
                self.deraumere += 1
            elif item == "sibur":
                self.sibur += 1
            elif item == "mendiane":
                self.mendiane += 1
            elif item == "phiras":
                self.phiras += 1
            elif item == "thystame":
                self.thystame += 1
            elif item == "player":
                self.players += 1

    def empty(self) -> bool:
        return (
            self.food == 0
            and self.linemate == 0
            and self.deraumere == 0
            and self.sibur == 0
            and self.mendiane == 0
            and self.phiras == 0
            and self.thystame == 0
            and self.players == 0
        )

    def __repr__(self) -> str:
        if self.empty():
            return "·"
        return "X"


class Look:
    def __init__(self, content: str) -> None:
        self.tiles = []
        for tile in content[1:-1].split(","):
            self.tiles.append(Tile(tile.split(" ")))

    def lv4(self) -> str:
        if len(self.tiles) == 16:
            return f"{self.tiles[9]}{self.tiles[10]}{self.tiles[11]}{self.tiles[12]}{self.tiles[13]}{self.tiles[14]}{self.tiles[15]}"
        else:
            return f"       "

    def lv3(self) -> str:
        if len(self.tiles) >= 9:
            return f" {self.tiles[4]}{self.tiles[5]}{self.tiles[6]}{self.tiles[7]}{self.tiles[8]} "
        else:
            return f"       "

    def lv2(self) -> str:
        if len(self.tiles) >= 4:
            return f"  {self.tiles[1]}{self.tiles[2]}{self.tiles[3]}  "
        else:
            return f"       "

    def lv1(self) -> str:
        if len(self.tiles) >= 1:
            return f"   {self.tiles[0]}   "
        else:
            return f"       "

class ManualAI:
    def __init__(self, hostname: str, port: int) -> None:
        # Curses window
        self.scr = curses.initscr()

        self.scr.keypad(True)
        self.scr.nodelay(True)
        curses.noecho()
        curses.curs_set(0)
        curses.start_color()
        curses.use_default_colors()
        curses.init_pair(1, curses.COLOR_RED, -1)
        curses.init_pair(2, curses.COLOR_GREEN, -1)
        curses.init_pair(3, curses.COLOR_YELLOW, -1)

        # AI Data
        self.team_name = "MANUAL"
        self.map_x = 0
        self.map_y = 0

        # Network Data
        self.servaddr = (hostname, port)
        self.ntw_thread = threading.Thread(target=self.task_ntw)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.slots_avl = 0

        # Shared Data: do not access directly unless you know what you are doing
        self.lock = threading.Lock()  # Lock for accessing the shared data
        self.connected = False  # Flag variable to check if connected to the server
        self.running = True  # Flag variable to stop the network thread
        self.buffer = ""  # Buffer for the received data
        self.msg_avl = threading.Event()  # Event to notify that a message is available

        # Start the network thread
        self.ntw_thread.start()

    def task_ntw(self):
        """
        This function is the task of the network thread.
        It connects to the server and receives data from the server.
        """
        self.scr.addstr(0, 0, f"connecting", curses.color_pair(3))
        # Connecting to the server
        with self.lock:
            try:
                self.socket.connect(self.servaddr)
            except ConnectionRefusedError:
                self.scr.addstr(
                    0, 0, f"connection refused", curses.color_pair(1))
                return

            r = self.socket.recv(1024)  # Receive the welcome message
            if r != b"WELCOME\n":
                self.scr.addstr(
                    0, 0, f"invalid welcome message", curses.color_pair(1))
                print(r)
                return

            # Sending the team name to the server
            # and receiving the map size and the number of slots available
            self.socket.send(f"{self.team_name}\n".encode())
            r = self.socket.recv(1024)
            self.slots_avl, self.map_x, self.map_y = [
                int(x) for x in r.split()]
            if self.slots_avl > 0:
                self.connected = True

        self.socket.settimeout(0.5)
        while self.running:
            try:
                data = self.socket.recv(1024)  # Receive data from the socket
                if not data:  # connection closed by the server
                    self.connected = False

                # Adding the received data to the buffer
                with self.lock:
                    self.buffer += data.decode()

                    if "\n" in self.buffer:
                        self.msg_avl.set()

            except socket.timeout:  # Timeout occurred, check the flag variable
                pass
        self.connected = False

    def get_next_message(self) -> str | None:
        """
        This function returns the next message from the buffer.
        """
        with self.lock:
            msg = self.buffer.split("\n", 1)[0]
            self.buffer = self.buffer[len(msg) + 1:]
            return msg

    def send_message(self, msg: str) -> None:
        """
        This function sends a message to the server.
        """
        self.socket.send(f"{msg}\n".encode())

    def get_nb_messages(self) -> int:
        """
        This function returns the number of messages in the buffer.
        """
        with self.lock:
            nb = len(self.buffer.split("\n")) - 1
        return nb

    def wait_for_message(self) -> str:
        """
        This function waits for a message to be available in the buffer.
        """
        self.msg_avl.wait()
        self.msg_avl.clear()
        return self.get_next_message()

    def __del__(self):
        """
        This function is the destructor of the AI class.
        It closes the network thread and the socket.
        """
        self.running = False
        self.connected = False
        if threading.current_thread() != self.ntw_thread:
            self.ntw_thread.join()
        self.socket.close()
        curses.endwin()

    def run(self) -> None:
        """
        This function is the main function of the AI.
        """
        # Check if the AI is connected to the server
        with self.lock:
            if not self.connected:
                self.scr.nodelay(False)
                self.scr.getch()
                return

        last_key = 0
        msg = ''
        broadcasting = False
        look = Look("")

        while self.connected:
            c = self.scr.getch()
            if c != -1:
                last_key = c

            self.scr.clear()

            self.scr.addstr(
                0, 0, f"host: {self.servaddr[0]}:{self.servaddr[1]}")
            self.scr.addstr(1, 0, f"status:")
            if self.connected:
                self.scr.addstr(1, 8, f"connected", curses.color_pair(2))
            else:
                self.scr.addstr(1, 8, f"disconnected", curses.color_pair(1))
            self.scr.addstr(2, 0, f"running:")
            if self.running:
                self.scr.addstr(2, 9, f"yes", curses.color_pair(2))
            else:
                self.scr.addstr(2, 9, f"no", curses.color_pair(1))
            self.scr.addstr(3, 0, f"slots available: {self.slots_avl}")
            self.scr.addstr(4, 0, f"map size: {self.map_x}x {self.map_y}y")
            self.scr.addstr(
                5, 0, f"messages in buffer: {self.get_nb_messages()}")
            self.scr.addstr(curses.LINES - 5, 0,
                            str(self.buffer.split()).center(curses.COLS, ' '))
            self.scr.addstr(2, curses.COLS - 10, look.lv4())
            self.scr.addstr(3, curses.COLS - 10, look.lv3())
            self.scr.addstr(4, curses.COLS - 10, look.lv2())
            self.scr.addstr(5, curses.COLS - 10, look.lv1())

            center_y = curses.LINES // 2
            center_x = curses.COLS // 2

            self.scr.addstr(center_y + 2, 0, ('"' + msg +
                            '"').center(curses.COLS, ' '))

            if broadcasting:
                if c == curses.ascii.NL:
                    self.send_message(f"Broadcast {msg}")
                    broadcasting = False
                    msg = ''

                elif c == curses.KEY_BACKSPACE:
                    msg = msg[:-1]
                elif c != -1:
                    msg += chr(c)
            else:
                if c == curses.ascii.ESC:
                    self.running = False
                elif c == curses.KEY_UP:
                    self.send_message("Forward")
                elif c == curses.KEY_RIGHT:
                    self.send_message("Right")
                elif c == curses.KEY_LEFT:
                    self.send_message("Left")
                elif c == ord('f'):
                    self.send_message("Fork")
                elif c == ord(' '):
                    self.send_message("Look")
                elif c == curses.ascii.NL:
                    broadcasting = True
                elif c == ord('+'):
                    m = self.get_next_message()
                    if m[0] == '[' and m[-1] == ']':
                        if r"\d+" in m:
                            pass
                        else:
                            look = Look(m)
                elif c == ord('i'):
                    self.send_message("Inventory")
                elif c == ord('e'):
                    self.send_message("Eject")
                elif c == ord('t'):
                    self.send_message("Take")
                elif c == ord('!'):
                    self.send_message("Incantation")
                elif c == ord('c'):
                    self.send_message("Connect_nbr")

            if last_key == curses.ascii.ESC:
                self.scr.addstr(
                    center_y, 0, f"ESCAPE".center(curses.COLS, ' '))
            elif last_key == curses.KEY_UP:
                self.scr.addstr(center_y, 0, f"UP".center(curses.COLS, ' '))
            elif last_key == curses.KEY_RIGHT:
                self.scr.addstr(center_y, 0, f"RIGHT".center(curses.COLS, ' '))
            elif last_key == curses.KEY_LEFT:
                self.scr.addstr(center_y, 0, f"LEFT".center(curses.COLS, ' '))
            elif last_key == ord(' '):
                self.scr.addstr(center_y, 0, f"SPACE".center(curses.COLS, ' '))
            elif last_key == curses.ascii.NL:
                self.scr.addstr(center_y, 0, f"ENTER".center(curses.COLS, ' '))
            elif last_key == curses.KEY_BACKSPACE:
                self.scr.addstr(
                    center_y, 0, f"BACKSPACE".center(curses.COLS, ' '))
            else:
                if last_key < 256 and last_key > 0:
                    self.scr.addstr(
                        center_y, 0, f"{chr(last_key)}".center(curses.COLS, ' '))
                else:
                    self.scr.addstr(
                        center_y, 0, f"{(last_key)}".center(curses.COLS, ' '))
            time.sleep(0.001)

        self.running = False


if __name__ == "__main__":
    try:
        args = []
        if len(sys.argv) == 3:
            args.append(sys.argv[1])
            args.append(int(sys.argv[2]))
        else:
            raise Exception(f"Usage: ./{sys.argv[0]} server_addr server_port")

        ManualAI(*args).run()

    except Exception as e:
        print(e)
        sys.exit(1)
