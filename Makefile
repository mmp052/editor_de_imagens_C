# CC = gcc
# CFLAGS = -Wall -Iinclude -I/usr/include -L/usr/lib -ljpeg

# OBJ = build/main.o build/image.o build/filter.o build/utils.o

# editor: $(OBJ)
#     $(CC) -o editor $(OBJ)

# build/%.o: src/%.c
#     $(CC) $(CFLAGS) -c $< -o $@

# clean:
#     rm -f build/*.o editor

# Definindo variáveis
CC = gcc
CFLAGS = -Wall -I./include
LDFLAGS = -ljpeg
SRC = src/main.c src/image.c
OBJ = $(SRC:.c=.o)
TARGET = build/meu_programa

# Regra padrão para compilar o programa
all: $(TARGET)

# Como construir o executável
$(TARGET): $(OBJ)
	@mkdir -p build
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Como compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar os arquivos compilados
clean:
	rm -rf $(OBJ) $(TARGET)

# Para facilitar, você pode limpar e recompilar com um comando
rebuild: clean all