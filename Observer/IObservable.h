
#ifndef PROYECTOII_IOBSERVABLE_H
#define PROYECTOII_IOBSERVABLE_H


#include "../Librerias.h"
#include "IObserver.h"

class IObservable {
public:
    virtual ~IObservable() = default;

    // Registra un nuevo observador/suscriptor
    virtual void agregarObserver(IObserver* obs) = 0;

    // Elimina el observador con el username dado
    virtual void eliminarObserver(const string& username) = 0;

    // Notifica a todos los observadores sobre un nuevo video
    virtual void notificar(const string& nombreVideo) = 0;
};


#endif //PROYECTOII_IOBSERVABLE_H
