from . import AIManagerHelper as h

class AIManager:
    # def __init__(self, port: int, frequency: int, host: str) -> None:
    #     self.port: int = port
    #     self.host: str = host
    #     self.frequency: int = frequency
    #     self.socket = None

    def __init__(self):
        self.parser = h.argparse.ArgumentParser(add_help=False)
        self.parser.add_argument('-help', action='help', help='Show this help message and exit')
        self.parser.add_argument('-p', type=int, required=True, help='Port number')
        self.parser.add_argument('-n', type=str, required=True, help='Name of the team')
        self.parser.add_argument('-h', type=str, default='localhost', help='Name of the machine; localhost by default')

    def parse_args(self, args):
        args = self.parser.parse_args(args)
        self.start_ai(args)

    def start_socket(self, host: str, port: int, team_name: str) -> h.socket.socket:
        socket_cl = None

        try:
            socket_cl = h.socket.socket(h.socket.AF_INET, h.socket.SOCK_STREAM)
            socket_cl.connect((host, port))
            print(f"-- Connected to {host}:{port}") ## DEBUG

            # Recieve Welcome from server
            print(f"{socket_cl.recv(1024).decode()}")

            # Send team name
            init_msg = f"{team_name}\n"
            socket_cl.sendall(init_msg.encode())

            # Recieve CLIENT-NUM + MAP: X Y
            print(f"{socket_cl.recv(1024).decode()}")

        except Exception as e:
            print(f"-- Failed to connect to server: {host}:{port}")
        return socket_cl

    def start_ai(self, args):
        print(f"-- Starting AI for team {args.n} on {args.h}:{args.p}")
        socket_cl = self.start_socket(args.h, args.p, args.n)

        # h.run(socket_cl)
        h.Drone.run(socket_cl)

