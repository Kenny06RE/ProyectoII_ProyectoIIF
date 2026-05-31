//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_IITERADOR_H
#define PROYECTOII_IITERADOR_H
#include "../Librerias.h"


template<typename T>
class IIterador {
public:
    virtual ~IIterador() = default;
    virtual bool haySiguiente() const = 0;
    virtual const T& siguiente() = 0;
    virtual void reiniciar() = 0;
};


#endif //PROYECTOII_IITERADOR_H
