CXX=/home/marc/mingw-cross/usr/bin/i686-pc-mingw32-g++
CXXFLAGS=-D__WINDOWS_MM__ -I./rtmidi-1.0.12/ -I./Python27/include -g

all: pyramid

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

pyramid: RtMidi.o MIDIListener.o MIDIWriter.o MIDIMapper.o pyramid_wrap.o Pyramid.o
	$(CXX) $(CXXFLAGS) -o pyramid RtMidi.o MIDIListener.o MIDIWriter.o MIDIMapper.o pyramid_wrap.o Pyramid.o -lwinmm Python27/libpython27.a

clean:
	rm -f *.o pyramid pyramid_wrap.cxx
