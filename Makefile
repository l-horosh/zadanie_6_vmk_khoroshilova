all: main
clean:
	rm main ./*.o
main.o: main.c
	gcc -c -o main.o main.c -m32 -lm
functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm
main: main.o functions.o
	gcc -o main main.o functions.o -m32