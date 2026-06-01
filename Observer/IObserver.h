
#ifndef PROYECTOII_OBSERVER_H
#define PROYECTOII_OBSERVER_H


#include "../Librerias.h"

 
class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void actualizar(const string& nombreCanal, const string& nombreVideo) = 0;

    virtual string getUsername() const = 0;
};




#endif //PROYECTOII_OBSERVER_H
