
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
		time -p ./$@ < testfiles/temp_file > testfiles/file$$i.copy; \
		echo; \
	done;

testfiles: 
	mkdir -p testfile
	dd if=/dev/urandom of=testfiles/temp_file count=104800;  \

