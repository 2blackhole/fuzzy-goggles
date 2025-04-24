extends Node

@onready var camera_manager: CameraManager = get_node("../CameraManager")

func _ready():
	if not camera_manager:
		push_error("CameraManager not found! Check scene structure.")
		return
	
	var cameras = []
	var parent = get_parent()
	
	for child in parent.get_children():
		if child is Camera3D:
			cameras.append(child)
			print("Found camera: ", child.name)
	
	if cameras.is_empty():
		push_error("No cameras found in scene!")
		return
	
	for camera in cameras:
		camera_manager.register_camera(camera)
	
	print("Camera system initialized. Total cameras: ", cameras.size())

func _input(event):
	if event.is_action_pressed("ui_right"):
		camera_manager.switch_to_next_camera()
	elif event.is_action_pressed("ui_left"):
		camera_manager.switch_to_previous_camera()
