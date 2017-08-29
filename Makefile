CC=gcc-7
OUTPUT_OPTION=-MMD -MP -o $@

CFLAGS += -Wall -Ofast --std=c99 -Wvla -I../include
MODULES :=
CFLAGS += $(patsubst %,-I%,$(MODULES))

LIBS :=
SRC := main.c
include $(patsubst %,%/module.mk,$(MODULES))
OBJ := $(patsubst %.c,%.o,$(filter %.c,$(SRC)))
DEP := $(patsubst %.c,%.d,$(filter %.c,$(SRC)))

all : hexx

hexx : $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

debug : CFLAGS += -O0 -g
debug : clean prog

valgrind: debug
	valgrind ./hexx

-include $(DEP)

.PHONY: clean

clean:
	rm -f $(OBJ) $(DEP) hexx
	rm -rf *.dSYM
