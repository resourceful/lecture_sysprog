
PROGRAMS = fdcount hole mycat setfl

CFLAGS = -g -Wall -O0

all: ${PROGRAMS}

%.o: %.c
	${CC} ${CFLAGS} -c $<

${PROGRAMS}: %: %.o
	${CC} ${CFLAGS} -o $@ $< 

clean:
	rm -r ${PROGRAMS} *.o iotest testfiles ftest

iotest: mycat.c testfiles 
	for NUM in 1 64 256 512 2048 4096 16384 32768 65536 81920; do \
		echo "BUFFSIZE = $$NUM"; \
		cc -Wall -DBUFFSIZE=$$NUM -o $@ $< ; \
		i=$$(( $$i + 1 )) ; \
		time -p ./$@ < testfiles/temp_file > testfiles/file$$i.copy; \
		echo; \
	done;

testfiles: 
	mkdir -p testfiles
	dd if=/dev/urandom of=testfiles/temp_file count=104800;  \

ftest: setfl.c testfiles
	for FLAGS in a b c d; do \
		echo "FLAGS = $$FLAGS"; \
		cc -Wall -o $@ $< ; \
		time -p ./$@ -$$FLAGS < testfiles/temp_file > testfiles/file_$$FLAGS; \
		echo ; \
	done;

