#CXX = clang++
CXXFLAGS = -Wall -Wextra -g -I. -Iinclude  -c 

main: main.cpp
	$(CXX) main.cpp -o main $(CXXFLAGS)

libMKSms-cpp.a: main.o
	ar -r -s bin/Debug/libMKSms-cpp.a obj/Debug/main.o

main.o: main.cpp 
	$(CXX) main.cpp -o obj/Debug/main.o $(CXXFLAGS)
	rm -f bin/Debug/libMKSms-cpp.a 

clean:
	rm -f *.o

