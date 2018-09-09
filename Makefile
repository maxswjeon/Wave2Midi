OBJS	= main.o wave/WaveReader.o
SOURCE	= main.cpp wave/WaveReader.cpp
HEADER	= 
OUT	= wav2mid
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

wave/WaveReader.o: wave/WaveReader.cpp
	$(CC) $(FLAGS) wave/WaveReader.cpp -o wave/WaveReader.o


clean:
	rm -f $(OBJS) $(OUT)