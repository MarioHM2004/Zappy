extends CharacterBody3D

signal set_movement_state(_movement_state: MovementState)
signal set_movement_direction(_movement_direction: Vector3)

@export var movement_states: Dictionary
@export var gravity: float = -9.8

var target_coordinate: Vector3
var movement_direction: Vector3

func _ready():
	set_movement_state.emit(movement_states["Idle"])

func _process(_delta):
	var current_position_xz = Vector3(global_transform.origin.x, 0, global_transform.origin.z)
	var target_coordinate_xz = Vector3(target_coordinate.x, 0, target_coordinate.z)
	if current_position_xz.distance_to(target_coordinate_xz) < 0.5:
		set_movement_state.emit(movement_states["Idle"])
		movement_direction = Vector3.ZERO

func _physics_process(delta):
	if !is_on_floor():
		velocity.y += gravity * delta
	if is_movement_ongoing():
		set_movement_direction.emit(movement_direction)

func is_movement_ongoing() -> bool:
	return abs(movement_direction.x) > 0 or abs(movement_direction.z) > 0

func move_to_coordinate(coordinate: Vector3):
	target_coordinate = coordinate
	movement_direction = (coordinate - global_transform.origin).normalized()
	movement_direction.y = 0
	set_movement_direction.emit(movement_direction)
	set_movement_state.emit(movement_states["run"])

func tint_one(path: String, principal: Color, dim: Color, shade: Color, light: Color):
	var node: MeshInstance3D = get_node(path);
	var shader_material: ShaderMaterial = node.get_surface_override_material(0).duplicate();
	node.set_surface_override_material(0, shader_material)
	shader_material.set("shader_parameter/NEWCOLORS", [principal, dim, shade, light])

func tint(principal: Color, dim: Color, shade: Color, light: Color):
	var paths = [
		"MeshRoot/3DGodotRobot/RobotArmature/Skeleton3D/Llimbs and head",
		"MeshRoot/3DGodotRobot/RobotArmature/Skeleton3D/Face",
		"MeshRoot/3DGodotRobot/RobotArmature/Skeleton3D/Chest",
		"MeshRoot/3DGodotRobot/RobotArmature/Skeleton3D/Bottom",
	]
	
	for path in paths:
		tint_one(path, principal, dim, shade, light)
