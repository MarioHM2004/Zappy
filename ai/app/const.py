###########
# EXAMPLE #
###########
# Database configuration
DB_HOST = "localhost"
DB_PORT = 5432
DB_NAME = "mydatabase"
DB_USER = "myuser"
DB_PASSWORD = "mypassword"

# API configuration
API_KEY = "myapikey"
API_URL = "https://api.example.com"

# Logging configuration
LOG_LEVEL = "DEBUG"
LOG_FILE = "app.log"

# Other project-specific settings
MAX_RESULTS = 100
DEFAULT_TIMEOUT = 10

###########
# EXAMPLE #
###########

# Commands

import ai.app.modules.Drone.DroneHelper as d

CMD_FUNC = {
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