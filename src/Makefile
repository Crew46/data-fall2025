GAME = game
CFLAGS = -Wall -o $(GAME).asm
AFLAGS = 
PFLAGS = 
CC = compile
ASM = assemble
PACK = packrom
BINPATH = ../bin
all: head source object $(GAME) tail

debug: CFLAGS += -v -g
debug: AFLAGS += -v -g v32
debug: PFLAGS += -v
debug: DEBUG = debug
debug: source object $(GAME) 

head:
ifndef DEBUG
	@printf "\033[1;33m%s\033[0m:\n" "code"
	@printf "\033[1;33m==========================================================\033[0m\n"
endif

tail:
ifndef DEBUG
	@echo
endif

source:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;33m%s\033[0m]    %-16s -> %-16s ... " "$(CC)" "main.c" "$(GAME).asm"
	@$(CC)   $(CFLAGS) main.c 2>> errors && echo "\033[0;32mOK\033[0m" || echo "\033[0;31mFAIL\033[0m"
else
	$(CC)    $(CFLAGS) main.c
endif

object:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;33m%s\033[0m]   %-16s -> %-16s ... " "$(ASM)" "$(GAME).asm" "$(GAME).vbin"
	@$(ASM)  $(AFLAGS) $(GAME).asm 2>> errors && echo "\033[0;32mOK\033[0m" || echo "\033[0;31mFAIL\033[0m"
else
	$(ASM)   $(AFLAGS) $(GAME).asm
endif

$(GAME):
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;33m%s\033[0m]    %-16s -> %-16s ... " "$(PACK)" "$(GAME).vbin" "$(GAME).v32"
	@$(PACK) $(PFLAGS) $(GAME).xml 2>> errors && echo "\033[1;32mOK\033[0m" || echo "\033[1;31mFAIL\033[0m"
else
	$(PACK)  $(PFLAGS) $(GAME).xml
endif
	@cp -f $(GAME).v32 $(BINPATH)/

clean:
	@printf "[\033[0;33m%s\033[0m]      %-36s ... " "clean" "removing object files"
	@rm -f .*.sw[op] *.save* *~ $(BINPATH)/$(GAME) err* *.debug *.asm *.vbin && echo "\033[1;32mOK\033[0m" || echo "\033[1;31mFAIL\033[0m"
