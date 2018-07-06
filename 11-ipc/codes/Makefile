
PROGRAMS = pipe1 pipe2 pipe4 popen1 popen2 myuclc add2 create_fifo server client msg_send msg_receive tshm shm_send shm_receive

CFLAGS = -g -Wall -O0

all: ${PROGRAMS}

%.o: %.c
	${CC} ${CFLAGS} -c $<

${PROGRAMS}: %: %.o
	${CC} ${CFLAGS} -o $@ $< 

clean:
	rm -r ${PROGRAMS} *.o 

