#include "VideoMPG.h"

VideoMPG::VideoMPG(const string& nombre,
                   const string& descripcion,
                   const string& fechaPublicacion)
    : nombre(nombre), descripcion(descripcion), fechaPublicacion(fechaPublicacion) {}

void VideoMPG::playAntiguo() const {
    cout << "\n*******************************************\n";
    cout << "*     REPRODUCIENDO  [MPG-LEGACY]          *\n";
    cout << "********************************************\n";
    cout << "*  Titulo    : " << left << setw(28) << nombre << "*\n";
    cout << "*  Desc.     : " << left << setw(28) << descripcion.substr(0, 28) << "*\n";
    cout << "*  Publicado : " << left << setw(28) << fechaPublicacion << "*\n";
    cout << "*******************************************\n";
    cout << "  [Formato antiguo MPG - reproducido via playAntiguo()]\n";
}
