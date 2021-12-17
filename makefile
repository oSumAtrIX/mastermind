all:
	gcc -Wall -Wextra -ansi -pedantic src/main.c -I src/headers -o bin/mastermind 

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)