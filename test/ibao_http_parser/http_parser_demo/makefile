all: http_parser_demo percent_show
http_parser_demo: http_parser_demo.c http_parser.c http_parser.h
	gcc -o $@ http_parser_demo.c http_parser.c
percent_show: percent_show.c
	gcc -o $@ percent_show.c
clean:
	rm -f http_parser_demo
