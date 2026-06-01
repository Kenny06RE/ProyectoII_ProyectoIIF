cmake_minimum_required(VERSION 3.20)
project(ProyectoII)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoII
        main.cpp
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
        JsonManager.h
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
        Iterador/IIterador.h
        Iterador/IColeccion.h
        SistemaTuTubo.cpp
        SistemaTuTubo.h
        Iterador/IteradorLista.h
)