##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Inventory.py
##


class Inventory:
    def __init__(self) -> None:
        self.food: int = 0
        self.sibur: int = 0
        self.phiras: int = 0
        self.thystame: int = 0
        self.mendiane: int = 0
        self.linemate: int = 0
        self.deraumere: int = 0

    def __update_food(self, food: int) -> None:
        self.food += food

    def __update_linemate(self, linemate: int) -> None:
        self.linemate += linemate

    def __update_deraumere(self, deraumere: int) -> None:
        self.deraumere += deraumere

    def __update_sibur(self, sibur: int) -> None:
        self.sibur += sibur

    def __update_mendiane(self, mendiane: int) -> None:
        self.mendiane += mendiane

    def __update_phiras(self, phiras: int) -> None:
        self.phiras += phiras

    def __update_thystame(self, thystame: int) -> None:
        self.thystame += thystame

    def add_item(self, attribute_name: str, x: int) -> None:
        match attribute_name.lower():
            case "food":
                self.__update_food(x)
            case "linemate":
                self.__update_linemate(x)
            case "deraumere":
                self.__update_deraumere(x)
            case "sibur":
                self.__update_sibur(x)
            case "mendiane":
                self.__update_mendiane(x)
            case "phiras":
                self.__update_phiras(x)
            case "thystame":
                self.__update_thystame(x)
            case _:
                raise ValueError(f"Item {attribute_name} not found")

    def remove_item(self, item: str, x: int) -> None:
        self.add_item(item, -x if x > 0 else x)

    def update_inventory(self, inventory: list[str]) -> None:
        try:
            # clear inventory (remove [ and ])
            if inventory[0] == '[':
                inventory = inventory[1:]
            if inventory[len(inventory) - 1] == ']':
                inventory = inventory[:-1]
            inventory = inventory.split(',')

            for item in inventory:
                #remove first space if exists
                if item[0] == ' ':
                    item = item[1:]

                if item.startswith("food"):
                    self.food = int(item[len("food"):])
                elif item.startswith("linemate"):
                    self.linemate = int(item[len("linemate"):])
                elif item.startswith("deraumere"):
                    self.deraumere = int(item[len("deraumere"):])
                elif item.startswith("sibur"):
                    self.sibur = int(item[len("sibur"):])
                elif item.startswith("mendiane"):
                    self.mendiane = int(item[len("mendiane"):])
                elif item.startswith("phiras"):
                    self.phiras = int(item[len("phiras"):])
                elif item.startswith("thystame"):
                    self.thystame = int(item[len("thystame"):])

        except Exception as e:
            print(f"Error updating inventory: {e}")

    def getInventory(self, object: str) -> int:
        match object:
            case "food":
                return self.food
            case "linemate":
                return self.linemate
            case "deraumere":
                return self.deraumere
            case "sibur":
                return self.sibur
            case "mendiane":
                return self.mendiane
            case "phiras":
                return self.phiras
            case "thystame":
                return self.thystame
            case _:
                raise ValueError(f"Item {object} not found")

    def __str__(self) -> str:
        return f"food={self.food}, linemate={self.linemate}, deraumere={self.deraumere}, sibur={self.sibur}, mendiane={self.mendiane}, phiras={self.phiras}, thystame={self.thystame}"
