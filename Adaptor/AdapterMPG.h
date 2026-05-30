

#ifndef PROYECTOII_ADAPTORMPG_H
#define PROYECTOII_ADAPTORMPG_H


#include "../Video.h"
#include "../VideoMPG.h"

/**
 * Patrón Adapter: adapta VideoMPG (interfaz legada) a la interfaz Video (play()).
 *
 * Problema: VideoMPG tiene playAntiguo() y no hereda de Video.
 * Solución: AdaptadorMPG hereda de Video y delega play() → mpg->playAntiguo().
 *
 * Principios:
 *  - OCP: VideoMPG no se modifica, se envuelve.
 *  - DIP: el canal solo conoce Video*, nunca sabe si es MP4 o MPG.
 *  - Demeter: AdaptadorMPG interactúa solo con su VideoMPG.
 */
class AdapterMPG : public Video {
    unique_ptr<VideoMPG> mpg;   // composición – posee el objeto legado

public:
    /**
     * Recibe el VideoMPG por unique_ptr (transferencia de propiedad).
     * El adaptador copia nombre/descripción/fecha al Video base para coherencia.
     */
    explicit AdapterMPG(unique_ptr<VideoMPG> mpg);

    /** Llama internamente a mpg->playAntiguo() */
    void   play()    const override;
    string getTipo() const override { return "MPG"; }
};

#endif //PROYECTOII_ADAPTORMPG_H