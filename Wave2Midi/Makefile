OBJS	= main.o wave/WaveReader.o
SOURCE	= main.c wave/WaveReader.c
HEADER	= 
OUT	= wav2mid
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

wave/WaveReader.o: wave/WaveReader.c
	$(CC) $(FLAGS) wave/WaveReader.c 


clean:
	rm -f $(OBJS) $(OUT)