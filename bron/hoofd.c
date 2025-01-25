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

void framebuffer_size_callback(GLFWwindow *window, int width,
                               int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

    vec3s position = {.x = 1.0f, .y = 1.0f, .z = 1.0f};
bool press_w = false;
bool press_s = false;
bool press_a = false;
bool press_d = false;
bool press_e = false;
bool press_q = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS) press_w = true;
    if (key == GLFW_KEY_A && action == GLFW_PRESS) press_a = true;
    if (key == GLFW_KEY_S && action == GLFW_PRESS) press_s = true;
    if (key == GLFW_KEY_D && action == GLFW_PRESS) press_d = true;
    if (key == GLFW_KEY_E && action == GLFW_PRESS) press_e = true;
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) press_q = true;
    if (key == GLFW_KEY_W && action == GLFW_RELEASE) press_w = false;
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) press_a = false;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) press_s = false ;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) press_d = false;
    if (key == GLFW_KEY_E && action == GLFW_RELEASE) press_e = false;
    if (key == GLFW_KEY_Q && action == GLFW_RELEASE) press_q = false;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                          "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
        return -1;
    }

    uint32_t sp =
        sp_maak_programma("bron/schaduwprogramma/sp_hoekpunt.c",
                          "bron/schaduwprogramma/sp_fragment.c");

    unsigned int VBO, VAO, EBO;
    float vertices[] = {// pos      	  // tex
                        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, //
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, //
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
						      //
                        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, //
			2.0f, 1.0f, 0.0f, 1.0f, 1.0f, //
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
			2.0f, 0.0f, 0.0f, 1.0f, 0.0f, //
			2.0f, 1.0f, 0.0f, 1.0f, 1.0f, //
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
						      //
                        1.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
			2.0f, 0.0f, 1.0f, 1.0f, 1.0f, //
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
			2.0f, 0.0f, 0.0f, 1.0f, 0.0f, //
			2.0f, 0.0f, 1.0f, 1.0f, 1.0f, //
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
						      //
                        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
			1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //
			1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f  //
    				};
glfwSetKeyCallback(window, key_callback);
    glBindVertexArray(0);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3*sizeof(float)));
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
    //stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load("middelen/muur_1.png", &width, &height,
                  &nrChannels, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    sp_gebruik(sp);
    glUniform1i(glGetUniformLocation(sp, "texture1"), 0);

    vec2s size = {.x = 50.0f, .y = 50.0f};
    vec3s color = {.r = 1.0f, .g = 1.0f, .b = 1.0f};
    float rotate = 0.0f;
	float rot = 0.0f;

    mat4 projection;
    glm_perspective(glm_rad(90.0f), 800.0f/600.0f, 0.1f, 100.0f, projection);

    sp_uniform_zet_int(sp, "image", 0);
    int modelLoc = glGetUniformLocation(sp, "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&projection);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (press_w) position.z += 0.2f;
        if (press_a) position.x += 0.2f;
        if (press_s) position.z -= 0.2f;
        if (press_d) position.x -= 0.2f;


        sp_gebruik(sp);
        mat4s model = glms_mat4_identity();
        model = glms_translate(model, position);
        model = glms_rotate(model, glm_rad(0.0f),
                            (vec3s){.x = 0.0f, .y = 0.0f, .z = 0.0f});
	mat4 view ;
	float yaw = 0.0f;
	float pitch = 90.0f;
	vec3 direction = {cos(glm_rad(yaw)) * cos(glm_rad(pitch)),  sin(glm_rad(pitch)),  sin(glm_rad(yaw)) * cos(glm_rad(pitch)) };
	glm_vec3_normalize(direction);
	glm_lookat(
		(vec3){-1.0f,  4.0f ,  1.0f },
		(vec3){0.0f,  3.0f ,  0.0f },
		direction, view
			);

        int modelLoc = glGetUniformLocation(sp, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat *)&model);
        int viewLoc = glGetUniformLocation(sp, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat *)&view);
        int colorLoc = glGetUniformLocation(sp, "spriteColor");
        glUniform3fv(colorLoc, 1, (GLfloat *)&color);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 24);
        glBindVertexArray(0);

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

void framebuffer_size_callback(GLFWwindow *window, int width,
                               int height) {
    glViewport(0, 0, width, height);
}
