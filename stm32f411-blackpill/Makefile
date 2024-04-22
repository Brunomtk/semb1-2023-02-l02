/****************************************************************************
 * main.c
 *
 *   Bruno Mendes da Silva
 *   brunomendestk@ufu.br
 *   11921EAU016
 *
 *   Direitos autorais (C) 2024 Bruno Mendes da Silva.
 *   Todos os direitos reservados.
 *   Autores: Bruno Mendes da Silva <brunomendestk@ufu.br>
 *
 ****************************************************************************/

# Nome do programa
PROGNAME := blinky

# Ferramentas do toolchain
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
CP = arm-none-eabi-objcopy
RM = rm -rf

# Diretórios onde arquivos objeto e de lista de dependências serão salvos
OBJDIR = build
DEPDIR = .deps

# Arquivos a serem compilados
SRCS = src/startup.c \
       src/main.c

# Flags do compilador
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O0
DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d
LFLAGS = -nostdlib -T stm32f411-rom.ld -Wl,-Map=blinky.map

# Gera lista de arquivos objeto e cria diretório onde serão salvos
OBJS = $(patsubst %, $(OBJDIR)/%.o, $(basename $(SRCS)))
$(shell mkdir -p $(dir $(OBJS)) > /dev/null)

# Gera lista de arquivos de lista de dependências e cria diretório onde serão salvos
DEPS = $(patsubst %, $(DEPDIR)/%.d, $(basename $(SRCS)))
$(shell mkdir -p $(dir $(DEPS)) > /dev/null)

all: $(OBJS) $(PROGNAME).elf $(PROGNAME).bin

$(PROGNAME).elf: $(OBJS)
	$(LD) $(LFLAGS) -o $@ $^

$(PROGNAME).bin: $(PROGNAME).elf
	$(CP) -O binary $^ $@

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

# Cria um novo target para cada arquivo de dependência possível
$(DEPS):

# Inclui conteúdo dos arquivos de dependência
-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(DEPDIR)
	$(RM) $(PROGNAME).elf $(PROGNAME).bin $(PROGNAME).map
