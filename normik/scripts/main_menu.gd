extends Control

func _ready():
	var exit_menu = $MarginContainer/VBoxContainer/Exit
	if exit_menu:
		var popup = exit_menu.get_popup()
		if popup:
			popup.connect("id_pressed", _on_Exit_menu_selected)
		else:
			push_error("PopupMenu у Exit не найден!")
	else:
		push_error("Кнопка Exit не найдена или не MenuButton!")

func _on_Exit_menu_selected(id):
	match id:
		0:
			print("SISKI")
			get_tree().change_scene_to_file("res://main_menu.tscn")
		1:
			get_tree().quit()

func _on_IGRAT_V_IGRU_pressed_ching_chong_bing():
	get_tree().change_scene_to_file("res://level.tscn")

func _on_nekiy_prostofilia_pressed():
	pass
