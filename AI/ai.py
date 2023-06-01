import socket
import threading


class AI():
    def __init__(self, team_name, port, host='localhost') -> None:
        """
        This function is the constructor of the AI class.
        It initializes the AI and connects to the server.
        """
        # AI Data
        self.team_name = team_name
        self.map_size: tuple[int, int] = (0, 0)

        # Network Data
        self.servaddr = (host, port)
        self.ntw_thread = threading.Thread(target=self.task_ntw)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.slots_avl = 0

        # Shared Data: do not access directly unless you know what you are doing
        self.lock = threading.Lock()    # Lock for accessing the shared data
        self.connected = False          # Flag variable to check if connected to the server
        self.running = True             # Flag variable to stop the network thread
        self.buffer = ""                # Buffer for the received data

        # Start the network thread
        self.ntw_thread.start()

    def task_ntw(self):
        """
        This function is the task of the network thread.
        It connects to the server and receives data from the server.
        """
        self.lock.acquire()

        # Connecting to the server
        try:
            self.socket.connect(self.servaddr)
        except ConnectionRefusedError:
            print("Error: Connection refused")
            return

        r = self.socket.recv(1024)  # Receive the welcome message
        if r != b"WELCOME\n":
            print("Error: Invalid welcome message")
            return

        # Sending the team name to the server
        # and receiving the map size and the number of slots available
        self.socket.send(f"{self.team_name}\n".encode())
        r = self.socket.recv(1024)
        self.slots_avl, self.map_size[0], self.map_size[1] = [
            int(x) for x in r.split("\n").split(" ")]

        if self.slots_avl > 0:
            self.connected = True
        print(
            f"Connected to the server. Slots available: {self.slots_avl}, Map size: w={self.map_size[0]}, h={self.map_size[1]}")
        self.lock.release()

        self.socket.settimeout(0.5)
        while self.running:
            try:
                data = self.socket.recv(1024)  # Receive data from the socket
                if not data:  # connection closed by the server
                    break

                # Adding the received data to the buffer
                self.buffer += data.decode()

            except socket.timeout:  # Timeout occurred, check the flag variable
                if not self.running:
                    break

    def __del__(self):
        """
        This function is the destructor of the AI class.
        It closes the network thread and the socket.
        """
        self.running = False
        self.ntw_thread.join()
        self.socket.close()

    def run(self):
        """
        This function is the main function of the AI.
        """
        # Check if the AI is connected to the server
        self.lock.acquire()  # wait for the connection handshake sequence to finish
        if not self.connected:
            return
        self.lock.release()

        # Client is now connected to the server
        # TODO: Implement the AI logic here  |
        #                                    v
        pass
