
#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "schaduwprogramma.h"
#include "stb_image.h"

#define SP_FORMAAT_TUSSENOPSLAG 2048
#define SP_TEXTUUR_TUSSENOPSLAG 16

ivec2 textuur_formaat[SP_TEXTUUR_TUSSENOPSLAG] = {};

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

    uint32_t index = glCreateShader(type);
    glShaderSource(index, 1, (char const *const *)&tussenopslag, NULL);
    glCompileShader(index);

    int32_t success;
    char infoLog[512];
    glGetShaderiv(index, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(index, 512, NULL, infoLog);
        printf("sp_compileer_bestand: %s\n", infoLog);
        return 0;
    }

    return index;
}

uint32_t sp_compileer_locatie(GLenum type, char *locatie) {
    FILE *bestand = fopen(locatie, "r");
    if (bestand == NULL) {
        printf("sp_compileer_locatie: bestand niet open, %s.\n", locatie);
        return 0;
    }

    char *tussenopslag = malloc(SP_FORMAAT_TUSSENOPSLAG);
    uint32_t index = sp_compileer_bestand(type, bestand, tussenopslag);
    if (index == 0) {
        printf("sp_compileer_locatie: fout bij compilatie, %s\n", locatie);
    }

    free(tussenopslag);
    fclose(bestand);
    return index;
}

void sp_maak_programma(programma_t *programma, char *bestand_hoek,
                       char *bestand_fragment) {
    uint32_t index_hoek = sp_compileer_locatie(GL_VERTEX_SHADER, bestand_hoek);
    uint32_t index_fragment = sp_compileer_locatie(GL_FRAGMENT_SHADER, bestand_fragment);

    programma->index = glCreateProgram();
    glAttachShader(programma->index, index_hoek);
    glAttachShader(programma->index, index_fragment);
    glLinkProgram(programma->index);

    int32_t success;
    char infoLog[512];
    glGetProgramiv(programma->index, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programma->index, 512, NULL, infoLog);
        printf(
            "sp_maak_programma: fout bij het maken van programma, "
            "%s\n",
            infoLog);
        sp_verwijder(programma);
        programma->index = UINT32_MAX;
    }

    glDeleteShader(index_hoek);
    glDeleteShader(index_fragment);
}

void sp_uniform_zet_bool(programma_t *programma, char *uniform, bool waarde) {
    glUniform1i(glGetUniformLocation(programma->index, uniform), (int)waarde);
}
void sp_uniform_zet_int(programma_t *programma, char *uniform, uint32_t waarde) {
    glUniform1i(glGetUniformLocation(programma->index, uniform), waarde);
}
void sp_uniform_zet_float(programma_t *programma, char *uniform, float waarde) {
    glUniform1i(glGetUniformLocation(programma->index, uniform), waarde);
}
void sp_uniform_zet_m4f(programma_t *programma, char *uniform, mat4 waarde) {
    glUniformMatrix4fv(glGetUniformLocation(programma->index, uniform), 1, GL_FALSE,
                       (GLfloat *)waarde);
}
void sp_uniform_zet_2f(programma_t *programma, char *uniform, vec2 waarde) {
    glUniform2fv(glGetUniformLocation(programma->index, uniform), 1, (GLfloat *)waarde);
}
void sp_uniform_zet_3f(programma_t *programma, char *uniform, vec3 waarde) {
    glUniform3fv(glGetUniformLocation(programma->index, uniform), 1, (GLfloat *)waarde);
}
void sp_uniform_zet_2i(programma_t *programma, char *uniform, ivec2 waarde) {
    glUniform2iv(glGetUniformLocation(programma->index, uniform), 1, (GLint *)waarde);
}

void sp_teken_array(programma_t *programma, ivec2 hoeken) {
    glBindVertexArray(programma->vao);
    glDrawArrays(GL_TRIANGLES, hoeken[0], hoeken[1]);
    glBindVertexArray(0);
}

uint32_t sp_laad_textuur(char *locatie, ivec2 formaat) {
    uint32_t textuur;
    glGenTextures(1, &textuur);
    glBindTexture(GL_TEXTURE_2D, textuur);
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
    if (textuur > SP_TEXTUUR_TUSSENOPSLAG) {
        glDeleteTextures(1, &textuur);  // ?? todo
        printf("textuur index te groot.\n");
        return UINT32_MAX;
    }
    textuur_formaat[textuur][0] = formaat[0];
    textuur_formaat[textuur][1] = formaat[1];
    return textuur;
}

void sp_gebruik_textuur(programma_t *programma, uint32_t textuur) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textuur);
    sp_uniform_zet_2i(programma, "formaat", textuur_formaat[textuur]);
}

void sp_gebruik(programma_t *programma) { glUseProgram(programma->index); }
void sp_verwijder(programma_t *programma) { glDeleteProgram(programma->index); }
