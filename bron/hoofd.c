#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "entiteit.h"
#include "schaduwprogramma.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 576;
const float SCR_ASPECT = (float)SCR_WIDTH / (float)SCR_HEIGHT;

int world[WORLD_Z][WORLD_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},  //
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},  //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  //
    {1, 1, 1, 0, 0, 0, 0, 1, 1, 1},  //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  //
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},  //
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},  //
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //
};

unsigned int texture1;
unsigned int texture2;

bool press_w = false;
bool press_s = false;
bool press_a = false;
bool press_d = false;
bool press_q = false;
bool press_e = false;

bool destroy = false;

bool press_up = false;
bool press_down = false;
bool press_left = false;
bool press_right = false;

vec2 flip = {0.0f, 0.0f};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) press_w = true;
    if (key == GLFW_KEY_A && action == GLFW_PRESS) press_a = true;
    if (key == GLFW_KEY_S && action == GLFW_PRESS) press_s = true;
    if (key == GLFW_KEY_D && action == GLFW_PRESS) press_d = true;
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) press_q = true;
    if (key == GLFW_KEY_E && action == GLFW_PRESS) press_e = true;

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) destroy = true;

    if (key == GLFW_KEY_UP && action == GLFW_PRESS) press_up = true;
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) press_down = true;
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) press_left = true;
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) press_right = true;

    if (key == GLFW_KEY_W && action == GLFW_RELEASE) press_w = false;
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) press_a = false;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) press_s = false;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) press_d = false;
    if (key == GLFW_KEY_Q && action == GLFW_RELEASE) press_q = false;
    if (key == GLFW_KEY_E && action == GLFW_RELEASE) press_e = false;

    if (key == GLFW_KEY_UP && action == GLFW_RELEASE) press_up = false;
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) press_down = false;
    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) press_left = false;
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) press_right = false;
}

void draw_model(uint32_t sp, uint32_t vao, vec3s position, uint32_t start, uint32_t end) {
    mat4s model = glms_mat4_identity();
    model = glms_translate(model, position);
    int modelLoc = glGetUniformLocation(sp, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, start, end);
    glBindVertexArray(0);
}

void draw_model_sprite(uint32_t sp, uint32_t vao, vec3s position, uint32_t start,
                       uint32_t end) {
    mat4s model = glms_mat4_identity();
    model = glms_translate(model, position);
    model = glms_rotate(model, glm_rad(-45.0f), (vec3s){.y = 1.0f});
    int tcoordLoc = glGetUniformLocation(sp, "tcoord");
    glUniform2fv(tcoordLoc, 1, (GLfloat *)flip);
    int modelLoc = glGetUniformLocation(sp, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, start, end);
    glBindVertexArray(0);
    glUniform2fv(tcoordLoc, 1, (GLfloat *)(vec2){0.0f, 0.0f});
}

void draw_model_scaled(uint32_t sp, uint32_t vao, vec3s position, uint32_t start,
                       uint32_t end, float yscale) {
    mat4s model = glms_mat4_identity();
    model = glms_translate(model, position);
    model = glms_scale(model, (vec3s){.x = 1.0f, .y = yscale, .z = 1.0f});
    int modelLoc = glGetUniformLocation(sp, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, start, end);
    glBindVertexArray(0);
}

unsigned int prev_drawn = 0xFF;

void draw_entity(unsigned int sp, unsigned int vao, entiteit_t *e) {
    if (prev_drawn != e->texture) {
        if (e->texture == texture1) {
            sp_gebruik_texture(sp, e->texture, (vec2){3.0f, 1.0f});
        } else {
            sp_gebruik_texture(sp, e->texture, (vec2){4.0f, 4.0f});
        }
    }

    if (e->texture == texture1) {
        draw_model_scaled(sp, vao, e->positie, e->start, e->eind, 3.0f);
    } else {
        draw_model_sprite(sp, vao, e->positie, e->start, e->eind);
    }
}

void draw_world(unsigned int sp, unsigned int vao) {
    sp_gebruik_texture(sp, texture1, (vec2){3.0f, 1.0f});
    for (int z = 0; z < WORLD_Z; z++) {
        for (int x = WORLD_X - 1; x >= 0; x--) {
            draw_model(sp, vao, (vec3s){.x = x, .y = -1.0f, .z = z}, 18, 24);
        }
    }

    for (int z = 0; z < WORLD_Z; z++) {
        for (int x = WORLD_X - 1; x >= 0; x--) {
            if (wereld_entiteit_id(VEC3S(x, z))) {
                draw_entity(sp, vao, wereld_entiteit_neem(VEC3S(x, z)));
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
        // back face
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  //
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
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

    texture1 = sp_laad_texture("middelen/muur_map_1.png");
    texture2 = sp_laad_texture("middelen/speler_1.png");

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

    int colorLoc = glGetUniformLocation(sp, "spriteColor");
    int viewLoc = glGetUniformLocation(sp, "view");
    glUniform3fv(colorLoc, 1, (GLfloat *)&color);

    uint32_t muur_id = wereld_entiteit_maak_id();
    for (int z = 0; z < WORLD_Z; z++) {
        for (int x = WORLD_X - 1; x >= 0; x--) {
            if (world[z][x] == 1) {
                wereld_entiteit_voegtoe((vec3s){.x = x, .y = 0.0f, .z = z}, muur_id,
                                        texture1, 6, 24);
            }
        }
    }

    vec3s speler_positie = {.x = 5.0f, .y = 0.0f, .z = 5.0f};
    uint32_t speler_id = wereld_entiteit_maak_id();
    wereld_entiteit_voegtoe(speler_positie, texture2, speler_id, 0, 6);

    double timeAnim = glfwGetTime();

    float yaw = -45.0f;
    float pitch = -45.0f;
    float czup = sin(glm_rad(yaw));
    float cxup = cos(glm_rad(yaw));
    float czright = sin(glm_rad(90 + yaw));
    float cxright = cos(glm_rad(90 + yaw));
    vec3 direction;
    vec3s camera = {.x = 0.0f, .y = 3.0f, .z = 0.0f};
    mat4 view;
    vec3 up;
    direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    direction[1] = sin(glm_rad(pitch));
    direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
    glm_vec3_normalize(direction);

    glm_vec3_add((vec3){camera.x, camera.y, camera.z}, direction, up);
    glm_lookat((vec3){camera.x, camera.y, camera.z}, up, (vec3){0.0f, 1.0f, 0.0f}, view);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat *)&view);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        bool cam_moved = false;
        if (press_q && yaw > -85.0f) {
            yaw -= 1.0f;
            camera.z += 0.2f;
            cam_moved = true;
        }
        if (press_e && yaw < -05.0f) {
            yaw += 1.0f;
            camera.z -= 0.2f;
            cam_moved = true;
        }

        if (cam_moved) {
            czup = sin(glm_rad(yaw));
            cxup = cos(glm_rad(yaw));
            czright = sin(glm_rad(90 + yaw));
            cxright = cos(glm_rad(90 + yaw));
            direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
            direction[1] = sin(glm_rad(pitch));
            direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
            glm_vec3_normalize(direction);
        }

        if (press_w) {
            camera.z += 0.2f * czup;
            camera.x += 0.2f * cxup;
            cam_moved = true;
        }
        if (press_a) {
            camera.z -= 0.2f * czright;
            camera.x -= 0.2f * cxright;
            cam_moved = true;
        }
        if (press_s) {
            camera.z -= 0.2f * czup;
            camera.x -= 0.2f * cxup;
            cam_moved = true;
        }
        if (press_d) {
            camera.z += 0.2f * czright;
            camera.x += 0.2f * cxright;
            cam_moved = true;
        }

        if (cam_moved) {
            glm_vec3_add((vec3){camera.x, camera.y, camera.z}, direction, up);
            glm_lookat((vec3){camera.x, camera.y, camera.z}, up, (vec3){0.0f, 1.0f, 0.0f},
                       view);
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat *)&view);
        }

        double newTime = glfwGetTime();

        const float move = 0.05f;
        bool moved = false;
        vec3s speler_positie_oud = speler_positie;
        const float speler_kader = 0.3f;

#define id_up_le        \
    wereld_entiteit_id( \
        VEC3S(speler_positie.x - speler_kader, speler_positie.z - speler_kader - move))
#define id_up_ri        \
    wereld_entiteit_id( \
        VEC3S(speler_positie.x + speler_kader, speler_positie.z - speler_kader - move))
#define id_do_le        \
    wereld_entiteit_id( \
        VEC3S(speler_positie.x - speler_kader, speler_positie.z + speler_kader + move))
#define id_do_ri        \
    wereld_entiteit_id( \
        VEC3S(speler_positie.x + speler_kader, speler_positie.z + speler_kader + move))
#define id_le_to        \
    wereld_entiteit_id( \
        VEC3S(speler_positie.x - speler_kader - move, speler_positie.z - speler_kader))
#define id_le_bo        \
    wereld_entiteit_id( \
        VEC3S(speler_positie.x - speler_kader - move, speler_positie.z + speler_kader))
#define id_ri_to        \
    wereld_entiteit_id( \
        VEC3S(speler_positie.x + speler_kader + move, speler_positie.z - speler_kader))
#define id_ri_bo        \
    wereld_entiteit_id( \
        VEC3S(speler_positie.x + speler_kader + move, speler_positie.z + speler_kader))

        if (press_up && (id_up_le == 0 || id_up_le == speler_id) &&
            (id_up_ri == 0 || id_up_ri == speler_id)) {
            speler_positie.z -= move;
            moved = true;
            flip[0] = 3;
        }

        if (press_down && (id_do_le == 0 || id_do_le == speler_id) &&
            (id_do_ri == 0 || id_do_ri == speler_id)) {
            speler_positie.z += move;
            moved = true;
            flip[0] = 0;
        }

        if (press_left && (id_le_to == 0 || id_le_to == speler_id) &&
            (id_le_bo == 0 || id_le_bo == speler_id)) {
            speler_positie.x -= move;
            moved = true;
            flip[0] = 1;
        }

        if (press_right && (id_ri_to == 0 || id_ri_to == speler_id) &&
            (id_ri_bo == 0 || id_ri_bo == speler_id)) {
            speler_positie.x += move;
            moved = true;
            flip[0] = 2;
        }

        if (moved) {
            if ((newTime - timeAnim) > 0.2f) {
                timeAnim = newTime;
                flip[1] = (flip[1] == 0.0f) ? 1.0f : 0.0f;
            }
            wereld_entiteit_verwijder(speler_positie_oud);
            wereld_entiteit_voegtoe(speler_positie, texture2, speler_id, 0, 6);
        }

        if (flip[1] == 2.0f && (newTime - timeAnim) > 0.2f) {
            timeAnim = newTime;
            flip[1] = 3.0f;
        }

        if (flip[1] == 3.0f && (newTime - timeAnim) > 0.2f) {
            timeAnim = newTime;
            flip[1] = 0.0f;
        }

        if (destroy) {
            timeAnim = newTime;
            flip[1] = 2.0f;
            if (wereld_entiteit_id(VEC3S((int)(speler_positie.x + 0.5f),
                                         (int)(speler_positie.z + 1.0f)))) {
                wereld_entiteit_verwijder(VEC3S((int)(speler_positie.x + 0.5f),
                                                (int)(speler_positie.z + 1.0f)));
            }
            destroy = false;
        }

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
