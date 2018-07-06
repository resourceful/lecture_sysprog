
PROGRAMS = nonblocking rot13a rot13c2 mcopy2

CFLAGS = -g -Wall -O0

all: ${PROGRAMS}

%.o: %.c
	${CC} ${CFLAGS} -c $<

${PROGRAMS}: %: %.o
	${CC} ${CFLAGS} -o $@ $< 

clean:
	rm -r ${PROGRAMS} *.o deadlock.o deadlock

deadlock: deadlock.c tellwait.c
	${CC} -c tellwait.c 
	${CC} -c deadlock.c 
	${CC} -o deadlock deadlock.o tellwait.o
