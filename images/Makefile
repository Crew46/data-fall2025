IMAGES := $(wildcard *.png)
CSRC := $(wildcard *.c)
ASM := $(wildcard *.asm)
OBJECTS := $(patsubst %.png,%.vtex,${IMAGES})
FLAGS = 
PROCESS = png2vircon
all: head images tail

debug: FLAGS += -v
debug: DEBUG = debug
debug: images

head:
ifndef DEBUG
	@printf "\033[0;33m%s\033[0m:\n" "images"
	@printf "\033[0;33m==========================================================\033[0m\n"
endif

images: $(OBJECTS)
	@echo -n

%.vtex: %.png
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;34m%s\033[0m] %-16s -> %-16s ... " "$(PROCESS)" "$^" "$@"
	@$(PROCESS) $(FLAGS) $^ 2>> $(PROCESS).errors && echo "\033[0;32mOK\033[0m" || echo "\033[0;31mFAIL\033[0m"
else
	$(PROCESS) $(FLAGS) $^
endif

tail:
ifndef DEBUG
	@echo
endif

clean:
	@printf "[\033[0;33m%s\033[0m]      %-36s ... " "clean" "removing VTEX files"
	@rm -f *.vtex $(PROCESS).errors && echo "\033[1;32mOK\033[0m" || echo "\033[1;31mFAIL\033[0m"
