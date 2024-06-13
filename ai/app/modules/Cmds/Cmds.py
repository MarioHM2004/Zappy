def cmd_forward():
    return "forward"

def cmd_left():
    return "left"

def cmd_right():
    return "right"

def cmd_look():
    return "look"

def cmd_inventory():
    return "inventory"

def cmd_broadcast(msg: str):
    return f"broadcast {msg}"

def cmd_connect_nbr():
    return "connect_nbr"

def cmd_fork():
    return "fork"

def cmd_eject():
    return "eject"

def cmd_take():
    return "take"

def cmd_set():
    return "set"

def cmd_incantation():
    return "incantation"

def cmd_fork():
    return "fork"

def cmd_eject():
    return "eject"

def cmd_take():
    return "take"

def cmd_set():
    return "set"

def cmd_incantation():
    return "incantation"

cmd_func = {
    'forward': cmd_forward,
    'left': cmd_left,
    'right': cmd_right,
    'look': cmd_look,
    'inventory': cmd_inventory,
    'broadcast': cmd_broadcast,
    'connect_nbr': cmd_connect_nbr,
    'fork': cmd_fork,
    'eject': cmd_eject,
    'take': cmd_take,
    'set': cmd_set,
    'incantation': cmd_incantation
}

def exec_cmd(cmd: str) -> str:
    if cmd not in cmd_func:
        return "ko"
    return cmd_func[cmd]()
