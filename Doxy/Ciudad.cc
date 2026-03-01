/** @file Ciudad.cc
    @brief Código de la clase Ciudad 
*/

#include "Ciudad.hh"



Ciudad::Ciudad() {
    string nombre;
    map <int,int> inv_tiene;
    map <int,int> inv_necesarios;
    pesototal = 0;
    volumentotal = 0;
}

void Ciudad::modificar_peso_total(int& nuevopesototal) {
    this->pesototal = nuevopesototal;
}

void Ciudad::modificar_volumen_total(int& nuevovolumentotal) {
    this->volumentotal = nuevovolumentotal;
}

void Ciudad::determinar_cantidad(int& id, int& cantidad, const Productos& prod) {
    if (inv_tiene[id] == 0) {
        inv_tiene[id] = cantidad;
        this->pesototal += cantidad*prod.consultar_peso(id);
        this->volumentotal += cantidad*prod.consultar_volumen(id);
    }
    else {
        int cantidadanterior = inv_tiene[id];
        int diferencia = cantidad - cantidadanterior; 
        inv_tiene[id] = cantidad;
        this->pesototal += diferencia*prod.consultar_peso(id);  
        this->volumentotal += diferencia*prod.consultar_volumen(id);
    }
}

void Ciudad::determinar_necesarios(int& id, int& necesarios) {
    inv_necesarios[id] = necesarios;
}

void Ciudad::sumar_producto(int& id, int& cantidad, const Productos& prod) {
    inv_tiene[id] += cantidad;
    this->pesototal += cantidad*prod.consultar_peso(id);
    this->volumentotal += cantidad*prod.consultar_volumen(id);
}

void Ciudad::restar_producto(int& id, int& cantidad, const Productos& prod) {
    inv_tiene[id] -= cantidad;
    this->pesototal -= cantidad*prod.consultar_peso(id);
    this->volumentotal -= cantidad*prod.consultar_volumen(id);
}

void Ciudad::borrar_producto(int id, const Productos& prod) {
    this->pesototal -= inv_tiene[id]*prod.consultar_peso(id);
    this->volumentotal -= inv_tiene[id]*prod.consultar_volumen(id);
    inv_tiene.erase(id);
    inv_necesarios.erase(id);
}

void Ciudad::eliminar_inventario() {
    inv_tiene.clear();
    inv_necesarios.clear();
    this->pesototal = 0;
    this->volumentotal = 0;
}
bool Ciudad::existe_producto(int& id) const {
    auto it = this->inv_tiene.find(id);
    return it != this->inv_tiene.end();
}

int Ciudad::consultar_cantidad(int& id) const {
    return inv_tiene.at(id);
}

int Ciudad::consultar_necesarios(int& id) const {
    return inv_necesarios.at(id);
}

map<int,int> Ciudad::consultar_inv() const {
    return inv_tiene;
}

int  Ciudad::consultar_tamano_inv() const {
      return inv_tiene.size();
}

int Ciudad::consultar_peso_total() const {
    return pesototal;
}

int Ciudad::consultar_volumen_total() const {
    return volumentotal;
}

void Ciudad::escribir_inv_ciudad() const {
    for (auto it = inv_tiene.begin(); it != inv_tiene.end(); ++it) {
        int id = it->first;
        cout << it->first << ' ' << it->second << ' ' << consultar_necesarios(id) << endl;
    }
}




