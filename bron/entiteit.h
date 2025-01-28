
#include <cglm/struct.h>

#define WORLD_X 10
#define WORLD_Z 20
#define WORLD_S WORLD_X *WORLD_Z

typedef struct {
    unsigned char start;
    unsigned char eind;
    unsigned int texture;
    vec3s positie;
} entiteit_t;

void wereld_entiteit_voegtoe(vec3s positie, unsigned char id, unsigned int texture,
                             unsigned char start, unsigned char eind);

void wereld_entiteit_verwijder(vec3s positie);
uint32_t wereld_entiteit_id(vec3s positie);
entiteit_t *wereld_entiteit_neem(vec3s positie);
uint32_t wereld_entiteit_maak_id(void);

#define VEC3S(_x, _z) \
    (vec3s) { .x = _x, .z = _z }
