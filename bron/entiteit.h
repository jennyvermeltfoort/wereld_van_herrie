
#include <cglm/struct.h>

#define WORLD_X 10
#define WORLD_Z 20
#define WORLD_S WORLD_X *WORLD_Z

typedef struct {
    vec3 positie;
    ivec2 hoeken;
    unsigned int texture;
} entiteit_t;

void wereld_entiteit_voegtoe(vec3 positie, unsigned char id, unsigned int texture,
                             ivec2 hoeken);

void wereld_entiteit_verwijder(vec3 positie);
uint32_t wereld_entiteit_id(vec3 positie);
entiteit_t *wereld_entiteit_neem(vec3 positie);
uint32_t wereld_entiteit_maak_id(void);
