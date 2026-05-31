//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_TUTUBOEXCEPCION_H
#define PROYECTOII_TUTUBOEXCEPCION_H
#include "../Librerias.h"

// Excepción base del sistema. Todas las demás heredan de esta.

class TuTuboExcepcion : public runtime_error {
public:
    explicit TuTuboExcepcion(const string& msg)
        : runtime_error("Error TuTubo: " + msg) {}
};


#endif //PROYECTOII_TUTUBOEXCEPCION_H
