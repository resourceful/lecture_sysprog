
PROGRAMS = fdcount hole mycat 

CFLAGS = -g -Wall -O0

all: ${PROGRAMS}

%.o: %.c
	${CC} ${CFLAGS} -c $<

${PROGRAMS}: %: %.o
	${CC} ${CFLAGS} -o $@ $< 

clean:
	rm -r ${PROGRAMS} *.o iotest testfiles

iotest: mycat.c testfiles 
	for NUM in 1 64 256 512 2048 4096 16384 32768 65536 81920; do \
		echo "BUFFSIZE = $$NUM"; \
		cc -Wall -DBUFFSIZE=$$NUM -o $@ $< ; \
		i=$$(( $$i + 1 )) ; \
		time -p ./$@ < testfiles/file$$i > testfiles/file$$i.copy; \
		echo; \
	done;

testfiles: 
	mkdir -p testfiles
	for cnt in `seq 1 10`; do \
		dd if=/dev/urandom of=testfiles/file$$cnt count=104800;  \
	done;

