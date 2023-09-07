cmake_minimum_required(VERSION 3.27)
project( RecBot )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

add_executable( recbot_sampler recbot_sampler.cpp )
target_link_libraries( recbot_sampler ${OpenCV_LIBS} )

add_executable( recbot_recon recbot_recon.cpp )
target_link_libraries( recbot_recon ${OpenCV_LIBS} )