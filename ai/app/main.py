import sys
from .modules.AIManager.AIManager import AIManager

def main():
    print("Starting AI...")
    if len(sys.argv) < 2 or len(sys.argv) > 7:
        print("ERROR: bad arguments.")
        print("Try './zappy_ai -help' for more information.")
        sys.exit(84)

    ai_manager = AIManager()
    try:
        ai_manager.parse_args(sys.argv[1:])
    except Exception as e:
        print(e)
        sys.exit(84)
