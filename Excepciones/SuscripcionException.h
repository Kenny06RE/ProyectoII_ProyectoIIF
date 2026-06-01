
#ifndef PROYECTOII_SUSCRIPCIONEXCEPTION_H
#define PROYECTOII_SUSCRIPCIONEXCEPTION_H


#include "TuTuboExcepcion.h"


class SuscripcionExcepcion : public TuTuboExcepcion {
public:
    explicit SuscripcionExcepcion(const string& detalle)
        : TuTuboExcepcion("Error de suscripcion: " + detalle) {}
};


#endif //PROYECTOII_SUSCRIPCIONEXCEPTION_H
