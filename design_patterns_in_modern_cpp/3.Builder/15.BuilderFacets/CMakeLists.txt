cmake_minimum_required(VERSION 3.16.0)
project (FluentBuilder)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(Facets Facets.cpp ${SOURCES})