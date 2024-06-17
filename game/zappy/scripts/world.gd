extends Node3D

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
	
	add_child(tile_instance)

func _on_genesis_wsize(x, y):
	var start_x = -x / 2
	var start_y = -y / 2
	
	for i in range(start_y, start_y + y):
		for j in range(start_x, start_x + x):
			create_tile(
				j + 0.5 if x % 2 == 0 else float(j),
				i + 0.5 if y % 2 == 0 else float(i)
			)
			
	var ocean: PlaneMesh = get_node("Ocean").mesh
	ocean.size = Vector2(x * 2, y * 2)
