//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_REPRODUCCIONEXCEPCION_H
#define PROYECTOII_REPRODUCCIONEXCEPCION_H


/*
 Se lanza cuando no se puede reproducir un video porque no
 se encontró el canal o el video
 */

class ReproduccionExcepcion : public TuTuboExcepcion {
public:
    explicit ReproduccionExcepcion(const string& detalle)
        : TuTuboExcepcion("Error de reproduccion — " + detalle) {}
};


#endif //PROYECTOII_REPRODUCCIONEXCEPCION_H
