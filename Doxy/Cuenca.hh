/** @file Cuenca.hh
    @brief Especificación de la clase Cuenca
*/



#ifndef _CUENCA_HH_
#define _CUENCA_HH_

#include "Ciudad.hh"


#ifndef NO_DIAGRAM
#include <iostream>
#include <stack>
#include "BinTree.hh"
#endif


/** @class Cuenca
    @brief Representa una cuenca fluvial

    Se compone de un río principal que pasa por ciudades.

    Tiene un mapa de todas las ciudades del río.

    Tiene un barco que viaja entre ciudades.
*/
class Cuenca {
private:
    BinTree<string> c;
    Barco barco;
    map <string,Ciudad> inventarios;

    /** @brief Operación de comercio entre el barco y las ciudades del río

      
      \pre La ciudad compra un producto del barco
      \post El barco ha comprado todas las unidades posibles a la Ciudad c
    */
    static void viaje_comprar(Barco& barco, const Productos& prod, Ciudad& c);

    /** @brief Operación de comercio entre el barco y las ciudades del río

      
      \pre La ciudad vende un producto del barco
      \post El barco ha vendido todas las unidades posibles a la Ciudad c
    */
    static void viaje_vender(Barco& barco, const Productos& prod, Ciudad& c);

    /** @brief Ayudante de la creadora del río 

      
      \pre hashtag = "#"
      \post El resultado es un arbol binario de ciudades
    */
    static BinTree<string> leer_rio_helper(string& hashtag, map <string,Ciudad>& inv);
    
    /** @brief Operacion de búsqueda

      
      \pre <em>cierto</em>
      \post El resultado es un vector de nombres de ciudades que maximizariían el comercio con un barco
    */
    vector<string> rutaoptima();
    
    /** @brief Consultora de la existencia de una ciudad

      
      \pre <em>cierto</em>
      \post El resultado es la existencia de la ciudad identificada por name
    */
    bool ciudad_existe(string& name);
    
    /** @brief Ayudante de la función redistribuidora

      
      \pre <em>cierto</em>
      \post Todas las ciudades de t han realizado una operación de comercio con sus nodos hijos
    */
    void redistribuir_helper(const BinTree<string>& t, const Productos& p);
    
    /** @brief Operación de búsqueda

      
      \pre <em>cierto</em>
      \post el valor de mejorruta se ha modificado con la mejor sucesión de nombres de ciudades para comerciar
    */
    void encontrar_ruta_optima(Barco& barco, const BinTree<string>& t, vector<string>& rutaactual, int sumaactual, vector<string>& mejorruta, int& mejorsuma);
    
    /** @brief Ayudante de comercio 

      
      \pre <em>cierto</em>
      \post Ambas ciudades han intercambiado productos de su inventario lo máximo posible
    */
    static void comerciar_helper(Ciudad& c1, Ciudad& c2, const Productos& prod);

    /** @brief Simulador de comercio 

      
      \pre <em>cierto</em>
      \post El resultado es las unidades que se venderían/comprarían en un intercambio entre barco y la Ciudad c
    */
    static int simular_comercio(Barco& barco, Ciudad& c);
public:
    //Constructoras
    
    /** @brief Creadora por defecto

      
      \pre <em>cierto</em>
      \post El resultado es una cuenca con un mapa de ciudades vacío y un barco sin productos ni viajes
    */
    Cuenca();

    /** @brief Operación creadora del río

      
      \pre <em>cierto</em>
      \post Se ha leído la primera ciudad del río y llamado a la función auxiliar
    */
    void leer_rio();

    /** @brief Modifica los atributos del barco

      
      \pre idcompra y idvende > 0 y menor o igual a cantidad de productos existentes,
      cantidadcompra => 0 y cantidadvende > 0 o cantidadcompra > 0 y cantidadvende =>0  
      \post Se han modificado el id y la cantidad de productos que compra y vende el barco de la cuenca
    */
    void modificar_barco(int& idcompra, int& cantidadcompra, int& idvende, int& cantidadvende);

    /** @brief Operación de escritura

      
      \pre <em>cierto<em/>
      \post Se han escrito los atributos del barco
    */
    void escribir_barco() const;

    /** @brief Añade una destinación final al barco

      
      \pre <em>cierto</em>
      \post El barco añade a su vector de nombres de ciudades el nombre de la última ciudad con la que ha comerciado
    */
    void anadir_viaje_barco(string& name);

    /** @brief Elimina las destinaciones finales del barco

      
      \pre <em>cierto</em>
      \post El vector de nombres de ciudades del barco ahora es vacío
    */
    void borrar_viajes_barco();

    /** @brief Determina el inventario de una ciudad del río

      
      \pre name coincide con una ciudad del río
      \post Si n > 0, se ha modificado el inventario, peso y volumen total de la ciudad de nombre name 
    */
    void leer_inventario(string& name,const Productos& p);

    /** @brief Determina el inventario de ciudades del río

      Se garantiza la existencia de todas las ciudades
      \pre <em>cierto</em>
      \post Se ha modificado el inventario, peso y volumen totales de varias ciudades del río
    */
    void leer_inventarios(const Productos& p);

    /** @brief Operación de escritura

      
      \pre La ciudad con nombre name existe en el río
      \post Se escribe el inventario completo y peso y volumen totales de la ciudad
    */
    void escribir_ciudad(string& name);

    /** @brief Añade un producto nuevo a una ciudad del río 

      
      \pre La ciudad y el producto indicado por id existen en el río. La ciudad no tiene el producto.
      Un producto existe si id <= tamaño del vector de pesos de productos
      \post Se ha añadido el producto, la cantidad de unidades que tiene y que necesita al inventario de la ciudad.
      Se han ajustado el peso y volumen totales
    */
    void poner_prod(string& name, int& id, int& tiene, int& necesita,const Productos& p);

    /** @brief Modifica el producto de una ciudad del río

      
      \pre La ciudad existe y tiene el producto. El producto indicado por el id existe.
      Un producto existe si id <= tamaño d el vector de pesos de productos
      \post Se han modificado la cantidad de unidades del producto identificado por el id 
      que tiene y necesita la ciudad de nombre name. Se han ajustado el peso y volumen totales.
    */
    void modificar_prod(string& name, int& id, int& tiene, int& necesita, const Productos& p);

    /** @brief Retira un producto de una ciudad del río

      
      \pre La ciudad de nombre name y el producto identificado por id existen en el río
      Un producto existe si id <= tamaño d el vector de pesos de productos
      \post Se ha retirado el producto del inventario de la ciudad de nombre name.
      Se han ajustado el peso y volumen totales.
    */
    void quitar_prod(string& name, int& id, const Productos& p);

    /** @brief Escritura de un producto del inventario de una ciudad del río

      
      \pre La ciudad de nombre name y el producto identificado por el id existen en el río
      Un producto existe si id <= tamaño d el vector de pesos de productos
      \post Se escriben las unidades que se tienen y necesitan del producto id en del inventario de la ciudad
    */
    void consultar_prod(string& name, int& id);

    /** @brief Operación de comercio entre ciudades del río

      \pre Las ciudades c1 y c2 existen en el río
      \post Se llama a la operación de comercio para las 2 ciudades.
      Se han ajustado el peso y volumen totales.
    */
    void comerciar(string c1, string c2, const Productos& prod);

    /** @brief Operación de comercio entre ciudades del río

      
      \pre <em>cierto</em>
      \post Se ha llamado a la operación ayudante de redistribuir
    */
    void redistribuir(const Productos& prod);

    /** @brief Operación de comercio entre el barco y las ciudades del río

      
      \pre El barco del río tiene productos asignados
      \post El barco ha comerciado con las ciudades de la ruta encontrada y ha añadido la destinación
      final a su registro de viajes. Los atributos del barco no se modifican. Se escriben las unidades
      compradas y vendidas en el viaje.
    */
    void hacer_viaje(const Productos& prod);

};
#endif
