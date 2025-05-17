extends Control
var govno = 180;
signal time_ended;

@onready var score = $Score as Label
@onready var time_left = $TimeLeft as Label

func _ready() -> void:
	var target_node = get_parent().get_node("CanvasLayer")
	if !target_node:
		push_error("GOVNO")
	time_ended.connect(target_node._on_time_ended)
		
		
func _process(delta: float) -> void:
	score.text = "Score: " + str($"..".get_score())
	var minut = str(int(govno / 60))
	var sekund = int(govno) % 60;
	if sekund <= 9:
		sekund = str("0" + str(sekund))
	sekund = str(sekund)
	time_left.text = "Time left - " + minut + ":" + sekund;
	govno -= delta
	if govno <= 0:
		emit_signal("time_ended")
