# Makefile para Frevo Runner (Compatível com Windows, Linux e macOS)

CC = gcc
CFLAGS = -Wall -Iinclude -O2
TARGET = FrevoRunner

# Detecção do Sistema Operacional
ifeq ($(OS),Windows_NT)
	# Windows (MinGW)
	LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		# Linux
		LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	endif
	ifeq ($(UNAME_S),Darwin)
		# macOS
		LDFLAGS = -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
	endif
endif

SRC = src/main.c src/jogador.c src/obstaculos.c src/ranking.c src/recursos.c src/telas.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
