# settings_menu.gd
extends Control

func _ready():
	# Убедитесь, что меню настроек не ставит игру на паузу
	get_tree().paused = false

func _on_exit_pressed() -> void:
	# Возвращаемся на сцену, которая была сохранена в Global
	get_tree().change_scene_to_file(Global.return_scene_path)
