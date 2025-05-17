extends Control

@export var developers: Array[Dictionary] = [
	{
		"name": "EGOBR",
		"photo": preload("res://resources/images/EGOBR.jpg"),
		"github": "https://github.com/2blackhole"
	},
	{
		"name": "Valerian",
		"photo": preload("res://resources/images/VALERIAN.jpg"),
		"github": "https://github.com/Molingen"
	}
]

@onready var cards_container: HBoxContainer = $TextureRect/HBoxContainer

func _ready():
	var label = $TextureRect/Label
	
	# якоря
	label.anchor_left = 0.5
	label.anchor_right = 0.5
	label.anchor_top = 0.0
	label.anchor_bottom = 0.0
	
	# Смещение (чтобы текст не уезжал)
	label.offset_left = -100
	label.offset_right = 100
	label.offset_top = 20
	label.offset_bottom = 20 + label.size.y
	
	label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	
	_update_font_size()
	get_viewport().connect("size_changed", _update_font_size)
	
	for child in cards_container.get_children():
		child.queue_free()
	
	await get_tree().process_frame
	
	cards_container.alignment = BoxContainer.ALIGNMENT_CENTER
	cards_container.add_theme_constant_override("separation", get_viewport_rect().size.x * 0.44)
	
	var card_scene = preload("res://ui/for_creators/developer_card.tscn")
	
	for dev in developers:
		if dev["photo"] == null:
			print("ERROR: Photo not loaded for ", dev["name"])
		else:
			print("Photo loaded successfully for ", dev["name"])
		var card = card_scene.instantiate()
		card.developer_name = dev["name"]
		card.photo = dev["photo"]
		card.github_url = dev["github"]
		cards_container.add_child(card)
	
	print("Created cards: ", cards_container.get_child_count())
	print("Developers in array: ", developers.size())
	print("Actual cards created: ", cards_container.get_children().size())
	print("All children: ", cards_container.get_children())

func _update_font_size():
	var label = $TextureRect/Label
	var viewport = get_viewport()
	
	var base_size = 50.0
	var min_size = 32.0
	var max_size = 64.0
	
	var scale_factor = viewport.size.x / 1920.0
	var new_size = clamp(base_size * scale_factor, min_size, max_size)
	
	label.add_theme_font_size_override("font_size", new_size)

func _input(event):
	if event.is_action_pressed("ui_cancel"):
		get_tree().change_scene_to_file("res://ui/main_menu.tscn")
