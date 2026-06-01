
#ifndef PROYECTOII_ARCHIVOEXCEPCION_H
#define PROYECTOII_ARCHIVOEXCEPCION_H
#include "TuTuboExcepcion.h"




class ArchivoExcepcion : public TuTuboExcepcion {
public:
    explicit ArchivoExcepcion(const string& archivo)
        : TuTuboExcepcion("No se pudo abrir el archivo: " + archivo) {}
};


#endif //PROYECTOII_ARCHIVOEXCEPCION_H
