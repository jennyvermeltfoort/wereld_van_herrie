#ifndef __WACHTER_ENTITEIT_H
#define __WACHTER_ENTITEIT_H


typedef struct {
    uint16_t x;
    uint16_t y;
} entiteit_t;

typedef struct {
	entiteit_t *entiteiten;
	uint8_t aantal;
	uint8_t omvang;
} entiteit_lijst_t;

typedef enum { 
	entiteit_rang_l0, // teken eerst
	entiteit_rang_l1,
	entiteit_rang_l2,
	entiteit_rang_null,
} entiteit_rang_t;


#endif //  __WACHTER_ENTITEIT_H
