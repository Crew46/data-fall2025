CATEGORY = images
SRCTYPE = png
DSTTYPE = vtex
INPUTS := $(wildcard *.$(SRCTYPE))
OBJECTS := $(patsubst %.$(SRCTYPE),%.$(DSTTYPE),${INPUTS})
FLAGS = 
PROCESS = $(SRCTYPE)2vircon
all: head $(CATEGORY) tail

debug: FLAGS += -v
debug: DEBUG = debug
debug: sounds

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
	@$(PROCESS) $(FLAGS) $^ 2>> $(PROCESS).errors && echo "\033[0;32mOK\033[0m"   \
	                                              || echo "\033[0;31mFAIL\033[0m" \
	                                              || exit 1
else
	$(PROCESS)  $(FLAGS) $^                       || exit 1
endif

tail:
ifndef DEBUG
	@echo
endif

clean:
	@printf "[\033[0;33m%s\033[0m]      %-9s%-27s ... " "clean" \
	                                                    "$(CATEGORY): " \
	                                                    "removing $(DSTTYPE) files"
	@rm -f *.$(DSTTYPE) *.errors && echo "\033[1;32mOK\033[0m"   \
	                             || echo "\033[1;31mFAIL\033[0m"
