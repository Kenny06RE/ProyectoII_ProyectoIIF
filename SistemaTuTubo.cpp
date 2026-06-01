#include "SistemaTuTubo.h"
#include "VideoMP4.h"
#include "VideoMPG.h"
#include "Adaptor/AdapterMPG.h"
#include "Excepciones/LoginExcepcion.h"
#include "excepciones/UsuarioYaExisteExcepcion.h"
#include "excepciones/SuscripcionException.h"
#include "excepciones/ReproduccionExcepcion.h"
#include "excepciones/ArchivoExcepcion.h"
 

SistemaTuTubo::SistemaTuTubo() : usuarioActivo(nullptr) {

    try {
        if (JsonManager::getInstance().existeArchivo())
            cargarDatos();
    } catch (...) {

    }
}
 
SistemaTuTubo::~SistemaTuTubo() {

    try { guardarDatos(); } catch (...) {}
}
 

Canal* SistemaTuTubo::buscarCanal(const string& nombre) {
    for (int i = 0; i < usuarios.size(); ++i) {
        if (usuarios.obtener(i)->getCanal().getNombre() == nombre)
            return &usuarios.obtener(i)->getCanal();
    }
    return nullptr;
}
 
Usuario* SistemaTuTubo::buscarUsuario(const string& username) {
    for (int i = 0; i < usuarios.size(); ++i) {
        if (usuarios.obtener(i)->getUsername() == username)
            return usuarios.obtener(i).get();
    }
    return nullptr;
}
 
string SistemaTuTubo::obtenerFechaActual() const {
    time_t now = time(nullptr);
    tm* lt  = localtime(&now);
    ostringstream ss;
    ss << (lt->tm_year + 1900) << "-"
       << setw(2) << setfill('0') << (lt->tm_mon + 1) << "-"
       << setw(2) << setfill('0') << lt->tm_mday;
    return ss.str();
}

void SistemaTuTubo::reenlazarObservers() {
    for (int i = 0; i < usuarios.size(); ++i) {
        Usuario& u = *usuarios.obtener(i);
        for (int j = 0; j < u.getCanalesSuscritos().size(); ++j) {
            const string& nombreCanal = u.getCanalesSuscritos().obtener(j);
            Canal* canal = buscarCanal(nombreCanal);
            if (canal) canal->agregarObserver(&u);
        }
    }
}
 
//Crear usuario
string SistemaTuTubo::crearUsuario(const string& username, const string& password) {
    if (username.empty() || password.empty())
        throw LoginExcepcion("Username y password no pueden estar vacios.");
    if (buscarUsuario(username))
        throw UsuarioYaExisteExcepcion(username);
 
    usuarios.agregar(make_unique<Usuario>(username, password));
 
    ostringstream ss;
    ss << "\n Usuario '" << username << "' creado exitosamente.\n";
    ss << "   Canal '" << username << "' generado automaticamente.\n";
    return ss.str();
}
 
//Login
string SistemaTuTubo::login(const string& username, const string& password) {
    Usuario* u = buscarUsuario(username);
    if (!u)
        throw LoginExcepcion("El usuario '" + username + "' no existe.");
    if (!u->verificarPassword(password))
        throw LoginExcepcion("Contrasena incorrecta para '" + username + "'.");
 
    usuarioActivo = u;
 
    ostringstream ss;
    ss << "\n Bienvenido, " << username << "!\n";
    ss << "Canal activo : " << u->getCanal().getNombre() << "\n";
    ss << "Videos : " << u->getCanal().cantidadVideos() << "\n";
    ss << "Suscripciones: " << u->getCanalesSuscritos().size() << "\n";
    ss << "Notificaciones sin leer: " << u->getNotificaciones().size() << "\n";
    return ss.str();
}
 
//Logout
string SistemaTuTubo::logout() {
    if (!usuarioActivo) return "\n No hay sesion activa.\n";
    string user = usuarioActivo->getUsername();
    usuarioActivo = nullptr;
    return "\n Sesion de '" + user + "' cerrada.\n";
}
 
//Subir video
string SistemaTuTubo::subirVideo(const string& nombre,
                                  const string& descripcion,
                                  const string& tipo) {
    if (!usuarioActivo)
        throw LoginExcepcion("Debe hacer login primero.");
    if (nombre.empty())
        throw ReproduccionExcepcion("El nombre del video no puede estar vacio.");
 
    string fecha = obtenerFechaActual();
    unique_ptr<Video> video;
 
    if (tipo == "1") {
        video = make_unique<VideoMP4>(nombre, descripcion, fecha);
    } else if (tipo == "2") {
        auto mpg = make_unique<VideoMPG>(nombre, descripcion, fecha);
        video = make_unique<AdapterMPG>(move(mpg));
    } else {
        throw ReproduccionExcepcion("Tipo invalido. Use 1=MP4, 2=MPG.");
    }
 
    string tipoStr = (tipo == "1") ? "MP4" : "MPG";
    usuarioActivo->getCanal().publicarVideo(move(video));  // Observer notifica aquí
 
    ostringstream ss;
    ss << "\n Video '" << nombre << "' (" << tipoStr << ") subido al canal '"
       << usuarioActivo->getCanal().getNombre() << "'.\n";
    ss << " Notificacion enviada a "
       << usuarioActivo->getCanal().cantidadSuscriptores() << " suscriptores.\n";
    return ss.str();
}
 
//Suscribirse
string SistemaTuTubo::suscribirse(const string& nombreCanal) {
    if (!usuarioActivo)
        throw LoginExcepcion("Debe hacer login primero.");
    if (nombreCanal == usuarioActivo->getUsername())
        throw SuscripcionExcepcion("No puede suscribirse a su propio canal.");
    if (usuarioActivo->estaSuscritoA(nombreCanal))
        throw SuscripcionExcepcion("Ya esta suscrito al canal '" + nombreCanal + "'.");
 
    Canal* canal = buscarCanal(nombreCanal);
    if (!canal)
        throw SuscripcionExcepcion("El canal '" + nombreCanal + "' no existe.");
 
    canal->agregarObserver(usuarioActivo);
    usuarioActivo->agregarSuscripcion(nombreCanal);
 
    return "\n Suscrito al canal '" + nombreCanal + "' correctamente.\n";
}
 
//Desuscribirse
string SistemaTuTubo::desuscribirse(const string& nombreCanal) {
    if (!usuarioActivo)
        throw LoginExcepcion("Debe hacer login primero.");
    if (!usuarioActivo->estaSuscritoA(nombreCanal))
        throw SuscripcionExcepcion("No esta suscrito al canal '" + nombreCanal + "'.");
 
    Canal* canal = buscarCanal(nombreCanal);
    if (canal) canal->eliminarObserver(usuarioActivo->getUsername());
 
    usuarioActivo->eliminarSuscripcion(nombreCanal);
    return "\n Desuscrito del canal '" + nombreCanal + "'.\n";
}
 
//Buscar por nombre
string SistemaTuTubo::buscarVideosPorNombre(const string& query) const {
    if (query.empty()) return "\n Ingrese un termino de busqueda.\n";
 
    ostringstream ss;
    ss << "\n Resultados para \"" << query << "\":\n";
    ss << string(50, '-') << "\n";
 
    bool encontrado = false;
    for (int i = 0; i < usuarios.size(); ++i) {
        const Canal& c = usuarios.obtener(i)->getCanal();
        for (int j = 0; j < c.getVideos().size(); ++j) {
            const Video& v   = *c.getVideos().obtener(j);
            string titulo= v.getNombre();
            string tLower= titulo;
            string qLower= query;
            transform(tLower.begin(), tLower.end(), tLower.begin(), ::tolower);
            transform(qLower.begin(), qLower.end(), qLower.begin(), ::tolower);
            if (tLower.find(qLower) != string::npos) {
                ss << "  [" << v.getTipo() << "] " << v.getNombre()
                   << "  -  Canal: " << c.getNombre()
                   << "  /  Fecha: " << v.getFechaPublicacion() << "\n";
                encontrado = true;
            }
        }
    }
    if (!encontrado) ss << "  No se encontraron videos.\n";
    return ss.str();
}
 
//Buscar por canal
string SistemaTuTubo::buscarVideosPorCanal(const string& nombreCanal) const {
    ostringstream ss;
    ss << "\n Videos del canal '" << nombreCanal << "':\n";
    ss << string(50, '-') << "\n";
 
    for (int i = 0; i < usuarios.size(); ++i) {
        const Canal& c = usuarios.obtener(i)->getCanal();
        if (c.getNombre() == nombreCanal) {
            if (c.getVideos().vacia()) {
                ss << "  (El canal no tiene videos aun)\n";
            } else {
                for (int j = 0; j < c.getVideos().size(); ++j) {
                    const Video& v = *c.getVideos().obtener(j);
                    ss << "  " << (j+1) << ". [" << v.getTipo() << "] "
                       << v.getNombre() << "  /  " << v.getFechaPublicacion() << "\n";
                    ss << "     " << v.getDescripcion() << "\n";
                }
            }
            return ss.str();
        }
    }
    ss << "  Canal no encontrado.\n";
    return ss.str();
}
 
//Reproducir
string SistemaTuTubo::reproducirVideo(const string& nombreCanal,
                                       const string& nombreVideo) {
    Canal* canal = buscarCanal(nombreCanal);
    if (!canal)
        throw ReproduccionExcepcion("Canal '" + nombreCanal + "' no encontrado.");
 
    Video* video = canal->buscarPorNombre(nombreVideo);
    if (!video)
        throw ReproduccionExcepcion("Video '" + nombreVideo +
                                    "' no encontrado en el canal '" + nombreCanal + "'.");
    video->play();
    return "";
}
 
//Listar canales
string SistemaTuTubo::listarCanales() const {
    ostringstream ss;
    ss << "\n Canales registrados (" << usuarios.size() << "):\n";
    ss << string(50, '-') << "\n";
    for (int i = 0; i < usuarios.size(); ++i) {
        const Usuario& u = *usuarios.obtener(i);
        ss << "  " << (i+1) << ". @" << u.getCanal().getNombre()
           << "  (" << u.getCanal().cantidadVideos() << " videos, "
           << u.getCanal().cantidadSuscriptores() << " suscriptores)\n";
    }
    return ss.str();
}
 
//Ver notificaciones
string SistemaTuTubo::verNotificaciones() const {
    if (!usuarioActivo) return "\n Debe hacer login primero.\n";
 
    const ListaEnlazada<string>& nots = usuarioActivo->getNotificaciones();
    ostringstream ss;
    ss << "\n Notificaciones de @" << usuarioActivo->getUsername()
       << " (" << nots.size() << "):\n";
    ss << string(50, '-') << "\n";
 
    if (nots.vacia()) {
        ss << "  (Sin notificaciones)\n";
    } else {
        for (int i = 0; i < nots.size(); ++i)
            ss << "  " << (i+1) << ". " << nots.obtener(i) << "\n";
    }
    return ss.str();
}
 
//Guardar datos
string SistemaTuTubo::guardarDatos() {
    JsonManager::getInstance().guardar(usuarios);
    return "\n Datos guardados en '" +
           JsonManager::getInstance().getArchivo() + "'.\n";
}
 
//Cargar datos
string SistemaTuTubo::cargarDatos() {
    JsonManager::getInstance().cargar(usuarios);
    reenlazarObservers();
    ostringstream ss;
    ss << "\n Datos cargados: " << usuarios.size() << " usuarios.\n";
    return ss.str();
}