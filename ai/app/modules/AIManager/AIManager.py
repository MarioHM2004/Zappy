import app.modules.AIManager.AIManagerHelper as h

class AIManager:
    def __init__(self, port: int, frequency: int, host: str) -> None:
        self.port: int = port
        self.host: str = host
        self.frequency: int = frequency
        self.socket = None
    
    def start_socket(self):
        pass
