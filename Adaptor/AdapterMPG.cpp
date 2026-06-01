#include "AdapterMPG.h"
 
AdapterMPG::AdapterMPG(unique_ptr<VideoMPG> v)
    : Video(v->getNombre(), v->getDescripcion(), v->getFechaPublicacion()),
      mpg(move(v)) {}

void AdapterMPG::play() const {
    mpg->playAntiguo();
}
 