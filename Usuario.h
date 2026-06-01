

#ifndef PROYECTOII_USUARIO_H
#define PROYECTOII_USUARIO_H

#include "Librerias.h"
#include "Canal.h"
#include "Observer/IObserver.h"
#include "ListaEnlazada.h"

class Usuario : public IObserver {
    string username;
    string password;
    Canal  canal;
    ListaEnlazada<string> notificaciones;
    ListaEnlazada<string> canalesSuscritos;

public:
    Usuario(const string& username, const string& password);

    Usuario(const Usuario&)= delete;
    Usuario& operator=(const Usuario&) = delete;

    Usuario(Usuario&&) = default;
    Usuario& operator=(Usuario&&) = default;

    //  Patrón Observer
    void actualizar(const string& nombreCanal, const string& nombreVideo) override;
    string getUsername() const override { return username; }

    bool verificarPassword(const string& pwd) const { return password == pwd; }

    void agregarSuscripcion(const string& nombreCanal);
    bool estaSuscritoA(const string& nombreCanal) const;
    void eliminarSuscripcion(const string& nombreCanal);

    Canal& getCanal() { return canal; }
    const Canal& getCanal() const { return canal; }

    const ListaEnlazada<string>& getNotificaciones()   const { return notificaciones; }
    const ListaEnlazada<string>& getCanalesSuscritos() const { return canalesSuscritos; }

    const string& getPassword() const { return password; }

    void restaurarNotificacion(const string& msg) {
        notificaciones.agregar(msg);
    }
};


#endif //PROYECTOII_USUARIO_H