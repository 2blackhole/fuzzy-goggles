extends CanvasLayer
var time = 0;
func _ready() -> void:
	hide();
	get_tree().paused = false;
	process_mode = Node.PROCESS_MODE_ALWAYS  # Это позволит ноду обрабатывать ввод даже в паузе

func _input(event):
	if event.is_action_pressed("ui_cancel"):
		print('jopa')
		if (visible):
			hide()
			get_tree().paused = false
		else:
			show()
			get_tree().paused = true

func _process(delta: float) -> void:
	var cont = $ColorRect/MarginContainer;
	time += delta;
	cont.rotation_degrees += abs(sin(time)) / 2;
	cont.scale = Vector2(abs(sin(time)) * 2.4, abs(cos(time)) * 3.4)

func _on_continue_pressed() -> void:
	get_tree().paused = false
	hide()


func _on_settings_pressed() -> void:
	pass # Replace with function body.


func _on_exit_to_menu_pressed() -> void:
	get_tree().paused = false
	hide()
	get_tree().change_scene_to_file("res://main_menu.tscn")
