# Binaire
BINARY := firmware

# Configuration du MCU
MCU      := atmega1284p
F_CPU    := 16000000UL

# Toolchain
PREFIX   := avr-
CC       := $(PREFIX)gcc
OBJCOPY  := $(PREFIX)objcopy
GDB      := $(PREFIX)gdb

# Flags
CFLAGS   := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -g -I. -O0 -Wall
LDFLAGS  := -mmcu=$(MCU) -Wl,-Map=$(BINARY).map -Wl,--gc-sections

# Répertoires
SRC_DIR  := src
HAL_DIR  := libatmega

# Sources et objets
ASM := $(wildcard $(SRC_DIR)/*.S)
SRC := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(HAL_DIR)/*.c)
OBJS := $(SRC:.c=.o) $(ASM:.S=.o)

# quiet/verbose
ifneq ($(V),1)
  Q := @
endif

# Cibles par défaut
all: $(BINARY).elf $(BINARY).hex


# Construction ELF
# $(BINARY).elf : binaire complet au format ELF.
#   - Contient les symboles de débogage et toutes les métadonnées.
#   - Utilisé pour le débogage pas-à-pas avec GDB ou simavr.
$(BINARY).elf: $(OBJS) 
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Conversion en HEX
# $(BINARY).hex : image flashable au format Intel HEX.
#   - Généré à partir de l’ELF, ne contient que les sections à programmer en flash.
#   - Utilisé par les outils de programmation (avrdude, simavr) pour écrire le microcontrôleur.
$(BINARY).hex: $(BINARY).elf
	$(Q)$(OBJCOPY) -Oihex $< $@

# Simulation avec SimAVR
sim: $(BINARY).elf
	@echo "Launching simulation..."
	$(Q)simavr -m $(MCU) -f $(F_CPU) -g -vcd $(BINARY).elf -v

# Debug via GDB et SimAVR
debug:
	@echo "Starting GDB..."
	$(Q)$(GDB) -nx --nh $(BINARY).elf -ex "target remote localhost:1234"


vcd: $(BINARY).elf
	@echo "Lancement simulation avec dump VCD..."
	$(Q)simavr -m $(MCU) -f $(F_CPU) -vcd vcd_trace.vcd -vcd-names=ports $(BINARY).elf



# Compilation des sources
%.o: %.c
	$(Q)$(CC) $(CFLAGS) -MD -c $< -o $@

%.o: %.S
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	$(Q)rm -f $(BINARY).* */*.o */*.d

# Fichiers de dépendances auto-générés pour recompiler si un header file change
-include $(OBJS:.o=.d)

.PHONY: all sim debug clean

