//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_SUSCRIPCIONEXCEPTION_H
#define PROYECTOII_SUSCRIPCIONEXCEPTION_H


#include "TuTuboExcepcion.h"

/*
  Se lanza cuando hay un error en la suscripción porque el canal no existe,
  ya estaba suscrito, intentó suscribirse a su propio canal o no estaba suscrito al intentar desuscribirse
 */

class SuscripcionExcepcion : public TuTuboExcepcion {
public:
    explicit SuscripcionExcepcion(const string& detalle)
        : TuTuboExcepcion("Error de suscripcion — " + detalle) {}
};


#endif //PROYECTOII_SUSCRIPCIONEXCEPTION_H
