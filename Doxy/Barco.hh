/** @file Barco.hh
    @brief Especificación de la clase Barco
*/


#ifndef _BARCO_HH_
#define __BARCO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
using namespace std;
#endif

/** @class Barco
    @brief Representa un barco que comercia

    El barco compra ciertas unidades de un producto y vende ciertas unidades de otro

    La ultima ciudad en la que comercia el barco queda guardada en un registro*/
class Barco {
private:
    pair<int,int> comprando;
    pair<int,int> vendiendo;
    vector<string> viajes;

public:
    //Constructoras

    /** @brief Creadora por defecto
        
        Se ejecuta autométicamente al declarar un barco
        \pre <em>cierto</em>
        \post El resultado es un barco con atributos a determinar
    */
    Barco();

    //Consultoras

    /** @brief Consultora del id del producto que compra el barco
        
        \pre El barco tiene un producto a comprar asignado
        \post El resultado es el id del producto a comprar
    */
    int consultar_comprando() const;

    /** @brief Consultora de la cantidad de productos a comprar
        
        \pre El barco tiene un producto a comprar asignado
        \post El resultado es la cantidad del producto que ofrece el barco
    */
    int consultar_comprando_cantidad() const;

    /** @brief Consultora del id del producto que vende el barco
        
        \pre El barco tiene un producto a vender asignado
        \post El resultado es el id del producto a vender
    */
    int consultar_vendiendo() const;

    /** @brief Consultora de la cantidad de productos a vender
        
        \pre El barco tiene un producto a vender asignado
        \post El resultado es la cantidad del producto demandada por el barco
    */
    int consultar_vendiendo_cantidad() const;

    
    //Modificadoras

    /** @brief Determina el id de un producto y la cantidad a comprar
        
        \pre Se ha declarado un barco, existe el producto indicado por el id, cantidad > 0
        \post Se establece el id del producto a comprar y la cantidad demandada 
    */
    void modificar_comprando(int& id, int cantidad);

    /** @brief Determina el id de un producto y la cantidad a vender
        
        \pre Se ha declarado un barco, existe el producto indicado por el id, cantidad > 0
        \post Se establece el id del producto a vender y la cantidad ofrecida 
    */
    void modificar_vendiendo(int& id, int cantidad);

    /** @brief Añade un destino final al registro de viajes
        
        \pre El barco ha realizado un viaje
        \post El vector de viajes ahora contiene en su última posicion la última ciudad en la que ha comerciado el barco
    */
    void agregar_viaje(string& name);

    /** @brief Borra el registro de viajes del barco
        
        \pre Se ha declarado un barco
        \post El vector que registra los ultimos destinos del barco ahora es vacío
    */
    void borrar_viajes();

    
    /** @brief Escribe las ultimas destinaciones del barco
        
        \pre Se ha declarado un barco
        \post Escribe el contenido completo del vector que registra las últimas destinaciones del barco
    */
    void escribir_viajes() const;

    /** @brief Decrementa la cantidad de productos a comprar
        
        \pre Se ha declarado un barco
        \post La cantidad de productos que compra el barco ha disminuido en n
    */
    void restar_comprando(int& n);

    /** @brief Decrementa la cantidad de produtos a vender
        
        \pre Se ha declarado un barco
        \post La cantidad de productos que vende el barco ha disminuido en n
    */
    void restar_vendiendo(int& n);



    
};
#endif