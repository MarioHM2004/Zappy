##
## EPITECH PROJECT, 2023
## zappy
## File description:
## AlgorithmHelper.py
##
from abc import ABC
from abc import abstractmethod
import random

import app.const as const
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
    inventory: inv.Inventory = payload.get("inventory")
    connect_nbr: int = payload.get("connect_nbr")
    linemate: int = inventory.getInventory("linemate")
    deraumere: int = inventory.getInventory("deraumere")
    sibur: int = inventory.getInventory("sibur")
    mendiane: int = inventory.getInventory("mendiane")
    phiras: int = inventory.getInventory("phiras")
    thystame: int = inventory.getInventory("thystame")

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


def needs_object(object:str, incantation: int, inventory: inv.Inventory) -> bool:
    needs: bool = False

    match incantation:
        case 1:
            if object == "linemate" and inventory.getInventory("linemate") < 1:
                needs = True
        case 2:
            if object == "linemate" and inventory.getInventory("linemate") < 1:
                needs = True
            elif object == "deraumere" and inventory.getInventory("deraumere") < 1:
                needs = True
            elif object == "sibur" and inventory.getInventory("sibur") < 1:
                needs = True
        case 3:
            if object == "linemate" and inventory.getInventory("linemate") < 2:
                needs = True
            if object == "phiras" and inventory.getInventory("phiras") < 2:
                needs = True
            if object == "sibur" and inventory.getInventory("sibur") < 1:
                needs = True
        case 4:
            if object == "linemate" and inventory.getInventory("linemate") < 1:
                needs = True
            if object == "deraumere" and inventory.getInventory("deraumere") < 1:
                needs = True
            if object == "phiras" and inventory.getInventory("phiras") < 1:
                needs = True
            if object == "sibur" and inventory.getInventory("sibur") < 2:
                needs = True
        case 5:
            if object == "linemate" and inventory.getInventory("linemate") < 1:
                needs = True
            if object == "deraumere" and inventory.getInventory("deraumere") < 2:
                needs = True
            if object == "sibur" and inventory.getInventory("sibur") < 1:
                needs = True
            if object == "mendiane" and inventory.getInventory("mendiane") < 3:
                needs = True
        case 6:
            if object == "linemate" and inventory.getInventory("linemate") < 1:
                needs = True
            if object == "deraumere" and inventory.getInventory("deraumere") < 2:
                needs = True
            if object == "sibur" and inventory.getInventory("sibur") < 3:
                needs = True
            if object == "phiras" and inventory.getInventory("phiras") < 1:
                needs = True
        case 7:
            if object == "linemate" and inventory.getInventory("linemate") < 2:
                needs = True
            if object == "deraumere" and inventory.getInventory("deraumere") < 2:
                needs = True
            if object == "sibur" and inventory.getInventory("sibur") < 2:
                needs = True
            if object == "mendiane" and inventory.getInventory("mendiane") < 2:
                needs = True
            if object == "phiras" and inventory.getInventory("phiras") < 2:
                needs = True
            if object == "thystame" and inventory.getInventory("thystame") < 1:
                needs = True
        case _:
            needs = False
        
    return needs

class Decision(ABC):
    iterator: int = 0
    broadcast_msg: str = ""
    set_items: bool = False
    wants_to_look: bool = False
    waiting_to_elevate: bool = False
    direction_vias: dict[str, float] = {"forward": 0, "right": 0, "left": 0}
    next_cmds: list[str] = []

    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        self._life_weight_mult: int = life_weight_mult
        self._elevation_weight_mult: int = elevation_weight_mult
        self._view_food_weight_mult: int = view_food_weight_mult
        self._view_mineral_weight_mult: int = view_mineral_weight_mult
        self._view_player_weight_mult: int = view_player_weight_mult

    @abstractmethod
    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        """
        Compute the view weight part of the decision.

        Args:
            payload (const.AlgoPayload): Payload to be used to compute the weight.

        Returns:
            float: The weight of the view part of the decision.
        """
        pass

    @abstractmethod
    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        """
        Compute the elevation weight part of the decision.

        Args:
            payload (const.AlgoPayload): Payload to be used to compute the weight.

        Returns:
            float: The weight of the elevation part of the decision.
        """
        pass

    def _compute_conditional_cmd_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        """
        Computes additional weight when certain conditions are meet.
        Args:
            payload (const.AlgoPayload): Information from the drone

        Returns:
            float: The weight of the conditional command
        """
        return 0

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        """
        Compute the life weight part of the decision.

        Args:
            payload (const.AlgoPayload): Payload to be used to compute the weight.

        Returns:
            float: The weight of the life part of the decision.
        """
        weight: float = 0
        food_count: int = 0
        inventory: inv.Inventory = payload.get("inventory")

        if inventory is None:
            return weight
        food_count = inventory.getInventory("food")
        if food_count != 0:
            weight = 1 / food_count
        return weight * self._life_weight_mult

    def compute_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        """
        Compute the weight of a decision based on the payload.

        Args:
            payload (dict): Payload to be used to compute the weight.

        Returns:
            int: The weight of the decision.
        """
        weight: float = 0         
        if len(Decision.next_cmds) > 0:
            if Decision.next_cmds[0].find(self.__str__().partition(" ")[0]) != -1:
                Decision.next_cmds.pop(0)
                return float("inf")

        Decision.iterator += 1
        life_weight: float = self._compute_life_weight(payload)
        elevation_weight: float = self._compute_elevation_weight(payload)
        view_weight: float = self._compute_view_weight(payload, last_decision)
        conditional_cmd_weight: float = self._compute_conditional_cmd_weight(payload, last_decision)

        weight = life_weight + view_weight + elevation_weight + conditional_cmd_weight

        # print(f"\nDecision: \033[36m{self}\033[0m")
        # print(f"Life weight: {life_weight}")
        # print(f"View weight: {view_weight}")
        # print(f"Elevation weight: {elevation_weight}")
        # print(f"Conditional command weight: {conditional_cmd_weight}")
        # print(f"Total weight: {weight}")  
        print(f"Decision: \033[36m{self}\033[0m {weight}")
        return weight

    @abstractmethod
    def __str__(self) -> str:
        """
        Return the string representation of the decision.

        Returns:
            str: The string representation of the decision.
        """
        pass


class MoveDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        self.movecmd: str = "forward"
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0
        left_indexes: list[int] = [3, 7, 13, 8, 14, 15]
        right_indexes: list[int] = [1, 5, 11, 4, 10, 9]
        view: list[str] = payload.get("view")
        
        if view is None or len(view) == 0:
            return weight
        for i in range(1, len(view)):
            if view[i].find("player") != -1:
                weight = float("inf")
                Decision.next_cmds.append("forward")
                if i in right_indexes:
                    Decision.next_cmds.append("right")
                    Decision.next_cmds.append("left")
                elif i in left_indexes:
                    Decision.next_cmds.append("left")
                    Decision.next_cmds.append("right")
        if len(Decision.next_cmds) == 0:
            if len(view[0]) < len("player"):
                num: int = random.randint(0, 2)
                match num:
                    case 0:
                        Decision.next_cmds.append("right")
                    case 1:
                        Decision.next_cmds.append("left")
                    case _:
                        pass
                Decision.next_cmds.append("forward")
        if len(Decision.next_cmds) > 0 and Decision.next_cmds[0] in ["right", "left", "forward"]:
            self.movecmd = Decision.next_cmds[0]
        return weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self._elevation_weight_mult

    def __str__(self) -> str:
        return self.movecmd


class LookDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        return self._view_mineral_weight_mult * self._view_food_weight_mult * self._view_player_weight_mult

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self._elevation_weight_mult

    def _compute_conditional_cmd_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0

        if Decision.iterator % 3 == 0:
            weight = 3
        if self.wants_to_look is True:
            self.wants_to_look = False
            weight = float("inf")
        return weight

    def __str__(self) -> str:
        return "look"


class InventoryDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        return self._view_mineral_weight_mult * self._view_food_weight_mult * self._view_player_weight_mult

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self._elevation_weight_mult

    def _compute_conditional_cmd_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0

        if Decision.iterator % 5 == 0:
            weight = 5
        return weight

    def __str__(self) -> str:
        return "inventory"


class BroadcastDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        return self._view_mineral_weight_mult * self._view_food_weight_mult * self._view_player_weight_mult

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self._elevation_weight_mult

    def _compute_conditional_cmd_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0

        if self.waiting_to_elevate is True and Decision.broadcast_msg != "":
            weight = float("inf")
        Decision.wants_to_look = True
        return weight

    def __str__(self) -> str:
        msg: str = Decision.broadcast_msg
        Decision.broadcast_msg = ""
        return f"broadcast {msg}"


class ConnectNbrDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        return self._view_mineral_weight_mult * self._view_food_weight_mult * self._view_player_weight_mult

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self._elevation_weight_mult

    def _compute_conditional_cmd_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0

        if Decision.iterator % 25 == 0:
            weight = 25
        return weight

    def __str__(self) -> str:
        return "connect_nbr"


class ForkDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        return self._view_mineral_weight_mult * self._view_food_weight_mult * self._view_player_weight_mult

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        weight: float = 0
        elevation: int = payload.get("elevation")

        if elevation is None:
            return weight
        weight = elevation * self._elevation_weight_mult
        return weight

    def _compute_conditional_cmd_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0
        max_weight: int = 5
        connect_nbr: int = payload.get("connect_nbr")

        if connect_nbr is None:
            return weight
        if (abs(connect_nbr - 1) + 1) != 0:
            weight = max_weight / (abs(connect_nbr - 1) + 1)
        return weight

    def __str__(self) -> str:
        return "fork"


class EjectDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        return 0

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return 0

    def __str__(self) -> str:
        return "eject"


class TakeDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )
        self.item: str = ""

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0
        needed_objects: list[str] = []
        view: list[str] = payload.get("view")

        self.item = ""
        if view is None or len(view) == 0:
            return weight
        for object in const.INVENTORY:
            if needs_object(object, payload.get("elevation"), payload.get("inventory")):
                needed_objects.append(object)

        print(payload.get("inventory").getInventory("linemate"))
        if view[0].count("player") > 1:
            weight = -10
        elif len(needed_objects) > 0:
            for obj in view[0]:
                if obj in needed_objects:
                    weight = 1 * self._view_mineral_weight_mult
                    self.item = obj
                    break
        if payload.get("inventory").getInventory("food") < 3 and view[0].count("food") > 0:
            weight = self._view_food_weight_mult
            self.item = "food"
        return weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self._elevation_weight_mult

    def _compute_conditional_cmd_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        return 0

    def __str__(self) -> str:
        return f"take {self.item}"


class SetDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )
        self.item: str = ""

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0
        unnecesary_objects: list[str] = []
        view: list[str] = payload.get("view")

        if view is None or len(view) == 0:
            return weight
        if view[0].count("player") < 2:
            weight = -10
        if self.set_items is True:
            weight = float("inf")
        return weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self._elevation_weight_mult

    def _compute_conditional_cmd_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        weight: float = 0
        view: list[str] = payload.get("view")

        if view is None or len(view) == 0:
            return weight

        return weight

    def __str__(self) -> str:
        item = self.item
        self.item = ""
        return f"set {item}"


class IncantationDecision(Decision):
    def __init__(
        self,
        *,
        life_weight_mult: int = 0,
        elevation_weight_mult: int = 0,
        view_food_weight_mult: int = 0,
        view_mineral_weight_mult: int = 0,
        view_player_weight_mult: int = 0,
    ) -> None:
        super().__init__(
            life_weight_mult=life_weight_mult,
            elevation_weight_mult=elevation_weight_mult,
            view_food_weight_mult=view_food_weight_mult,
            view_mineral_weight_mult=view_mineral_weight_mult,
            view_player_weight_mult=view_player_weight_mult,
        )

    def _compute_view_weight(self, payload: const.AlgoPayload, last_decision: str) -> float:
        return self._view_mineral_weight_mult * self._view_food_weight_mult * self._view_player_weight_mult

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        weight: float = 0
        
        if wants_to_elevate(payload):
            if payload.get("elevation") == 1:
                weight = 1
        
        if payload.get("last_cmd") == "incantation":
            weight =  0
        return weight * self._elevation_weight_mult

    def __str__(self) -> str:
        return "incantation"
