##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Drone.py
##
import socket

import ai.app.const as const
import ai.app.modules.Drone.Algorithm.Algorithm as algo
import ai.app.modules.Drone.Inventory.Inventory as inv


class Drone:
    def __init__(self, team: str) -> None:
        self.life: int = 10
        self.team: str = team
        self.incantation_lvl: int = 1
        self.view: list[str] = []
        self.frozen: bool = False
        self.x_position: int = 0
        self.y_position: int = 0
        self.orientation: int = 0
        self.algo: algo.Algorithm = algo.Algorithm()
        self.inventory: inv.Inventory = inv.Inventory()

    # def __process_payload(self, payload: str) -> None:
    #     """
    #     Updates the drone's internal variables with the payload.

    #     Args:
    #         payload (str): Drone information coming from the server.
    #     """

    #     raise NotImplementedError

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
            "inventory": self.inventory,
        }

    def take_decision(self) -> str:
        """
        Decides what action (command) to take.

        Returns:
            str: The action (command) taken by the drone.
        """

        print(f"[TEST] Drone {self.team} at ({self.x_position}, {self.y_position}) with {self.life} life, {self.incantation_lvl} elevation and Inventory: {self.inventory}")

        action: str | None = None

        action = self.algo.choose_decision(self.__build_algo_payload())

        if action is None or action not in const.CMD_FUNC:
            return "ko"

        #! Most likely will change for a better implementation
        # if action.find("broadcast") != -1:
        #     return const.CMD_FUNC[action](self, action)
        # return const.CMD_FUNC[action](self, None)
        return action

    # def take_decision(self, payload: str) -> str:
    #     """
    #     Decides what action (command) to take based on the payload.

    #     Args:
    #         payload (str): Information coming from the server.

    #     Returns:
    #         str: The action (command) taken by the drone.
    #     """

    #     action: str | None = None


    #     # self.__process_payload(payload)  # Payload -> Internal Variables

    #     action = self.algo.choose_decision(self.__build_algo_payload())

    #     if action is None or action not in const.CMD_FUNC:
    #         return "ko"

    #     #! Most likely will change for a better implementation
    #     # if action.find("broadcast") != -1:
    #     #     return const.CMD_FUNC[action](self, action)
    #     # return const.CMD_FUNC[action](self, None)
    #     return action

    def __str__(self) -> str:
        return f"Drone {self.team} at ({self.x_position}, {self.y_position}) with {self.life} life, {self.incantation_lvl} elevation and Inventory: {self.inventory}"
