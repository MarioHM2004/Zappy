##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Algorithm_v3.py
##
import random

import app.const as const
import app.modules.Drone.Algorithm_v3.AlgorithmV3Helper as ah
import app.modules.Drone.Inventory.Inventory as inv


def wants_to_elevate(payload: const.AlgoPayload) -> bool:
    """
    Check if the drone wants to elevate.

    Args:
        payload (const.AlgoPayload): Payload to be used to check if the drone wants to elevate.

    Returns:
        bool: True if the drone wants to elevate, False otherwise.
    """
    value: bool = False
    elevation: int = payload.get("elevation")
    sinventory: inv.Inventory = payload.get("sinventory")
    connect_nbr: int = payload.get("connect_nbr")
    linemate: int = sinventory.getInventory("linemate")
    deraumere: int = sinventory.getInventory("deraumere")
    sibur: int = sinventory.getInventory("sibur")
    mendiane: int = sinventory.getInventory("mendiane")
    phiras: int = sinventory.getInventory("phiras")
    thystame: int = sinventory.getInventory("thystame")

    match elevation:
        # No case '1' cuz no additional users needed
        case 2:
            if connect_nbr > 1 and linemate > 0 and deraumere > 0 and sibur > 0:
                value = True
        case 3:
            if connect_nbr > 1 and linemate > 1 and sibur > 0 and phiras > 1:
                value = True
        case 4:
            if connect_nbr > 3 and linemate > 0 and deraumere > 0 and sibur > 1 and phiras > 0:
                value = True
        case 5:
            if connect_nbr > 3 and linemate > 0 and deraumere > 1 and sibur > 0 and mendiane > 2:
                value = True
        case 6:
            if connect_nbr > 5 and linemate > 0 and deraumere > 1 and sibur > 2 and phiras > 0:
                value = True
        case 7:
            if (
                connect_nbr > 5
                and linemate > 1
                and deraumere > 1
                and sibur > 2
                and mendiane > 1
                and phiras > 1
                and thystame > 0
            ):
                value = True
        case _:
            pass
    return value


class Algorithm:
    def __init__(self) -> None:
        self.move: ah.MoveDecision = ah.MoveDecision(
            life_weight_mult=0.0,
            elevation_weight_mult=1.2,
            view_food_weight_mult=0.0,
            view_mineral_weight_mult=1.2,
            view_player_weight_mult=1.5,
        )
        self.look: ah.LookDecision = ah.LookDecision(
            life_weight_mult=0.1,
            elevation_weight_mult=0.8,
            view_food_weight_mult=0.9,
            view_mineral_weight_mult=0.9,
            view_player_weight_mult=0.9,
        )
        self.inventory: ah.InventoryDecision = ah.InventoryDecision(
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=1,
        )
        self.broadcast: ah.BroadcastDecision = ah.BroadcastDecision(
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=1,
        )
        self.connect_nbr: ah.ConnectNbrDecision = ah.ConnectNbrDecision(
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=1,
        )
        self.fork: ah.ForkDecision = ah.ForkDecision(
            life_weight_mult=0.1,
            elevation_weight_mult=0.1,
            view_food_weight_mult=0.1,
            view_mineral_weight_mult=0.1,
            view_player_weight_mult=0.1,
        )
        self.eject: ah.EjectDecision = ah.EjectDecision(
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=1,
        )
        self.take: ah.TakeDecision = ah.TakeDecision(
            life_weight_mult=1.5,
            elevation_weight_mult=1.5,
            view_food_weight_mult=0.3,
            view_mineral_weight_mult=1.9,
            view_player_weight_mult=1,
        )
        self.set: ah.SetDecision = ah.SetDecision(
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=1,
        )
        self.incantation: ah.IncantationDecision = ah.IncantationDecision(
            life_weight_mult=1.1,
            elevation_weight_mult=1.1,
            view_food_weight_mult=1.1,
            view_mineral_weight_mult=1.1,
            view_player_weight_mult=1.1,
        )

    def __calculate_scores(self, payload: const.AlgoPayload) -> dict[str, float]:
        """
        Calculate the scores of each decision based on the payload.

        Args:
            payload (const.AlgoPayload): Payload to be used to calculate the scores.

        Returns:
            dict[str, float]: Dictionary with the name and scores of each decision.
        """
        scores: dict[str, float] = {}
        decisions: list[ah.Decision] = [
            self.move,
            self.look,
            self.inventory,
            self.broadcast,
            self.connect_nbr,
            self.fork,
            self.eject,
            self.take,
            self.set,
            self.incantation,
        ]

        scores = {
            str(decision): decision.compute_weight(payload=payload, last_decision=payload.get("last_cmd"))
            for decision in decisions
        }
        print(f"[SCORES]: {scores}")
        return scores

    def __get_max_score(self, scores: dict[str, float]) -> str:
        max_key = max(scores, key=scores.get)
        max_value = scores[max_key]

        max_keys = [key for key, value in scores.items() if value == max_value]

        return random.choice(max_keys)

    def choose_decision(self, payload: const.AlgoPayload) -> str:
        """
        Choose the best decision to take based on the payload.

        Args:
            payload (const.AlgoPayload): Payload to be used to take a decision.

        Returns:
            str: The decision to take.
        """
        scores: dict[str, float] = {}

        if payload.get("frozen") is True:
            return "ko"
        scores = self.__calculate_scores(payload)
        decision: str = self.__get_max_score(scores=scores)
        match decision.strip():
            case "take" | "set" | "eject":
                scores.pop(decision)
                decision = self.__get_max_score(scores=scores)

        # print(f"[NEXT_CMDS]: {self.broadcast.next_cmds}")
        return decision

    def display_payload(self, payload: const.AlgoPayload) -> None:
        print(
            f"PAYLOAD: life={payload.get('life')}, team={payload.get('team')}, elevation={payload.get('elevation')}, view={payload.get('view')}, frozen={payload.get('frozen')}, x_position={payload.get('x_position')}, y_position={payload.get('y_position')}, orientation={payload.get('orientation')}, connect_nbr={payload.get('connect_nbr')},"
        )
        print(f"inventory=[{payload.get('inventory')}]")
