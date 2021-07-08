PROGNAME=	flow-foss
CC	=	gcc
CFLAGS	=	-g -Wall -Wextra -Wpedantic
LIBS	=	-lncurses
OBJS	:=	$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))

all: flow-foss

flow-foss: $(OBJS)
	gcc $(LIBS) -o $@ $^

obj/%.o: src/%.c | obj
	gcc $(CFLAGS) -c -o $@ $^ 

obj:
	mkdir -p obj

run: flow-foss
	./flow-foss

.PHONY: run all
