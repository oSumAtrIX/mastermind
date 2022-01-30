all:
	gcc -Wall -Wextra -ansi -pedantic -o bin/mastermind -I ./src/headers/ src/*.c -std=c89

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)