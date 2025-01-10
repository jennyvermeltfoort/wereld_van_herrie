
SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard include/*.h)

TARGET = game.exe
TARGET_DEBUG = game_debug.exe

CC = gcc
CFLAGS = --std=c23 -I./include/
LIBS = -lgdi32

${TARGET}: ${HEADERS} ${SOURCES}
	${CC} ${CFLAGS} -o ${TARGET} $^ ${LIBS}

${TARGET_DEBUG}: ${HEADERS} ${SOURCES}
	${CC} ${CFLAGS} -g -o ${TARGET} $^ ${LIBS}

debug: ${TARGET_DEBUG}

run: ${TARGET}
	./${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} {TARGET_DEBUG}


