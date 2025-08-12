SHELL = /bin/bash -e
INC = -I inc/
CCFLAGS = -Wall 
OPTS =
CC = gcc $(CCFLAGS) $(OPTS) $(INC)
OBJ = 
AR = ar
DEBUG = 
PROJ = game
UNITS = images audio src 
BIN = 
default: game
debug: game-debug

game-debug: CC += -DDEBUG -g
game-debug: DEBUG = debug
game-debug: game

ifndef DEBUG
MAKEFLAGS += --no-print-directory
endif

game:
	@mkdir -p bin audio data images src
	@for item in $(UNITS); do make -C $$item $(DEBUG); done

clean:
	@for item in $(UNITS); do make -C $$item clean; done
	@rm -f bin/*

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
	@echo "**                                                                    **"
	@echo "** make save                - create a backup archive                 **"
	@echo "**                                                                    **"
	@echo "** make clean               - clean; remove all objects/compiled code **"
	@echo "** make help                - this information                        **"
	@echo "************************************************************************"
