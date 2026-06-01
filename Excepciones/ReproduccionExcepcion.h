

#ifndef PROYECTOII_REPRODUCCIONEXCEPCION_H
#define PROYECTOII_REPRODUCCIONEXCEPCION_H




class ReproduccionExcepcion : public TuTuboExcepcion {
public:
    explicit ReproduccionExcepcion(const string& detalle)
        : TuTuboExcepcion("Error de reproduccion: " + detalle) {}
};


#endif //PROYECTOII_REPRODUCCIONEXCEPCION_H
