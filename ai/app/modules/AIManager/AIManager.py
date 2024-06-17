##
## EPITECH PROJECT, 2023
## zappy
## File description:
## AIManager.py
##
import argparse
import socket

import ai.app.modules.Drone.Drone as d


class AIManager:
    # def __init__(self, frequency: int) -> None:
    def __init__(self) -> None:
        self.port: int
        self.host: str
        self.team: str
        self.client_id: int
        self.drone: d.Drone | None = None
        self.socket: socket.socket | None = None
        self.map_size: list[int] | None = None
        self.parser = argparse.ArgumentParser(add_help=False)
        self.parser.add_argument("-help", action="help", help="Show this help message and exit")
        self.parser.add_argument("-p", type=int, required=True, help="Port number")
        self.parser.add_argument("-n", type=str, required=True, help="Name of the team")
        self.parser.add_argument("-h", type=str, default="localhost", help="Name of the machine; localhost by default")
        # self.frequency: int = frequency

    def parse_args(self, args) -> None:
        args = self.parser.parse_args(args)
        self.port = args.p
        self.host = args.h
        self.team = args.n
        self.drone = d.Drone(0, 0, self.team)

    def send_data(self, socket: socket.socket, data: str) -> None:
        to_send: str = f"{data}\n"
        socket.sendall(to_send.encode())

    def recv_data(self, socket: socket.socket) -> str:
        data: str = socket.recv(1024).decode()
        return data

    def start_socket(self, host: str, port: int, team_name: str) -> socket.socket:
        data: str | None = None
        map: list[str] | None = None
        client_id: list[str] | None = None
        socket_cl: socket.socket | None = None

        try:
            socket_cl = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            socket_cl.connect((host, port))
            print(f"-- Connected to {host}:{port}")  ## DEBUG

            # Recieve Welcome from server
            data = self.recv_data(socket=socket_cl)
            print(f"{data}")

            # Send team name
            self.send_data(socket=socket_cl, data=team_name)

            # Recieve CLIENT-NUM
            data = self.recv_data(socket=socket_cl)
            print(f"{data}")
            client_id = data.split()

            # Recieve MAP-SIZE: msz X Y
            data = self.recv_data(socket=socket_cl)
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

    def close_socket(self, socket: socket.socket) -> None:
        print("-- Connection closed")
        socket.close()

    def start_ai(self) -> None:
        print(f"-- Starting AI for team {self.team} on {self.host}:{self.port}")

        self.socket = self.start_socket(host=self.host, port=self.port, team_name=self.team)
        self.loop()

    def loop(self) -> None:
        running: bool = True

        if self.socket is None:
            running = False
            return

        while running is True:
            running = self.run()
        self.close_socket(socket=self.socket)

    def run(self) -> bool:
        cmd: str = ""
        payload: str = ""
        data: str | None = None

        try:
            cmd = self.drone.take_decision(payload=payload)
            if cmd != "ko":
                self.send_data(socket=self.socket, cmd=cmd)

            # Recieve data from server
            data = self.recv_data(socket=self.socket)
            if data is None or len(data) == 0:
                return True
            print(f"[TEST] len: {len(data)}")

        except Exception as e:
            print(f"-- Error: {e}")
            return False
        return self.handle_data(data=data)

    def handle_data(self, data: str) -> bool:
        ret: bool = True

        print(f"[TEST] Data: {data}")
        if data.startswith("dead"):
            ret = self.handle_pdi(data=data)
        return ret

    def handle_pdi(self, data: str) -> bool:
        print("Player has died.")
        return False
