all:
	gcc -Wall -Wextra -ansi -pedantic -o bin/mastermind -I ./src/headers/ src/main.c 

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)