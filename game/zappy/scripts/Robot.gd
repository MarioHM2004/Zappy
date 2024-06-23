extends CharacterBody3D

signal set_movement_state(_movement_state: MovementState)
signal set_movement_direction(_movement_direction: Vector3)

@export var movement_states: Dictionary
@export var gravity: float = -9.8
@export var stuck_check_interval: float = 2.0
@export var stuck_rotation_angle: float = 45.0

var target_coordinate: Vector3
var movement_direction: Vector3

var arrived = false
var run_state: MovementState = MovementState.new()
var stopped_state: MovementState = MovementState.new()

func _ready():
	run_state.movement_speed = 3
	run_state.acceleration = 7
	run_state.animation_speed = 1.15
	stopped_state.movement_speed = 0
	stopped_state.acceleration = 6
	stopped_state.animation_speed = 1
	set_movement_state.emit(stopped_state)
	$"MeshRoot/3DGodotRobot/AnimationPlayer".play("Idle")
	pass

func _process(_delta):
	var current_position_xz = Vector3(global_transform.origin.x, 0, global_transform.origin.z)
	var target_coordinate_xz = Vector3(target_coordinate.x, 0, target_coordinate.z)
	if current_position_xz.distance_to(target_coordinate_xz) < 0.5 and not arrived:
		arrived = true
		$"MeshRoot/3DGodotRobot/AnimationPlayer".play("Idle")
		set_movement_state.emit(stopped_state)

func _physics_process(delta):
	if !is_on_floor():
		velocity.y += gravity * delta
	if is_movement_ongoing():
		movement_direction = (target_coordinate - global_transform.origin).normalized()
		set_movement_direction.emit(movement_direction)

func is_movement_ongoing():
	return abs(movement_direction.x) > 0 or abs(movement_direction.z) > 0

func move_to_coordinate(coordinate: Vector3):
	arrived = false
	target_coordinate = coordinate
	movement_direction = (coordinate - global_transform.origin).normalized()
	movement_direction.y = 0
	set_movement_direction.emit(movement_direction)
	set_movement_state.emit(run_state)
	$"MeshRoot/3DGodotRobot/AnimationPlayer".play("Run")

func invocation_anim():
	$"MeshRoot/3DGodotRobot/AnimationPlayer".play("Kick")

func death_anim():
	$"MeshRoot/3DGodotRobot/AnimationPlayer".play("Hurt")
	
func idle_anim():
	$"MeshRoot/3DGodotRobot/AnimationPlayer".play("Idle")
	set_movement_state.emit(stopped_state)
	
func drop_anim():
	$"MeshRoot/3DGodotRobot/AnimationPlayer".play("Emote1")

func egg_anim():
	$"MeshRoot/3DGodotRobot/AnimationPlayer".play("Emote2")

func tint_one(path: String, principal: Color, dim: Color, shade: Color, light: Color):
	var node: MeshInstance3D = get_node(path)
	var shader_material: ShaderMaterial = node.get_surface_override_material(0).duplicate()
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

func rotate_to(target):
	set_movement_direction.emit(target);
