#include "JsonManager.h"
#include "Usuario.h"
#include "VideoMP4.h"
#include "Adaptor/AdapterMPG.h"
#include "Excepciones/ArchivoExcepcion.h"
 
//Singleton: inicialización del puntero estático
JsonManager* JsonManager::instancia = nullptr;
 
JsonManager& JsonManager::getInstance(const string& arch) {
    if (!instancia)
        instancia = new JsonManager(arch);
    return *instancia;
}
 
bool JsonManager::existeArchivo() const {
    ifstream f(archivo);
    return f.good();
}
 
//GUARDAR
void JsonManager::guardar(const ListaEnlazada<unique_ptr<Usuario>>& usuarios) {

    ofstream salida(archivo);
    if (!salida.is_open())
        throw ArchivoExcepcion(archivo);
 
    Json::Value raiz;
    Json::Value arrUsuarios(Json::arrayValue);
 
    for (int i = 0; i < usuarios.size(); ++i) {
        const Usuario& u = *usuarios.obtener(i);
        Json::Value objU;
 
        objU["username"] = u.getUsername();
        objU["password"] = u.getPassword();
 
        //Canales suscritos
        Json::Value arrSus(Json::arrayValue);
        for (int j = 0; j < u.getCanalesSuscritos().size(); ++j)
            arrSus.append(u.getCanalesSuscritos().obtener(j));
        objU["canalesSuscritos"] = arrSus;
 
        //Notificaciones
        Json::Value arrNot(Json::arrayValue);
        for (int j = 0; j < u.getNotificaciones().size(); ++j)
            arrNot.append(u.getNotificaciones().obtener(j));
        objU["notificaciones"] = arrNot;
 
        //Canal y sus videos
        Json::Value objCanal;
        objCanal["nombre"] = u.getCanal().getNombre();
 
        Json::Value arrVideos(Json::arrayValue);
        const ListaEnlazada<unique_ptr<Video>>& vids = u.getCanal().getVideos();
        for (int j = 0; j < vids.size(); ++j) {
            const Video& v = *vids.obtener(j);
            Json::Value objV;
            objV["nombre"]= v.getNombre();
            objV["descripcion"]= v.getDescripcion();
            objV["tipo"]= v.getTipo();
            objV["fecha"]= v.getFechaPublicacion();
            arrVideos.append(objV);
        }
        objCanal["videos"] = arrVideos;
        objU["canal"]= objCanal;
 
        arrUsuarios.append(objU);
    }
 
    raiz["usuarios"] = arrUsuarios;

    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  ";
    unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(raiz, &salida);
    salida.close();
}
 
//CARGAR
void JsonManager::cargar(ListaEnlazada<unique_ptr<Usuario>>& usuarios) {
    ifstream entrada(archivo);
    if (!entrada.is_open())
        throw ArchivoExcepcion(archivo);
 
    Json::Value obj;
    Json::Reader reader;
    if (!reader.parse(entrada, obj)) {
        entrada.close();
        return;
    }
    entrada.close();
 
    usuarios.limpiar();
 
    const Json::Value& arrU = obj["usuarios"];
    for (int i = 0; i < (int)arrU.size(); ++i) {
        const Json::Value& ju = arrU[i];
 
        auto usuario = make_unique<Usuario>(
            ju["username"].asString(),
            ju["password"].asString()
        );
 
        //Canales suscritos
        const Json::Value& sus = ju["canalesSuscritos"];
        for (int j = 0; j < (int)sus.size(); ++j)
            usuario->agregarSuscripcion(sus[j].asString());
 
        //Notificaciones
        const Json::Value& nots = ju["notificaciones"];
        for (int j = 0; j < (int)nots.size(); ++j)
            usuario->restaurarNotificacion(nots[j].asString());
 
        //Videos del canal
        const Json::Value& canal= ju["canal"];
        const Json::Value& videos=canal["videos"];
 
        for (int j = 0; j < (int)videos.size(); ++j) {
            const Json::Value& jv = videos[j];
            string nombre= jv["nombre"].asString();
            string desc= jv["descripcion"].asString();
            string tipo= jv["tipo"].asString();
            string fecha= jv["fecha"].asString();
 
            unique_ptr<Video> video;
            if (tipo == "MP4") {
                video = make_unique<VideoMP4>(nombre, desc, fecha);
            } else {

                auto mpg = make_unique<VideoMPG>(nombre, desc, fecha);
                video= make_unique<AdapterMPG>(move(mpg));
            }

            usuario->getCanal().cargarVideo(move(video));
        }
 
        usuarios.agregar(move(usuario));
    }
}