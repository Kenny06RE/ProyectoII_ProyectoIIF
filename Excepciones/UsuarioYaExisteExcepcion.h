//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_USUARIOYAEXISTEEXCEPCION_H
#define PROYECTOII_USUARIOYAEXISTEEXCEPCION_H

#include "TuTuboExcepcion.h"

/* Se lanza al intentar crear un usuario con un username que ya existe. */

class UsuarioYaExisteExcepcion : public TuTuboExcepcion {
public:
    explicit UsuarioYaExisteExcepcion(const string& username)
        : TuTuboExcepcion("El usuario '" + username + "' ya existe.") {}
};



#endif //PROYECTOII_USUARIOYAEXISTEEXCEPCION_H
