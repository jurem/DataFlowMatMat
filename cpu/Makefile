CCFLAGS	:= -O3 -std=c99

all: matmat matmatt


matmat: matmat.c
	$(CC) $(CCFLAGS) $^ -o $@


matmatt: matmatt.c
	$(CC) $(CCFLAGS) $^ -o $@


%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $< -o $@


clean:
	@rm -f matmat matmatt
	@rm -f *.o


@PHONY: all clean
