#include "AdapterMPG.h"
 
AdapterMPG::AdapterMPG(unique_ptr<VideoMPG> v)
    : Video(v->getNombre(), v->getDescripcion(), v->getFechaPublicacion()),
      mpg(move(v)) {}
 
// Patrón Adapter: la llamada unificada play() delega en la interfaz legada
void AdapterMPG::play() const {
    mpg->playAntiguo();
}
 