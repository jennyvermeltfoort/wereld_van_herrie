#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "schaduwprogramma.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 576;
const float SCR_ASPECT = (float)SCR_WIDTH / (float)SCR_HEIGHT;

#define WORLD_X 10
#define WORLD_Z 20
#define WORLD_S WORLD_X *WORLD_Z
int world[WORLD_Z][WORLD_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
vec3s player = {.x = 5.0f, .y = 0.0f, .z = 5.0f};
vec3s player2 = {.x = 2.0f, .y = 0.0f, .z = 5.0f};
unsigned int texture1;
unsigned int texture2;

bool press_w = false;
bool press_s = false;
bool press_a = false;
bool press_d = false;

bool destroy = false;

bool press_up = false;
bool press_down = false;
bool press_left = false;
bool press_right = false;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) press_w = true;
    if (key == GLFW_KEY_A && action == GLFW_PRESS) press_a = true;
    if (key == GLFW_KEY_S && action == GLFW_PRESS) press_s = true;
    if (key == GLFW_KEY_D && action == GLFW_PRESS) press_d = true;

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) destroy = true;

    if (key == GLFW_KEY_UP && action == GLFW_PRESS) press_up = true;
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) press_down = true;
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) press_left = true;
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) press_right = true;

    if (key == GLFW_KEY_W && action == GLFW_RELEASE) press_w = false;
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) press_a = false;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) press_s = false;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) press_d = false;

    if (key == GLFW_KEY_UP && action == GLFW_RELEASE) press_up = false;
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) press_down = false;
    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) press_left = false;
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) press_right = false;
}

void draw_cube_walls(unsigned int sp, unsigned int vao, vec3s position,
                     unsigned int texture) {
    mat4s model = glms_mat4_identity();
    model = glms_translate(model, position);
    model = glms_scale(model, (vec3s){.x = 1.0f, .y = 2.0f, .z = 1.0f});
    int modelLoc = glGetUniformLocation(sp, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);

    int tilesLoc = glGetUniformLocation(sp, "tiles");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1f(tilesLoc, 3.0f);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

void draw_cube_top(unsigned int sp, unsigned int vao, vec3s position,
                   unsigned int texture) {
    mat4s model = glms_mat4_identity();
    model = glms_translate(model, position);
    int modelLoc = glGetUniformLocation(sp, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);

    int tilesLoc = glGetUniformLocation(sp, "tiles");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1f(tilesLoc, 3.0f);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 12, 18);
    glBindVertexArray(0);
}

void draw_sprite(unsigned int sp, unsigned int vao, vec3s position) {
    mat4s model = glms_mat4_identity();
    model = glms_translate(model, position);
    int modelLoc = glGetUniformLocation(sp, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void draw_player(vec3s position, unsigned int sp, unsigned int vao,
                 unsigned int texture) {
    int tilesLoc = glGetUniformLocation(sp, "tiles");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1f(tilesLoc, 1.0f);
    draw_sprite(sp, vao, position);
}

typedef struct {
    vec3s position;
    unsigned int id;
    unsigned int texture;
    unsigned char next;
    unsigned char prev;
} entity_t;

typedef struct {
    unsigned char count;
    unsigned char start;
    unsigned char end;
    entity_t list[256];
} world_entity_t;

entity_t world_entities[WORLD_Z][WORLD_X];

world_entity_t world_entities[WORLD_Z][WORLD_X] = {0};

unsigned char ent_add(vec3s position, unsigned int id, unsigned int texture) {
    world_entity_t *l = &world_entities[(int)position.z][(int)position.x];
    entity_t *e;
    do {
        e = &l->list[l->end++];
    } while (e->next != 0);
    unsigned int me = l->end - (unsigned char)1;
    e->position = position;
    e->id = id;
    e->texture = texture;
    e->next = l->end;
    l->list[e->next].prev = me;
    l->count++;
    return me;
}

void ent_remove(vec3s position, unsigned char index) {
    world_entity_t *l = &world_entities[(int)position.z][(int)position.x];
    entity_t *e = &l->list[index];
    entity_t *p = &l->list[e->prev];
    p->next = e->next;
    e->next = 0;
    l->count--;
    if (index == l->start) {
        l->start++;
        p->next = 0;
    }
}

void ent_draw(vec3s position, unsigned int sp, unsigned int vao) {
    world_entity_t *l = &world_entities[(int)position.z][(int)position.x];
    entity_t *e = &l->list[l->start];

    while (e->next != 0) {
        draw_player(e->position, sp, vao, e->texture);
        e = &l->list[e->next];
    }
}

void draw_world(unsigned int sp, unsigned int vao) {
    for (int z = 0; z < WORLD_Z; z++) {
        for (int x = WORLD_X - 1; x >= 0; x--) {
            int var = world[z][x];
            if (var == 1) {
                draw_cube_top(sp, vao, (vec3s){.x = x, .y = 1.0f, .z = z}, texture1);
                draw_cube_walls(sp, vao, (vec3s){.x = x, .y = 0.0f, .z = z}, texture1);
            } else if (var == 0) {
                draw_cube_top(sp, vao, (vec3s){.x = x, .y = -1.0f, .z = z}, texture1);
            }
            if ((z - 1) >= 0 && world_entities[z - 1][x].count != 0) {
                ent_draw((vec3s){.x = x, .y = 0.0f, .z = z - 1}, sp, vao);
            }
        }
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwSetWindowAspectRatio(window, SCR_WIDTH, SCR_HEIGHT);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
        return -1;
    }

    uint32_t sp = sp_maak_programma("bron/schaduwprogramma/sp_hoekpunt.vs",
                                    "bron/schaduwprogramma/sp_fragment.vs");

    unsigned int VBO, VAO, EBO;

    glfwSetKeyCallback(window, key_callback);
    glBindVertexArray(0);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    float vertices[] = {
        // right face
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  //
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  //
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  //
        // left face
        0.0f, 0.0f, 0.0f, 2.0f, 0.0f,  //
        0.0f, 1.0f, 0.0f, 2.0f, 1.0f,  //
        0.0f, 0.0f, 1.0f, 3.0f, 0.0f,  //
        0.0f, 1.0f, 1.0f, 3.0f, 1.0f,  //
        0.0f, 1.0f, 0.0f, 2.0f, 1.0f,  //
        0.0f, 0.0f, 1.0f, 3.0f, 0.0f,  //
        // top face
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        1.0f, 1.0f, 0.0f, 2.0f, 1.0f,  //
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
        1.0f, 1.0f, 1.0f, 2.0f, 0.0f,  //
        1.0f, 1.0f, 0.0f, 2.0f, 1.0f,  //
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nrChannels;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load("middelen/muur_map_1.png", &width, &height, &nrChannels, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // stbi_set_flip_vertically_on_load(true);
    data = stbi_load("middelen/speler_links_stil_1.png", &width, &height, &nrChannels, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    sp_gebruik(sp);

    vec3s color = {.r = 1.0f, .g = 1.0f, .b = 1.0f};

    mat4 projection;
    float pro_width = 12;
    glm_ortho(0.0f, pro_width * SCR_ASPECT, 0.0f, pro_width, 0.1f, 100.0f, projection);

    sp_uniform_zet_int(sp, "image", 0);
    int projectionLoc = glGetUniformLocation(sp, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (GLfloat *)&projection);

    float yaw = -45.0f;
    float pitch = -45.0f;
    float czup = sin(glm_rad(yaw));
    float cxup = cos(glm_rad(yaw));
    float czright = sin(glm_rad(90 + yaw));
    float cxright = cos(glm_rad(90 + yaw));
    vec3 direction = {cos(glm_rad(yaw)) * cos(glm_rad(pitch)), sin(glm_rad(pitch)),
                      sin(glm_rad(yaw)) * cos(glm_rad(pitch))};
    glm_vec3_normalize(direction);

    int colorLoc = glGetUniformLocation(sp, "spriteColor");
    int viewLoc = glGetUniformLocation(sp, "view");
    glUniform3fv(colorLoc, 1, (GLfloat *)&color);

    vec3s camera = {.x = 0.0f, .y = 2.0f, .z = 0.0f};

    unsigned char player_index = ent_add(player, 0, texture2);

    int bla = 1000;
    while (!glfwWindowShouldClose(window) && bla--) {
        processInput(window);

        glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (press_w) {
            camera.z += 0.2f * czup;
            camera.x += 0.2f * cxup;
        }
        if (press_a) {
            camera.z -= 0.2f * czright;
            camera.x -= 0.2f * cxright;
        }
        if (press_s) {
            camera.z -= 0.2f * czup;
            camera.x -= 0.2f * cxup;
        }
        if (press_d) {
            camera.z += 0.2f * czright;
            camera.x += 0.2f * cxright;
        }

        float move = 0.1f;
        bool moved = false;
        vec3s player_old = player;
        if (press_up && world[(int)(player.z + 0.8f)][(int)(player.x)] == 0 &&
            world[(int)(player.z + 0.8f)][(int)(player.x + 1.0f)] == 0) {
            player.z -= move;
            moved = true;
        }
        if (press_down && world[(int)(player.z + 1.2f)][(int)(player.x)] == 0 &&
            world[(int)(player.z + 1.2f)][(int)(player.x + 1.0f)] == 0) {
            player.z += move;
            moved = true;
        }
        if (press_left && world[(int)(player.z + 1.0f)][(int)(player.x - 0.2f)] == 0) {
            player.x -= move;
            moved = true;
        }
        if (press_right && world[(int)(player.z + 1.0f)][(int)(player.x + 1.2f)] == 0) {
            player.x += move;
            moved = true;
        }

        if (moved) {
            ent_remove(player_old, player_index);
            player_index = ent_add(player, 0, texture2);
        }

        if (destroy) {
            if (world[(int)(player.z + 2.0f)][(int)(player.x + 0.5f)] == 1) {
                world[(int)(player.z + 2.0f)][(int)(player.x + 0.5f)] = 0;
            }
            destroy = false;
        }

        mat4 view;
        vec3 up;
        glm_vec3_add((vec3){camera.x, camera.y, camera.z}, direction, up);
        glm_lookat((vec3){camera.x, camera.y, camera.z}, up, (vec3){0.0f, 1.0f, 0.0f},
                   view);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat *)&view);

        sp_gebruik(sp);
        draw_world(sp, VAO);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    sp_verwijder(sp);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
