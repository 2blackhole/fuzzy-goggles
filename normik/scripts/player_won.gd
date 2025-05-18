extends Control


func _on_button_pressed() -> void:
	AudioManager.play_sfx("res://music/ekh.mp3")
	get_tree().change_scene_to_file("res://ui/main_menu.tscn")
