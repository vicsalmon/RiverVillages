/**
    @mainpage Simulacion del comercio fluvial entre ciudades de una cuenca

    Práctica PRO2 (primavera 2024)
*/




/** @file program.cc
    @brief Programa principal
*/
#include "Cuenca.hh"
#include "Productos.hh"


int main() {
    //Productos
    int n; 
    cin >> n;
    Productos productos;
    for (int i = 0; i < n; ++i) {
        int peso, volumen;
        cin >> peso >> volumen;
        productos.anadir_producto(peso, volumen);
    }
    //Cuenca
    Cuenca cuenca;
    cuenca.leer_rio();
    //Barco
    int idcompra;
    cin >> idcompra;
    int cantidadcompra;
    cin >> cantidadcompra;
    int idvende;
    cin >> idvende;
    int cantidadvende;
    cin >> cantidadvende;
    cuenca.modificar_barco(idcompra, cantidadcompra, idvende, cantidadvende);
    //comandos
    string s;
    while (cin >> s and s != "fin") {
        if (s == "leer_rio" or s == "lr") {             
            cout << "#" << s << endl;
            cuenca.leer_rio();
            cuenca.borrar_viajes_barco();
        }
        else if (s == "leer_inventario" or s == "li") {     
            string name;
            cin >> name;
            cout << "#" << s << ' ' << name << endl;
            cuenca.leer_inventario(name, productos);
        }
        else if (s == "leer_inventarios" or s == "ls") {    
            cuenca.leer_inventarios(productos);
            cout << "#" << s << endl;
        }
        else if (s == "modificar_barco" or s == "mb") {             
            int idcompra;
            cin >> idcompra;
            int cantidadcompra;
            cin >> cantidadcompra;
            int idvende;
            cin >> idvende;
            int cantidadvende;
            cin >> cantidadvende;
            cout << "#" << s << endl;
            if (idcompra > productos.consultar_cantidad()) cout << "error: no existe el producto" << endl;
            else {
                if (idvende > productos.consultar_cantidad()) cout << "error: no existe el producto" << endl;
                else cuenca.modificar_barco(idcompra, cantidadcompra, idvende, cantidadvende);
            }
        }
        else if (s == "escribir_barco" or s == "eb") {               
            cout << "#" << s << endl;
            cuenca.escribir_barco();
        }
        else if (s == "consultar_num" or s == "cn") {          
            cout << '#' << s << endl;
            cout << productos.consultar_cantidad() << endl;
        }
        else if (s == "agregar_productos" or s == "ap") {       
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                int peso, volumen;
                cin >> peso >> volumen;
                productos.anadir_producto(peso,volumen);
            }
            cout << '#' << s << ' ' << n << endl;
        }
        else if (s == "escribir_producto" or s == "ep") {       
            int id;
            cin >> id;
            cout << '#' << s << ' ' << id << endl;
            if (id > productos.consultar_cantidad()) cout << "error: no existe el producto" << endl;
            else productos.escribir(id); 
        }
        else if (s == "escribir_ciudad" or s == "ec") { 
            string name;
            cin >> name;
            cout << "#" << s << ' ' << name << endl;
            cuenca.escribir_ciudad(name);
        }
        else if (s == "poner_prod" or s == "pp") {
            string name;
            cin >> name;
            int id, tiene, necesita;
            cin >> id >> tiene >> necesita;
            cout << "#" << s << ' ' << name << ' ' << id << endl;
            if (productos.consultar_cantidad() < id) cout << "error: no existe el producto" << endl;
            else {
                cuenca.poner_prod(name, id, tiene, necesita, productos);
            }
        }
        else if (s == "modificar_prod" or s == "mp") { 
            string name;
            cin >> name;
            int id, tiene, necesita;
            cin >> id >> tiene >> necesita;
            cout << "#" << s << ' ' << name << ' ' << id << endl;
            if (productos.consultar_cantidad() < id) cout << "error: no existe el producto" << endl;  
            else {
                cuenca.modificar_prod(name, id, tiene, necesita, productos);
            } 
        }
        else if (s == "quitar_prod" or s == "qp") { 
            string name;
            cin >> name;
            int id;
            cin >> id;
            cout << "#" << s << ' ' << name << ' ' << id << endl;
            if (productos.consultar_cantidad() < id) cout << "error: no existe el producto" << endl;
            else {
                cuenca.quitar_prod(name, id, productos);
            }
        }
        else if (s == "consultar_prod" or s == "cp") {  
            string name;
            cin >> name;
            int id;
            cin >> id;
            cout << "#" << s << ' ' << name << ' ' << id << endl;
            if (productos.consultar_cantidad() < id) cout << "error: no existe el producto" << endl;
            else {
                cuenca.consultar_prod(name, id);
            }
        }
        else if (s == "comerciar" or s == "co") {
            string c1;
            string c2;
            cin >> c1 >> c2;
            cout << "#" << s << ' ' << c1 << ' ' << c2 << endl; 
            if (c1 == c2) cout <<"error: ciudad repetida" << endl;
            else {
                cuenca.comerciar(c1, c2, productos);
            }
        }
        else if (s == "redistribuir" or s == "re") {
            cout << "#" << s << endl;
            cuenca.redistribuir(productos); 
        }
        else if (s == "hacer_viaje" or s == "hv") {
            cout << "#" << s << endl;
            cuenca.hacer_viaje(productos);
        }
        else if (s == "//") {
            string consumir;
            getline(cin, consumir);
        }
    }
}