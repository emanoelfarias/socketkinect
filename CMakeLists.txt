cmake_minimum_required(VERSION 2.8)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}/bin
    )

add_definitions(
    -std=c++11
    )

include_directories(
    $ENV{OPENNI2_INCLUDE}
   
   )

link_directories(
    $ENV{OPENNI2_REDIST}
   
    )

link_libraries(
    -lOpenNI2
    )

add_executable(
    main
    src/Socket.cpp	
    src/ServerSocket.cpp	
    src/main.cpp
    )
