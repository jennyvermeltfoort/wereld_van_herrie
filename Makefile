
BRONNEN = $(wildcard bron/*.c)
KOPPELINGEN = $(wildcard bron/*.h)

DOELWIT = spel.exe
DOELWIT_DEBUG = spel_debug.exe

COMPILER = gcc
CFLAG = --std=c23 
BIEBS = -lgdi32

${DOELWIT}: ${KOPPELINGEN} ${BRONNEN}
	${COMPILER} ${CFLAG} -o ${DOELWIT} $^ ${BIEBS}

${DOELWIT_DEBUG}: ${KOPPELINGEN} ${BRONNEN}
	${COMPILER} ${CFLAG} -g -o ${DOELWIT_DEBUG} $^ ${BIEBS}

debug: ${DOELWIT_DEBUG}

all: ${DOELWIT}

clean:
	rm -f ${DOELWIT} ${DOELWIT_DEBUG}


