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

bool press_w = false;
bool press_s = false;
bool press_a = false;
bool press_d = false;

float mult = 1;

bool press_up = false;
bool press_down = false;
bool press_left = false;
bool press_right = false;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) press_w = true;
    if (key == GLFW_KEY_A && action == GLFW_PRESS) press_a = true;
    if (key == GLFW_KEY_S && action == GLFW_PRESS) press_s = true;
    if (key == GLFW_KEY_D && action == GLFW_PRESS) press_d = true;

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) mult = 10;

    if (key == GLFW_KEY_UP && action == GLFW_PRESS) press_up = true;
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) press_down = true;
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) press_left = true;
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) press_right = true;

    if (key == GLFW_KEY_W && action == GLFW_RELEASE) press_w = false;
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) press_a = false;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) press_s = false;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) press_d = false;

    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) mult = 1;

    if (key == GLFW_KEY_UP && action == GLFW_RELEASE) press_up = false;
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) press_down = false;
    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) press_left = false;
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) press_right = false;
}

void draw_plane_vertical(unsigned int sp, unsigned int vao, vec3s position, vec3s scale,
                         vec2s tscale) {
    mat4s model = glms_mat4_identity();
    model = glms_translate(model, position);
    model = glms_scale(model, scale);
    int modelLoc = glGetUniformLocation(sp, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);

    int texture_scale_i = glGetUniformLocation(sp, "texture_scale");
    glUniform2fv(texture_scale_i, 1, (GLfloat *)&tscale);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void draw_plane_horizontal(unsigned int sp, unsigned int vao, vec3s position, vec3s scale,
                           vec2s tscale) {
    mat4s model = glms_mat4_identity();
    model = glms_translate(model, position);
    model = glms_scale(model, scale);
    int modelLoc = glGetUniformLocation(sp, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);

    int texture_scale_i = glGetUniformLocation(sp, "texture_scale");
    glUniform2fv(texture_scale_i, 1, (GLfloat *)&tscale);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 6, 12);
    glBindVertexArray(0);
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

    uint32_t sp = sp_maak_programma("bron/schaduwprogramma/sp_hoekpunt.c",
                                    "bron/schaduwprogramma/sp_fragment.c");

    unsigned int VBO, VAO, EBO;

    glfwSetKeyCallback(window, key_callback);
    glBindVertexArray(0);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    float vertices[] = {
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  //
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //

        0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  //
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
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

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nrChannels;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load("middelen/muur_1.png", &width, &height, &nrChannels, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // stbi_set_flip_vertically_on_load(true);
    data = stbi_load("middelen/vloer_1.png", &width, &height, &nrChannels, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    unsigned int texture3;
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
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
    // glm_perspective(glm_rad(90.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection);
    float pro_width = 10;
    glm_ortho(0.0f, pro_width, 0.0f, pro_width, 0.1f, 100.0f, projection);

    sp_uniform_zet_int(sp, "image", 0);
    int modelLoc = glGetUniformLocation(sp, "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&projection);

    float yaw = -30.0f;
    float pitch = -45.0f;
    float czup = sin(glm_rad(yaw));
    float cxup = cos(glm_rad(yaw));
    float czright = sin(glm_rad(90 + yaw));
    float cxright = cos(glm_rad(90 + yaw));
    vec3 direction = {cos(glm_rad(yaw)) * cos(glm_rad(pitch)), sin(glm_rad(pitch)),
                      sin(glm_rad(yaw)) * cos(glm_rad(pitch))};

    int colorLoc = glGetUniformLocation(sp, "spriteColor");
    glUniform3fv(colorLoc, 1, (GLfloat *)&color);

    vec3s player = {.x = 5.0f, .y = 0.0f, .z = 5.0f};
    vec3s camera = {.x = 0.0f, .y = 0.0f, .z = 0.0f};

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (press_w) {
            camera.z += 0.2f * czup * mult;
            camera.x += 0.2f * cxup * mult;
        }
        if (press_a) {
            camera.z -= 0.2f * czright * mult;
            camera.x -= 0.2f * cxright * mult;
        }
        if (press_s) {
            camera.z -= 0.2f * czup * mult;
            camera.x -= 0.2f * cxup * mult;
        }
        if (press_d) {
            camera.z += 0.2f * czright * mult;
            camera.x += 0.2f * cxright * mult;
        }

        if (press_up) player.z -= 0.2f;
        if (press_down) player.z += 0.2f;
        if (press_left) player.x -= 0.2f;
        if (press_right) player.x += 0.2f;

        mat4 view;
        vec3 up;
        glm_vec3_normalize(direction);
        glm_vec3_add((vec3){camera.x, camera.y, camera.z}, direction, up);
        glm_lookat((vec3){camera.x, camera.y, camera.z}, up, (vec3){0.0f, 1.0f, 0.0f},
                   view);
        int viewLoc = glGetUniformLocation(sp, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat *)&view);

        sp_gebruik(sp);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        draw_plane_vertical(sp, VAO, (vec3s){.x = 0.0f, .y = 0.0f, .z = 0.0f},
                            (vec3s){.x = 100.0f, .y = 2.0f, .z = 0.0f}, (vec2s){.x = 100.0f, .y = 1.0f});

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        draw_plane_horizontal(sp, VAO, (vec3s){.x = 0.0f, .y = 0.0f, .z = 0.0f},
                              (vec3s){.x = 100.0f, .y = 0.0f, .z = 100.0f}, (vec2s){.x = 100.0f, .y = 100.0f});

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture3);
        draw_plane_vertical(sp, VAO, player, (vec3s){.x = 1.0f, .y = 1.0f, .z = 0.0f}, (vec2s){.x = 1.0f, .y = 1.0f});

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
