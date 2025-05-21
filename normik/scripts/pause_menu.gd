# pause_menu.gd
extends CanvasLayer
var time = 0
var acum = 0
var pomehi = load("res://govninga/pomehi.ogv")
var anomaly_ef = load("res://govninga/anomaly_hit.ogv")
@onready var level: GameManager = $".."
@onready var camera_manager: CameraManager = $"../CameraManager"
@onready var video_stream_player: VideoStreamPlayer = $"../VideoStreamPlayer"
@onready var score: Control = $"../Score"
@onready var audio_stream_player: AudioStreamPlayer = $"../AudioStreamPlayer"

var change_camera_sound = load("res://music/audiocheck.net_whitenoise.wav")
var anomaly_hit_sound = load("res://music/Fart with reverb sound effect.mp3")

func _on_time_ended() -> void:
	get_tree().change_scene_to_file("res://ui/player_won.tscn")
	

func camera_switched(_govno) -> void:
	video_stream_player.visible = true
	audio_stream_player.stream = change_camera_sound
	audio_stream_player.play()

func anomaly_hit(_govno) -> void:
	video_stream_player.stream = anomaly_ef
	video_stream_player.play()
	video_stream_player.visible = true
	audio_stream_player.stream = anomaly_hit_sound
	audio_stream_player.play()
	
	
func total_active_anomalies_reached(_govno) -> void:
	get_tree().change_scene_to_file("res://ui/anomalies_won.tscn")
	
	
func all_anomalies_deactivated(_govno) -> void:
	get_tree().change_scene_to_file("res://ui/player_won.tscn")
	
	
func _ready() -> void:
	hide()
	get_tree().paused = false
	process_mode = Node.PROCESS_MODE_ALWAYS
	camera_manager.camera_switched.connect(camera_switched)
	camera_manager.anomaly_hit.connect(anomaly_hit)
	level.total_active_anomalies_reached.connect(total_active_anomalies_reached)
	level.all_anomalies_deactivated.connect(all_anomalies_deactivated)
	
	

func _input(event):
	var tutorial_active = false
	for node in get_tree().get_nodes_in_group("tutorial"):
		if node.visible:
			tutorial_active = true
			break
	
	if event.is_action_pressed("ui_cancel") and not tutorial_active:
		if visible:
			hide()
			get_tree().paused = false
		else:
			show()
			get_tree().paused = true
			Global.return_scene_path = get_tree().current_scene.scene_file_path

func _process(delta: float) -> void:
	var cont = $ColorRect/MarginContainer
	time += delta
	cont.rotation_degrees += abs(sin(time)) / 2
	cont.scale = Vector2(abs(sin(time)) * 2.4, abs(cos(time)) * 3.4)
	
	if video_stream_player.visible:
		acum+=delta
		if acum > 0.3:
			acum = 0
			audio_stream_player.stop()
			video_stream_player.hide()
			video_stream_player.stream = pomehi
			video_stream_player.play()

func _on_continue_pressed() -> void:
	AudioManager.play_sfx("res://music/ekh.mp3")
	get_tree().paused = false
	hide()

#func _on_settings_pressed() -> void:
	## Сохраняем текущую сцену перед переходом в настройки
	#Global.return_scene_path = get_tree().current_scene.scene_file_path
	#get_tree().change_scene_to_file("res://ui/settings_menu.tscn")

func _on_exit_to_menu_pressed() -> void:
	AudioManager.play_sfx("res://music/ekh.mp3")
	get_tree().paused = false
	hide()
	get_tree().change_scene_to_file("res://ui/main_menu.tscn")
	
