# COMPILER=g++
COMPILER=clang++
OUTFILE=clusterizer

# all: main.cxx sample.h
#      	$(COMPILER) main.cxx -o clusterizer

all: main.cxx sample.h
	$(COMPILER) -stdlib=libc++ main.cxx -o clusterizer
clean:
	rm clusterizer
