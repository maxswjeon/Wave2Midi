OBJS	= Wave2Midi/main.o Wave2Midi/wave/WaveReader.o
SOURCE	= Wave2Midi/main.cpp Wave2Midi/wave/WaveReader.cpp
HEADER	= 
OUT	= wav2mid
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 
MAKE = make

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: Wave2Midi/main.cpp
	$(CC) $(FLAGS) Wave2Midi/main.cpp 

wave/WaveReader.o: Wave2Midi/wave/WaveReader.cpp
	$(CC) $(FLAGS) Wave2Midi/wave/WaveReader.cpp -o Wave2Midi/wave/WaveReader.o


clean:
	rm -f $(OBJS) $(OUT)