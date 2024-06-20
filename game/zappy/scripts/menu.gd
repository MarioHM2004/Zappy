extends Control

signal server_address(address: String, port: int);

@onready var StartBtn = $MarginContainer/VBoxContainer/StartBtn
@onready var QuitBtn = $MarginContainer/VBoxContainer/QuitBtn


func _ready():
	pass

func _on_start_btn_pressed() -> void:
	var server_ip: LineEdit = get_node("MarginContainer/VBoxContainer/ServerIp")
	var server_port: LineEdit = get_node("MarginContainer/VBoxContainer/ServerPort")
	get_tree().change_scene_to_file("res://scenes/main.tscn")
	# TODO: set ip and port in code
	# TODO: check server is up 
	
func _on_quit_btn_pressed() -> void:
	get_tree().quit()
