extends TabBar
@onready var check_box: CheckBox = $MarginContainer/VBoxContainer/CheckBox

var time_acum = 0

func _process(delta: float) -> void:
	time_acum += delta
	if time_acum >= 2:
		if check_box.button_pressed == false:
			check_box.button_pressed = true
