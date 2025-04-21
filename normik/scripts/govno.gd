extends Node3D

@export var cameras: Array[Camera3D] = []

@export var switch_time: float = 3.0  

var current_camera_index: int = 0
var timer: float = 0.0

func _ready():
	if cameras.size() > 0:
		cameras[0].current = true

func _process(delta):
	timer += delta
	
	if timer >= switch_time:
		timer = 0.0
		switch_to_next_camera()

func switch_to_next_camera():
	if cameras.size() == 0:
		return
	
	cameras[current_camera_index].current = false
	
	current_camera_index = (current_camera_index + 1) % cameras.size()
	
	cameras[current_camera_index].current = true
	print("Переключено на камеру: ", cameras[current_camera_index].name)
