import ai.app.modules.AIManager.AIManager as m


def main(argc: int, argv: list[str]):
    ai_manager: m.AIManager = None

    print("Starting AI...")
    if len(argv) < 2 or len(argv) > 7:
        print("ERROR: bad arguments.")
        print("Try './zappy_ai -help' for more information.")
        exit(84)

    ai_manager = m.AIManager()

    try:
        ai_manager.parse_args(argv[1:])
        ai_manager.start_ai()
    except Exception as e:
        print(e)
