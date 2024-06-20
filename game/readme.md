# zappy gui

Created with `Godot` and its `C++` bindings.

## setup

> [!WARNING]\
> You need to have
> [`Godot v4.2`](https://docs.godotengine.org/en/stable/index.html) and
> [`Scons`](https://scons.org) installed to run this project.

1. Clone the repository with submodules:

```bash
git clone --recurse-submodules $URL $TARGET
```

2. Configure the project:

```bash
cmake -B build -G Ninja
```

3. Build the project:

```bash
cmake --build build
```

4. Open the editor:

```bash
godot
```

## reference

In order to use the `C++` bindings, follow this
[guide](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#gdextension-c-example).

## commands

List with all the commands that the server can send to the client and its
parameters.

| Command                             | Name                         | Done | Description of its parameter                                                                                                                                                                                                                                                                                                                     |
| ----------------------------------- | ---------------------------- | ---- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `msz X Y\n`                         | Map Size                     | [X]  | `X` width or horizontal position, `Y` height or vertical position                                                                                                                                                                                                                                                                                |
| `bct X Y q0 q1 q2 q3 q4 q5 q6\n`    | Content of a Tile            | [X]  | `X` width or horizontal position, `Y` height or vertical position, `q0` resource 0 (food) quantity, `q1` resource 1 (linemate) quantity, `q2` resource 2 (deraumere) quantity, `q3` resource 3 (sibur) quantity, `q4` resource 4 (mendiane) quantity, `q5` resource 5 (phiras) quantity, `q6` resource 6 (thystame) quantity                     |
| `tna N\n`                           | Name of All the Teams        | [X]  | `N` name of the team                                                                                                                                                                                                                                                                                                                             |
| `pnw #n X Y O L N\n`                | Connection of a New Player   | [X]  | `#n` player number, `X` width or horizontal position, `Y` height or vertical position, `O` orientation: 1(N), 2(E), 3(S), 4(W), `L` player level, `N` name of the team                                                                                                                                                                           |
| `ppo #n X Y O\n`                    | Player’s Position            | [X]  | `#n` player number, `X` width or horizontal position, `Y` height or vertical position, `O` orientation: 1(N), 2(E), 3(S), 4(W)                                                                                                                                                                                                                   |
| `plv #n L\n`                        | Player’s Level               | [X]  | `#n` player number, `L` player level                                                                                                                                                                                                                                                                                                             |
| `pin #n X Y q0 q1 q2 q3 q4 q5 q6\n` | Player’s Inventory           | [X]  | `#n` player number, `X` width or horizontal position, `Y` height or vertical position, `q0` resource 0 (food) quantity, `q1` resource 1 (linemate) quantity, `q2` resource 2 (deraumere) quantity, `q3` resource 3 (sibur) quantity, `q4` resource 4 (mendiane) quantity, `q5` resource 5 (phiras) quantity, `q6` resource 6 (thystame) quantity |
| `pex #n\n`                          | Expulsion                    | [X]  | `#n` player number                                                                                                                                                                                                                                                                                                                               |
| `pbc #n M\n`                        | Broadcast                    | [ ]  | `#n` player number, `M` message                                                                                                                                                                                                                                                                                                                  |
| `pic X Y L #n #n ... \n`            | Start of an Incantation      | [X]  | `X` width or horizontal position, `Y` height or vertical position, `L` level, `#n` player number (multiple)                                                                                                                                                                                                                                      |
| `pie X Y R\n`                       | End of an Incantation        | [X]  | `X` width or horizontal position, `Y` height or vertical position, `R` result                                                                                                                                                                                                                                                                    |
| `pfk #n\n`                          | Egg Laying by the Player     | [ ]  | `#n` player number                                                                                                                                                                                                                                                                                                                               |
| `pdr #n i\n`                        | Resource Dropping            | [ ]  | `#n` player number, `i` resource number                                                                                                                                                                                                                                                                                                          |
| `pgt #n i\n`                        | Resource Collecting          | [ ]  | `#n` player number, `i` resource number                                                                                                                                                                                                                                                                                                          |
| `pdi #n\n`                          | Death of a Player            | [ ]  | `#n` player number                                                                                                                                                                                                                                                                                                                               |
| `enw #e #n X Y\n`                   | An Egg Was Laid by a Player  | [ ]  | `#e` egg number, `#n` player number, `X` width or horizontal position, `Y` height or vertical position                                                                                                                                                                                                                                           |
| `ebo #e\n`                          | Player Connection for an Egg | [ ]  | `#e` egg number                                                                                                                                                                                                                                                                                                                                  |
| `edi #e\n`                          | Death of an Egg              | [ ]  | `#e` egg number                                                                                                                                                                                                                                                                                                                                  |
| `sgt T\n`                           | Time Unit Request            | [ ]  | `T` time unit                                                                                                                                                                                                                                                                                                                                    |
| `sst T\n`                           | Time Unit Modification       | [ ]  | `T` time unit                                                                                                                                                                                                                                                                                                                                    |
| `seg N\n`                           | End of Game                  | [ ]  | `N` name of the team                                                                                                                                                                                                                                                                                                                             |
| `smg M\n`                           | Message from the Server      | [ ]  | `M` message                                                                                                                                                                                                                                                                                                                                      |
| `suc\n`                             | Unknown Command              | [ ]  | none                                                                                                                                                                                                                                                                                                                                             |
| `sbp\n`                             | Command Parameter Error      | [ ]  | none                                                                                                                                                                                                                                                                                                                                             |
