#include <stdint.h>
#include <stdio.h>

#include "../bron/map.h"

#define ONGEDEFINEERD 0XFF
#define EINDE_SECTIE 0XEF

uint8_t ascii_naar_waarde[] = {[0 ... 47] = ONGEDEFINEERD,
                               [48] = 0x00,
                               [49] = 0x01,
                               [50] = 0x02,
                               [51] = 0x03,
                               [52] = 0x04,
                               [53] = 0x05,
                               [54] = 0x06,
                               [55] = 0x07,
                               [56] = 0x08,
                               [57] = 0x09,
                               [58 ... 64] = ONGEDEFINEERD,
                               [65] = 0x0A,
                               [66] = 0x0B,
                               [67] = 0x0C,
                               [68] = 0x0D,
                               [69] = 0x0E,
                               [70] = 0x0F,
                               [71] = 0x10,
                               [72] = 0x11,
                               [73] = 0x12,
                               [74] = 0x13,
                               [75] = 0x14,
                               [76] = 0x15,
                               [77] = 0x16,
                               [78] = 0x17,
                               [79] = 0x18,
                               [80] = 0x19,
                               [81] = 0x1A,
                               [82] = 0x1B,
                               [83] = 0x1C,
                               [84] = 0x1D,
                               [85] = 0x1E,
                               [86] = 0x1F,
                               [87] = 0x20,
                               [88] = 0x21,
                               [89] = 0x23,
                               [90] = 0x24,
                               [91 ... 94] = ONGEDEFINEERD,
                               [95] = EINDE_SECTIE,  // '_'
                               [96] = ONGEDEFINEERD,
                               [97] = 0x25,
                               [98] = 0x26,
                               [99] = 0x27,
                               [100] = 0x28,
                               [101] = 0x29,
                               [102] = 0x2A,
                               [103] = 0x2B,
                               [104] = 0x2C,
                               [105] = 0x2D,
                               [106] = 0x2E,
                               [107] = 0x2F,
                               [108] = 0x30,
                               [109] = 0x31,
                               [110] = 0x32,
                               [111] = 0x33,
                               [112] = 0x34,
                               [113] = 0x35,
                               [114] = 0x36,
                               [115] = 0x37,
                               [116] = 0x38,
                               [117] = 0x39,
                               [118] = 0x3A,
                               [119] = 0x3B,
                               [120] = 0x3C,
                               [121] = 0x3D,
                               [122] = 0x3E,
                               [123 ... 127] = ONGEDEFINEERD};

void bestand_lees_tot_nieuwelijn(void) {
    while (label[li] == '\0' && (c = fgetc) != '\n')
        ;
}

void bestand_zet_positie(FILE *bestand, char *label) {
    uint8_t li = 0;
    char c;

    while (feof(bestand) == 0 && label[li] != '\0') {
        c = fgetc(bestand);
        if (c == label[li]) {
            li++;
        } else {
            li = 0;
        }
    }

    bestand_lees_tot_nieuwelijn();
}

uint32_t bestand_lees_sector(FILE *bestand, char *label,
                             uint8_t *buffer, uint8_t omvang) {
    bestand_zet_positie(bestand, label);

    uint8_t in[32] = {};
    uint8_t uit[32] = {};
    uint32_t gelezen;
    uint8_t ib = 0;

    do {
        uint32_t positie = ftell(bestand);
        gelezen = fread_s(in, 32 * sizeof(in[0]), sizeof(in[0]), 32,
                          ingang);

        for (uint8_t i = 0; i < gelezen; i++) {
            uint8_t waarde = ascii_naar_waarde[in[i]];

            if (waarde == ONGEDEFINEERD) {
                continue;
            }

            if (waarde == EINDE_SECTIE) {
                fsetpos(bestand, positie);
                bestand_lees_tot_nieuwelijn();
                return ib;
            }

            buffer[ib++] = waarde;
            if (ib >= omvang) {
                return geschreven;
            }
        }
    } while (gelezen > 0);
}

int main(int agc, char **argv) {
    if (agc != 3) {
        printf(
            "Usage: map_compiler <ingang_bestand> <uitgang_bestand>");
        return 1;
    }

    FILE *ingang;
    FILE *uitgang;

    if (fopen_s(&ingang, argv[1], "r") != 0) {
        printf("Het is niet gelukt om '%s' te openen.", argv[1]);
        return 1;
    }

    if (fopen_s(&uitgang, argv[2], "wb") != 0) {
        printf("Het is niet gelukt om '%s' te openen.", argv[2]);
        return 1;
    }

    map_bestand_t map = {};
    uint32_t gelezen = 0;
    gelezen += bestand_lees_sector(
		    ingang, "__start_terrein", map.terrein,
                    MAP_MAAT * sizeof(map.terrein[0]));
    gelezen += bestand_lees_sector(
        ingang, "__start_eigenschappen", map.eigenschappen,
        MAP_MAAT * sizeof(map.eigenschappen[0]));

    printf("Klaar, error: %i, geschreven bytes: %u.\n",
           ferror(ingang), geschreven);
    printf("Van: %s.\n", argv[1]);
    printf("Naar: %s.\n", argv[2]);

    fclose(ingang);
    fclose(uitgang);

    return 0;
}
