import argparse
import socket
from typing import List

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
        self.client_id: int
        self.map_size: List[int] = []
        # self.frequency: int = frequency
        self.socket = None
        self.drone: d.Drone = None

    def parse_args(self, args):
        args = self.parser.parse_args(args)
        self.port = args.p
        self.host = args.h
        self.team = args.n
        self.drone = d.Drone(0, 0, self.team)

    def send_data(self, socket, data: str):
        to_send = f"{data}\n"
        socket.sendall(to_send.encode())

    def recv_data(self, socket) -> str:
        data = socket.recv(1024).decode()
        return data

    def start_socket(self, host: str, port: int, team_name: str) -> socket.socket:
        socket_cl = None

        try:
            socket_cl = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            socket_cl.connect((host, port))
            print(f"-- Connected to {host}:{port}")  ## DEBUG

            # Recieve Welcome from server
            data = self.recv_data(socket_cl)
            print(f"{data}")

            # Send team name
            self.send_data(socket_cl, team_name)

            # Recieve CLIENT-NUM
            data = self.recv_data(socket_cl)
            print(f"{data}")
            client_id = data.split()

            # Recieve MAP-SIZE: msz X Y
            data = self.recv_data(socket_cl)
            map = data.split()
            if len(map) != 3 and map[0] != "msz":
                print("-- Failed to connect to server: Invalid response")
                return None
            print(f"{map[1]} {map[2]}")

            self.client_id = int(client_id[0])
            self.map_size.extend([int(map[1]), int(map[2])])

            print(f"[TEST] Client ID: {self.client_id}")
            print(f"[TEST] Map Size: {self.map_size[0]}x{self.map_size[1]}")

        except Exception as e:
            print(f"-- Failed to connect to server: {host}:{port}, {e}")
        return socket_cl

    def close_socket(self, socket):
        print("-- Connection closed")
        socket.close()

    def start_ai(self):
        print(f"-- Starting AI for team {self.team} on {self.host}:{self.port}")
        self.socket = self.start_socket(self.host, self.port, self.team)

        self.loop()

    def loop(self):
        running = True

        if self.socket is None:
            running = False
            return

        while running is True:
            running = self.run()
        self.close_socket(self.socket)

    def run(self) -> bool:
        try:
            # cmd = take_decision TO DO
            # cmd = "forward"
            cmd = ""
            if cmd != "":
                self.drone.exec_cmd(cmd)
                self.send_data(self.socket, cmd)

            # Recieve data from server
            data = self.recv_data(self.socket)
            if data is None or len(data) == 0:
                return True
            print(f"[TEST] len: {len(data)}")
            return self.handle_data(data)

        except Exception as e:
            print(f"-- Error: {e}")
            return False
        return True

    def handle_data(self, data: str) -> bool:
        print(f"[TEST] Data: {data}")
        ret = True
        if data.startswith("dead"):
            ret = self.handle_pdi(data)
        return ret

    def handle_pdi(self, data):
        print("Player has died.")
        return False
