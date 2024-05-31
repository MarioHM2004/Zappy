#!/usr/bin/env python3
import argparse
import socket

class AIManager:
    def __init__(self):
        self.parser = argparse.ArgumentParser(add_help=False)
        self.parser.add_argument('-help', action='help', help='Show this help message and exit')
        self.parser.add_argument('-p', type=int, required=True, help='Port number')
        self.parser.add_argument('-n', type=str, required=True, help='Name of the team')
        self.parser.add_argument('-h', type=str, default='localhost', help='Name of the machine; localhost by default')

    def parse_args(self, args):
        args = self.parser.parse_args(args)
        self.start_ai(args)

    def start_ai(self, args):
        print(f"-- Starting AI for team {args.n} on {args.h}:{args.p}")

        client_socket = self.establish_connection(args.h, args.p, args.n)
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
                print(f"-- Error: {e}")
                break

        print("-- Connection closed")
        client_socket.close()

    def establish_connection(self, host, port, team_name):
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            client_socket.connect((host, port))
            print(f"-- Connected to {host}:{port}")
            init_msg = f"team_name:{team_name}n"
            client_socket.sendall(init_msg.encode())
            return client_socket
        except Exception as e:
            print(f"-- Failed to connect to server: {host}:{port}")
            return None
