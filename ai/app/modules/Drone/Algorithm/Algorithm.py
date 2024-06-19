##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Algorithm.py
##
import app.const as const
import app.modules.Drone.Algorithm.AlgorithmHelper as ah


class Algorithm:
    def __init__(self) -> None:
        self.forward: ah.ForwardDecision = ah.ForwardDecision()
        self.right: ah.RightDecision = ah.RightDecision()
        self.left: ah.LeftDecision = ah.LeftDecision()
        self.look: ah.LookDecision = ah.LookDecision()
        self.inventory: ah.InventoryDecision = ah.InventoryDecision()
        self.broadcast: ah.BroadcastDecision = ah.BroadcastDecision()
        self.connect_nbr: ah.ConnectNbrDecision = ah.ConnectNbrDecision()
        self.fork: ah.ForkDecision = ah.ForkDecision()
        self.eject: ah.EjectDecision = ah.EjectDecision()
        self.take: ah.TakeDecision = ah.TakeDecision()
        self.set: ah.SetDecision = ah.SetDecision()
        self.incantation: ah.IncantationDecision = ah.IncantationDecision()

    def __calculate_scores(self, payload: const.AlgoPayload) -> dict[str, float]:
        """
        Calculate the scores of each decision based on the payload.

        Args:
            payload (const.AlgoPayload): Payload to be used to calculate the scores.

        Returns:
            dict[str, float]: Dictionary with the name and scores of each decision.
        """
        raise NotImplementedError

    def choose_decision(self, payload: const.AlgoPayload) -> str:
        """
        Choose the best decision to take based on the payload.

        Args:
            payload (const.AlgoPayload): Payload to be used to take a decision.

        Returns:
            str: The decision to take.
        """

        if payload.get("frozen") is True:
            return "ko"
        # scores = self.__calculate_scores(payload)
        # return max(scores, key=scores.get)
        return "forward" # Testing purposes
