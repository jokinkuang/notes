ALL: server client select_server
select_server: select_server.c
	gcc select_server.c -o select_server -g
server: server.c
	gcc server.c -o server -g
client: client.c
	gcc client.c -o client -g
clean:
	rm -f server
	rm -f select_server
