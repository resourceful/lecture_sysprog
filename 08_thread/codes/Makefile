
PROGRAMS = print_thrID exit-state exit-wrong push-pop timedlock barrier

CFLAGS = -g -Wall -O0

all: ${PROGRAMS}

%.o: %.c
	${CC} ${CFLAGS} -pthread -c $<

${PROGRAMS}: %: %.o
	${CC} ${CFLAGS} -o $@ $< 

clean:
	rm -r ${PROGRAMS} *.o hello

hello: hello.o
	${CC} -nostartfiles -o $@ $<  -e my_main
