

#ifndef PROYECTOII_VIDEOMP4_H
#define PROYECTOII_VIDEOMP4_H

#include <fenv.h>

#include "Video.h"

class VideoMP4 : public Video {
public:
    VideoMP4(const string& nombre,
             const string& descripcion,
             const string& fechaPublicacion);

    void play() const override;
    string getTipo() const override { return "MP4"; }
};

#endif //PROYECTOII_VIDEOMP4_H
