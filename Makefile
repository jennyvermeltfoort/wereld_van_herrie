
BRONNEN = $(wildcard bron/*.c)
BRONNEN_MAP_COMPILER = bron/map.c bron/compiler.c
KOPPELINGEN = $(wildcard bron/*.h)
OBJECTEN = $(filter-out bron/compiler.o, ${BRONNEN:.c=.o})
OBJECTEN_MAP_COMPILER = ${BRONNEN_MAP_COMPILER:.c=.o}

DOELWIT = spel.exe
DOELWIT_DEBUG = spel_debug.exe
DOELWIT_MAP_COMPILER = map_compiler.exe

COMPILER = gcc
CFLAG = -g --std=c23 -Wall
BIEBS_WIN = -lglfw3 -lgdi32 -lopengl32
BIEBS_LIN = -lm -ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lcglm 
BIEBS = ${BIEBS_WIN}

${DOELWIT}: ${OBJECTEN}
	${COMPILER} ${CFLAG} -o $@ $^ ${BIEBS}

%.o: %.c 
	${COMPILER} ${CFLAG} -c $< -o $@ ${BIEBS} 

${DOELWIT_MAP_COMPILER}: ${OBJECTEN_MAP_COMPILER}
	${COMPILER} ${CFLAG} -o $@ $^

debug: ${DOELWIT_DEBUG}

map: ${DOELWIT_MAP_COMPILER}

all: ${DOELWIT} 

clean:
	rm -f ${DOELWIT} ${DOELWIT_DEBUG}
	rm -f ${OBJECTEN}
	rm -f ${DOELWIT_MAP_COMPILER}
	rm -f ${OBJECTEN_MAP_COMPILER}


