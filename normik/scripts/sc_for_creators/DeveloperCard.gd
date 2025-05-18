extends Control

@export var developer_name: String = "Developer"
@export var photo: Texture2D
@export var github_url: String = "https://github.com"

@onready var photo_texture: TextureRect = $Panel/VBoxContainer/TextureRect
@onready var name_label: Label = $Panel/VBoxContainer/Label
@onready var github_button: Button = $Panel/VBoxContainer/Button

func _ready():
	if photo:
		photo_texture.texture = photo
		photo_texture.visible = true
		photo_texture.custom_minimum_size = Vector2(256+128, 256+128)  # Фиксированный минимальный размер
		photo_texture.expand_mode = TextureRect.EXPAND_IGNORE_SIZE  # Для правильного масштабирования
		photo_texture.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED  # Сохраняем пропорции
	else:
		photo_texture.visible = false
		var placeholder = ColorRect.new()
		placeholder.color = Color(0.2, 0.2, 0.2)
		placeholder.custom_minimum_size = Vector2(256, 256)
		photo_texture.add_child(placeholder)
		
	if developer_name:
		name_label.text = developer_name
		name_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	else:
		name_label.text = "Unknown Developer"
		push_warning("Developer name not specified")
		
	github_button.text = "GitHub"
	github_button.custom_minimum_size = Vector2(80, 30)
	github_button.disabled = github_url.is_empty()
	
	if github_url.is_empty():
		push_warning("GitHub URL not provided for: %s" % developer_name)
	else:
		github_button.tooltip_text = github_url
	
func _on_button_pressed():
	AudioManager.play_sfx("res://music/ekh.mp3")
	OS.shell_open(github_url)
