##
## EPITECH PROJECT, 2023
## zappy
## File description:
## DroneHelper.py
##
from __future__ import annotations

import typing


if typing.TYPE_CHECKING:
    from ai.app.modules.Drone.Drone import Drone

# Solves circular import, that way we can have the Drone type hint in the functions

# def cmd_move(drone: Drone, payload) -> str:
# pass


def cmd_forward(drone: Drone, payload) -> str:
    # drone.y_position += 1
    return "forward"


def cmd_left(drone: Drone, payload) -> str:
    # drone.x_position -= 1
    return "left"


def cmd_right(drone: Drone, payload) -> str:
    # drone.x_position += 1
    return "right"


def cmd_look(drone: Drone, payload) -> str:
    return "look"


def cmd_inventory(drone: Drone, payload) -> str:
    return "inventory"


def cmd_broadcast(drone, msg: str) -> str:
    return f"broadcast {msg}"


def cmd_connect_nbr(drone: Drone, payload) -> str:
    return "connect_nbr"


def cmd_fork(drone: Drone, payload) -> str:
    return "fork"


def cmd_eject(drone: Drone, payload) -> str:
    return "eject"


def cmd_take(drone: Drone, payload) -> str:
    return "take"


def cmd_set(drone: Drone, payload) -> str:
    return "set"


def cmd_incantation(drone: Drone, payload) -> str:
    return "incantation"
