/** @file Barco.cc
    @brief Código de la clase Barco
*/


#include "Barco.hh"

Barco::Barco() {
    pair<int,int> comprando;
    pair<int,int> vendiendo;
    vector<string> viajes;
}

void Barco::modificar_comprando(int& id, int c) {
    this->comprando.first = id;
    this->comprando.second = c;
}

void Barco::modificar_vendiendo(int& id, int c) {
    this->vendiendo.first = id;
    this->vendiendo.second = c;
}

void Barco::agregar_viaje(string& name) {
    viajes.push_back(name);
}

void Barco::borrar_viajes() {
    vector<string> nuevosviajes;
    this->viajes = nuevosviajes;
}

void Barco::escribir_viajes() const {
    for (auto it =  this->viajes.begin(); it != this->viajes.end(); ++it) cout << *it << endl;
}
void Barco::restar_comprando(int& n) {
    this->comprando.second -= n;
}

void Barco::restar_vendiendo(int& n) {
    this->vendiendo.second -= n;
}

int Barco::consultar_comprando() const {
    int c = comprando.first;
    return c;
}

int Barco::consultar_comprando_cantidad() const {
    int cc = comprando.second;
    return cc;
}

int Barco::consultar_vendiendo() const {
    int v = vendiendo.first;
    return v;
}

int Barco::consultar_vendiendo_cantidad() const {
    int vc = vendiendo.second;
    return vc;
}








