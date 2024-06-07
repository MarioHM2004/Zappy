import argparse
import socket

import ai.app.modules.Drone.Drone as d


class AIManager:
    # def __init__(self, frequency: int) -> None:
    def __init__(self):
        self.parser = argparse.ArgumentParser(add_help=False)
        self.parser.add_argument("-help", action="help", help="Show this help message and exit")
        self.parser.add_argument("-p", type=int, required=True, help="Port number")
        self.parser.add_argument("-n", type=str, required=True, help="Name of the team")
        self.parser.add_argument("-h", type=str, default="localhost", help="Name of the machine; localhost by default")
        self.port: int
        self.host: str
        self.team: str
        # self.frequency: int = frequency
        self.socket = None

    def parse_args(self, args):
        args = self.parser.parse_args(args)
        self.port = args.p
        self.host = args.h
        self.team = args.n
        self.start_ai()

    def start_socket(self, host: str, port: int, team_name: str) -> socket.socket:
        socket_cl = None

        try:
            socket_cl = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            socket_cl.connect((host, port))
            print(f"-- Connected to {host}:{port}")  ## DEBUG

            # Recieve Welcome from server
            print(f"{socket_cl.recv(1024).decode()}")

            # Send team name
            init_msg = f"{team_name}\n"
            socket_cl.sendall(init_msg.encode())

            # Recieve CLIENT-NUM + MAP: X Y
            print(f"{socket_cl.recv(1024).decode()}")

        except Exception as e:
            print(f"-- Failed to connect to server: {host}:{port}, {e}")
        return socket_cl

    def start_ai(self):
        print(f"-- Starting AI for team {self.team} on {self.host}:{self.port}")
        self.socket = self.start_socket(self.host, self.port, self.team)

        self.loop()

    def loop(self):
        running = True

        if self.socket is None:
            running = False
            return

        while running:
            self.run()
        print("-- Connection closed")
        self.socket.close()

    def run(self):
        try:
            data = self.socket.recv(1024).decode()
            if not data:
                return True
            print(f"Received: {data}")
        except Exception as e:
            print(f"-- Error: {e}")
            return False
        return True

