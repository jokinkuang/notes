all: broadcaster listener bind_broadcaster
broadcaster: broadcaster.c
	gcc -o $@ $^
listener: listener.c
	gcc -o $@ $^ 
bind_broadcaster: bind_broadcaster.c
	gcc -o $@ $^ 
clean:
	rm -f broadcaster
	rm -f listener
	rm -f bind_broadcaster
