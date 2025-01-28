#version 330 core
layout (location = 0) in vec3 vertex; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec2 texture; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 tiles;
uniform vec2 tcoord;

void main()
{
    gl_Position = projection * view * model * vec4(vertex, 1.0);
    TexCoords = vec2((tcoord.x + texture.x) / tiles.x, 1.0 - (texture.y + tcoord.y) / tiles.y);
}
