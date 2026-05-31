//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_LOGINEXCEPCION_H
#define PROYECTOII_LOGINEXCEPCION_H

#include "TuTuboExcepcion.h"

/* Se lanza cuando las credenciales de login son incorrectas
 o el usuario no existe
 */

class LoginExcepcion : public TuTuboExcepcion {
public:
    explicit LoginExcepcion(const string& detalle = "Credenciales incorrectas.")
        : TuTuboExcepcion("Login fallido — " + detalle) {}
};

#endif //PROYECTOII_LOGINEXCEPCION_H
