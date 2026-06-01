
#ifndef PROYECTOII_LOGINEXCEPCION_H
#define PROYECTOII_LOGINEXCEPCION_H

#include "TuTuboExcepcion.h"



class LoginExcepcion : public TuTuboExcepcion {
public:
    explicit LoginExcepcion(const string& detalle = "Credenciales incorrectas.")
        : TuTuboExcepcion("Login fallido: " + detalle) {}
};

#endif //PROYECTOII_LOGINEXCEPCION_H
