import ai.app.const as const
import ai.app.modules.Drone.Inventory.Inventory as i

class Drone:
    def __init__(self, x_position: int, y_position: int, team: str) -> None:
        self.life: int = 10
        self.team: str = team
        self.elevation: int = 1
        self.x_position: int = x_position
        self.y_position: int = y_position
        self.inventory: i.Inventory | None = None
        self.view: list[str] = []

        # self.frozen: bool = False

    def exec_cmd(self, cmd: str) -> str:
        if cmd not in const.CMD_FUNC:
            return "ko"
        return const.CMD_FUNC[cmd]()

    def __str__(self) -> str:
        return f"Drone {self.team} at ({self.x_position}, {self.y_position}) with {self.life} life, {self.elevation} elevation and Inventory: {self.inventory}"