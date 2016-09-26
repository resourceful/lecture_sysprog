
PROGRAMS = myls filetype access myumask mychmod myunlink futimens_ex

CFLAGS = -g -Wall -O0

all: ${PROGRAMS}

%.o: %.c
	${CC} ${CFLAGS} -c $<

${PROGRAMS}: %: %.o
	${CC} ${CFLAGS} -o $@ $< 

clean:
	rm -r ${PROGRAMS} *.o tempfile 

unlink: tempfile myunlink

tempfile: 
	echo "creats 500MB file"
	dd if=/dev/urandom of=tempfile count=1024000

