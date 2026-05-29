
#ifndef PROYECTOII_VIDEO_H
#define PROYECTOII_VIDEO_H

#include "Librerias.h"

/**
 * Clase abstracta que representa un video en el sistema "Tu Tubo".
 *
 * Principios aplicados:
 *  - OCP (SOLID): abierta a extensión (nuevos formatos), cerrada a modificación.
 *  - Parnas: los detalles de reproducción están encapsulados en cada subclase.
 *  - Demeter: la clase no accede a estructuras internas de otras clases.
 */
class Video {
protected:
    string nombre;
    string descripcion;
    string fechaPublicacion;

public:
    Video(const string& nombre,
          const string& descripcion,
          const string& fechaPublicacion)
        : nombre(nombre), descripcion(descripcion), fechaPublicacion(fechaPublicacion) {}

    virtual ~Video() = default;


    virtual void play() const = 0;


    virtual string getTipo() const = 0;

    const string& getNombre()           const { return nombre; }
    const string& getDescripcion()      const { return descripcion; }
    const string& getFechaPublicacion() const { return fechaPublicacion; }
};

#endif //PROYECTOII_VIDEO_H