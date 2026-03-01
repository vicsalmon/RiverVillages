/** @file Productos.hh
    @brief Especificación de la clase productos
*/


#ifndef _PRODUCTO_HH_
#define _PRODUCTO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
using namespace std;
#endif

/** @class Productos
    @brief Representa un listado de pesos y volumenes

    Si un producto existe, sus atributos se ven representados en esta clase */
class Productos {
private:
    vector<int> peso;
    vector<int> volumen;
    
public:
    //Constructoras

    /** @brief Creadora por defecto
    
        Se ejecuta automáticamente al declarar Productos
        \pre <em>cierto</em>
        \post El resultado es dos vectores vacíos de pesos y volumenes 
    */
    Productos();

    //Modificadoras

    /** @brief Modifica el peso de un producto
    
        \pre El vector peso es de tamaño mayor o igual al id, nuevopeso > 0, id > 0
        \post La posición del vector peso de índice id-1 toma por valor nuevopeso
    */
    void modificar_peso(int& id, int& nuevopeso);
    
    /** @brief Modifica el volumen de un producto
    
        \pre El vector volumen es de tamaño mayor o igual al id, nuevovolumen > 0, id > 0
        \post La posición del vector volumen de índice id-1 toma por valor nuevovolumen
    */
    void modificar_volumen(int& id, int& nuevovolumen);

    /** @brief Añade un nuevo producto a ambos vectores de la clase
    
        \pre pesoprod > 0, volumenprod > 0
        \post Los vectores peso/volumen aumentan su tamaño en 1 con el peso/volumen del nuevo producto
    */
    void anadir_producto(int& pesoprod, int& volumenprod);

    //Consultoras

    /** @brief Consultora del peso de un producto
    
        \pre id > 0, el vector peso es de tamaño mayor o igual al id
        \post El resultado es el peso de el producto con el id indicado
    */
    int consultar_peso(int& id) const;

    /** @brief Consultora del volumen de un producto
    
        \pre id > 0, el vector volumen es de tamaño mayor o igual al id
        \post El resultado es el volumen de el producto con el id indicado
    */
    int consultar_volumen(int& id) const;

    /** @brief Consultora de la cantidad de productos existentes
    
        \pre <em>cierto</em>
        \post El resultado es el tamaño del vector peso, equivalente a la cantidad de productos
    */
    int consultar_cantidad() const;

    //Escritura de los atributos de un producto

    /** @brief Operación de escritura
    
        \pre los vectores peso y volumen son de tamaño mayor o igual a id
        \post Escribe el peso y el volumen del producto con el id indicado 
    */
    void escribir(int& id) const;
};
#endif