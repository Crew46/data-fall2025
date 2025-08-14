CATEGORY = v32rom
GAME = game
DSTTYPE = cartridge
CFLAGS = -Wall -o $(GAME).asm
AFLAGS = 
PFLAGS = 
CC = compile
ASM = assemble
PACK = packrom
BINPATH = ../bin
all: packhead $(GAME) tail

debug: CFLAGS += -v -g
debug: AFLAGS += -v -g v32
debug: PFLAGS += -v
debug: DEBUG = debug
debug: $(GAME) 

packhead:
ifndef DEBUG
	@printf "\033[1;33m%s\033[0m:\n" "$(CATEGORY)"
	@printf "\033[1;33m==========================================================\033[0m\n"
endif

$(GAME):
	@./mkxml.sh $(GAME)
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[1;34m%s\033[0m]    %-16s -> %-16s ... " "$(PACK)"      \
	                                                       "$(GAME).vbin" \
	                                                       "$(GAME).v32"
	@$(PACK) $(PFLAGS) $(GAME).xml 2>> $(PACK).errors && echo "\033[1;32mDONE\033[0m"  \
	                                                  || (echo "\033[1;31mFAIL\033[0m" \
	                                                  && exit 1)
else
	$(PACK)  $(PFLAGS) $(GAME).xml                    || exit 1
endif
	@cp -f $(GAME).v32 $(BINPATH)/

tail:
ifndef DEBUG
	@echo -n
endif

clean:
ifneq ("$(wildcard $(GAME).v32)","")
	@rm -f .*.sw[op] *.save* *~ *.errors *.debug
	@printf "[\033[0;34m%s\033[0m]     %-36s\n" "$(CATEGORY)" \
	                                            "removing $(DSTTYPE) files"
	@make -f Makefile.clean --no-print-directory
endif
	@echo -n
