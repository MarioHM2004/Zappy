import sys
from .modules.AIManager.AIManager import AIManager

def main():
    print("Starting AI...")
    if len(sys.argv) > 1 and len(sys.argv) <= 7:
        ai_manager = AIManager()
        try:
            ai_manager.parse_args(sys.argv[1:])
        except Exception as e:
            print(e)
            sys.exit(84)
    else:
        print("ERROR: bad arguments.")
        print("Try './zappy_ai -help' for more information.")
        sys.exit(84)