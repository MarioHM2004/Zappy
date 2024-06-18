##
## EPITECH PROJECT, 2023
## zappy
## File description:
## AlgorithmHelper.py
##
from abc import ABC
from abc import abstractmethod

import ai.app.const as const


class Decision(ABC):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        self.life_weight: int = life_weight
        self.team_weight: int = team_weight
        self.view_weight: int = view_weight
        self.elevation_weight: int = elevation_weight
        self.inventory_weight: int = inventory_weight

    @abstractmethod
    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        """
        Compute the life weight part of the decision.

        Args:
            payload (const.AlgoPayload): Payload to be used to compute the weight.

        Returns:
            float: The weight of the life part of the decision.
        """
        pass

    @abstractmethod
    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        """
        Compute the team weight part of the decision.

        Args:
            payload (const.AlgoPayload): Payload to be used to compute the weight.

        Returns:
            float: The weight of the team part of the decision.
        """
        pass

    @abstractmethod
    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
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

    @abstractmethod
    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        """
        Compute the inventory weight part of the decision.

        Args:
            payload (const.AlgoPayload): Payload to be used to compute the weight.

        Returns:
            float: The weight of the inventory part of the decision.
        """
        pass

    def compute_weight(self, payload: const.AlgoPayload) -> float:
        """
        Compute the weight of a decision based on the payload.

        Args:
            payload (dict): Payload to be used to compute the weight.

        Returns:
            int: The weight of the decision.
        """
        weight: float = 0

        weight += self._compute_life_weight(payload)
        weight += self._compute_team_weight(payload)
        weight += self._compute_view_weight(payload)
        weight += self._compute_elevation_weight(payload)
        weight += self._compute_inventory_weight(payload)

        return weight

    @abstractmethod
    def __str__(self) -> str:
        """
        Return the string representation of the decision.

        Returns:
            str: The string representation of the decision.
        """
        pass


class ForwardDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "forward"


class RightDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "right"


class LeftDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "left"


class LookDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "look"


class InventoryDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "inventory"


class BroadcastDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "broadcast"


class ConnectNbrDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "connect_nbr"


class ForkDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "fork"


class EjectDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "eject"


class TakeDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "take"


class SetDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "set"


class IncantationDecision(Decision):
    def __init__(
        self,
        *,
        life_weight: int = 0,
        team_weight: int = 0,
        view_weight: int = 0,
        elevation_weight: int = 0,
        inventory_weight: int = 0,
    ) -> None:
        super().__init__(
            life_weight=life_weight,
            team_weight=team_weight,
            view_weight=view_weight,
            elevation_weight=elevation_weight,
            inventory_weight=inventory_weight,
        )

    def _compute_life_weight(self, payload: const.AlgoPayload) -> float:
        return self.life_weight

    def _compute_team_weight(self, payload: const.AlgoPayload) -> float:
        return self.team_weight

    def _compute_view_weight(self, payload: const.AlgoPayload) -> float:
        return self.view_weight

    def _compute_elevation_weight(self, payload: const.AlgoPayload) -> float:
        return self.elevation_weight

    def _compute_inventory_weight(self, payload: const.AlgoPayload) -> float:
        return self.inventory_weight

    def __str__(self) -> str:
        return "incantation"
