cmake_minimum_required(VERSION 3.23)
project(Compress)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

aux_source_directory(src DIR_SRC)
aux_source_directory(src/huffman DIR_SRC_HUFFMAN)

add_executable(Compress ${DIR_SRC} ${DIR_SRC_HUFFMAN})
