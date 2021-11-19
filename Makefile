src = $(wildcard ./*/*.c)
dest = $(patsubst %.c, %.o, $(src))
basename = ./demo0${version}/demo0${version}
CFLAGS = -Wall -Wextra -Wfloat-equal -ansi -pedantic -lm -lcurses -O2
target = app

all: ${dest}
	${dest}:${src}
	gcc ${src} ${CFLAGS} -o ${dest}

single:
	gcc ${basename}.c ${CFLAGS} -o ${basename}.o

clean:
	rm -f $(dest)

hello:
	echo $(src2)
