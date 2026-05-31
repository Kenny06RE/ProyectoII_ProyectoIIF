//
// Created by favio on 30/5/2026.
//

#ifndef PROYECTOII_NODO_H
#define PROYECTOII_NODO_H
#include "Librerias.h"

template<typename T>
class Nodo {
public:
    T dato;
    unique_ptr<Nodo<T>> siguiente;

    explicit Nodo(T&& val) : dato(move(val)), siguiente(nullptr) {}

    Nodo(const Nodo&) = delete;
    Nodo& operator=(const Nodo&) = delete;
};


#endif //PROYECTOII_NODO_H
