# Binaire
BINARY := firmware


# Configuration du MCU
MCU      := atmega1284p
F_CPU    := 16000000UL

SIMAVR   := simavr/simavr/run_avr

# Toolchain
PREFIX   := avr-
CC       := $(PREFIX)gcc
OBJCOPY  := $(PREFIX)objcopy
GDB      := $(PREFIX)gdb

# Target Flags
CFLAGS   := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -g -I. -I ./simavr/simavr/sim -O0 -Wall
LDFLAGS  := -mmcu=$(MCU) -Wl,-Map=$(BINARY).map -Wl,--gc-sections


# Répertoires
KERNEL_DIR  := kernel
HAL_DIR     := libatmega

# Sources et objets
SRC   := $(wildcard $(KERNEL_DIR)/*.c) $(wildcard $(HAL_DIR)/*.c) main.c
OBJS  := $(SRC:.c=.o)

LST_FILES := $(SRC:.c=.lst)

# Tests unitaires
TEST_SRC  := $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJS := $(TEST_SRC:.c=.o)

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


# # Simulation avec SimAVR
# sim: $(BINARY).elf
# 	@echo "Launching simulation..."
# 	$(Q)simavr -m $(MCU) -f $(F_CPU) -g -vcd $(BINARY).elf -v


# # Debug via GDB et SimAVR
# debug:
# 	@echo "Starting GDB..."
# 	$(Q)$(GDB) -nx --nh $(BINARY).elf -ex "target remote localhost:1234"

uart:
	$(Q)$(SIMAVR) -m $(MCU) -f $(F_CPU) -g $(BINARY).elf -v 

# Compilation des sources
%.o: %.c
	$(Q)$(CC) $(CFLAGS) -MD -c $< -o $@


%.o: %.S
	$(Q)$(CC) $(CFLAGS) -c $< -o $@




# Genere l'asm du projet a partir du binaire (decompilation)
asm: 
	avr-objdump -d firmware.elf > firmware.asm

# fichier .lst = equivalent asm de chaque fichier 
lst: $(LST_FILES)

%.lst: %.c
	$(Q)$(CC) $(CFLAGS) -Wa,-adhln -g -c $< -o /dev/null > $@


# Fichiers de dépendances auto-générés pour recompiler si un header file change
-include $(OBJS:.o=.d)

.PHONY: all sim debug clean lst asm

# Nettoyage
clean:
	$(Q)rm -f $(BINARY).* */*.o */*.d */*.lst *.lst *.d *.o
