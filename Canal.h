
#ifndef PROYECTOII_CANAL_H
#define PROYECTOII_CANAL_H
#include "Librerias.h"
#include "ListaEnlazada.h"
#include "Video.h"
#include "Observer/IObservable.h"
#include "Observer/IObserver.h"


class Canal : public IObservable {
    string nombre;
    ListaEnlazada<unique_ptr<Video>> videos;
    ListaEnlazada<IObserver*>suscriptores;

public:
    explicit Canal(const string& nombre);


    Canal(const Canal&)= delete;
    Canal& operator=(const Canal&) = delete;


    Canal(Canal&&)= default;
    Canal& operator=(Canal&&) = default;


    // Agrega el video al canal y notifica a todos los suscriptores
    void publicarVideo(unique_ptr<Video> video);

    // Busca un video por nombre
    Video* buscarPorNombre(const string& query) const;

    void agregarObserver(IObserver* obs) override;
    void eliminarObserver(const string& username) override;
    void notificar(const string& nombreVideo) override;


    const string& getNombre() const { return nombre; }
    int  cantidadVideos() const { return videos.size(); }
    int  cantidadSuscriptores()const { return suscriptores.size(); }

    const ListaEnlazada<unique_ptr<Video>>& getVideos() const { return videos; }


    void cargarVideo(unique_ptr<Video> video) {
        videos.agregar(move(video));
    }
};


#endif //PROYECTOII_CANAL_H