

#ifndef PROYECTOII_JSONMANAGER_H
#define PROYECTOII_JSONMANAGER_H

#include "Librerias.h"
#include "dist/json/json.h"
#include "ListaEnlazada.h"

class Usuario; // forward declaration para evitar inclusion circular

/**
 * Gestiona la persistencia del sistema en formato JSON.
 *
 * Patrón Singleton (extra +5 pts):
 *  - Una sola instancia global gestiona el archivo de datos.
 *  - Acceso mediante JsonManager::getInstance().
 *
 * Principios:
 *  - SRP: solo se ocupa de leer y escribir JSON.
 *  - DIP: trabaja con listas abstractas, no con menús ni lógica de negocio.
 *
 * Estructura del JSON generado:
 * {
 *   "usuarios": [
 *     {
 *       "username": "...",
 *       "password": "...",
 *       "canalesSuscritos": [...],
 *       "notificaciones": [...],
 *       "canal": {
 *         "nombre": "...",
 *         "videos": [
 *           { "nombre":"...", "descripcion":"...", "tipo":"MP4|MPG", "fecha":"..." }
 *         ]
 *       }
 *     }
 *   ]
 * }
 */
class JsonManager {
    // ── Singleton ────────────────────────────────────────────────────────────
    static JsonManager* instancia;
    string archivo;

    explicit JsonManager(const string& arch) : archivo(arch) {}

public:
    JsonManager(const JsonManager&)            = delete;
    JsonManager& operator=(const JsonManager&) = delete;

    /** Devuelve la instancia única. La primera llamada establece la ruta del archivo. */
    static JsonManager& getInstance(const string& arch = "data/tutubo.json");

    // ── Operaciones de archivos ───────────────────────────────────────────────
    /** Serializa todos los usuarios y sus datos al archivo JSON */
    void guardar(const ListaEnlazada<unique_ptr<Usuario>>& usuarios);

    /**
     * Deserializa el archivo JSON y carga los usuarios en la lista.
     * Después de cargar, el llamador debe re-enlazar los Observers.
     */
    void cargar(ListaEnlazada<unique_ptr<Usuario>>& usuarios);

    bool existeArchivo() const;

    const string& getArchivo() const { return archivo; }
};

#endif //PROYECTOII_JSONMANAGER_H