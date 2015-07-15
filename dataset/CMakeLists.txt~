cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(csv_writer)

find_package(OpenCV REQUIRED)
find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (csv_writer csv_writer.cpp hira_label.cpp)
target_link_libraries (csv_writer ${PCL_LIBRARIES} ${OpenCV_LIBS})
