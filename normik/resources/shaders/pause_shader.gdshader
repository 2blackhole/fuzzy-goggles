shader_type canvas_item;

uniform float blur_amount : hint_range(0, 10) = 2.0;
uniform vec4 bg_color : source_color = vec4(0.0, 0.0, 0.0, 0.8);

void fragment() {
    COLOR = bg_color; // Просто показывает цвет с альфа-каналом
}