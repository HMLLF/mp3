TARGET:=mp3

CC:=arm-linux-gcc

CARCS+=$(wildcard *.c)
OBJS+=$(patsubst %.c,%.o,$(CARCS))

#LIBS+=
#INCL+=

%.o:%c
	$(CC) -c $^ -o $@W
	
$(TARGET):$(OBJS)
	$(CC) $^ -o $@ 
	cp $@ ~/tftp
	
clean:
	rm $(TARGET)$(OBJS)