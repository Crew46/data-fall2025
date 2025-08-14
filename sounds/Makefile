CATEGORY = sounds
SRCTYPE = wav
DSTTYPE = vsnd
INPUTS := $(wildcard *.$(SRCTYPE))
OBJECTS := $(patsubst %.$(SRCTYPE),%.$(DSTTYPE),${INPUTS})
FLAGS = 
PROCESS = $(SRCTYPE)2vircon
MAKEFLAGS += --always-make
all: head $(CATEGORY) tail

debug: FLAGS += -v
debug: DEBUG = debug
debug: $(CATEGORY)

head:
ifndef DEBUG
	@printf "\033[0;33m%s\033[0m:\n" "$(CATEGORY)"
	@printf "\033[0;33m==========================================================\033[0m\n"
endif

$(CATEGORY): $(OBJECTS)
	@echo -n

%.$(DSTTYPE): %.$(SRCTYPE)
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;34m%s\033[0m] %-16s -> %-16s ... " "$(PROCESS)" "$^" "$@"
	@$(PROCESS) $(FLAGS) $^ 2>> $(PROCESS).errors && echo "\033[0;32mOK\033[0m"    \
	                                              || (echo "\033[0;31mFAIL\033[0m" \
	                                              && exit 1)
else
	$(PROCESS)  $(FLAGS) $^                       || exit 1
endif

tail:
ifndef DEBUG
	@echo
endif

clean:
	@printf "[\033[0;34m%s\033[0m]     %-36s\n" "$(CATEGORY)" \
	                                            "removing $(DSTTYPE) files"
	@rm -f *.errors
	@make -f Makefile.clean --no-print-directory
	@echo
