#!/usr/bin/env python3


def running_ai(client_socket):
    running = True

    if client_socket is None:
        running = False
        return

    while running:
        try:
            data = client_socket.recv(1024).decode()
            if not data:
                break
            print(f"Received: {data}")
        except Exception as e:
            print(f"-- Error running: {e}")
            running = False
            break

    print("-- Connection closed")
    client_socket.close()
