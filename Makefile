src = $(wildcard ./*/*.c)
dest = $(patsubst %.c, %.o, $(src))
basename = ./demo0${version}/demo0${version}
CFLAGS = -Wall -Wextra -Wfloat-equal -ansi -pedantic -lm -lcurses -O2

all: ${dest}
	${dest}:${src}
		gcc $^ ${CFLAGS} -o $@

single:
	gcc ${basename}.c ${CFLAGS} -o ${basename}.o

clean:
	rm -f $(dest)

hello:
	echo $(src2) 