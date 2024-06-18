shader_type spatial;

uniform vec3 OLDCOLORS[4] : source_color;
uniform vec3 NEWCOLORS[4] : source_color;

uniform sampler2D texture_albedo : source_color;

bool colors_are_close(vec3 color1, vec3 color2, float threshold) {
    return distance(color1, color2) < threshold;
}

void fragment() {
    vec3 curr_color = texture(texture_albedo, UV).rgb;
    float threshold = 0.1;
    vec3 new_color = curr_color;

    for (int i = 0; i < 4; ++i) {
        if (colors_are_close(curr_color, OLDCOLORS[i], threshold)) {
            new_color = NEWCOLORS[i];
            break;
        }
    }

    ALBEDO = new_color;
}