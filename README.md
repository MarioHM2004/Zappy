# Zappy

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Gameplay](#gameplay)
- [Communication Protocol](#communication-protocol)
- [Project Structure](#project-structure)
- [License](#license)

## Overview

**Zappy** is a multiplayer network game inspired by the fictional character Zaphod Beeblebrox from "The Hitchhiker's Guide to the Galaxy." In Zappy, several teams of players compete to reach the highest level of evolution in a world called Trantor, a tile-based map abundant in resources. The game includes a server, a graphical user interface (GUI), and AI clients.

The primary goal is for each team to help their players gather resources and elevate their level through a series of incantation rituals. The first team to have six players reach the maximum level wins.

## Features

- **Multiplayer Network Game**: Supports multiple teams and players.
- **Tile-based Map**: Dynamic world with various resources.
- **Graphical User Interface**: Visual representation of the game world using Godot.
- **AI Clients**: Autonomous agents that simulate players' actions.
- **Custom Protocol**: Client-server communication for game events.

## Installation

### Prerequisites

- **C Compiler**: For compiling the server.
- **Godot 4.2.2**: For running the GUI.
- **Make**: For building the project.

### Steps

1. **Clone the Repository**

    ```bash
    git clone https://github.com/MarioHM2004/Zappy.git
    cd Zappy
    ```

2. **Build the Project**

    Inside each folder you can find a dedicated README in order to understand each section of the project and how to build it and run it (game, AI, server).

## Gameplay

### Objective

The objective is to collect resources, perform rituals, and elevate the players' levels to win the game by having at least six players reach the highest level.

### Resources

- **Food**: Essential for survival.
- **Stones**: Required for rituals and elevation.
    - Linemate
    - Deraumere
    - Sibur
    - Mendiane
    - Phiras
    - Thystame

### Commands

- **Move**: Navigate through the map.
- **Collect/Drop Resources**: Interact with the environment.
- **Broadcast**: Communicate with other players.
- **Incantation**: Perform rituals for elevation.

## Communication Protocol

The Zappy protocol defines how the server and clients communicate using TCP sockets. It includes commands for:

- **Player Actions**: Movement, collecting resources, etc.
- **Game Events**: Player connection, game status, etc.
- **GUI Commands**: Visualization updates, map details, etc.

### Client-Server Commands

#### Player Commands
- **Move**: `Forward`, `Right`, `Left`
- **Resource Management**: `Take <resource>`, `Set <resource>`
- **Inventory**: `Inventory`
- **Broadcast**: `Broadcast <message>`
- **Incantation**: `Incantation`

#### Server Responses
- **OK**: Indicates a successful command.
- **ko**: Indicates a failed command.
- **Broadcast**: Returns a broadcast message from another player.
- **Inventory**: Lists current resources held by the player.

### GUI Commands
- **Map Details**: `msz` to get map size.
- **Tile Content**: `bct x y` to get content of tile (x, y).
- **Player Position**: `ppo #n` to get player position.

Look to the full Zappy GUI Protocol document for a comprehensive list of commands and responses on game folder README.

## Project Structure

- **`server`**: The game server.
- **`game`**: The graphical interface developed with Godot.
- **`ai`**: The AI client.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
