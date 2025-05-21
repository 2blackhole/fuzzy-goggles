class_name HotkeyRebindButton
extends Control

@onready var label = $HBoxContainer/Label as Label
@onready var button = $HBoxContainer/Button as Button

@export var action_name : String = "ui_left"

func _ready() -> void:
	set_process_unhandled_key_input(false)
	set_action_name()
	
	
func set_action_name() -> void:
	label.text = "Пусто"
	
	match action_name:
		"ui_left":
			label.text = "Переключиться ТУДА"
			button.text = "->"
		"ui_right":
			label.text = "Переключиться СЮДА"
			button.text = "<-"
		"ui_cancel":
			label.text = "Меню паузы / Выход"
			button.text = "Esc"
	
