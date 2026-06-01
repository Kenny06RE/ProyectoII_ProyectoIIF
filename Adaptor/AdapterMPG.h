
#ifndef PROYECTOII_ADAPTORMPG_H
#define PROYECTOII_ADAPTORMPG_H


#include "../Video.h"
#include "../VideoMPG.h"

class AdapterMPG : public Video {
    unique_ptr<VideoMPG> mpg;

public:

    explicit AdapterMPG(unique_ptr<VideoMPG> mpg);

    void play()const override;
    string getTipo() const override { return "MPG"; }
};

#endif //PROYECTOII_ADAPTORMPG_H