cmake_minimum_required(VERSION 4.2)
project(modulo_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(modulo_cpp
        src/main.cpp
        src/Banner.cpp
        src/Opciones.cpp
        src/Util.cpp
        src/CursoClass.cpp
        src/HistorialClass.cpp
        src/InteresClass.cpp
        src/PrerrequisitoClass.cpp
)

target_include_directories(modulo_cpp PRIVATE include)