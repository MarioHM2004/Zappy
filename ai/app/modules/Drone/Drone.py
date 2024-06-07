class Drone:
    def __init__(self, x_position: int, y_position: int, team: str) -> None:
        self.life: int = 10
        self.team: str = team
        self.elevation: int = 1
        self.x_position: int = x_position
        self.y_position: int = y_position
        self.view: list[str] = []

        # self.frozen: bool = False
