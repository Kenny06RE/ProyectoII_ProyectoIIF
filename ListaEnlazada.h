//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_LISTAENLAZADA_H
#define PROYECTOII_LISTAENLAZADA_H
#include "Librerias.h"

template<typename T>
class ListaEnlazada {
private:
    unique_ptr<Nodo<T>> raiz;
    int tamano;

public:
    ListaEnlazada() : raiz(nullptr), tamano(0) {}

    ListaEnlazada(const ListaEnlazada&) = delete;
    ListaEnlazada& operator=(const ListaEnlazada&) = delete;

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

    int  size() const { return tamano; }
    bool vacia() const { return tamano == 0; }
    void limpiar() { raiz.reset(); tamano = 0; }

    void forEach(const function<void(const T&)>& fn) const {
        Nodo<T>* actual = raiz.get();
        while (actual) { fn(actual->dato); actual = actual->siguiente.get(); }
    }
};



#endif //PROYECTOII_LISTAENLAZADA_H
