
BRONNEN = $(wildcard bron/*.c)
KOPPELINGEN = $(wildcard bron/*.h)
OBJECTEN = ${BRONNEN:.c=.o}

BRON_MAP_COMPILER = mappen/compiler.c

DOELWIT = spel.exe
DOELWIT_DEBUG = spel_debug.exe
DOELWIT_MAP_COMPILER = map_compiler.exe

COMPILER = gcc
CFLAG = --std=c23 -Wall
BIEBS = -lgdi32

${DOELWIT}: ${OBJECTEN}
	${COMPILER} ${CFLAG} -o $@ $^ ${BIEBS}

%.o: %.c ${KOPPELINGEN}
	${COMPILER} ${CFLAG} -c $< -o $@

debug: ${DOELWIT_DEBUG}

${DOELWIT_MAP_COMPILER}: ${BRON_MAP_COMPILER}
	${COMPILER} ${CFLAG} -o $@ $<

all: ${DOELWIT} ${DOELWIT_MAP_COMPILER}

clean:
	rm -f ${DOELWIT} ${DOELWIT_DEBUG}
	rm -f ${OBJECTEN}
	rm -f ${DOELWIT_MAP_COMPILER}


