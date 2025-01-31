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
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  //
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

unsigned int textuur1;
unsigned int textuur2;
unsigned int textuur3;

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

int animatie_offset_x = 0;
ivec2 animatie_frame = {0, 0};

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

void teken_model(programma_t *programma, vec3 positie, ivec2 hoeken) {
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, positie);
    sp_uniform_zet_m4f(programma, "model", model);
    sp_uniform_zet_2i(programma, "vak", (ivec2){0, 0});

    sp_teken_array(programma, hoeken);
}

void teken_model_sprite(programma_t *programma, vec3 positie, ivec2 hoeken) {
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, positie);
    glm_rotate(model, glm_rad(-0.0f), (vec3){0.0f, 1.0f, 0.0f});
    sp_uniform_zet_m4f(programma, "model", model);
    sp_uniform_zet_2i(programma, "vak",
                      (ivec2){animatie_frame[0] + animatie_offset_x, animatie_frame[1]});

    sp_teken_array(programma, hoeken);
}

void teken_model_schaal(programma_t *programma, vec3 positie, ivec2 hoeken, vec3 schaal) {
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, positie);
    glm_scale(model, schaal);
    sp_uniform_zet_m4f(programma, "model", model);
    sp_uniform_zet_2i(programma, "vak", (ivec2){0, 0});

    sp_teken_array(programma, hoeken);
}

unsigned int vorige_textuur = 0xFF;

void teken_entiteit(programma_t *programma, entiteit_t *entiteit) {
    if (vorige_textuur != entiteit->texture) {
        sp_gebruik_textuur(programma, entiteit->texture);
    }

    if (entiteit->texture == textuur1) {
        teken_model_schaal(programma, entiteit->positie, entiteit->hoeken,
                           (vec3){1.0f, 3.0f, 1.0f});
    } else {
        teken_model_sprite(programma, entiteit->positie, entiteit->hoeken);
    }
}

void teken_wereld(programma_t *programma) {
    sp_gebruik_textuur(programma, textuur1);
    for (int z = 0; z < WORLD_Z; z++) {
        for (int x = WORLD_X - 1; x >= 0; x--) {
            teken_model(programma, (vec3){x, -1.0f, z}, (ivec2){18, 24});
        }
    }

    for (int z = 0; z < WORLD_Z; z++) {
        for (int x = WORLD_X - 1; x >= 0; x--) {
            if (wereld_entiteit_id((vec3){x, 0.0f, z})) {
                teken_entiteit(programma, wereld_entiteit_neem((vec3){x, 0.0f, z}));
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
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
        return -1;
    }

    programma_t programma;
    sp_maak_programma(&programma, "bron/schaduwprogramma/sp_hoekpunt.vs",
                      "bron/schaduwprogramma/sp_fragment.vs");

    unsigned int VBO, EBO;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glBindVertexArray(0);
    glGenVertexArrays(1, &programma.vao);
    glGenBuffers(1, &VBO);
    glBindVertexArray(programma.vao);
    float vertices[] = {
        // back face
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  //
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
        // right face
        0.0f, 1.0f, 1.0f, 2.0f, 1.0f,  //
        1.0f, 1.0f, 1.0f, 3.0f, 1.0f,  //
        0.0f, 0.0f, 1.0f, 2.0f, 0.0f,  //
        1.0f, 0.0f, 1.0f, 3.0f, 0.0f,  //
        1.0f, 1.0f, 1.0f, 3.0f, 1.0f,  //
        0.0f, 0.0f, 1.0f, 2.0f, 0.0f,  //
        // left face
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 1.0f, 2.0f, 0.0f,  //
        0.0f, 1.0f, 1.0f, 2.0f, 1.0f,  //
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 1.0f, 2.0f, 0.0f,  //
        // top face
        0.0f, 1.0f, 0.0f, 3.0f, 1.0f,  //
        1.0f, 1.0f, 0.0f, 4.0f, 1.0f,  //
        0.0f, 1.0f, 1.0f, 3.0f, 0.0f,  //
        1.0f, 1.0f, 1.0f, 4.0f, 0.0f,  //
        1.0f, 1.0f, 0.0f, 4.0f, 1.0f,  //
        0.0f, 1.0f, 1.0f, 3.0f, 0.0f,  //
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

    textuur1 = sp_laad_textuur("middelen/muur_map_1.png", (ivec2){4, 1});
    textuur2 = sp_laad_textuur("middelen/speler_1.png", (ivec2){8, 2});
    textuur3 = sp_laad_textuur("middelen/muur_map_2.png", (ivec2){4, 1});

    sp_gebruik(&programma);
    mat4 projectie;
    float pro_width = 12;
    glm_ortho(0.0f, pro_width * SCR_ASPECT, 0.0f, pro_width, 0.1f, 100.0f, projectie);
    sp_uniform_zet_int(&programma, "afbeelding", 0);
    sp_uniform_zet_m4f(&programma, "projectie", projectie);

    vec3 color = {1.0f, 1.0f, 1.0f};
    sp_uniform_zet_3f(&programma, "spriteColor", color);

    uint32_t muur_id = wereld_entiteit_maak_id();
    for (int z = 0; z < WORLD_Z; z++) {
        for (int x = WORLD_X - 1; x >= 0; x--) {
            if (world[z][x] == 1) {
                // wereld_entiteit_voegtoe((vec3){x, 0.0f, z}, muur_id, textuur1,
                //                         (ivec2){6, 24});
            }
        }
    }

    vec3 speler_positie = {5.0f, 0.0f, 5.0f};
    uint32_t speler_id = wereld_entiteit_maak_id();
    wereld_entiteit_voegtoe(speler_positie, textuur2, speler_id, (ivec2){0, 6});

    float yaw = -90.0f;
    float pitch = -45.0f;
    float czup = sin(glm_rad(yaw));
    float cxup = cos(glm_rad(yaw));
    float czright = sin(glm_rad(90 + yaw));
    float cxright = cos(glm_rad(90 + yaw));
    vec3 camera = {0.0f, 4.0f, 0.0f};
    mat4 zicht;
    vec3 up;
    vec3 direction;
    direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    direction[1] = sin(glm_rad(pitch));
    direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
    glm_vec3_normalize(direction);
    glm_vec3_add(camera, direction, up);
    glm_lookat(camera, up, (vec3){0.0f, 1.0f, 0.0f}, zicht);
    sp_uniform_zet_m4f(&programma, "zicht", zicht);

    double timeAnim = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        bool cam_moved = false;
        if (press_q && yaw > -85.0f) {
            yaw -= 1.0f;
            camera[2] += 0.2f;
            cam_moved = true;
        }
        if (press_e && yaw < -05.0f) {
            yaw += 1.0f;
            camera[2] -= 0.2f;
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
            camera[2] += 0.2f * czup;
            camera[0] += 0.2f * cxup;
            cam_moved = true;
        }
        if (press_a) {
            camera[2] -= 0.2f * czright;
            camera[0] -= 0.2f * cxright;
            cam_moved = true;
        }
        if (press_s) {
            camera[2] -= 0.2f * czup;
            camera[0] -= 0.2f * cxup;
            cam_moved = true;
        }
        if (press_d) {
            camera[2] += 0.2f * czright;
            camera[0] += 0.2f * cxright;
            cam_moved = true;
        }

        if (cam_moved) {
            glm_vec3_add(camera, direction, up);
            glm_lookat(camera, up, (vec3){0.0f, 1.0f, 0.0f}, zicht);
            sp_uniform_zet_m4f(&programma, "zicht", zicht);
        }

        double newTime = glfwGetTime();

        const float move = 0.05f;
        bool moved = false;
        vec3 speler_positie_oud = {speler_positie[0], 0.0f, speler_positie[2]};
        const float speler_kader = 0.3f;

#define id_up_le                                                      \
    wereld_entiteit_id((vec3){speler_positie[0] - speler_kader, 0.0f, \
                              speler_positie[2] - speler_kader - move})
#define id_up_ri                                                      \
    wereld_entiteit_id((vec3){speler_positie[0] + speler_kader, 0.0f, \
                              speler_positie[2] - speler_kader - move})
#define id_do_le                                                      \
    wereld_entiteit_id((vec3){speler_positie[0] - speler_kader, 0.0f, \
                              speler_positie[2] + speler_kader + move})
#define id_do_ri                                                      \
    wereld_entiteit_id((vec3){speler_positie[0] + speler_kader, 0.0f, \
                              speler_positie[2] + speler_kader + move})
#define id_le_to                                                             \
    wereld_entiteit_id((vec3){speler_positie[0] - speler_kader - move, 0.0f, \
                              speler_positie[2] - speler_kader})
#define id_le_bo                                                             \
    wereld_entiteit_id((vec3){speler_positie[0] - speler_kader - move, 0.0f, \
                              speler_positie[2] + speler_kader})
#define id_ri_to                                                             \
    wereld_entiteit_id((vec3){speler_positie[0] + speler_kader + move, 0.0f, \
                              speler_positie[2] - speler_kader})
#define id_ri_bo                                                             \
    wereld_entiteit_id((vec3){speler_positie[0] + speler_kader + move, 0.0f, \
                              speler_positie[2] + speler_kader})

        if (press_up && (id_up_le == 0 || id_up_le == speler_id) &&
            (id_up_ri == 0 || id_up_ri == speler_id)) {
            speler_positie[2] -= move;
            moved = true;
            animatie_frame[0] = 3;
        }

        if (press_down && (id_do_le == 0 || id_do_le == speler_id) &&
            (id_do_ri == 0 || id_do_ri == speler_id)) {
            speler_positie[2] += move;
            moved = true;
            animatie_frame[0] = 0;
        }

        if (press_left && (id_le_to == 0 || id_le_to == speler_id) &&
            (id_le_bo == 0 || id_le_bo == speler_id)) {
            speler_positie[0] -= move;
            moved = true;
            animatie_frame[0] = 1;
        }

        if (press_right && (id_ri_to == 0 || id_ri_to == speler_id) &&
            (id_ri_bo == 0 || id_ri_bo == speler_id)) {
            speler_positie[0] += move;
            moved = true;
            animatie_frame[0] = 2;
        }

        if (moved) {
            wereld_entiteit_verwijder(speler_positie_oud);
            wereld_entiteit_voegtoe(speler_positie, textuur2, speler_id, (ivec2){0, 6});
        }

        if ((newTime - timeAnim) > 0.2f) {
            if (animatie_offset_x != 4 && moved) {
                timeAnim = newTime;
                animatie_frame[1] = (animatie_frame[1] == 0) ? 1 : 0;
            } else if (animatie_offset_x == 4 && animatie_frame[1] == 0) {
                timeAnim = newTime;
                animatie_frame[1] = 1;
            } else if (animatie_offset_x == 4 && animatie_frame[1] == 1) {
                timeAnim = newTime;
                animatie_offset_x = 0;
                animatie_frame[1] = 0;
            }
        }

        if (destroy && animatie_offset_x != 4) {
            timeAnim = newTime;
            animatie_offset_x = 4;
            animatie_frame[1] = 0;
            if (press_down &&
                wereld_entiteit_id((vec3){(int)speler_positie[0] + 0.35f, 0.0f,
                                          (int)(speler_positie[2] + 1.1f)})) {
                wereld_entiteit_verwijder((vec3){(int)speler_positie[0] + 0.35f, 0.0f,
                                                 (int)(speler_positie[2] + 1.1f)});
            }
            if (press_up &&
                wereld_entiteit_id((vec3){(int)speler_positie[0] + 0.35f, 0.0f,
                                          (int)(speler_positie[2] - 0.5f)})) {
                wereld_entiteit_verwijder((vec3){(int)speler_positie[0] + 0.35f, 0.0f,
                                                 (int)(speler_positie[2] - 0.5f)});
            }
            if (press_right &&
                wereld_entiteit_id((vec3){(int)speler_positie[0] + 1.1f + 0.35f, 0.0f,
                                          (int)(speler_positie[2])})) {
                wereld_entiteit_verwijder((vec3){(int)speler_positie[0] + 1.1f + 0.35f,
                                                 0.0f, (int)(speler_positie[2])});
            }
            if (press_left &&
                wereld_entiteit_id((vec3){(int)speler_positie[0] - 0.5f + 0.35f, 0.0f,
                                          (int)(speler_positie[2])})) {
                wereld_entiteit_verwijder((vec3){(int)speler_positie[0] - 0.5f + 0.35f,
                                                 0.0f, (int)(speler_positie[2])});
            }
            destroy = false;
        }

        sp_gebruik(&programma);
        teken_wereld(&programma);
        sp_gebruik_textuur(&programma, textuur3);
        teken_model(&programma, (vec3){8.0f, 0.0f, 1.0f}, (ivec2){0, 24});

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &programma.vao);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    sp_verwijder(&programma);

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
