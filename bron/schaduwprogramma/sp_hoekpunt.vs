#version 330 core
layout (location = 0) in vec3 vertex; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec2 texture; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 zicht;
uniform mat4 projectie;

uniform ivec2 formaat;
uniform ivec2 vak;

void main()
{
    gl_Position = projectie * zicht * model * vec4(vertex, 1.0);
    TexCoords = vec2((texture.x + vak.x ) / formaat.x, 1.0 - (texture.y + vak.y) / formaat.y);
}
