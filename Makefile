build:
	gcc processgen.c -o processgen.out
	gcc clk.c -o clk.out
	gcc finalscheduler.c -o finalscheduler.out
	gcc process.c -o process.out


clean:
	rm -f *.out  processes.txt

all: clean build

run:
	./processgen.out
