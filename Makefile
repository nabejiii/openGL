CXX=g++
CXXFLAGS=`pkg-config opencv4 --cflags`
LDLIBS=-lglut -lGLU -lGL `pkg-config opencv4 --libs`