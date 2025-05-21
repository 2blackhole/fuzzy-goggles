# global.gd
extends Node

var return_scene_path: String = "res://ui/main_menu.tscn" 

const AUDIO_SETTINGS_PATH = "user://audio_settings.cfg"

func _ready():
	load_audio_settings()

func save_audio_settings():
	var settings = {
		"master_mute": AudioServer.is_bus_mute(AudioServer.get_bus_index("Master")),
		"master_volume": db_to_linear(AudioServer.get_bus_volume_db(AudioServer.get_bus_index("Master"))),
		"music_volume": db_to_linear(AudioServer.get_bus_volume_db(AudioServer.get_bus_index("Music"))),
		"sfx_volume": db_to_linear(AudioServer.get_bus_volume_db(AudioServer.get_bus_index("Sfx")))
	}
	
	var file = FileAccess.open(AUDIO_SETTINGS_PATH, FileAccess.WRITE)
	file.store_var(settings)

func load_audio_settings():
	if not FileAccess.file_exists(AUDIO_SETTINGS_PATH):
		set_default_audio_settings()
		return
	
	var file = FileAccess.open(AUDIO_SETTINGS_PATH, FileAccess.READ)
	if file == null:
		push_error("Failed to load audio settings")
		set_default_audio_settings()
		return
	
	var settings = file.get_var()
	
	AudioServer.set_bus_mute(AudioServer.get_bus_index("Master"), settings.get("master_mute", false))
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Master"), linear_to_db(settings.get("master_volume", 1.0)))
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Music"), linear_to_db(settings.get("music_volume", 0.8)))
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Sfx"), linear_to_db(settings.get("sfx_volume", 0.9)))

func set_default_audio_settings():
	AudioServer.set_bus_mute(AudioServer.get_bus_index("Master"), false)
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Master"), linear_to_db(1.0))
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Music"), linear_to_db(0.8))
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Sfx"), linear_to_db(0.9))
	save_audio_settings()
