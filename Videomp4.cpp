#include "VideoMP4.h"
 
VideoMP4::VideoMP4(const string& nombre,
                   const string& descripcion,
                   const string& fechaPublicacion)
    : Video(nombre, descripcion, fechaPublicacion) {}
 
void VideoMP4::play() const {
    cout << "\n╔══════════════════════════════════════════╗\n";
    cout << "║  ▶  REPRODUCIENDO  [MP4]                 ║\n";
    cout << "╠══════════════════════════════════════════╣\n";
    cout << "║  Titulo    : " << left << setw(28) << nombre << "║\n";
    cout << "║  Desc.     : " << left << setw(28) << descripcion.substr(0, 28) << "║\n";
    cout << "║  Publicado : " << left << setw(28) << fechaPublicacion << "║\n";
    cout << "╚══════════════════════════════════════════╝\n";
}