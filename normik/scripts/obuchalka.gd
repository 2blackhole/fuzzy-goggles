extends CanvasLayer

func _ready():
	add_to_group("tutorial")
	get_tree().paused = true
	show()
	process_mode = Node.PROCESS_MODE_ALWAYS
	
func _on_button_pressed() -> void:
	remove_from_group("tutorial")
	hide()
	get_tree().paused = false
	queue_free()
