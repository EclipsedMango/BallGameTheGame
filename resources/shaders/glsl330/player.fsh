#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 velocity;
uniform vec3 playerColor;
uniform vec3 playerOutlineColor;

// Output fragment color
out vec4 finalColor;

vec2 rotate(vec2 v, float a) {
    float s = sin(a);
    float c = cos(a);
    mat2 m = mat2(c, s, -s, c);
    return m * v;
}

void main() {
    float squishAmount = clamp(1800.0 / length(velocity), 0.45, 1.0);

    float theta = atan(velocity.x, velocity.y);
    float dist = length(rotate(fragTexCoord - 0.5, theta) * vec2(1.0 / squishAmount, squishAmount));

    if (dist < 0.1) {
        finalColor = vec4(playerColor, 1.0);
    } else if (dist < 0.125) {
        finalColor = vec4(playerOutlineColor, 1.0);
    } else {
        finalColor = vec4(vec3(1.0), 0.0);
    }
}