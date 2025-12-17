cmake_minimum_required(VERSION 3.22)

project(visitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(visitor
	main.cpp
	instructions.h instructions.cpp
	program.h program.cpp
	visitor.h visitor.cpp
)
