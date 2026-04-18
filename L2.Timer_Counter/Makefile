# =========================
# Configuración del proyecto
# =========================

PROJECT = Timer_counter
MCU     = atmega328p
F_CPU   = 16000000UL
CC      = avr-gcc
OBJCOPY = avr-objcopy

# =========================
# Rutas de Carpetas
# =========================

COMMON_DIR  = ../Common
PROJECT_DIR = .
BUILD_DIR   = build

# =========================
# Flags
# =========================

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Os
CFLAGS += -I$(COMMON_DIR)/include
CFLAGS += -I$(PROJECT_DIR)

LDFLAGS = -mmcu=$(MCU)

# =========================
# Archivos Fuente y Objetos
# =========================

# Fuentes
SRC = $(COMMON_DIR)/src/millis.c \
      $(PROJECT_DIR)/millis_test.c

# Objetos: Los colocamos todos dentro de la carpeta build/
# Usamos 'notdir' para que no replique la estructura de carpetas en build
OBJ = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))

# =========================
# Reglas
# =========================

all: $(BUILD_DIR) $(BUILD_DIR)/$(PROJECT).hex

# Crear la carpeta build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regla para el archivo HEX
$(BUILD_DIR)/$(PROJECT).hex: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Regla para el archivo ELF
$(BUILD_DIR)/$(PROJECT).elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

# Regla para compilar Seg7.c (desde common)
$(BUILD_DIR)/millis.o: $(COMMON_DIR)/src/millis.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar tu archivo principal (local)
$(BUILD_DIR)/millis_test.o: $(PROJECT_DIR)/millis_test.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean