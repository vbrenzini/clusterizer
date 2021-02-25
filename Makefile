COMPILER=g++
OUTFILE=clusterizer

all: main.cxx sample.h
	$(COMPILER) main.cxx -o clusterizer

clean:
	rm clusterizer
