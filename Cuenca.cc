/** @file Cuenca.cc
    @brief Código de la clase Cuenca
*/


#include "Cuenca.hh"

BinTree<string> Cuenca::leer_rio_helper(string& hashtag) {
    string s;
    cin >> s;
    if (s == hashtag) {
        BinTree<string> e;
        return e;
    }
    else {
        string ciudad = s;
        Ciudad ciudadvacia;
        inventarios[s] = ciudadvacia;
        BinTree<string> l(leer_rio_helper(hashtag));
        BinTree<string> r(leer_rio_helper(hashtag));
        BinTree<string> c(ciudad, l, r);        
        return c;
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

bool Cuenca::ciudad_existe(string& name) {
    auto it = this->inventarios.find(name);
    return it != this->inventarios.end();
}

void Cuenca::redistribuir_helper(const BinTree<string>& t, const Productos& prod) {
    //caso base
    if (t.empty()) return;
    //caso general
    if (not(t.left().empty())) {
            comerciar(t.value(), t.left().value(), prod);
            comerciar(t.value(), t.right().value(), prod);
            redistribuir_helper(t.left(), prod);
            redistribuir_helper(t.right(), prod);
    }
}


void Cuenca::encontrar_ruta_optima(Barco& barcoaux, const BinTree<string>& t, vector<string>& rutaactual, int sumaactual, vector<string>& mejorruta, int& mejorsuma) {
    //if (barcoaux.consultar_comprando_cantidad() == 0 and barcoaux.consultar_vendiendo_cantidad() == 0) return;
    rutaactual.push_back(t.value());
    int antescompraba = barcoaux.consultar_comprando_cantidad();
    int antesvendia = barcoaux.consultar_vendiendo_cantidad();
    int compraventas = inventarios[t.value()].simular_comercio(barcoaux);
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

Cuenca::Cuenca() {
    BinTree<Ciudad> c;
    Barco barco;
    map <string,Ciudad> inventarios;
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
        BinTree<string> l(leer_rio_helper(hashtag));
        BinTree<string> r(leer_rio_helper(hashtag));
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
            inventarios[name].eliminar_inventario();
            for (int i = 0; i < n; ++i) {
                int id;
                int tiene;
                int necesita;
                cin >> id >> tiene >> necesita;
                inventarios[name].determinar_cantidad(id, tiene, p);
                inventarios[name].determinar_necesarios(id, necesita);
            }
        }
        else inventarios[name].eliminar_inventario();
    }
}

void Cuenca::leer_inventarios(const Productos& p) {
    string name;
    while (cin >> name and name != "#") {
        int n;
        cin >> n;
        if (n > 0) {
        inventarios[name].eliminar_inventario();
        for (int i = 0; i < n; ++i) {
            int id;
            int tiene;
            int necesita;
            cin >> id >> tiene >> necesita;
            inventarios[name].determinar_cantidad(id, tiene, p);
            inventarios[name].determinar_necesarios(id, necesita);
        }
        }
        else inventarios[name].eliminar_inventario();
    }
    inventarios[name].eliminar_inventario();
}

void Cuenca::escribir_ciudad(string& name) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else {
        inventarios[name].escribir_inv_ciudad();
        cout << inventarios[name].consultar_peso_total() << ' ' << inventarios[name].consultar_volumen_total() << endl;
    }
}

void Cuenca::poner_prod(string& name, int& id, int& tiene, int& necesita, const Productos& p) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else if (inventarios[name].existe_producto(id)) {
        cout << "error: la ciudad ya tiene el producto" << endl;
    }
    else {
        inventarios[name].determinar_cantidad(id, tiene, p);
        inventarios[name].determinar_necesarios(id, necesita);
        cout << inventarios[name].consultar_peso_total() << ' ' << inventarios[name].consultar_volumen_total() << endl;
    }
}

void Cuenca::modificar_prod(string& name, int& id, int& tiene, int& necesita, const Productos& p) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else if (not(inventarios[name].existe_producto(id))) {
        cout << "error: la ciudad no tiene el producto" << endl;
    }
    else {
        inventarios[name].determinar_cantidad(id, tiene, p);
        inventarios[name].determinar_necesarios(id, necesita);
        cout << inventarios[name].consultar_peso_total() << ' ' << inventarios[name].consultar_volumen_total() << endl;
    }
}

void Cuenca::quitar_prod(string& name, int& id, const Productos& p) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else if (not(inventarios[name].existe_producto(id))) {
        cout << "error: la ciudad no tiene el producto" << endl;
    }
    else {
        inventarios[name].borrar_producto(id, p);
        cout << inventarios[name].consultar_peso_total() << ' ' << inventarios[name].consultar_volumen_total() << endl;
    }
}

void Cuenca::consultar_prod(string& name, int& id) {
    if (not(ciudad_existe(name))) cout << "error: no existe la ciudad" << endl;
    else if (not(inventarios[name].existe_producto(id))) cout << "error: la ciudad no tiene el producto" << endl;
    else {
        cout << inventarios[name].consultar_cantidad(id) << ' ';
        cout << inventarios[name].consultar_necesarios(id) << endl; 
    }
}

void Cuenca::comerciar(string ciudad1, string ciudad2, const Productos& prod) {
    if (not(ciudad_existe(ciudad1)) or not(ciudad_existe(ciudad2))) cout << "error: no existe la ciudad" << endl;
    else {
        inventarios[ciudad1].comerciar_helper(inventarios[ciudad2], prod);
        inventarios[ciudad2].comerciar_helper(inventarios[ciudad1], prod);
    }
}

void Cuenca::redistribuir(const Productos& prod) {
    redistribuir_helper(c, prod);
}

void Cuenca::hacer_viaje(const Productos& prod) {
    if (not inventarios.empty()) {
        int idc = this->barco.consultar_comprando();
        int cc = this->barco.consultar_comprando_cantidad();
        int idv = this->barco.consultar_vendiendo();
        int cv = this->barco.consultar_vendiendo_cantidad();
        vector<string> ruta = rutaoptima();
        for (auto it = ruta.begin(); it != ruta.end(); ++it) {
            if (inventarios[*it].consultar_tamano_inv() > 0) {
                inventarios[*it].viaje_comprar_helper(barco, prod);
                inventarios[*it].viaje_vender_helper(barco, prod);
            }
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
}