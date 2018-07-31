cc=gcc
#cc=arm-linux-gnueabi-gcc
obj=main.o list_stack.o map_operate.o walk.o produce_map.o
target=labyrinth
cflags=-Wall -g

$(target): $(obj)
	$(cc) $^ -o $@ $(cflags)
main.o: main.c main.h list_stack.h walk.h map_operate.h	
	$(cc) -c $< -o $@ $(cflags)	
list_stack.o: list_stack.c list_stack.h main.h
	$(cc) -c $< -o $@ $(cflags)
map_operate.o: map_operate.c map_operate.h list_stack.h main.h
	$(cc) -c $< -o $@ $(cflags)
walk.o: walk.c walk.h list_stack.h map_operate.h main.h
	$(cc) -c $< -o $@ $(cflags)
produce_map.o: produce_map.c produce_map.h main.h
	$(cc) -c $< -o $@ $(cflags)
clean:
	rm $(obj)
	del $(obj) 


