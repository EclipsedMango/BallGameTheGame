#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

const vec2 size = vec2(1920, 1080);   // Framebuffer size
const float samples = 13.0;          // Pixels per axis; higher = bigger glow, worse performance
const float quality = 2.5;          // Defines size factor: Lower = smaller glow, better quality

void main() {
    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1) / size * quality;

    // Texel color fetching from texture sampler
    vec4 source = texture(texture0, fragTexCoord);

    const int range = 3;            // should be = (samples - 1)/2;

    for (int x = -range; x <= range; x++)  {
        for (int y = -range; y <= range; y++)  {
            vec4 cool = texture(texture0, fragTexCoord + vec2(x, y) * sizeFactor);
            float nice = (cool.r + cool.g + cool.b) / 3.0;
            if (nice > 0.2) {
                sum += cool;
            }
        }
    }

    // Calculate final fragment color
    finalColor = ((sum / (samples * samples)) + source) * colDiffuse;
}