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

Ciudad::Ciudad(string& name) {
    nombre = name;
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


string Ciudad::consultar_nombre() const {
    return nombre;
}

int Ciudad::consultar_cantidad(int& id)  {
    return inv_tiene[id];
}

int Ciudad::consultar_necesarios(int& id)  {
    return inv_necesarios[id];
}

map<int,int> Ciudad::consultar_inv() {
    return inv_tiene;
}

int  Ciudad::consultar_tamano_inv() {
      return inv_tiene.size();
}

int Ciudad::consultar_peso_total() {
    return pesototal;
}

int Ciudad::consultar_volumen_total() {
    return volumentotal;
}

int Ciudad::simular_comercio(Barco& barco) {
    int compras = 0;
    int ventas = 0;
    int idc = barco.consultar_comprando();
    int idv = barco.consultar_vendiendo();
    if (existe_producto(idc)) {
        int oferta = this->inv_tiene[idc] - this->inv_necesarios[idc];
        if (oferta > 0) {
            if (barco.consultar_comprando_cantidad() > oferta) {
            compras += oferta;
            barco.restar_comprando(oferta);
            }
            else {
                compras += barco.consultar_comprando_cantidad();
                barco.modificar_comprando(idc, 0);
            }
        }
    }
    if (existe_producto(idv)) {
        int demanda = this->inv_necesarios[idv] - this->inv_tiene[idv];
        if (demanda > 0) {
            if (barco.consultar_vendiendo_cantidad() < demanda) {
                ventas += barco.consultar_vendiendo_cantidad(); 
                barco.modificar_vendiendo(idv, 0);
            }
            else {
                ventas += demanda;
                barco.restar_vendiendo(demanda);
            }
        }
    }
    return compras + ventas;
}

void Ciudad::escribir_inv_ciudad() {
    for (auto it = inv_tiene.begin(); it != inv_tiene.end(); ++it) {
        cout << it->first << ' ' << it->second << ' ' << inv_necesarios[it->first] << endl;
    }
}
/*
void Ciudad::comerciar_helper(Ciudad& ciudadquecompra, const Productos& prod) {
    for (auto it = this->inv_tiene.begin(); it != this->inv_tiene.end(); ++it) {
    int id = it->first;
        if (ciudadquecompra.existe_producto(id)) {
            int tiene = ciudadquecompra.consultar_cantidad(id);
            int necesita = ciudadquecompra.consultar_necesarios(id);
            int demanda = necesita - tiene;
            if (demanda > 0) {
                int oferta = this->inv_tiene[id] - this->inv_necesarios[id];
                if (oferta > 0) {
                    if (demanda > oferta) { //la ciudad que vende(par.imp) le da a la ciudad que compra toda su oferta
                        ciudadquecompra.sumar_producto(id, oferta, prod);
                        restar_producto(id, oferta, prod);
                    } else {    //la ciudad que vende le da a la ciudad que compra la cantidad demandada
                        ciudadquecompra.sumar_producto(id, demanda, prod);
                        restar_producto(id, demanda, prod);
                    }
                }
            }
        }
    }
} */

void Ciudad::viaje_comprar_helper(Barco& barco, const Productos& prod) {
    int id = barco.consultar_comprando();
    if (existe_producto(id)) {
        int oferta = this->inv_tiene[id] - this->inv_necesarios[id];
        if (oferta > 0) {
            if (oferta < barco.consultar_comprando_cantidad()) {
                barco.restar_comprando(oferta);
                //this->inv_tiene[id] = this->inv_necesarios[id];
                restar_producto(id, oferta, prod);
            }
            else {
                //this->inv_tiene[id] -= barco.consultar_comprando_cantidad();
                int can = this->inv_tiene[id] - barco.consultar_comprando_cantidad();
                determinar_cantidad(id, can, prod);
                barco.modificar_comprando(id, 0);
            }
        }
    }
}

void Ciudad::viaje_vender_helper(Barco& barco, const Productos& prod) {
    int id = barco.consultar_vendiendo();
    if (existe_producto(id)) {
        int demanda = this->inv_necesarios[id] - this->inv_tiene[id];
        if (demanda > 0) {
            if (barco.consultar_vendiendo_cantidad() < demanda) {
                //this->inv_tiene[id] += barco.consultar_vendiendo_cantidad();
                int can = this->inv_tiene[id] + barco.consultar_vendiendo_cantidad();
                determinar_cantidad(id, can, prod);
                barco.modificar_vendiendo(id, 0);
            }
            else {
                barco.restar_vendiendo(demanda);
                //this->inv_tiene[id] = this->inv_necesarios[id];
                determinar_cantidad(id, this->inv_necesarios[id], prod);
            }
        }
    }
}



