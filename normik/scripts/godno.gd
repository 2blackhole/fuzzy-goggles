extends Node

@onready var anomaly: Anomaly = get_node("Anomaly")
var govno = 0;
var flag = 0


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	#anomaly.deactivate()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	govno += delta

	if (govno >= 3):
		if (flag % 2 == 0):
			anomaly.deactivate()
			flag+=1
		else:
			anomaly.activate()
			flag+=1
		govno = 0
