CATEGORY = images
SRCTYPE = png
DSTTYPE = vtex
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
ifneq ("$(wildcard *.$(SRCTYPE))","")
	@printf "\033[0;33m%s\033[0m:\n" "$(CATEGORY)"
	@printf "\033[0;33m================================================================"
	@printf "==================\033[0m\n"
endif
endif

$(CATEGORY): $(OBJECTS)
	@echo -n

%.$(DSTTYPE): %.$(SRCTYPE)
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;34m%s\033[0m] %-28s -> %-28s ... " "$(PROCESS)" "$^" "$@"
	@$(PROCESS) $(FLAGS) $^ 2>> $(PROCESS).errors && echo "\033[0;32mOK\033[0m"    \
	                                              || (echo "\033[0;31mFAIL\033[0m" \
	                                              && exit 1)
	@[ ! -s "$(PROCESS).errors" ] && rm -f $(PROCESS).errors || echo -n
else
	$(PROCESS)  $(FLAGS) $^                       || exit 1
endif

tail:
ifndef DEBUG
ifneq ("$(wildcard *.$(SRCTYPE))","")
	@echo
endif
endif

clean:
	@rm -f *.errors
ifneq ("$(wildcard *.$(DSTTYPE))","")
	@printf "[\033[0;34m%s\033[0m]     %-36s\n" "$(CATEGORY)" \
	                                            "removing $(DSTTYPE) files"
	@make -f Makefile.clean --no-print-directory
	@echo
endif
	@echo -n
