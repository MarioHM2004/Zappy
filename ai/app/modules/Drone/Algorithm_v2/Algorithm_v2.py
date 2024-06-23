##
## EPITECH PROJECT, 2024
## B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
## File description:
## Algorithm_v2
##
from typing import List

import app.const as const
import app.modules.Drone.Inventory.Inventory as inv

class Algorithm:
    def __init__(self) -> None:
        self.forward: str = "forward"
        self.right: str = "right"
        self.left: str = "left"
        self.look: str = "look"
        self.inventory: str = "inventory"
        self.broadcast: str = "broadcast"
        self.connect_nbr: str = "connect_nbr"
        self.fork: str = "fork"
        self.eject: str = "eject"
        self.take: str = "take"
        self.set: str = "set"
        self.incantation: str = "incantation"
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

    def __calculate_scores(self, payload: const.AlgoPayload, scores: dict[str, float]) -> dict[str, float]:
        """
        Calculate the scores of each decision based on the payload.

        Args:
            payload (const.AlgoPayload): Payload to be used to calculate the scores.

        Returns:
            dict[str, float]: Dictionary with the name and scores of each decision.
        """
        objects_needed = dict()
        objects_in_view = dict()
        position_object = int

        if len(self.objective) > 0:
            scores = self.__reset_scores(scores)
            scores[self.objective[0]] = 1
            self.objective.pop(0)
            return scores

        if self.__all_objects_recollected(payload):
            scores = self.__reset_scores(scores)
            if payload.get("last_cmd") != "incantation" and payload.get("elevation") == 1:
                scores["incantation"] = 1
                self.objective.append("inventory")
                return scores
        if len(self.objective) == 0 and payload.get("last_cmd") != "look":
            scores["look"] = 1
            return scores

        # check if need to take object
        objects_needed = self.__need_object(payload)
        # print(f"******************OBJ NEED: {objects_needed}")

        # check if object is in view
        objects_in_view = self.__object_in_view(payload)
        # print(f"******************OBJ IN VIEW: {objects_in_view}")

        for object in objects_in_view:
            for item in object:
                if item in objects_needed and objects_needed[item] == 1:
                    position_object = self.__position_object(item, objects_in_view)
                    match position_object:
                        case 0:
                            str_take = "take " + item
                            scores[str_take] = 3
                            self.objective.clear()
                            return scores
                        case 2:
                            scores["forward"] = 2
                            str_take = "take " + item
                            self.objective.clear()
                            self.objective.append(str_take)
                            return scores
                        case 1:
                            scores["left"] = 1
                            self.objective.clear()
                            self.objective.append("forward")
                            self.objective.append("right")
                            self.objective.append("forward")
                            self.objective.append("take " + item)
                            return scores
                        case 3:
                            scores["right"] = 1
                            self.objective.clear()
                            self.objective.append("forward")
                            self.objective.append("left")
                            self.objective.append("forward")
                            self.objective.append("take " + item)
                            return scores
                    break
        return scores

    def __position_object(self, object:str, objects_in_view:List[str]) -> int:
        """
        Return the position of the object in the view.

        Args:
            object (str): Object to be searched.
            objects_in_view (List[str]): List with the objects in view.

        Returns:
            int: Position of the object in the view.
        """
        for i in range(len(objects_in_view)):
            if object in objects_in_view[i]:
                return i
        return -1

    def __need_object(self, payload: const.AlgoPayload) -> dict[str, float]:
        """
        Return a dictionary with the objects that the drone needs.

        Args:
            payload (const.AlgoPayload): Payload to be used to check the objects needed.

        Returns:
            dict[str, float]: Dictionary with the name and scores of each object needed.
        """
        objects_needed = dict()

        for object in const.INVENTORY:
            if payload.get("inventory").getInventory(object) < 1:
                objects_needed[object] = 1
            else:
                objects_needed[object] = 0

        return objects_needed

    def __all_objects_recollected(self, payload: const.AlgoPayload) -> bool:
        """
        Check if all the objects have been recollected.

        Args:
            payload (const.AlgoPayload): Payload to be used to check the objects recollected.

        Returns:
            bool: True if all the objects have been recollected, False otherwise.
        """
        for object in const.INVENTORY:
            if payload.get("inventory").getInventory(object) < 1:
                return False
        return True

    def __object_in_view(self, payload: const.AlgoPayload) -> list[str]:
        """
        Return a list with the objects that the drone can see.

        Args:
            payload (const.AlgoPayload): Payload to be used to check the objects in view.

        Returns:
            list[str]: List with the name of the objects in view.
        """
        objects_in_view = list[str]

        objects_in_view = payload.get("view")

        if len(objects_in_view) > 0:
            objects_in_view = [item.split() for item in objects_in_view]

        return objects_in_view

    def choose_decision(self, payload: const.AlgoPayload) -> str:
        """
        Choose the best decision to take based on the payload.

        Args:
            payload (const.AlgoPayload): Payload to be used to take a decision.

        Returns:
            str: The decision to take.
        """
        scores = dict()
        scores["forward"] = 0
        scores["right"] = 0
        scores["left"] = 0
        scores["look"] = 0
        scores["inventory"] = 0
        scores["broadcast"] = 0
        scores["connect_nbr"] = 0
        scores["fork"] = 0
        scores["eject"] = 0
        scores["set"] = 0
        scores["incantation"] = 0

        # self.display_payload(payload)

        if payload.get("frozen") is True:
            return "ko"
        scores = self.__calculate_scores(payload, scores)
        decision = max(scores, key=scores.get)
        scores[decision] = 0
        return decision
        # return "forward" # Testing purposes

    def display_payload(self, payload: const.AlgoPayload) -> None:
        print(f"PAYLOAD: life={payload.get('life')}, team={payload.get('team')}, elevation={payload.get('elevation')}, view={payload.get('view')}, frozen={payload.get('frozen')}, x_position={payload.get('x_position')}, y_position={payload.get('y_position')}, orientation={payload.get('orientation')}, connect_nbr={payload.get('connect_nbr')},")
        print(f"inventory=[{payload.get('inventory')}]")
