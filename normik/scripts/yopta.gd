extends AnomalyManager

var govno = 0
# Called when the node enters the scene tree for the first time.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	govno += delta;
	if govno > 10:
		superpuperbingcheling_yehaopien_bingchelin(5)
		govno = 0
