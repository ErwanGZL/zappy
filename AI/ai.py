import socket
import threading
from . import player
from time import sleep


class AI:
    def __init__(self, team_name, port, host="localhost") -> None:
        """
        This function is the constructor of the AI class.
        It initializes the AI and connects to the server.
        """
        self.player = None

        # AI Data
        self.team_name = team_name
        self.map_x = 0
        self.map_y = 0

        # Network Data
        self.servaddr = (host, port)
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
        # Connecting to the server
        with self.lock:
            try:
                self.socket.connect(self.servaddr)
            except ConnectionRefusedError:
                print("Error: Connection refused")
                self.lock.release()
                return

            r = self.socket.recv(1024)  # Receive the welcome message
            if r != b"WELCOME\n":
                print("Error: Invalid welcome message")
                print(r)
                return

            # Sending the team name to the server
            # and receiving the map size and the number of slots available
            self.socket.send(f"{self.team_name}\n".encode())
            r = self.socket.recv(1024)
            self.slots_avl, self.map_x, self.map_y = [int(x) for x in r.split()]
            #
            self.player = player.Player(
                self.team_name, self.servaddr[0], self.servaddr[1]
            )
            if self.slots_avl > 0:
                self.connected = True

        self.socket.settimeout(0.5)
        while self.running:
            try:
                data = self.socket.recv(1024)  # Receive data from the socket
                if not data:  # connection closed by the server
                    break

                # Adding the received data to the buffer
                with self.lock:
                    self.buffer += data.decode()

            except socket.timeout:  # Timeout occurred, check the flag variable
                if not self.running:
                    return
            with self.lock:
    
                if "\n" in self.buffer:
                    # print("____", self.buffer.count("\n"))
                    # for _ in range(self.buffer.count("\n")):
                    self.msg_avl.set()

    def get_next_message(self) -> str | None:
        """
        This function returns the next message from the buffer.
        """
        with self.lock:
            if "\n" not in self.buffer:
                return None
            msg = self.buffer.split("\n", 1)[0]
            self.buffer = self.buffer[len(msg) + 1 :]
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
        if threading.current_thread() != self.ntw_thread:
            self.ntw_thread.join()
        self.socket.close()

    def run(self) -> None:
        """
        This function is the main function of the AI.
        """
        # Check if the AI is connected to the server
        with self.lock:
            if not self.connected:
                return
            print(
                f"Connected to the server. Slots available: {self.slots_avl}, Map size: w={self.map_x}, h={self.map_y}"
            )

        recieved = []
        message = []
        send = []
        elevation = 0

        while self.running:
            # Wait for a message from the server
            i = 0
            while i < (min(len(send), 10)):
                if self.msg_avl.is_set():
                    str_recieved = self.wait_for_message()
                else:
                    tmp = self.get_next_message()
                    if tmp == None:
                        str_recieved = self.wait_for_message()
                    else:
                        str_recieved = tmp
                print(str_recieved)
                if str_recieved.split(" ")[0] == "message":
                    message.append(str_recieved.split("message ")[1])
                elif send[i].split("\n", 1)[0] == "Incantation" and elevation == 0:
                    recieved.append(send[i].split("\n", 1)[0] + "|" + str_recieved)
                    elevation += 1
                else:
                    elevation = 0
                    recieved.append(send[i].split("\n", 1)[0] + "|" + str_recieved)
                    i += 1

            if len(send) > 10:
                send = send[10:]
            else:
                send = []

            # Process the message
            if send == []:
                send = self.player.logic(recieved, message)
                recieved = []
                message = []

            for i in range(min(len(send), 10)):
                self.send_message(send[i])
                print("send:", "|", send[i], "|", sep="")
        pass
