all:
	gcc -Wall -Wextra -Wno-unknown-pragmas -Wno-pragmas -flto -g3 -O2 *.c 
#-fsanitize=address,leak,undefined
