cmake_minimum_required(VERSION 3.23)
project(Dijkstra)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dijkstra main.cpp Dijkstra_pq.h Dijkstra.h Node.h Arc.h Graph.h Graph_pq.h CompareDistance.h)
find_package(TBB)
target_link_libraries(Dijkstra TBB::tbb)