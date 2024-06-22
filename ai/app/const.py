##
## EPITECH PROJECT, 2023
## zappy
## File description:
## const.py
##
from typing import Callable
from typing import Union

import app.modules.Drone.DroneHelper as dh
import app.modules.Drone.Inventory.Inventory as inv


# Type hint for the payload that will be sent to the algorithm
AlgoPayload = dict[str, Union[int, str, list[str], inv.Inventory, bool, None]]

INVENTORY: list[str] = ["food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

# Commands
CMD_FUNC: list[str, Callable] = {
    "forward": dh.cmd_forward,
    "left": dh.cmd_left,
    "right": dh.cmd_right,
    "look": dh.cmd_look,
    "inventory": dh.cmd_inventory,
    "broadcast": dh.cmd_broadcast,
    "connect_nbr": dh.cmd_connect_nbr,
    "fork": dh.cmd_fork,
    "eject": dh.cmd_eject,
    "take": dh.cmd_take,
    "set": dh.cmd_set,
    "incantation": dh.cmd_incantation,
}
