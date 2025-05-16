extends Control

@onready var label = $Label as Label

func _process(_delta: float) -> void:
	label.text = "Score: " + str($"..".get_score())
