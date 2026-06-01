

#ifndef PROYECTOII_TUTUBOEXCEPCION_H
#define PROYECTOII_TUTUBOEXCEPCION_H
#include "../Librerias.h"


class TuTuboExcepcion : public runtime_error {
public:
    explicit TuTuboExcepcion(const string& msg)
        : runtime_error("Error TuTubo: " + msg) {}
};


#endif //PROYECTOII_TUTUBOEXCEPCION_H
