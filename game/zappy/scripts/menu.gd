extends Control

func _ready():
	pass

func _on_start_btn_pressed() -> void:
	get_tree().change_scene_to_file("res://scenes/main.tscn")

func _on_quit_btn_pressed() -> void:
	get_tree().quit()
