CXX=$(HOME)/mingw-cross/usr/bin/i686-pc-mingw32-g++
AR=$(HOME)/mingw-cross/usr/bin/i686-pc-mingw32-ar
CXXFLAGS=-D__WINDOWS_MM__ -I./rtmidi-1.0.12/ -I./Python27/include -O3 -fexpensive-optimizations

all: libpyramid.a

RtMidi.o: rtmidi-1.0.12/RtMidi.cpp
	$(CXX) $(CXXFLAGS) -c rtmidi-1.0.12/RtMidi.cpp

MIDIListener.o: MIDIListener.cpp
	$(CXX) $(CXXFLAGS) -c MIDIListener.cpp

MIDIWriter.o: MIDIWriter.cpp
	$(CXX) $(CXXFLAGS) -c MIDIWriter.cpp

MIDIMapper.o: MIDIMapper.cpp
	$(CXX) $(CXXFLAGS) -c MIDIMapper.cpp

pyramid_wrap.cxx: pyramid.i PythonMapper.h
	swig -Wall -features directors -c++ -python pyramid.i

pyramid_wrap.o: pyramid_wrap.cxx
	$(CXX) $(CXXFLAGS) -c pyramid_wrap.cxx

Pyramid.o: Pyramid.cpp
	$(CXX) $(CXXFLAGS) -c Pyramid.cpp

libpyramid.a: RtMidi.o MIDIListener.o MIDIWriter.o MIDIMapper.o pyramid_wrap.o Pyramid.o
	$(AR) rs libpyramid.a RtMidi.o MIDIListener.o MIDIWriter.o MIDIMapper.o pyramid_wrap.o Pyramid.o

clean:
	rm -f *.o libpyramid.a pyramid_wrap.cxx
