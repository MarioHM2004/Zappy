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

func create_food(x, y):
	var food_scene = preload("res://scenes/sprites/food.tscn")
	var food_instance = food_scene.instantiate()
	food_instance.position = Vector3(x, 1.7, y)
	food_instance.scale = Vector3(0.5, 0.5, 0.5)
	var static_body = StaticBody3D.new()

	var box_shape = BoxShape3D.new()
	box_shape.extents = Vector3(0.5, 0.5, 0.5)
	
	static_body.translate(Vector3(0, 0, 0))
	static_body.scale = Vector3(1, 1, 1)

	food_instance.add_child(static_body)
	
	add_child(food_instance)

func create_egg(x, y):
	var egg_scene = preload("res://scenes/sprites/egg.tscn")
	var egg_instance = egg_scene.instantiate()
	egg_instance.position = Vector3(x, 1.7, y)
	egg_instance.scale = Vector3(0.5, 0.5, 0.5)
	var static_body = StaticBody3D.new()

	var box_shape = BoxShape3D.new()
	box_shape.extents = Vector3(0.5, 0.5, 0.5)

	static_body.translate(Vector3(0, 0, 0))
	static_body.scale = Vector3(1, 1, 1)

	egg_instance.add_child(static_body)
	
	add_child(egg_instance)
	
func create_linemate(x, y):
	var linemate_scene = preload("res://scenes/sprites/linemate.tscn")
	var linemate_instance = linemate_scene.instantiate()
	linemate_instance.position = Vector3(x, 1.7, y)
	linemate_instance.scale = Vector3(0.5, 0.5, 0.5)
	var static_body = StaticBody3D.new()

	var box_shape = BoxShape3D.new()
	box_shape.extents = Vector3(0.5, 0.5, 0.5)

	static_body.translate(Vector3(0, 0, 0))
	static_body.scale = Vector3(1, 1, 1)

	linemate_instance.add_child(static_body)
	
	add_child(linemate_instance)
	
func create_mendiane(x, y):
	var mendiane_scene = preload("res://scenes/sprites/mendiane.tscn")
	var mendiane_instance = mendiane_scene.instantiate()
	mendiane_instance.position = Vector3(x, 1.7, y)
	mendiane_instance.scale = Vector3(0.5, 0.5, 0.5)
	var static_body = StaticBody3D.new()

	var box_shape = BoxShape3D.new()
	box_shape.extents = Vector3(0.5, 0.5, 0.5)

	static_body.translate(Vector3(0, 0, 0))
	static_body.scale = Vector3(1, 1, 1)

	mendiane_instance.add_child(static_body)
	
	add_child(mendiane_instance)

func create_phiras(x, y):
	var phiras_scene = preload("res://scenes/sprites/phiras.tscn")
	var phiras_instance = phiras_scene.instantiate()
	phiras_instance.position = Vector3(x, 1.7, y)
	phiras_instance.scale = Vector3(0.5, 0.5, 0.5)
	var static_body = StaticBody3D.new()

	var box_shape = BoxShape3D.new()
	box_shape.extents = Vector3(0.5, 0.5, 0.5)

	static_body.translate(Vector3(0, 0, 0))
	static_body.scale = Vector3(1, 1, 1)

	phiras_instance.add_child(static_body)
	
	add_child(phiras_instance)
	
func create_sibur(x, y):
	var sibur_scene = preload("res://scenes/sprites/sibur.tscn")
	var sibur_instance = sibur_scene.instantiate()
	sibur_instance.position = Vector3(x, 1.7, y)
	sibur_instance.scale = Vector3(0.5, 0.5, 0.5)
	var static_body = StaticBody3D.new()

	var box_shape = BoxShape3D.new()
	box_shape.extents = Vector3(0.5, 0.5, 0.5)

	static_body.translate(Vector3(0, 0, 0))
	static_body.scale = Vector3(1, 1, 1)

	sibur_instance.add_child(static_body)
	
	add_child(sibur_instance)
	
func create_thystame(x, y):
	var thystame_scene = preload("res://scenes/sprites/thystame.tscn")
	var thystame_instance = thystame_scene.instantiate()
	thystame_instance.position = Vector3(x, 1.7, y)
	thystame_instance.scale = Vector3(0.5, 0.5, 0.5)
	var static_body = StaticBody3D.new()

	var box_shape = BoxShape3D.new()
	box_shape.extents = Vector3(0.5, 0.5, 0.5)

	static_body.translate(Vector3(0, 0, 0))
	static_body.scale = Vector3(1, 1, 1)

	thystame_instance.add_child(static_body)
	
	add_child(thystame_instance)

func create_world(x, y):
	for i in range(y):
		for j in range(x):
			create_tile(j, i)
			
	var plane: MeshInstance3D = get_node("Ocean")
	var ocean: PlaneMesh = get_node("Ocean").mesh
	ocean.size = Vector2(x * 2, y * 2)
	plane.global_transform.origin = Vector3((x - (x * 0.5)), 0, (y - (y * 0.5)))

func _on_genesis_wsize(x, y):
	create_world(x, y)
