
PROGRAMS = cat-copier ls-w-stat minimal-cat pid tiny-ls toy-shell toy-shellv2 welcome

CFLAGS = -g -Wall -O0

all: ${PROGRAMS}

%.o: %.c
	${CC} ${CFLAGS} -c $<

${PROGRAMS}: %: %.o
	${CC} ${CFLAGS} -o $@ $< 

clean:
	rm ${PROGRAMS} *.o
