

#ifndef PROYECTOII_JSONMANAGER_H
#define PROYECTOII_JSONMANAGER_H

#include "Librerias.h"
#include "dist/json/json.h"
#include "ListaEnlazada.h"

class Usuario; // forward declaration para evitar inclusion circular

class JsonManager {
    //Singleton
    static JsonManager* instancia;
    string archivo;

    explicit JsonManager(const string& arch) : archivo(arch) {}

public:
    JsonManager(const JsonManager&)= delete;
    JsonManager& operator=(const JsonManager&) = delete;
    static JsonManager& getInstance(const string& arch = "data/tutubo.json");

    //Operaciones de archivos
    void guardar(const ListaEnlazada<unique_ptr<Usuario>>& usuarios);

    void cargar(ListaEnlazada<unique_ptr<Usuario>>& usuarios);

    bool existeArchivo() const;

    const string& getArchivo() const { return archivo; }
};

#endif //PROYECTOII_JSONMANAGER_H