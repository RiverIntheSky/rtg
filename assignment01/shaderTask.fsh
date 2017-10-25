in vec2 E;

out vec3 fColor;

uniform sampler2D uTexture;

void main()
{
    fColor = texture(uTexture, E).rgb;
    if (fColor.r < 0.01) discard;
}
