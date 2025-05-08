#extends AnomalyManager
#
#var govno = 0
#var c = 0
#
## Called when the node enters the scene tree for the first time.
#
## Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta: float) -> void:
	#govno += delta;
	#if govno > 5:
		#superpuperbingcheling_yehaopien_bingchelin(c)
		#govno = 0
		#c+=1
