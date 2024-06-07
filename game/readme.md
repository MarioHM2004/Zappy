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

4. Run the mock server:

```bash
./build/server 4242&
```

5. Open the editor:

```bash
godot
```

## reference

In order to use the `C++` bindings, follow this
[guide](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#gdextension-c-example).
