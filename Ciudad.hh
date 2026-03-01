/** @file Ciudad.hh
    @brief Especificación de la clase Ciudad
*/


#ifndef _CIUDAD_HH_
#define _CIUDAD_HH_

#include "Productos.hh"
#include "Barco.hh"

#ifndef NO_DIAGRAM
#include <map>
#endif

/** @class Ciudad
    @brief Representa una ciudad

    Tiene por nombre un string identificador

    Tiene un inventario de todos los productos que tiene, con cuantas unidades cuenta y cuantas necesita

    Tiene como atributos adicionales el peso y volumen total
*/

class Ciudad {  
private:
    string nombre;
    map <int,int> inv_tiene;
    map <int,int> inv_necesarios;
    int pesototal;
    int volumentotal;
    
public:
    //Constructoras

    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al crear una ciudad.
      \pre <em>cierto</em>
      \post El resultado es una ciudad sin nombre y vacía
    */
    Ciudad();

    /** @brief Creadora por con nombre preasignado 

      
      \pre <em>cierto</em>
      \post El resultado es una ciudad vacía con el nombre asignado
    */
    Ciudad(string& name);

    //Modificadoras


    /** @brief Modifica el peso total de la ciudad

      
      \pre nuevopesototal > 0
      \post El atributo pesototal de la ciudad toma por valor nuevopesototal
    */
    void modificar_peso_total(int& nuevopesototal);

    /** @brief Modifica el volumen total de una ciudad  

      
      \pre nuevovolumentotal > 0
      \post El atributo volumentotal de la ciudad toma por valor nuevovolumentotal
    */
    void modificar_volumen_total(int& nuevovolumentotal);

    /** @brief Establece cuantas unidades de un producto tiene la ciudad  

      
      \pre id > 0 y de un producto existente en prod, cantidad >= 0
      \post La ciudad ahora tiene =cantidad unidades del producto con el id indicado
            El peso y el volumen total se modifican conforme a los cambios
    */
    void determinar_cantidad(int& id, int& cantidad, const Productos& prod);

    /** @brief Establece cuantas unidades de un producto necesita la ciudad 

      
      \pre id > 0, necesarios > 0
      \post La ciudad ahora necesita =necesarios unidades del producto con el id indicado
    */
    void determinar_necesarios(int& id, int& necesarios);
    
    /** @brief Incrementa la cantidad de productos en una ciudad  

      
      \pre id > 0 y de un producto existente en prod 
      \post La cantidad del producto con el id indicado aumenta en 1 en la ciudad
    */
    void sumar_producto(int& id, int& cantidad, const Productos& prod);

    /** @brief Decrementa la cantidad de productos en una ciudad  

      
      \pre id > 0 y de un producto existente en prod 
      \post La cantidad del producto con el id indicado disminuye en 1 en la ciudad
    */
    void restar_producto(int& id, int& cantidad, const Productos& prod);

    /** @brief Elimina un producto del inventario de la ciudad  

      
      \pre id > 0 y de un producto existente en prod y en el inventario
      \post Se eliminan los datos del producto indicado por el id en la ciudad
    */
    void borrar_producto(int id, const Productos& prod);

    /** @brief Elimina el inventario de una ciudad  

      
      \pre <em>cierto</em>
      \post Se borra el contenido de los mapas con el inventario de la ciudad
    */
    void eliminar_inventario();

    //Consultoras

    /** @brief Consultora de la existencia de un producto

      
      \pre <em>cierto</em>
      \post El resultado indica si existe el producto indicado por el id en el inventario de la ciudad
    */
    bool existe_producto(int& id) const;

    /** @brief Consultora del nombre de una ciudad

      
      \pre Se ha declarado una ciudad con nombre
      \post El resultado es el string identificador nombre de la ciudad
    */
    string consultar_nombre() const;

    /** @brief Consultora de la cantidad de un producto de la ciudad  

      
      \pre id > 0
      \post El resultado es la cantidad del producto indicado por el id en el inventario de la ciudad
    */
    int consultar_cantidad(int& id);

    /** @brief Consultora de la cantidad demandada de un producto

      
      \pre id > 0
      \post El resultado es la cantidad demandada del producto indicado por el id en el inventario de la ciudad
    */
    int consultar_necesarios(int& id);

    /** @brief Consultora de la cantidad de productos en la ciudad   

      
      \pre <em>cierto</em>
      \post El resultado es la cantidad de ids de productos que la ciudad guarda en su inventario
    */
    int consultar_tamano_inv();

    /** @brief Consultora del peso total  

      
      \pre <em>cierto</em>
      \post El resultado es el peso total de la suma de todos los productos de la ciudad
    */
    int consultar_peso_total();

    /** @brief Consultora del volumen total  

      
      \pre <em>cierto</em>
      \post El resultado es el volumen total de la suma de todos los productos del inventairo de la ciudad
    */
    int consultar_volumen_total();

    /** @brief Consultora de intercambios ciudad-barco  

      
      \pre <em>cierto<em/>
      \post El resultado es la cantidad de productos que comerciaría el barco en el parámetro implícito
    */
    int simular_comercio(Barco& barco);

    //Escritura del inventario

    /** @brief Operación de escritura  

      
      \pre <em>cierto</em>
      \post Se escriben el id, la cantidad y la demanda de cada producto de la ciudad
    */
    void escribir_inv_ciudad();

    //Comercio entre ciudades

    /** @brief Operación de comercio  

      
      \pre El parametro implicito y ciudadquecompra tienen un nombre
      \post El parámetro implícito satisface la demanda de ciudadquecompra en la medida de lo posible
    */
    void comerciar_helper(Ciudad& ciudadquecompra, const Productos& p);

    /** @brief Operación de compra   

      
      \pre El barco y el parámetro implícito tienen productos asignados
      \post La ciudad compra al barco todas las unidades posibles del producto que vende
    */
    void viaje_comprar_helper(Barco& barco, const Productos& prod);

    /** @brief Operación de venta 

      
      \pre El barco y el parámetro implícito tienen productos asignados
      \post La ciudad vende al barco todas las unidades posibles del producto que compra
    */
    void viaje_vender_helper(Barco& barco, const Productos& prod);
};
#endif