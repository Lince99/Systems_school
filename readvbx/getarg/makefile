#Basso Nicola
#aka Lince99

CC=gcc #g++
RM=rm -f

# name of the source (include folders if the source isn't in the current dir)
SRC=getarg.c
# name of the executable
EXC=getarg
# params used in the program
PARAMS=
# compile params like optimization or other platform targeting
C_PAR=-Os -Wall -fdiagnostics-color=auto
# - - - warnings - - -
#-Wextra -Wall

# - - - general info - - -
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
C_OPT+= -falign-labels -falign-loops -floop-nest-optimize
C_OPT+= -foptimize-strlen -ftree-loop-optimize


# - - - folding optimizations - - -
C_FOLD_OPT=-fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-reference
C_FOLD_OPT+= -fipa-pta -foptimize-sibling-calls -freorder-blocks
C_FOLD_OPT+= -freorder-functions



#all: clean_reset compile run
all: clean compile

all_opt: clean_reset compile_optimize run_less

help:
	@echo "Use make [option]:"
	@echo "help: show this help"
	@echo "compile: compile from the source and strip it"
	@echo "compile_info: compile and show compilation/linking stuffs"
	@echo "compile_optimize: compile and try to use built-in optimizers"
	@echo "cron_time: cronometrate compilation time and execution time"
	@echo "debug: enter debug mode"
	@echo "clean: remove executable"
	@echo "clean_reset: remove executable and reset terminal"

compile:
	@$(CC) -o $(EXC) $(SRC)
	@strip $(EXC)

compile_info:
	@$(CC) -o $(EXC) $(SRC) $(C_PAR) $(C_INFO)
	@strip $(EXC)

compile_optimize:
	@$(CC) -o $(EXC) $(SRC) $(C_PAR) $(C_OPT) $(C_FOLD_OPT)
	@strip $(EXC)

cron_time:
	@time -p $(CC) -o $(EXC) $(SRC) $(C_PAR)
	@time -p ./$(EXC)

debug:
	@gdb $(EXC) $(PARAMS)

clean:
	@$(RM) $(EXC)

clean_reset:
	@$(RM) $(EXC)
	@reset && clear

run:
	@./$(EXC) $(PARAMS)

run_less:
	@./$(EXC) $(PARAMS) | less -Cqrs
