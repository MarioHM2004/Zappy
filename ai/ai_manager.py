#!/usr/bin/env python3
import argparse

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
        print(f"Starting AI for team {args.n} on {args.h}:{args.p}")
