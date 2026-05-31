#include "Usuario.h"
 
Usuario::Usuario(const string& username, const string& password)
    : username(username), password(password), canal(username) {}
 
//Observer: recibe notificación de un canal suscrito
void Usuario::actualizar(const string& nombreCanal, const string& nombreVideo) {
    notificaciones.agregar(
        " Nuevo video '" + nombreVideo + "' publicado en el canal '" + nombreCanal + "'"
    );
}
 
//Registrar suscripción
void Usuario::agregarSuscripcion(const string& nombreCanal) {
    canalesSuscritos.agregar(nombreCanal);
}
 
//Verificar suscripción
bool Usuario::estaSuscritoA(const string& nombreCanal) const {
    for (int i = 0; i < canalesSuscritos.size(); ++i) {
        if (canalesSuscritos.obtener(i) == nombreCanal)
            return true;
    }
    return false;
}
 
//Eliminar suscripción
void Usuario::eliminarSuscripcion(const string& nombreCanal) {
    canalesSuscritos.eliminarSi([&](const string& c) {
        return c == nombreCanal;
    });
}