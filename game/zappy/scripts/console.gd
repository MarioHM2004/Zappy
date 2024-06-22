extends Control

signal server_command(command: String);
signal console_focus(active: bool);

@onready var sendBtn = $MarginContainer/VBoxContainer/HBoxContainer/sendBtn as Button
@onready var lastCmd = $MarginContainer/VBoxContainer/LastCmd as Label

func _ready():
	handle_connecting_signals()

func _on_send_btn_pressed() -> void:
	var textbox: LineEdit = get_node("MarginContainer/VBoxContainer/HBoxContainer/Console")
	var command: String = textbox.get_text()
	textbox.text = "";
	server_command.emit(command)

func handle_connecting_signals() -> void:
	sendBtn.button_down.connect(_on_send_btn_pressed)

func _on_code_edit_focus_entered():
	console_focus.emit(true);

func _on_code_edit_focus_exited():
	console_focus.emit(false);

func _on_genesis_last_command(command):
	lastCmd.text = command;
