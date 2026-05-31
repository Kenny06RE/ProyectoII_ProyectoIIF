

#ifndef PROYECTOII_VIDEOMPG_H
#define PROYECTOII_VIDEOMPG_H


#include "Librerias.h"

/**
 * Video en formato MPG (formato legado).
 * NOTA: esta clase NO hereda de Video; usa playAntiguo() en lugar de play().
 * Por eso se requiere el Patrón Adapter para poder usarla de forma unificada.
 *
 * Principio OCP: la clase existente no se modifica, se adapta desde afuera.
 */
class VideoMPG {
    string nombre;
    string descripcion;
    string fechaPublicacion;

public:
    VideoMPG(const string& nombre,
             const string& descripcion,
             const string& fechaPublicacion);

    /** Interfaz legada de reproducción */
    void playAntiguo() const;

    const string& getNombre()           const { return nombre; }
    const string& getDescripcion()      const { return descripcion; }
    const string& getFechaPublicacion() const { return fechaPublicacion; }
};


#endif //PROYECTOII_VIDEOMPG_H