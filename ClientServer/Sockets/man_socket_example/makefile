#Copyright (c) 2019 Lince99 under MIT license

CC=gcc
RM=rm -f

# name of the source (include folders if the source isn't in the current dir)
C_SRC=client.c
S_SRC=server.c
# name of the executable
C_EXC=client
S_EXC=server
# params used in the program
PARAMS=
# compile params like optimization or other platform targeting
C_PAR=-Os -Wall -fdiagnostics-color=auto

# - - - infoes - - -
C_INFO=
#-ftime-report
#-fopt-info
#-fdump-statistics -fstack-usage ( -fstats for C++)
#-aux-info signatures.txt
#-fdiagnostics-color=auto
#-fdiagnostics-parseable-fixits -fdiagnostics-generate-patch

# - - - optimizations - - -
C_OPT=-faggressive-loop-optimizations -fcombine-stack-adjustments
C_OPT+= -fexpensive-optimizations -falign-functions -falign-jumps
C_OPT+= -falign-labels -falign-loops -floop-nest-optimize -floop-nest-optimize
C_OPT+= -foptimize-strlen -ftree-loop-optimize -fpredictive-commoning

# - - - folding optimizations - - -
C_FOLD_OPT=-fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-reference
C_FOLD_OPT+= -fipa-pta -foptimize-sibling-calls -freorder-blocks
C_FOLD_OPT+= -freorder-functions



all: clean_reset compile

all_opt: clean_reset compile_optimize

help:
	@echo "\nUse make [option]:\n"
	@echo "help \n\tshow this help"
	@echo "compile \n\tcompile from the source and strip it"
	@echo "compile_optimize \n\tcompile and try to use built-in optimizers"
	@echo "clean \n\tremove executable"
	@echo "clean_reset \n\tremove executable AND clear the terminal"
	@echo "run \n\texecute the program"

compile:
	@$(CC) -o $(S_EXC) $(S_SRC)
	@$(CC) -o $(C_EXC) $(C_SRC)
	@strip $(S_EXC)
	@strip $(C_EXC)

compile_optimize:
	@$(CC) -o $(S_EXC) $(S_SRC) $(C_PAR) $(C_OPT) $(C_FOLD_OPT)
	@$(CC) -o $(C_EXC) $(C_SRC) $(C_PAR) $(C_OPT) $(C_FOLD_OPT)
	@strip $(S_EXC)
	@strip $(C_EXC)

clean:
	@$(RM) $(C_EXC)
	@$(RM) $(S_EXC)

clean_reset: clean
	@reset && clear

run:
	@./$(C_EXC) $(PARAMS)
