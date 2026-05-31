//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_LISTAENLAZADA_H
#define PROYECTOII_LISTAENLAZADA_H
#include "Librerias.h"
#include "Nodo.h"
#include "Iterador/IIterador.h"
#include "Iterador/IColeccion.h"


// ── 1. Declaración hacia adelante de la clase externa del Iterador Concreto ──
template<typename T>
class IteradorLista;

// ── 2. Clase ListaEnlazada heredando de IColeccion ───────────────────────────
template<typename T>
class ListaEnlazada : public IColeccion<T> {
private:
    unique_ptr<Nodo<T>> raiz; // Usa tu clase externa Nodo<T>
    int tamano;

    // Hacemos que el Iterador Concreto sea amigo para que pueda leer la raíz
    friend class IteradorLista<T>;

public:
    ListaEnlazada() : raiz(nullptr), tamano(0) {}

    ListaEnlazada(const ListaEnlazada&) = delete;
    ListaEnlazada& operator=(const ListaEnlazada&) = delete;

    // Implementación del método de la interfaz IColeccion
    unique_ptr<IIterador<T>> crearIterador() const override {
        return make_unique<IteradorLista<T>>(raiz.get());
    }

    // ── Operaciones básicas de la lista ───────────────────────────────────────
    void agregar(T elemento) {
        auto nuevoNodo = make_unique<Nodo<T>>(move(elemento));
        if (!raiz) {
            raiz = move(nuevoNodo);
        } else {
            Nodo<T>* actual = raiz.get();
            while (actual->siguiente) actual = actual->siguiente.get();
            actual->siguiente = move(nuevoNodo);
        }
        ++tamano;
    }

    void eliminar(int indice) {
        if (indice < 0 || indice >= tamano)
            throw out_of_range("Indice fuera del rango");
        if (indice == 0) {
            raiz = move(raiz->siguiente);
        } else {
            Nodo<T>* actual = raiz.get();
            for (int i = 0; i < indice - 1; ++i) actual = actual->siguiente.get();
            actual->siguiente = move(actual->siguiente->siguiente);
        }
        --tamano;
    }

    bool eliminarSi(const function<bool(const T&)>& pred) {
        if (!raiz) return false;
        if (pred(raiz->dato)) {
            raiz = move(raiz->siguiente);
            --tamano;
            return true;
        }
        Nodo<T>* actual = raiz.get();
        while (actual->siguiente) {
            if (pred(actual->siguiente->dato)) {
                actual->siguiente = move(actual->siguiente->siguiente);
                --tamano;
                return true;
            }
            actual = actual->siguiente.get();
        }
        return false;
    }

    const T& obtener(int indice) const {
        if (indice < 0 || indice >= tamano)
            throw out_of_range("Indice fuera del rango");
        Nodo<T>* actual = raiz.get();
        for (int i = 0; i < indice; ++i) actual = actual->siguiente.get();
        return actual->dato;
    }

    T& obtener(int indice) {
        if (indice < 0 || indice >= tamano)
            throw out_of_range("Indice fuera del rango");
        Nodo<T>* actual = raiz.get();
        for (int i = 0; i < indice; ++i) actual = actual->siguiente.get();
        return actual->dato;
    }

    void forEach(const function<void(const T&)>& fn) const {
        Nodo<T>* actual = raiz.get();
        while (actual) { fn(actual->dato); actual = actual->siguiente.get(); }
    }

    void forEach(const function<void(T&)>& fn) {
        Nodo<T>* actual = raiz.get();
        while (actual) { fn(actual->dato); actual = actual->siguiente.get(); }
    }

    T* buscar(const function<bool(const T&)>& pred) {
        Nodo<T>* actual = raiz.get();
        while (actual) {
            if (pred(actual->dato)) return &actual->dato;
            actual = actual->siguiente.get();
        }
        return nullptr;
    }

    const T* buscar(const function<bool(const T&)>& pred) const {
        Nodo<T>* actual = raiz.get();
        while (actual) {
            if (pred(actual->dato)) return &actual->dato;
            actual = actual->siguiente.get();
        }
        return nullptr;
    }

    int  size()  const { return tamano; }
    bool vacia() const { return tamano == 0; }
    void limpiar()     { raiz.reset(); tamano = 0; }
};

// ── 3. Implementación del Iterador Concreto Externo heredando de IIterador ──
template<typename T>
class IteradorLista : public IIterador<T> {
private:
    Nodo<T>* inicio;  // Guarda la posición inicial para reiniciar
    Nodo<T>* actual;  // Posición actual del recorrido

public:
    explicit IteradorLista(Nodo<T>* nodoInicio) : inicio(nodoInicio), actual(nodoInicio) {}

    bool haySiguiente() const override {
        return actual != nullptr;
    }

    const T& siguiente() override {
        if (!actual) {
            throw out_of_range("No hay mas elementos en el iterador");
        }
        const T& dato = actual->dato;
        actual = actual->siguiente.get(); // Avanza al siguiente nodo
        return dato;
    }

    void reiniciar() override {
        actual = inicio;
    }
};



#endif //PROYECTOII_LISTAENLAZADA_H
