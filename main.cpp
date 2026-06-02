#include "SistemaTuTubo.h"
#include "excepciones/TuTuboExcepcion.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;


void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerOpcion(int min, int max) {
    int op;
    while (!(cin >> op) || op < min || op > max) {
        cout << "  Opcion invalida. Ingrese entre " << min << " y " << max << ": ";
        cin.clear();
        limpiarBuffer();
    }
    limpiarBuffer();
    return op;
}

string leerLinea(const string& prompt) {
    string linea;
    cout << prompt;
    getline(cin, linea);
    return linea;
}

void pausar() {
    cout << "\n  Presione ENTER para continuar...";
    cin.get();
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void mostrarCabecera(const string& titulo, const string& usuarioActivo = "") {
    cout << "\n";
    cout << "****************************************************\n";
    cout << "*              TU TUBO - Sistema de Videos         *\n";
    cout << "****************************************************\n";
    cout << "*  " << left << setw(48) << titulo << "*\n";
    if (!usuarioActivo.empty())
        cout << "*  Usuario activo: @"<< left << setw(32)<< usuarioActivo<<"*\n";
        cout << "****************************************************\n";
}

//Menu Usuarios
void menuUsuarios(SistemaTuTubo& sistema) {
    bool salir = false;
    while (!salir) {
        string activo = sistema.hayUsuarioActivo()
                      ? sistema.getUsuarioActivo()->getUsername() : "(sin sesion)";
        mostrarCabecera("MENU DE USUARIOS", activo);
        cout << "\n";
        cout << "  1. Crear Usuario\n";
        cout << "  2. Hacer Login\n";
        cout << "  3. Subir Video a mi Canal\n";
        cout << "  4. Suscribirme a un Canal\n";
        cout << "  5. Desuscribirme de un Canal\n";
        cout << "  6. Ver mis Notificaciones\n";
        cout << "  7. Ver lista de Canales\n";
        cout << "  8. Logout\n";
        cout << "  9. Salir\n";
        cout << "\n  Opcion: ";
        int op = leerOpcion(1, 9);

        try {
            switch (op) {
            case 1: {
                cout << "\n--- Crear Usuario ---\n";
                string user = leerLinea("  Username: ");
                string pwd  = leerLinea("  Password: ");
                cout << sistema.crearUsuario(user, pwd);
                break;
            }
            case 2: {
                cout << "\n--- Login ---\n";
                string user = leerLinea("  Username: ");
                string pwd  = leerLinea("  Password: ");
                cout << sistema.login(user, pwd);
                break;
            }
            case 3: {
                if (!sistema.hayUsuarioActivo()) {
                    cout << "\n Debe hacer login primero.\n";
                    break;
                }
                cout << "\n--- Subir Video ---\n";
                string nombre = leerLinea("  Nombre del video: ");
                string desc   = leerLinea("  Descripcion: ");
                cout << "  Formato (1=MP4, 2=MPG): ";
                int tipo = leerOpcion(1, 2);
                cout << sistema.subirVideo(nombre, desc, to_string(tipo));
                break;
            }
            case 4: {
                if (!sistema.hayUsuarioActivo()) { cout << "\n Debe hacer login primero.\n"; break; }
                cout << sistema.listarCanales();
                string canal = leerLinea("\n  Nombre del canal a suscribir: ");
                cout << sistema.suscribirse(canal);
                break;
            }
            case 5: {
                if (!sistema.hayUsuarioActivo()) { cout << "\n Debe hacer login primero.\n"; break; }
                string canal = leerLinea("  Nombre del canal a desuscribir: ");
                cout << sistema.desuscribirse(canal);
                break;
            }
            case 6:
                cout << sistema.verNotificaciones();
                break;
            case 7:
                cout << sistema.listarCanales();
                break;
            case 8:
                cout << sistema.logout();
                break;
            case 9:
                salir = true;
                break;
            }
        } catch (const TuTuboExcepcion& e) {
            cout << "\n Error: " << e.what() << "\n";
        }

        if (!salir) pausar();
    }
}

//Menú Videos
void menuVideos(SistemaTuTubo& sistema) {
    bool salir = false;
    while (!salir) {
        string activo = sistema.hayUsuarioActivo()
                      ? sistema.getUsuarioActivo()->getUsername() : "(sin sesion)";
        mostrarCabecera("MENU DE VIDEOS", activo);
        cout << "\n";
        cout << "  1. Buscar Videos por Nombre\n";
        cout << "  2. Buscar Videos por Canal de Usuario\n";
        cout << "  3. Reproducir Video\n";
        cout << "  4. Salir\n";
        cout << "\n  Opcion: ";
        int op = leerOpcion(1, 4);

        try {
            switch (op) {
            case 1: {
                string query = leerLinea("\n  Termino de busqueda: ");
                cout << sistema.buscarVideosPorNombre(query);
                break;
            }
            case 2: {
                cout << sistema.listarCanales();
                string canal = leerLinea("\n  Nombre del canal: ");
                cout << sistema.buscarVideosPorCanal(canal);
                break;
            }
            case 3: {
                cout << sistema.listarCanales();
                string canal = leerLinea("\n  Canal: ");
                cout << sistema.buscarVideosPorCanal(canal);
                string video = leerLinea("  Nombre del video (o parte): ");
                sistema.reproducirVideo(canal, video);
                break;
            }
            case 4:
                salir = true;
                break;
            }
        } catch (const TuTuboExcepcion& e) {
            cout << "\n Error: " << e.what() << "\n";
        }

        if (!salir) pausar();
    }
}

//Menú Principal
int main() {
    SistemaTuTubo sistema;

    bool salir = false;
    while (!salir) {
        string activo = sistema.hayUsuarioActivo()
                      ? sistema.getUsuarioActivo()->getUsername() : "(sin sesion)";
        mostrarCabecera("MENU PRINCIPAL", activo);
        cout << "\n";
        cout << "  1. Manejo de Usuarios\n";
        cout << "  2. Manejo de Videos\n";
        cout << "  3. Guardar Datos Manualmente\n";
        cout << "  4. Recuperar Datos Manualmente\n";
        cout << "  5. Salir\n";
        cout << "\n  Opcion: ";
        int op = leerOpcion(1, 5);

        try {
            switch (op) {
            case 1: menuUsuarios(sistema); break;
            case 2: menuVideos(sistema);   break;
            case 3: cout << sistema.guardarDatos();   pausar(); break;
            case 4: cout << sistema.cargarDatos();    pausar(); break;
            case 5:
                cout << "\n Guardando datos y cerrando...\n";
                salir = true;
                break;
            }
        } catch (const TuTuboExcepcion& e) {
            cout << "\n Error: " << e.what() << "\n";
            pausar();
        } catch (const exception& e) {
            cout << "\n Error inesperado: " << e.what() << "\n";
            pausar();
        }
    }

    return 0;
}