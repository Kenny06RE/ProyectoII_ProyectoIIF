#include "Canal.h"
#include <algorithm>
#include <cctype>
 
Canal::Canal(const string& nombre) : nombre(nombre) {}
 

void Canal::publicarVideo(unique_ptr<Video> video) {
    string nombreVideo = video->getNombre();
    videos.agregar(move(video));
    notificar(nombreVideo);
}
 

Video* Canal::buscarPorNombre(const string& query) const {
    string qLower = query;
    transform(qLower.begin(), qLower.end(), qLower.begin(), ::tolower);
 
    for (int i = 0; i < videos.size(); ++i) {
        const string& titulo = videos.obtener(i)->getNombre();
        string tLower = titulo;
        transform(tLower.begin(), tLower.end(), tLower.begin(), ::tolower);
        if (tLower.find(qLower) != string::npos)
            return videos.obtener(i).get();
    }
    return nullptr;
}
 

void Canal::agregarObserver(IObserver* obs) {
    // Verificar que no este ya registrado
    for (int i = 0; i < suscriptores.size(); ++i) {
        if (suscriptores.obtener(i)->getUsername() == obs->getUsername())
            return;
    }
    suscriptores.agregar(obs);
}
 
// Observer: eliminar suscriptor
void Canal::eliminarObserver(const string& username) {
    suscriptores.eliminarSi([&](IObserver* const& obs) {
        return obs->getUsername() == username;
    });
}
 
//Observer: notificar a todos los suscriptores
void Canal::notificar(const string& nombreVideo) {
    suscriptores.forEach([&](IObserver* const& obs) {
        obs->actualizar(nombre, nombreVideo);
    });
}