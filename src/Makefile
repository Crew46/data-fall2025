CATEGORY = "source"
GAME = game
SRCFILE = main.c
DSTTYPE = asm, object
CFLAGS = -Wall -o $(GAME).asm
AFLAGS = 
PFLAGS = 
CC = compile
ASM = assemble
PACK = packrom
BINPATH = ../bin
all: head source object tail

debug: CFLAGS += -v -g
debug: AFLAGS += -v -g v32
debug: PFLAGS += -v
debug: DEBUG = debug
debug: source object $(GAME) 

head:
ifndef DEBUG
	@printf "\033[0;33m%s\033[0m:\n" "$(CATEGORY)"
	@printf "\033[0;33m================================================================"
	@printf "==================\033[0m\n"
endif

packhead:
ifndef DEBUG
	@printf "\033[1;33m%s\033[0m:\n" "packing"
	@printf "\033[0;33m================================================================"
	@printf "==================\033[0m\n"
endif

source:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;34m%s\033[0m]    %-28s -> %-28s ... "	  "$(CC)"        \
															  "$(SRCFILE)"   \
															  "$(GAME).asm"
	@$(CC)   $(CFLAGS) $(SRCFILE) 2> $(CC).errors     && echo "\033[0;32mOK\033[0m" \
													  || (echo "\033[0;31mFAIL\033[0m" \
													  && exit 1)
	@[ ! -s "$(CC).errors" ] && rm -f $(CC).errors    || /bin/echo -n
else
	$(CC)    $(CFLAGS) $(SRCFILE)					  || exit 1
endif

object:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;34m%s\033[0m]   %-28s -> %-28s ... "     "$(ASM)"       \
															  "$(GAME).asm"  \
															  "$(GAME).vbin"
	@$(ASM)  $(AFLAGS) $(GAME).asm 2> $(ASM).errors   && echo "\033[0;32mOK\033[0m"    \
													  || (echo "\033[0;31mFAIL\033[0m" \
													  && exit 1)
	@[ ! -s "$(ASM).errors" ] && rm -f $(ASM).errors  || echo -n
else
	$(ASM)   $(AFLAGS) $(GAME).asm					  || exit 1
endif

$(GAME):
	@../data/mkxml.sh $(GAME)
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[1;34m%s\033[0m]    %-28s -> %-28s ... "    "$(PACK)"      \
															  "$(GAME).vbin" \
															  "$(GAME).v32"
	@$(PACK) $(PFLAGS) $(GAME).xml 2>> $(PACK).errors && echo "\033[1;32mDONE\033[0m"  \
													  || (echo "\033[1;31mFAIL\033[0m" \
													  && exit 1)
	@[ ! -s "$(PACK).errors" ] && rm -f $(PACK).errors || echo -n
else
	$(PACK)  $(PFLAGS) $(GAME).xml                    || exit 1
endif

tail:
ifndef DEBUG
	@echo
endif

clean:
	@rm -f .*.sw[op] *.save* *~ *.errors *.debug *.v32 *.xml
ifneq ("$(wildcard $(GAME).asm)","")
	@printf "[\033[0;34m%s\033[0m]     %-36s\n" "$(CATEGORY)" \
	                                            "removing $(DSTTYPE) files"
	@make -f Makefile.clean --no-print-directory
	@echo
endif
	@echo -n
