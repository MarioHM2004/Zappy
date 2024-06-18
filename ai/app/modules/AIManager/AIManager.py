##
## EPITECH PROJECT, 2023
## zappy
## File description:
## AIManager.py
##
import argparse
import socket

import ai.app.modules.Drone.Drone as d
import ai.app.modules.Drone.DroneHelper as dh
import ai.app.const as const


class AIManager:
    # def __init__(self, frequency: int) -> None:
    def __init__(self) -> None:
        self.port: int
        self.host: str
        self.team: str
        self.client_id: int
        self.drone: d.Drone | None = None
        self.socket: socket.socket | None = None
        self.map_size: list[int] = []
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
        self.drone = d.Drone(self.team)

    def send_data(self, socket: socket.socket, data: str) -> None:
        to_send: str = f"{data}\n"
        socket.sendall(to_send.encode())

    def recv_data(self, socket: socket.socket) -> str:
        data: str = socket.recv(1024).decode()
        data = data.strip()
        return data

    def start_socket(self, host: str, port: int, team_name: str) -> socket.socket:
        data: str | None = None
        connect_nbr: str | None = None
        map: list[str] | None = None
        client_info: list[str] | None = None
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

            # Ignore ebo
            self.recv_data(socket=socket_cl)

            # Recieve CLIENT-NUM and MAP-SIZE: pnw #n X Y O L N msz X Y
            data = self.recv_data(socket=socket_cl)
            client_info = data.split()
            if len(client_info) != 10 or client_info[0] != "pnw" or client_info[7] != "msz":
                print("-- Failed to connect to server: Invalid response pnw")
                return None
            self.client_id = int(client_info[1])
            self.drone.x_position = int(client_info[2])
            self.drone.y_position = int(client_info[3])
            self.drone.orientation = int(client_info[4])
            self.drone.incantation_lvl = int(client_info[5])

            map = [int(client_info[8]), int(client_info[9])]

            # Connect nbr
            self.send_data(socket=socket_cl, data="connect_nbr")
            connect_nbr = self.recv_data(socket=socket_cl)

            print(f"{connect_nbr}")
            print(f"{map[0]} {map[1]}")

            self.drone.connect_nbr = int(connect_nbr)
            self.map_size.extend([int(map[0]), int(map[1])])


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
        aux: str = ""
        # payload: str = ""

        try:
            # cmd = self.drone.take_decision(payload=payload)
            cmd = self.drone.take_decision()

            print(f"[TEST] cmd: {cmd}")
            if cmd == "ko":
                return False

            # if eject, we need to check if egg is ejected
            if cmd == "eject":
                if self.execute_cmd(cmd=cmd) == "eject_failed":
                    print("[TEST] eject failed")
                    return True
                elif self.execute_cmd(cmd="inventory") == "ko":
                    return False
            elif cmd.startswith("take"):
                aux = self.execute_cmd(cmd=cmd)
                if aux == "take_failed":
                    print("[TEST] take failed")
                    return True
                if aux == "ko":
                    return False
                return True
            elif cmd.startswith("set"):
                aux = self.execute_cmd(cmd=cmd)
                if aux == "set_failed":
                    print("[TEST] set failed")
                    return True
                if aux == "ko":
                    return False
                return True
            elif self.execute_cmd(cmd=cmd) == "ko":
                return False

        except Exception as e:
            print(f"-- Error run: {e}")
            return False
        return True

    def handle_data(self, data: str) -> bool:
        print(f"[TEST] Data: {data}")
        if data.startswith("dead"):
            return self.handle_pdi(data=data)
        return True

    def handle_pdi(self, data: str) -> bool:
        print("Player has died.")
        return False

    def execute_cmd(self, cmd: str) -> str:
        s_data: str = ""

        self.send_data(socket=self.socket, data=cmd)
        s_data = self.recv_data(socket=self.socket)

        # check if is dead
        if self.handle_data(data=s_data) is False:
            return "ko"
        # check if cmd is valid
        if cmd == "eject" and s_data == "ko":
            return "eject_failed"
        if s_data == "suc":
            return "ko"
        if cmd.startswith("broadcast"):
            return "broadcast"
        if cmd.startswith("take"):
            if s_data == "ok":
                cmd = "take"
            else:
                return "take_failed"
        if cmd.startswith("set"):
            if s_data == "ok":
                cmd = "set"
            else:
                return "set_failed"
        # parse payload
        self.drone.parse_payload(cmd=cmd, payload=s_data)
        return const.CMD_FUNC[cmd](self.drone, "")
