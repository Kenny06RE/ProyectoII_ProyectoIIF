
#ifndef PROYECTOII_ITERADORLISTA_H
#define PROYECTOII_ITERADORLISTA_H

#include "IIterador.h"
#include "../Nodo.h"

template<typename T>
class IteradorLista : public IIterador<T> {
private:
    Nodo<T>* inicio;
    Nodo<T>* actual;

public:
    explicit IteradorLista(Nodo<T>* nodoInicio) : inicio(nodoInicio), actual(nodoInicio) {}

    bool haySiguiente() const override {
        return actual != nullptr;
    }

    const T& siguiente() override {
        if (!actual) {
            throw std::out_of_range("No hay mas elementos en el iterador");
        }
        const T& dato = actual->dato;
        actual = actual->siguiente.get();
        return dato;
    }

    void reiniciar() override {
        actual = inicio;
    }
};


#endif //PROYECTOII_ITERADORLISTA_H