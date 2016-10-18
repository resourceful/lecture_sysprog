
PROGRAMS = usr_sig tsleep

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
