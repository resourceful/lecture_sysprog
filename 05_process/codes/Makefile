
PROGRAMS = fork zombies exit_stat avoid_zombie race_cond exec echoall interp echoarg system tsys pruid nice

CFLAGS = -g -Wall -O0

all: ${PROGRAMS}

%.o: %.c
	${CC} ${CFLAGS} -c $<

${PROGRAMS}: %: %.o
	${CC} ${CFLAGS} -o $@ $< 

clean:
	rm -r ${PROGRAMS} *.o hello

hello: hello.o
	${CC} -nostartfiles -o $@ $<  -e my_main
