extends TabBar

@onready var check_box: CheckBox = $MarginContainer/VBoxContainer/CheckBox
@onready var sfx: HSlider = $MarginContainer/VBoxContainer/Sfx
@onready var music: HSlider = $MarginContainer/VBoxContainer/Music

func _ready() -> void:
	music.value = db_to_linear(AudioServer.get_bus_volume_db(AudioServer.get_bus_index("Music")))
	sfx.value = db_to_linear(AudioServer.get_bus_volume_db(AudioServer.get_bus_index("Sfx")))
	check_box.button_pressed = AudioServer.is_bus_mute(AudioServer.get_bus_index("Master"))
	
func _on_music_value_changed(value: float) -> void:
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Music"), linear_to_db(value))
	Global.save_audio_settings()

func _on_sfx_value_changed(value: float) -> void:
	AudioServer.set_bus_volume_db(AudioServer.get_bus_index("Sfx"), linear_to_db(value))
	Global.save_audio_settings()
	
func _on_check_box_toggled(toggled_on: bool) -> void:
	AudioServer.set_bus_mute(AudioServer.get_bus_index("Master"), toggled_on)
	Global.save_audio_settings()
