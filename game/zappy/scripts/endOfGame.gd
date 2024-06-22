extends Control

signal server_address(address: String, port: int);

@onready var HomeBtn = $MarginContainer/VBoxContainer/HomeBtn as Button
@onready var QuitBtn = $MarginContainer/VBoxContainer/QuitBtn as Button


func _ready():
	handle_connecting_signals()

func _on_home_btn_pressed() -> void:
	get_tree().change_scene_to_file("res://scenes/menu.tscn")
	
func _on_quit_btn_pressed() -> void:
	get_tree().quit()

func handle_connecting_signals() -> void:
	HomeBtn.button_down.connect(_on_home_btn_pressed)
	QuitBtn.button_down.connect(_on_quit_btn_pressed)
