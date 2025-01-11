#include "entiteit.h"
#include "map.h"

// [][][]
// [][][]
// [][][]

// Wereld is een grid van 16 x 16 pixel cellen;
// Een entity bestaat uit x cellen breed en y cellen hoog? OF een enitity is een cell.
// De wereld word per entity geprint naa rhet scherm op volgorde van priority.

#define CEL_MAAT_X 16
#define CEL_MAAT_Y 16
#define CEL_MAAT CEL_MAAT_X * CEL_MAAT_Y
#define MAP_MAAT_X 17
#define MAP_MAAT_Y 16
#define MAP_MAAT MAP_MAAT_X * MAP_MAAT_Y

typedef uint32_t cel_t[CEL_MAAT];

cel_t map[MAP_MAAT] = {};

scherm_kaderdata_t *kaderdata_ptr;

void map_prepareer(scherm_kaderdata_t *kaderdata) {
	uint32_t tijdelijk = 0;
	uint32_t cel_kleur = 0XFFFFFF;
	uint32_t cel_vorige = 0;

	kaderdata_ptr = kaderdata;
	
	for (uint32_t mi = 0 ; mi < MAP_MAAT ; mi++) {
		uint32_t *p = map[mi];
		for (uint32_t ci = 0 ; ci < CEL_MAAT ; ci++) {
			p[ci] = cel_kleur;
		}
		tijdelijk = cel_kleur;
		cel_kleur = cel_vorige;
		cel_vorige = tijdelijk;
	}
}

void map_vul_scherm(void) {
	for (uint32_t mi = 0; mi < MAP_MAAT; mi++) {
		uint32_t *p = map[mi];
		uint32_t offset_y = CEL_MAAT_Y * (mi / MAP_MAAT_X);
		uint32_t offset_x = CEL_MAAT_X * (mi % MAP_MAAT_X);

		if (offset_x + CEL_MAAT_X > kaderdata_ptr->breedte)
		{
			continue;
		}

		if (offset_y + CEL_MAAT_Y > kaderdata_ptr->hoogte) {
			break;
		}

		for (uint32_t ci = 0 ; ci < CEL_MAAT ; ci++) {
			uint32_t ypos = ci / CEL_MAAT_X + offset_y;
			uint32_t xpos = ci % CEL_MAAT_X + offset_x;
			kaderdata_ptr->pixels[ypos * kaderdata_ptr->breedte + xpos] 
					= p[ci];
		}
	}
}

