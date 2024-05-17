# Definición de variables
CC = gcc
CFLAGS = -g -Wall

# Nombre del ejecutable
TARGET = hashTable

# Archivos fuente
SRCS = $(wildcard *.c)

# Archivos objeto
OBJS = $(SRCS:.c=.o)

# Regla por defecto
all: $(TARGET)

# Regla para el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regla para los archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET)
	