extends Node

# Музыкальный плеер
var music_player: AudioStreamPlayer
# Плееры для звуковых эффектов
var sfx_players := []
const MAX_SFX_PLAYERS := 5

func _ready():
	# Инициализация музыкального плеера
	music_player = AudioStreamPlayer.new()
	music_player.name = "BackgroundMusic"
	music_player.bus = "Music"
	music_player.autoplay = true
	add_child(music_player)
	
	# Загрузка музыки
	var music = load("res://music/Lil Phoebe (Acordian) - by Bismack Biyombo.mp3")
	if music:
		music_player.stream = music
		music_player.play()
	else:
		printerr("Музыка не найдена")
	
	# Инициализация SFX-плееров
	for i in MAX_SFX_PLAYERS:
		var player = AudioStreamPlayer.new()
		player.bus = "Sfx"
		add_child(player)
		sfx_players.append(player)

func _process(delta: float) -> void:
	# Управление музыкой в зависимости от сцены
	if str(get_tree().current_scene).contains("W"):  # Более надежная проверка
		stop_music()
	else:
		play_music()

# Функции управления музыкой
func stop_music():
	if music_player.playing:
		music_player.stop()

func play_music():
	if not music_player.playing and music_player.stream:
		music_player.play()

# Функции для звуков кнопок
func play_sfx(sound_path: String):
	var sound = load(sound_path)
	if not sound:
		printerr("SFX не найден:", sound_path)
		return
	
	# Ищем свободный плеер
	for player in sfx_players:
		if not player.playing:
			player.stream = sound
			player.play()
			return
	
	# Если все заняты, создаем временный плеер
	var temp_player = AudioStreamPlayer.new()
	temp_player.bus = "SFX"
	add_child(temp_player)
	temp_player.stream = sound
	temp_player.play()
	await temp_player.finishedAudioManager.play_sfx.bind("res://music/ekh.mp3")
	temp_player.queue_free()
