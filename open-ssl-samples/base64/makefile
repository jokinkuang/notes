CFLAG = -lssl -lcrypto -g
TARGET = base64_demo
all: $(TARGET)
base64_demo: base64_demo.c
	gcc -o $@ $^ $(CFLAG) 
clean:
	rm -rf $(TARGET)
