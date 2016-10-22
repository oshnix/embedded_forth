COMP=gcc
TARGET=main
CFLAGS= -ansi -pedantic -Wall -Werror -m32
MFLAGS= -m32
CK= -c -m32
LDK= -o
FILES= main.c memalloc.c
OFILES= main.o memalloc.o

main: main.c
	$(COMP) $(CK) $(FILES)
	$(COMP) $(LDK) $(TARGET) $(CFLAGS) $(OFILES) 
clean: 
	rm -f $(TARGET) $(OFILES)
