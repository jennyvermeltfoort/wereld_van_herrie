
#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "schaduwprogramma.h"
#include "stb_image.h"

#define SP_FORMAAT_TUSSENOPSLAG 2048

uint32_t sp_compileer_bestand(GLenum type, FILE *bestand, char *tussenopslag) {
    uint32_t gelezen = fread(tussenopslag, 1, SP_FORMAAT_TUSSENOPSLAG, bestand);
    if (!feof(bestand) || gelezen == SP_FORMAAT_TUSSENOPSLAG) {
        printf(
            "sp_compileer_bestand: fout bij het lezen, gelezen: %i, "
            "verwacht: %i.\n",
            gelezen, SP_FORMAAT_TUSSENOPSLAG);
        return 0;
    }
    tussenopslag[gelezen] = '\0';

    uint32_t sp = glCreateShader(type);
    glShaderSource(sp, 1, (char const *const *)&tussenopslag, NULL);
    glCompileShader(sp);

    int32_t success;
    char infoLog[512];
    glGetShaderiv(sp, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(sp, 512, NULL, infoLog);
        printf("sp_compileer_bestand: %s\n", infoLog);
        return 0;
    }

    return sp;
}

uint32_t sp_compileer_locatie(GLenum type, char *locatie) {
    FILE *bestand = fopen(locatie, "r");
    if (bestand == NULL) {
        printf("sp_compileer_locatie: bestand niet open, %s.\n", locatie);
        return 0;
    }

    char *tussenopslag = malloc(SP_FORMAAT_TUSSENOPSLAG);
    uint32_t sp = sp_compileer_bestand(type, bestand, tussenopslag);
    if (sp == 0) {
        printf("sp_compileer_locatie: fout bij compilatie, %s\n", locatie);
    }

    free(tussenopslag);
    fclose(bestand);
    return sp;
}

uint32_t sp_maak_programma(char *bestand_hoek, char *bestand_fragment) {
    uint32_t spv = sp_compileer_locatie(GL_VERTEX_SHADER, bestand_hoek);
    uint32_t spf = sp_compileer_locatie(GL_FRAGMENT_SHADER, bestand_fragment);

    uint32_t sp = glCreateProgram();
    glAttachShader(sp, spv);
    glAttachShader(sp, spf);
    glLinkProgram(sp);

    int32_t success;
    char infoLog[512];
    glGetProgramiv(sp, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(sp, 512, NULL, infoLog);
        printf(
            "sp_maak_programma: fout bij het maken van programma, "
            "%s\n",
            infoLog);
    }

    glDeleteShader(spv);
    glDeleteShader(spf);
    return sp;
}

void sp_uniform_zet_bool(uint32_t programma, char *uniform, bool waarde) {
    glUniform1i(glGetUniformLocation(programma, uniform), (int)waarde);
}
void sp_uniform_zet_int(uint32_t programma, char *uniform, uint32_t waarde) {
    glUniform1i(glGetUniformLocation(programma, uniform), waarde);
}
void sp_uniform_zet_float(uint32_t programma, char *uniform, float waarde) {
    glUniform1i(glGetUniformLocation(programma, uniform), waarde);
}

uint32_t sp_laad_texture(char *locatie) {
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    uint8_t *data = stbi_load(locatie, &width, &height, &nrChannels, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return texture;
}

void sp_gebruik_texture(uint32_t sp, uint32_t texture, vec2 tiles) {
    int tilesLoc = glGetUniformLocation(sp, "tiles");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform2fv(tilesLoc, 1, (GLfloat *)tiles);
}

void sp_gebruik(uint32_t programma) { glUseProgram(programma); }
void sp_verwijder(uint32_t programma) { glDeleteProgram(programma); }
