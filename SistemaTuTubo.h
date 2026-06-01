
#ifndef PROYECTOII_SISTEMATUTUBO_H
#define PROYECTOII_SISTEMATUTUBO_H

#include "Librerias.h"
#include "ListaEnlazada.h"
#include "Usuario.h"
#include "JsonManager.h"


class SistemaTuTubo {
    ListaEnlazada<unique_ptr<Usuario>> usuarios;
    Usuario* usuarioActivo;


    Canal* buscarCanal(const string& nombreCanal);
    Usuario* buscarUsuario(const string& username);
    string obtenerFechaActual() const;
    void reenlazarObservers();

public:
    SistemaTuTubo();
    ~SistemaTuTubo();


    string crearUsuario(const string& username, const string& password);
    string login(const string& username, const string& password);
    string logout();

    Usuario* getUsuarioActivo() const { return usuarioActivo; }
    bool hayUsuarioActivo() const { return usuarioActivo != nullptr; }

    string subirVideo(const string& nombre, const string& descripcion, const string& tipo);

    //Suscripciones
    string suscribirse(const string& nombreCanal);
    string desuscribirse(const string& nombreCanal);

    //Búsquedas
    string buscarVideosPorNombre(const string& query) const;
    string buscarVideosPorCanal(const string& nombreCanal) const;

    //Reproducción
    string reproducirVideo(const string& nombreCanal, const string& nombreVideo);

    //Persistencia
    string guardarDatos();
    string cargarDatos();

    //Vistas
    string listarCanales() const;
    string verNotificaciones() const;
};


#endif //PROYECTOII_SISTEMATUTUBO_H