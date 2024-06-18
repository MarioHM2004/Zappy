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

# takes 7/f
def cmd_forward(drone: Drone, payload) -> str:
    match drone.orientation:
        case 1:
            drone.y_position += 1
        case 2:
            drone.x_position += 1
        case 3:
            drone.y_position -= 1
        case 4:
            drone.x_position -= 1
    return "forward"

# takes 7/f
def cmd_left(drone: Drone, payload) -> str:
    match drone.orientation:
        case 1:
            drone.orientation = 4
        case 2:
            drone.orientation = 1
        case 3:
            drone.orientation = 2
        case 4:
            drone.orientation = 3
    return "left"

# takes 7/f
def cmd_right(drone: Drone, payload) -> str:
    match drone.orientation:
        case 1:
            drone.orientation = 2
        case 2:
            drone.orientation = 3
        case 3:
            drone.orientation = 4
        case 4:
            drone.orientation = 1
    return "right"

# takes 7/f
def cmd_look(drone: Drone, payload) -> str:
    print(f"look: {drone.view}")
    return "look"

# takes 1/f
def cmd_inventory(drone: Drone, payload) -> str:
    print(f"inventory: {drone.inventory}")
    return "inventory"

# takes 7/f
def cmd_broadcast(drone, msg: str) -> str:
    return f"broadcast {msg}"

# doesn't take any time
def cmd_connect_nbr(drone: Drone, payload) -> str:
    return "connect_nbr"

# takes 42/f
def cmd_fork(drone: Drone, payload) -> str:
    drone.connect_nbr += 1
    return "fork"

# takes 7/f
def cmd_eject(drone: Drone, payload) -> str:
    return "eject"

# takes 7/f
def cmd_take(drone: Drone, payload) -> str:
    return "take"

# takes 7/f
def cmd_set(drone: Drone, payload) -> str:
    return "set"

# takes 300/f
def cmd_incantation(drone: Drone, payload) -> str:
    return "incantation"
