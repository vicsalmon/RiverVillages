/** @file Cuenca.cc
 *  @brief Codigo de la clase Cuenca
*/


#include "Cuenca.hh"

Cuenca::Cuenca() {
    BinTree<Ciudad> c;
    Barco barco;
    map <string,Ciudad> inventarios;
}

BinTree<string> Cuenca::leer_rio_helper(string& hashtag, map <string,Ciudad>& inventario) {
    string s;
    cin >> s;
    if (s == hashtag) {
        BinTree<string> e;
        return e;
    }
    else {
        string ciudad = s;
        Ciudad ciudadvacia;
        inventario[s] = ciudadvacia;
        BinTree<string> l(leer_rio_helper(hashtag, inventario));
        BinTree<string> r(leer_rio_helper(hashtag, inventario));
        BinTree<string> c(ciudad, l, r);        
        return c;
    }
}

bool Cuenca::ciudad_existe(string& name) {
    auto it = this->inventarios.find(name);
    return it != this->inventarios.end();
}

void Cuenca::leer_rio() {
    string first;
    cin >> first;
    if (first != "#") {
        inventarios.clear();
        string primeraciudad = first;
        Ciudad ciudadvacia;
        inventarios[first] = ciudadvacia;
        string hashtag = "#";
        BinTree<string> l(leer_rio_helper(hashtag, inventarios));
        BinTree<string> r(leer_rio_helper(hashtag, inventarios));
        BinTree<string> t(primeraciudad, l, r);
        this->c = t;
    }
}

void Cuenca::modificar_barco(int& idcompra, int& cantidadcompra, int& idvende, int& cantidadvende) {
    if (idcompra != idvende) {
        this->barco.modificar_comprando(idcompra, cantidadcompra);
        this->barco.modificar_vendiendo(idvende, cantidadvende);
    }
    else cout << "error: no se puede comprar y vender el mismo producto" << endl;
}

void Cuenca::escribir_barco() const {
    cout << barco.consultar_comprando() << ' ';
    cout << barco.consultar_comprando_cantidad() << ' ';
    cout << barco.consultar_vendiendo() << ' ';
    cout << barco.consultar_vendiendo_cantidad() << endl;
    barco.escribir_viajes();
}

void Cuenca::anadir_viaje_barco(string& name) {
    this->barco.agregar_viaje(name);
}

void Cuenca::borrar_viajes_barco() {
    this->barco.borrar_viajes();
}

void Cuenca::leer_inventario(string& name, const Productos& p) {
    Ciudad c;
    if (not(ciudad_existe(name))) {
        cout << "error: no existe la ciudad" << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int id, tiene, necesita;
            cin >> id >> tiene >> necesita;
        }
    }
    else {
        int n;
        cin >> n;
        if (n > 0) {
            for (int i = 0; i < n; ++i) {
                int id;
                int tiene;
                int necesita;
                cin >> id >> tiene >> necesita;
                c.determinar_cantidad(id, tiene, p);
                c.determinar_necesarios(id, necesita);
            }
        }
        inventarios[name] = c;
    }
}

void Cuenca::leer_inventarios(const Productos& p) {
    string name;
    while (cin >> name and name != "#") {
        Ciudad c;
        int n;
        cin >> n;
        if (n > 0) {
        for (int i = 0; i < n; ++i) {
            int id;
            int tiene;
            int necesita;
            cin >> id >> tiene >> necesita;
            c.determinar_cantidad(id, tiene, p);
            c.determinar_necesarios(id, necesita);
        }
        }
        inventarios[name] = c;
    }
    inventarios[name].eliminar_inventario();
}

void Cuenca::escribir_ciudad(string& name) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else {
        Ciudad c = inventarios[name];
        c.escribir_inv_ciudad();
        cout << c.consultar_peso_total() << ' ' << c.consultar_volumen_total() << endl;
        inventarios[name] = c;
    }
}

void Cuenca::poner_prod(string& name, int& id, int& tiene, int& necesita, const Productos& p) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else {
        Ciudad c = inventarios[name];
        if (c.existe_producto(id))cout << "error: la ciudad ya tiene el producto" << endl;
        else {
            c.determinar_cantidad(id, tiene, p);
            c.determinar_necesarios(id, necesita);
            cout << c.consultar_peso_total() << ' ' << c.consultar_volumen_total() << endl;
            inventarios[name] = c;
        }
    }
}

void Cuenca::modificar_prod(string& name, int& id, int& tiene, int& necesita, const Productos& p) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else {
    Ciudad c = inventarios[name];
    if (not(c.existe_producto(id))) cout << "error: la ciudad no tiene el producto" << endl;
        else {
            c.determinar_cantidad(id, tiene, p);
            c.determinar_necesarios(id, necesita);
            cout << c.consultar_peso_total() << ' ' << c.consultar_volumen_total() << endl;
            inventarios[name] = c;
        }
    }
}

void Cuenca::quitar_prod(string& name, int& id, const Productos& p) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else {
        Ciudad c = inventarios[name];
        if (not(c.existe_producto(id))) cout << "error: la ciudad no tiene el producto" << endl;
        else {
        c.borrar_producto(id, p);
        cout << c.consultar_peso_total() << ' ' << c.consultar_volumen_total() << endl;
        inventarios[name] = c;
        }  
    }
}

void Cuenca::consultar_prod(string& name, int& id) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else {
        Ciudad c = inventarios[name];
        if (not(c.existe_producto(id))) cout << "error: la ciudad no tiene el producto" << endl;
        else {
            cout << c.consultar_cantidad(id) << ' ';
            cout << c.consultar_necesarios(id) << endl;
            inventarios[name] = c;
        }
    }
}

void Cuenca::comerciar(string ciudad1, string ciudad2, const Productos& prod) {
    if (not(ciudad_existe(ciudad1)) or not(ciudad_existe(ciudad2))) cout << "error: no existe la ciudad" << endl;
    else {
        comerciar_helper(inventarios[ciudad1], inventarios[ciudad2], prod);
    }
}


void Cuenca::redistribuir_helper(const BinTree<string>& t, const Productos& prod) {
    //caso baseç
    if (t.empty()) return;
    //caso general
    if (not(t.left().empty())) {
            comerciar(t.value(), t.left().value(), prod);
            comerciar(t.value(), t.right().value(), prod);
            redistribuir_helper(t.left(), prod);
            redistribuir_helper(t.right(), prod);
    }
}

void Cuenca::redistribuir(const Productos& prod) {
    redistribuir_helper(c, prod);
}

int Cuenca::simular_comercio(Barco& barco, Ciudad& c) {
    int compras = 0;
    int ventas = 0;
    int idc = barco.consultar_comprando();
    int idv = barco.consultar_vendiendo();
    if (c.existe_producto(idc)) {
        int oferta = c.consultar_cantidad(idc) - c.consultar_necesarios(idc);
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
    if (c.existe_producto(idv)) {
        int demanda = c.consultar_necesarios(idv) - c.consultar_cantidad(idv);
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

void Cuenca::encontrar_ruta_optima(Barco& barcoaux, const BinTree<string>& t, vector<string>& rutaactual, int sumaactual, vector<string>& mejorruta, int& mejorsuma) {
    rutaactual.push_back(t.value());
    int antescompraba = barcoaux.consultar_comprando_cantidad();
    int antesvendia = barcoaux.consultar_vendiendo_cantidad();
    Ciudad city = inventarios[t.value()];
    int compraventas = simular_comercio(barcoaux, city);
    sumaactual += compraventas;
    if (compraventas > 0) {  
        if ((sumaactual > mejorsuma) or (sumaactual == mejorsuma and rutaactual.size() < mejorruta.size())) {       
            mejorsuma = sumaactual;
            mejorruta = rutaactual; 
        }
    }
    if (not t.left().empty()) {
        encontrar_ruta_optima(barcoaux, t.left(), rutaactual, sumaactual, mejorruta, mejorsuma);
        encontrar_ruta_optima(barcoaux, t.right(), rutaactual, sumaactual, mejorruta, mejorsuma);
    }
    rutaactual.pop_back();
    sumaactual -= compraventas;
    int c = barcoaux.consultar_comprando();
    int v = barcoaux.consultar_vendiendo();
    barcoaux.modificar_comprando(c, antescompraba);
    barcoaux.modificar_vendiendo(v, antesvendia);
}

void Cuenca::comerciar_helper(Ciudad& c1, Ciudad& c2, const Productos& prod) {
    map <int,int> inv;
    Ciudad c;
    if (c1.consultar_tamano_inv() < c2.consultar_tamano_inv()) {
        inv = c1.consultar_inv();
        c = c2;
    }
    else {
        inv = c2.consultar_inv();
        c = c1;
    }
    for (auto it = inv.begin(); it != inv.end(); ++it) {
        int id = it->first;
        if (c.existe_producto(id)) {
            if (c1.consultar_cantidad(id) > c1.consultar_necesarios(id) and c2.consultar_cantidad(id) < c2.consultar_necesarios(id)) {
                int oferta = c1.consultar_cantidad(id) - c1.consultar_necesarios(id);
                int demanda = c2.consultar_necesarios(id) - c2.consultar_cantidad(id);
                if (oferta < demanda) {
                    c1.restar_producto(id, oferta, prod);
                    c2.sumar_producto(id, oferta, prod);
                }
                else {
                    c1.restar_producto(id, demanda, prod);
                    c2.sumar_producto(id, demanda, prod);
                }
            }
            else if (c1.consultar_cantidad(id) < c1.consultar_necesarios(id) and c2.consultar_cantidad(id) > c2.consultar_necesarios(id)) {
                int oferta = c2.consultar_cantidad(id) - c2.consultar_necesarios(id);
                int demanda = c1.consultar_necesarios(id) - c1.consultar_cantidad(id);
                if (oferta < demanda) {
                    c2.restar_producto(id, oferta, prod);
                    c1.sumar_producto(id, oferta, prod);
                }
                else {
                    c2.restar_producto(id, demanda, prod);
                    c1.sumar_producto(id, demanda, prod);
                }
            }
        }
    }
}

vector<string> Cuenca::rutaoptima() {
    vector<string> mejorruta;
    vector<string> rutaactual;
    int mejorsuma = 0;
    int sumaactual = 0;
    Barco barcoaux = this->barco;
    encontrar_ruta_optima(barcoaux, c, rutaactual, sumaactual, mejorruta, mejorsuma);
    return mejorruta;
}

void Cuenca::hacer_viaje(const Productos& prod) {
    int idc = this->barco.consultar_comprando();
    int cc = this->barco.consultar_comprando_cantidad();
    int idv = this->barco.consultar_vendiendo();
    int cv = this->barco.consultar_vendiendo_cantidad();
    vector<string> ruta = rutaoptima();
        for (auto it = ruta.begin(); it != ruta.end(); ++it) {
            Ciudad c = inventarios[*it];
            if (c.existe_producto(idc))viaje_comprar(barco, prod, c);
            if (c.existe_producto(idv))viaje_vender(barco, prod, c);
            inventarios[*it] = c;
        }
    int comprados = cc - barco.consultar_comprando_cantidad();
    int vendidos = cv - barco.consultar_vendiendo_cantidad();
        if (comprados > 0 or vendidos > 0) {
            barco.agregar_viaje(ruta[ruta.size() - 1]);
            barco.modificar_comprando(idc, cc);
            barco.modificar_vendiendo(idv, cv);
        }
    cout << comprados+vendidos << endl;
}

void Cuenca::viaje_comprar(Barco& barco, const Productos& prod, Ciudad& c) {
    int id = barco.consultar_comprando();
        int oferta = c.consultar_cantidad(id) - c.consultar_necesarios(id);
        if (oferta > 0) {
            if (oferta < barco.consultar_comprando_cantidad()) {
                barco.restar_comprando(oferta);
                //this->inv_tiene[id] = this->inv_necesarios[id];
                c.restar_producto(id, oferta, prod);
            }
            else {
                //this->inv_tiene[id] -= barco.consultar_comprando_cantidad();
                int can = c.consultar_cantidad(id) - barco.consultar_comprando_cantidad();
                c.determinar_cantidad(id, can, prod);
                barco.modificar_comprando(id, 0);
            }
        }
    
}

void Cuenca::viaje_vender(Barco& barco, const Productos& prod, Ciudad& c) {
    int id = barco.consultar_vendiendo();
    int demanda = c.consultar_necesarios(id) - c.consultar_cantidad(id);
    if (demanda > 0) {
        if (barco.consultar_vendiendo_cantidad() < demanda) {
            int can = c.consultar_cantidad(id) + barco.consultar_vendiendo_cantidad();
            c.determinar_cantidad(id, can, prod);
            barco.modificar_vendiendo(id, 0);
        }
        else {
            barco.restar_vendiendo(demanda);
            int nec = c.consultar_necesarios(id);
            c.determinar_cantidad(id, nec, prod);
        }
    }
}