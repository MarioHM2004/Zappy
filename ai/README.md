# Zappy ai

An ai, created in Python, that simulates drone's mind.

## Usage

```sh
USAGE: ./zappy_ai -p port -n team_name -ai id [-h host]
    port        is the port number
    team_name   is the name of the team
    host        is the name of the machine; localhost   by default
    id          ai identifier, 1 for first algorithm 2 for second algorithm
```

## Example usage

```sh
./zappy_server -p 4040 -x 20 -y 20 -n team1 team2 team3 -c 3 -f 10 --auto-start on --display-eggs true
```

```sh
./zappy_ai -p 4040 -n team1
```
