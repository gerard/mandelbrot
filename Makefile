CFLAGS=-g -std=c99
BIN=mandelbrot

${BIN}: main.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -f ${BIN} *.ppm

.PHONY: clean
