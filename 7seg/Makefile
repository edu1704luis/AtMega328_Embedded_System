# =========================
# Configuración del proyecto
# =========================

PROJECT = 7seg
MCU     = atmega328p
F_CPU   = 16000000UL
CC      = avr-gcc
OBJCOPY = avr-objcopy

# =========================
# Flags
# =========================

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Os
CFLAGS += -Iinclude

LDFLAGS = -mmcu=$(MCU)

# =========================
# Archivos
# =========================

SRC = src/7seg.c
OBJ = $(SRC:.c=.o)

# =========================
# Reglas
# =========================

all: $(PROJECT).hex

$(PROJECT).elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o *.elf *.hex