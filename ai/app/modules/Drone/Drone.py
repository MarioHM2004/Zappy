##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Drone.py
##
import app.const as const
import app.modules.Drone.Algorithm_v2.Algorithm_v2 as algo2
import app.modules.Drone.Algorithm_v3.Algorithm_v3 as algo3
import app.modules.Drone.Inventory.Inventory as inv


class Drone:
    def __init__(self, team: str, id: int) -> None:
        self.life: int = 10
        self.team: str = team
        self.incantation_lvl: int = 1
        self.view: list[str] = []
        self.frozen: bool = False
        self.x_position: int = 0
        self.y_position: int = 0
        self.orientation: int = 0
        self.connect_nbr: int = 0
        if id == 1:
            self.algo: algo2.Algorithm = algo2.Algorithm()
        elif id == 2:
            self.algo: algo3.Algorithm = algo3.Algorithm()
        self.inventory: inv.Inventory = inv.Inventory()
        self.last_cmd: str = ""

    def __build_algo_payload(self) -> const.AlgoPayload:
        """
        Builds the payload to be sent to the algorithm.

        Returns:
            const.AlgoPayload: Payload to be sent to the algorithm.
        """

        return {
            "life": self.life,
            "team": self.team,
            "elevation": self.incantation_lvl,
            "view": self.view,
            "frozen": self.frozen,
            "x_position": self.x_position,
            "y_position": self.y_position,
            "orientation": self.orientation,
            "connect_nbr": self.connect_nbr,
            "inventory": self.inventory,
            "last_cmd": self.last_cmd,
        }

    def parse_payload(self, cmd: str, payload: str) -> None:
        """
        Parses the payload to update the drone's internal variables.

        Args:
            payload (str): Information coming from the server.
        """

        if payload == "dead":
            self.life = 0
            return

        if payload == "suc" or payload == "ko" or payload == "ok":
            return

        try:
            if payload.startswith("elevation underway"):
                self.frozen = True
                return
            else:
                self.frozen = False
            match cmd:
                case "look":
                    self.view = payload.split(",")
                case "inventory":
                    self.inventory.update_inventory(payload)
                case "connect_nbr":
                    self.connect_nbr = int(payload)
                case "eject":
                    print(f"eject: {payload}")
                case "take":
                    self.inventory.add_item(payload, 1)
                    print(f"Inventory: {self.inventory}")
        except Exception as e:
            print(f"Error parsing payload: {e}")

    def take_decision(self) -> str:
        """
        Decides what action (command) to take.

        Returns:
            str: The action (command) taken by the drone.
        """

        # print(f"**info [Drone {self.team} at ({self.x_position}, {self.y_position} - orientation: {self.orientation}) with {self.life} life, {self.incantation_lvl} elevation, {self.connect_nbr} connect nbr and Inventory: {self.inventory}]\n")

        action: str | None = None

        action = self.algo.choose_decision(self.__build_algo_payload())

        if (
            action is None
            or action not in const.CMD_FUNC
            and action.startswith("broadcast") is False
            and action.startswith("take") is False
            and action.startswith("set") is False
        ):
            return "ko"
        if len(self.last_cmd) == 0:
            self.last_cmd = "look"
            return "look"
        self.last_cmd = action
        return action

    def __str__(self) -> str:
        return f"Drone {self.team} at ({self.x_position}, {self.y_position}) with {self.life} life, {self.incantation_lvl} elevation, {self.connect_nbr} connect number and Inventory: {self.inventory}"
