# main_menu.gd
extends Control

func _ready():
	var exit_menu = $TextureRect/MarginContainer/VBoxContainer/Exit
	if exit_menu:
		var popup = exit_menu.get_popup()
		if popup:
			popup.connect("id_pressed", _on_Exit_menu_selected)
		else:
			push_error("PopupMenu у Exit не найден!")
	else:
		push_error("Кнопка Exit не найдена или не MenuButton!")
	
	# Устанавливаем сцену возврата как главное меню
	Global.return_scene_path = "res://ui/main_menu.tscn"

func _on_Exit_menu_selected(id):
	match id:
		0:
			get_tree().change_scene_to_file("res://ui/main_menu.tscn")
		1:
			get_tree().quit()

func _on_IGRAT_V_IGRU_pressed_ching_chong_bing():
	get_tree().change_scene_to_file("res://level.tscn")

func _on_nekiy_prostofilia_pressed():
	get_tree().change_scene_to_file("res://ui/for_creators/game_created_by.tscn")
	

func _on_settings_pressed() -> void:
	# Перед переходом в настройки сохраняем текущую сцену
	Global.return_scene_path = "res://ui/main_menu.tscn"
	get_tree().change_scene_to_file("res://ui/settings_menu.tscn")
