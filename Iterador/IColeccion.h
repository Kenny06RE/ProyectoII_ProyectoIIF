//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_ICOLECCION_H
#define PROYECTOII_ICOLECCION_H
#include "../Librerias.h"

template<typename T>
class IColeccion {
public:
    virtual ~IColeccion() = default;
    virtual unique_ptr<IIterador<T>> crearIterador() const = 0;
};


#endif //PROYECTOII_ICOLECCION_H
