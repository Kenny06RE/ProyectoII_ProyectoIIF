

#ifndef PROYECTOII_VIDEOMPG_H
#define PROYECTOII_VIDEOMPG_H


#include "Librerias.h"

class VideoMPG {
    string nombre;
    string descripcion;
    string fechaPublicacion;

public:
    VideoMPG(const string& nombre,
             const string& descripcion,
             const string& fechaPublicacion);


    void playAntiguo() const;

    const string& getNombre() const { return nombre; }
    const string& getDescripcion() const { return descripcion; }
    const string& getFechaPublicacion() const { return fechaPublicacion; }
};


#endif //PROYECTOII_VIDEOMPG_H