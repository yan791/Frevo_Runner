CC      := gcc
TARGET  := FrevoRunner
SRC     := src/main.c src/jogador.c src/obstaculos.c src/ranking.c src/recursos.c src/telas.c
OBJ     := $(SRC:.c=.o)
CFLAGS  := -Wall -Wextra -std=c99 -O2 -I./include

SFX_SRC := tools_generate_sfx.c
SFX_BIN := tools_generate_sfx
SFX_OUT := assets/audio/menu.wav assets/audio/score.wav \
           assets/audio/collision.wav assets/audio/jump.wav

UNAME_S    := $(shell uname -s)
PKG_RAYLIB := $(shell pkg-config --libs --cflags raylib 2>/dev/null)

ifeq ($(strip $(PKG_RAYLIB)),)
    ifeq ($(UNAME_S),Darwin)
        RAYLIB_FLAGS := -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    else
        RAYLIB_FLAGS := -lraylib -lGL -lpthread -ldl -lrt -lX11
    endif
else
    RAYLIB_FLAGS := $(PKG_RAYLIB)
endif

LDLIBS := $(RAYLIB_FLAGS) -lm

.PHONY: all run clean sfx

all: sfx $(TARGET)
sfx: $(SFX_OUT)

$(SFX_OUT): $(SFX_SRC)
	$(CC) -O2 -o $(SFX_BIN) $(SFX_SRC) -lm
	./$(SFX_BIN)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(SFX_BIN) $(SFX_OUT)