
#ifndef PROYECTOII_USUARIOYAEXISTEEXCEPCION_H
#define PROYECTOII_USUARIOYAEXISTEEXCEPCION_H

#include "TuTuboExcepcion.h"


class UsuarioYaExisteExcepcion : public TuTuboExcepcion {
public:
    explicit UsuarioYaExisteExcepcion(const string& username)
        : TuTuboExcepcion("El usuario '" + username + "' ya existe.") {}
};



#endif //PROYECTOII_USUARIOYAEXISTEEXCEPCION_H
