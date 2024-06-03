from . import DroneHelper as h

class Drone:
    def __init__(self, x_position: int, y_position: int, team: str) -> None:
        self.life: int = 10
        self.team:str = team
        self.elevation: int = 1
        self.x_position: int = x_position
        self.y_position: int = y_position
        self.view: list[str] = []

        # self.frozen: bool = False

    def run(socket_cl):
        running = True

        if socket_cl is None:
            running = False
            return

        while running:
            try:
                data = socket_cl.recv(1024).decode()
                if not data:
                    break
                print(f"Received: {data}")
            except Exception as e:
                print(f"-- Error: {e}")
                running = False
                break

        print("-- Connection closed")
        socket_cl.close()