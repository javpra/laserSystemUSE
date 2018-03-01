cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project(geocom_leicaUDP)

# Compiler specific options
 if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11 -pthread -Wl,--no-as-needed)
 endif()

 find_package(Qt5Widgets REQUIRED)

 include_directories(${Qt5Widgets_INCLUDE_DIRS})
 add_definitions(${Qt5Widgets_DEFINITIONS})

 find_package(Qt5Network REQUIRED)

 include_directories(${Qt5Network_INCLUDE_DIRS})
 add_definitions(${Qt5Network_DEFINITIONS})


# Collect all sources
file(GLOB_RECURSE leica_udp "src/*.cpp" "src/*.h" "src/*.inl")


# Add Executable
add_executable(geocom_leicaUDP ${leica_udp})

target_link_libraries(geocom_leicaUDP LINK_PUBLIC ${Qt5Widgets_LIBRARIES})
target_link_libraries(geocom_leicaUDP LINK_PUBLIC ${Qt5Network_LIBRARIES})
target_include_directories(geocom_leicaUDP PUBLIC ${PROJECT_SOURCE_DIR}/src)
