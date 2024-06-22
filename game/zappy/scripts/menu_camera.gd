extends Camera3D

var rotation_speed = 0.1
var tile_parent: Node3D
var ocean_plane: MeshInstance3D

func create_tile(x, y):
	var tile_scene = preload ("res://assets/tile.gltf")
	var tile_instance = tile_scene.instantiate()
	
	tile_instance.position = Vector3(x, 1, y)
	tile_instance.scale = Vector3(0.5, 0.5, 0.5)

	var static_body = StaticBody3D.new()

	var collision_shape = CollisionShape3D.new()
	var box_shape = BoxShape3D.new()
	box_shape.extents = Vector3(0.5, 0.5, 0.5)

	collision_shape.shape = box_shape

	static_body.add_child(collision_shape)
	
	static_body.translate(Vector3(0, 0, 0))
	static_body.scale = Vector3(2, 2, 2)

	tile_instance.add_child(static_body)
	
	tile_parent.add_child(tile_instance)

func create_world(x, y):
	
	tile_parent = Node3D.new()
	get_parent().get_parent().get_parent().add_child.call_deferred(tile_parent)
	
	tile_parent.position = Vector3((x - 1) * 0.5, 0, (y - 1) * 0.5)
	
	for i in range(y):
		for j in range(x):
			create_tile(j - (x - 1) * 0.5, i - (y - 1) * 0.5)
			
	var plane: MeshInstance3D = get_parent().get_parent().get_parent().get_node("Ocean")
	var ocean: PlaneMesh = plane.mesh
	ocean.size = Vector2(x * 3, y * 3)
	plane.global_transform.origin = Vector3((x - (x * 0.5)), 0, (y - (y * 0.5)))
	
	ocean_plane = plane

func _ready():
	create_world(10, 10)

func _process(delta):
	var r = rotation_speed * delta

	if tile_parent:
		tile_parent.rotate_y(r)
		
	if ocean_plane:
		ocean_plane.rotate_y(r)
