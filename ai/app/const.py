# Commands

from typing import Callable
import ai.app.modules.Drone.DroneHelper as d

CMD_FUNC: list[str, Callable] = {
    'forward': d.cmd_forward,
    'left': d.cmd_left,
    'right': d.cmd_right,
    'look': d.cmd_look,
    'inventory': d.cmd_inventory,
    'broadcast': d.cmd_broadcast,
    'connect_nbr': d.cmd_connect_nbr,
    'fork': d.cmd_fork,
    'eject': d.cmd_eject,
    'take': d.cmd_take,
    'set': d.cmd_set,
    'incantation': d.cmd_incantation
}