extends Control

signal error_logs(error: String)

@onready var errorLabel = $VBoxContainer/ErrorLabel as Label

var last_error_time: float = 0.0

func _ready():
	var timer = Timer.new()
	timer.name = "Timer"
	timer.wait_time = 5.0
	timer.timeout.connect(_on_timer_timeout)
	add_child(timer)

func _on_timer_timeout():
	if Time.get_unix_time_from_system() - last_error_time >= 5.0:
		errorLabel.text = ""

func _on_genesis_last_error(error: String):
	var timer = get_node("Timer")
	timer.start()

	var current_time = Time.get_unix_time_from_system()
	errorLabel.text = Time.get_time_string_from_system() + " " + error
	last_error_time = current_time

