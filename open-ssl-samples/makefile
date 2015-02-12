CFLAG = -lssl -g
TARGET = nossl withssl
all: $(TARGET)
nossl: nossl.c
	gcc -o $@ $^ $(CFLAG) 
withssl: withssl.c
	gcc -o $@ $^ $(CFLAG)
clean:
	rm -rf $(TARGET)
