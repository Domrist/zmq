cmake_minimum_required(VERSION 3.22)

project(ZeroMq)

find_package(cppzmq REQUIRED)

add_executable(main
	server.cpp
)

add_executable(client client.cpp)

target_link_libraries(main cppzmq)
target_link_libraries(client cppzmq)
