SHELL = /bin/bash -e
INC = -I inc/
CCFLAGS = -Wall 
OPTS =
CC = gcc $(CCFLAGS) $(OPTS) $(INC)
OBJ = 
AR = ar
DEBUG = 
PROJ = game
UNITS = images sounds src 
BIN = 
default: game
debug: game-debug

game-debug: CC += -DDEBUG -g
game-debug: DEBUG = debug
game-debug: game

ifndef DEBUG
MAKEFLAGS += --no-print-directory
endif

header:
ifndef DEBUG
	@printf "\033[1;36m%s\033[0m ...\n" "building $(PROJ)"
	@echo
endif

game: header
	@mkdir -p $(UNITS) bin data
	@for item in $(UNITS); do make -C $$item $(DEBUG); done

all: v32
cart: v32
rom: v32
v32rom: v32
v32: game
	@make -C data $(DEBUG)

clean:
ifndef DEBUG
	@printf "\033[0;33m%s\033[0m:\n" "clean"
	@printf "\033[0;33m==================================================================================\033[0m\n"
endif
	@for item in $(UNITS) data; do make -C $$item clean; done
	@echo

save: clean
	@echo "Archiving the project ..."
	@(cd ..; tar cf $(PROJ)-`date +%Y%m%d-%H`.tar $(PROJ))
	@echo "Compressing the archive ..."
	@gzip -f -9 ../$(PROJ)-*.tar
	@echo "Setting Permissions ..."
	@chmod 600 ../$(PROJ)-*.gz

help:
	@echo
	@echo "*************************[ fall2025-data game ]*************************"
	@echo "** make                     - build everything                        **"
	@echo "** make debug               - build everything with debug symbols     **"
	@echo "** make clean               - clean; remove all objects/compiled code **"
	@echo "**                                                                    **"
	@echo "** make cart                - pack the Vircon32 cartridge             **"
	@echo "**                                                                    **"
	@echo "** make save                - create a backup archive                 **"
	@echo "**                                                                    **"
	@echo "** make help                - this information                        **"
	@echo "************************************************************************"
