cmake_minimum_required(VERSION 3.27)
project(CriadorDeProjetoCpp)

include_directories(${CMAKE_SOURCE_DIR}/src/include)

set(SOURCE 
    src/main.cpp
    src/criadorprojetocpp.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)