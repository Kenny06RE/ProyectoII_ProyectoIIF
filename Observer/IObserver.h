//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_OBSERVER_H
#define PROYECTOII_OBSERVER_H


#include "../Librerias.h"

// Interfaz del Patrón Observer – rol: Observador (subscriber).
 
class IObserver {
public:
    virtual ~IObserver() = default;

    /**
     * Llamado por el Observable cuando publica un nuevo video.
     * @param nombreCanal  Canal que publicó el video
     * @param nombreVideo  Nombre del video publicado
     */
    virtual void actualizar(const string& nombreCanal, const string& nombreVideo) = 0;

    /** Identificador único del observador (username) */
    virtual string getUsername() const = 0;
};




#endif //PROYECTOII_OBSERVER_H
