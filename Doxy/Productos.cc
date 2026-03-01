/** @file Productos.cc
    @brief Código de la clase Productos
*/


#include "Productos.hh"

Productos::Productos() {
    vector<int> peso;
    vector<int> volumen;
}

void Productos::modificar_peso(int& id, int& nuevopeso) {
    this->peso[id-1] = nuevopeso;
}

void Productos::modificar_volumen(int& id, int& nuevovolumen) {
    this->volumen[id-1] = nuevovolumen;
}

void Productos::anadir_producto(int& pesoprod, int& volumenprod) {
    this->peso.push_back(pesoprod);
    this->volumen.push_back(volumenprod);
}

int Productos::consultar_peso(int& id) const {
    return peso[id-1];
}

int Productos::consultar_volumen(int& id) const {
    return volumen[id-1];
}

int Productos::consultar_cantidad() const {
    return peso.size();
}

void Productos::escribir(int& id) const {
    cout << id << ' ' << consultar_peso(id) << ' ' << consultar_volumen(id) << endl;
}