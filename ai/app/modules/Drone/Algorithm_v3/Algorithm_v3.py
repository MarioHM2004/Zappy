##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Algorithm_v3.py
##
from typing import List

import app.const as const
import app.modules.Drone.Inventory.Inventory as inv
import app.modules.Drone.Algorithm_v3.AlgorithmV3Helper as ah

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
    linemate: int = sinventory.get_item("linemate")
    deraumere: int = sinventory.get_item("deraumere")
    sibur: int = sinventory.get_item("sibur")
    mendiane: int = sinventory.get_item("mendiane")
    phiras: int = sinventory.get_item("phiras")
    thystame: int = sinventory.get_item("thystame")

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
            life_weight_mult=1.5,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=2,
        )
        self.look: ah.LookDecision = ah.LookDecision(
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=1,
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
            life_weight_mult=0.2,
            elevation_weight_mult=0.2,
            view_food_weight_mult=0.2,
            view_mineral_weight_mult=0.2,
            view_player_weight_mult=0.2,
        )
        self.eject: ah.EjectDecision = ah.EjectDecision(
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=1,
        )
        self.take: ah.TakeDecision = ah.TakeDecision(
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1.5,
            view_mineral_weight_mult=1,
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
            life_weight_mult=1,
            elevation_weight_mult=1,
            view_food_weight_mult=1,
            view_mineral_weight_mult=1,
            view_player_weight_mult=1,
        )
        self.objective: list[str] = []

    def __reset_scores(self, scores: dict[str, float]) -> dict[str, float]:
        """
        Reset the scores of each decision.

        Args:
            scores (dict[str, float]): Scores to be reset.

        Returns:
            dict[str, float]: Dictionary with the name and scores of each decision.
        """
        for key in scores:
            scores[key] = 0
        return scores

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
        return scores

    def choose_decision(self, payload: const.AlgoPayload) -> str:
        """
        Choose the best decision to take based on the payload.

        Args:
            payload (const.AlgoPayload): Payload to be used to take a decision.

        Returns:
            str: The decision to take.
        """
        print("HERE: choose_decision")
        if payload.get("frozen") is True:
            print("HERE: Drone is frozen")
            return "ko"
        scores = self.__calculate_scores(payload)
        decision: str = max(scores, key=scores.get)
        print("----self.move.next_cmds: ", self.broadcast.next_cmds)
        match decision.strip():
            case "take":
                scores.pop("take")
                decision = max(scores, key=scores.get)
            case "set":
                scores.pop("set")
                decision = max(scores, key=scores.get)
            case "eject":
                scores.pop("eject")
                decision = max(scores, key=scores.get)
                
        return decision

    def display_payload(self, payload: const.AlgoPayload) -> None:
        print(f"PAYLOAD: life={payload.get('life')}, team={payload.get('team')}, elevation={payload.get('elevation')}, view={payload.get('view')}, frozen={payload.get('frozen')}, x_position={payload.get('x_position')}, y_position={payload.get('y_position')}, orientation={payload.get('orientation')}, connect_nbr={payload.get('connect_nbr')},")
        print(f"inventory=[{payload.get('inventory')}]")
