//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_ARCHIVOEXCEPCION_H
#define PROYECTOII_ARCHIVOEXCEPCION_H
#include "TuTuboExcepcion.h"


// Se lanza cuando no se puede abrir o escribir el archivo

class ArchivoExcepcion : public TuTuboExcepcion {
public:
    explicit ArchivoExcepcion(const string& archivo)
        : TuTuboExcepcion("No se pudo abrir el archivo: " + archivo) {}
};


#endif //PROYECTOII_ARCHIVOEXCEPCION_H
