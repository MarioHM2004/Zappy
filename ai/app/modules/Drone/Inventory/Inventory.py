class Inventory:
    def __init__(self) -> None:
        self.food: int = 0
        self.sibur: int = 0
        self.phiras: int = 0
        self.thystame: int = 0
        self.mendiane: int = 0
        self.linemate: int = 0
        self.deraumere: int = 0

    def __str__(self) -> str:
        return f"Inventory: {self.food}, {self.linemate}, {self.deraumere}, {self.sibur}, {self.mendiane}, {self.phiras}, {self.thystame}"