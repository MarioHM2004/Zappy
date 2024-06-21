extends Control

signal server_address(address: String, port: String);

@onready var ConnectBtn = $MarginContainer/VBoxContainer/ConnectBtn as Button

func _ready():
	handle_connecting_signals()

func _on_connect_btn_pressed() -> void:
	var server_ip: String = get_node("MarginContainer/VBoxContainer/ServerIp").get_text()
	var server_port: String = get_node("MarginContainer/VBoxContainer/ServerPort").get_text()
	server_address.emit(server_ip, server_port)

func handle_connecting_signals() -> void:
	ConnectBtn.button_down.connect(_on_connect_btn_pressed)
