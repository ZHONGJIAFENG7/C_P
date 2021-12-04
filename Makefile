src = $(wildcard ./*/*.c)
dest = $(patsubst %.c, %.o, $(src))
basename = ./demo${version}/demo${version}
CFLAGS = -Wall -Wextra -Wfloat-equal -ansi -pedantic -lm -lcurses -O2

all: clean mutiple

mutiple:${dest}
	${src}:${dest}
	gcc $@ ${CFLAGS} -o $^

single:
	gcc ${basename}.c ${CFLAGS} -o ${basename}.o

clean:
	rm -f ${dest}

hello:
	echo ${src}
	echo ${dest}
