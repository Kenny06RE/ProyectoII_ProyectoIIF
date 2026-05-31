cmake_minimum_required(VERSION 4.1)
project(ProyectoII)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoII main.cpp
        Librerias.h
        Excepciones/TuTuboExcepcion.h
        Excepciones/ArchivoExcepcion.h
        Excepciones/ReproduccionExcepcion.h
        Excepciones/SuscripcionException.h
        Excepciones/UsuarioYaExisteExcepcion.h
        Excepciones/LoginExcepcion.h
        Observer/IObserver.h
        Observer/IObservable.h
        ListaEnlazada.h
        Nodo.h
)
