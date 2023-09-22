all:
	gcc -Wall -Wextra -Wno-unknown-pragmas -Wno-pragmas -flto -g3 -Ofast *.c -pthread -fsanitize=address,undefined
#-fsanitize=thread
#-fsanitize=address,leak,undefined
