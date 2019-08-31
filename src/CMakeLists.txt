cmake_miimum_required(VERSION 3.10)
project(mksms)

set(SRCS mksms.hpp httplib.hpp json.hpp)

add_library(mksms ${SRCS})