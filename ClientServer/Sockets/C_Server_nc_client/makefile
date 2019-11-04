#Copyright (c) 2019 Lince99 under MIT license

CC=gcc
RM=rm -f

# name of the source
S_SRC=server.c
S_EXC=server

# - - - optimizations - - -
C_OPT=-faggressive-loop-optimizations -fcombine-stack-adjustments
C_OPT+= -fexpensive-optimizations -falign-functions -falign-jumps
C_OPT+= -falign-labels -falign-loops -floop-nest-optimize -floop-nest-optimize
C_OPT+= -foptimize-strlen -ftree-loop-optimize -fpredictive-commoning

# - - - folding optimizations - - -
C_FOLD_OPT=-fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-reference
C_FOLD_OPT+= -fipa-pta -foptimize-sibling-calls -freorder-blocks
C_FOLD_OPT+= -freorder-functions


all: compile_optimize

compile:
	@$(CC) -o $(S_EXC) $(S_SRC)
	@strip $(S_EXC)

compile_optimize:
	@$(CC) -o $(S_EXC) $(S_SRC) $(C_PAR) $(C_OPT) $(C_FOLD_OPT)
	@strip $(S_EXC)

clean:
	@$(RM) $(S_EXC)

clean_reset: clean
	@reset && clear
