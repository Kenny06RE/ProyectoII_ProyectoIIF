cmake_minimum_required(VERSION 4.1)
project(ProyectoII)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoII main.cpp
        Librerias.h
        Video.h
        Videomp4.cpp
        Videomp4.h
        VideoMPG.cpp
        VideoMPG.h
        Adaptor/AdapterMPG.cpp
        Adaptor/AdapterMPG.h
        Canal.cpp
        Canal.h
        Usuario.cpp
        Usuario.h
dist/jsoncpp.cpp
dist/json/json.h
        JsonManager.cpp
        JsonManager.h)
