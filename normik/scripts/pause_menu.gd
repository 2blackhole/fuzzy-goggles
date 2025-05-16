# pause_menu.gd
extends CanvasLayer
var time = 0

func _ready() -> void:
	hide()
	get_tree().paused = false
	process_mode = Node.PROCESS_MODE_ALWAYS

func _input(event):
	if event.is_action_pressed("ui_cancel"):
		if visible:
			hide()
			get_tree().paused = false
		else:
			show()
			get_tree().paused = true
			# Устанавливаем сцену возврата как текущую сцену
			Global.return_scene_path = get_tree().current_scene.scene_file_path

func _process(delta: float) -> void:
	var cont = $ColorRect/MarginContainer
	time += delta
	cont.rotation_degrees += abs(sin(time)) / 2
	cont.scale = Vector2(abs(sin(time)) * 2.4, abs(cos(time)) * 3.4)

func _on_continue_pressed() -> void:
	get_tree().paused = false
	hide()

func _on_settings_pressed() -> void:
	# Сохраняем текущую сцену перед переходом в настройки
	Global.return_scene_path = get_tree().current_scene.scene_file_path
	get_tree().change_scene_to_file("res://ui/settings_menu.tscn")

func _on_exit_to_menu_pressed() -> void:
	get_tree().paused = false
	hide()
	get_tree().change_scene_to_file("res://ui/main_menu.tscn")
