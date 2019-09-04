#CXX = clang++
CXXFLAGS = -g -O0 -std=c++11  -I.. -I. -Wall -Wextra
OPENSSL_SUPPORT = -DCPPHTTPLIB_OPENSSL_SUPPORT -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto

all: test_mksms
	./test_mksms

test_mksms : test_mksms.cpp  Makefile
	$(CXX) -o test_mksms $(CXXFLAGS) test_mksms.cpp gtest/gtest-all.cc gtest/gtest_main.cc $(OPENSSL_SUPPORT) -pthread

clean:
	rm -f ./test_mksms

