
#ifndef GESTION_INVENTARIO_INVENTARIO
#define GESTION_INVENTARIO_INVENTARIO
#include <iostream>
#include <algorithm>

#include "Producto.h"
#include <vector>
#include <string>

using namespace std;

template<typename x>
class CInventario {
private:
    vector<x*> pro; //lista de productos
public:
    void InvLis() {
        cout << "Lista de Productos:" << endl;
        for (auto& producto : pro) {
            producto->info();
            cout << "--------------------------" << endl;
        }
    }

    void InvAgr(x* pr) {
        pro.push_back(pr); //Agrega producto a la lista
    }

    void InvEli(string cod) { //elimina prodcuto mediante codigo
        auto i = pro.begin();
        while (i != pro.end()) {
            if ((*i)->getCodigo() == cod) {
                delete* i;
                i = pro.erase(i); // elimina producto de la lista
            }
            else {
                ++i;
            }
        }
    }

    void InvSto() {  //elimina si el se acaba el stock
        auto i = pro.begin();
        while (i != pro.end()) {
            if ((*i)->getStock() == 0) {
                delete* i;
                i = pro.erase(i); // elimina producto de la lista
            }
            else {
                ++i;
            }
        }
    }

    void InvFV() { // elimina los productos vencidos
        time_t ahora;
        time(&ahora);
        tm FA;
        localtime_s(&FA, &ahora);

        auto it = pro.begin();
        while (it != pro.end()) {
            CComida* comida = dynamic_cast<CComida*>(*it);
            if (comida) {
                tm FV = comida->getFechaVencimiento();
                if (mktime(&FV) < mktime(&FA)) {
                    delete* it;
                    it = pro.erase(it); // elimina producto de la lista
                    continue;
                }
            }
            ++it;
        }
    }

    void InvModP(const string& cod, float pr) {//Modificar el precii mediante codigo
        bool encontrado = false;
        for (auto& producto : pro) {
            if (producto->getCodigo() == cod) {
                encontrado = true;
                producto->setPrecio(pr); // Modifica el precio
                break;
            }
        }
        if (!encontrado) {
            cout << "Producto no encontrado." << endl;
        }
    }
    void InvModSM(const string& cod, int cc) {
        bool encontrado = false; // Variable para indicar si el producto fue encontrado
        for (auto& producto : pro) { // Iterar sobre cada producto en el vector 'pro'
            if (producto->getCodigo() == cod) { // Si el código del producto coincide con el código buscado
                encontrado = true; // Producto encontrado
                producto->ProVenta(cc); // Intenta vender la cantidad especificada
                break; // Una vez encontrado y procesado, salimos del bucle
            }
        }
        if (!encontrado) { // Si no se encontró el producto
            cout << "Producto no encontrado." << endl; // Imprimir mensaje de error
        }
    }

    vector<x*> InvBusN(const std::string& nm) const {
        std::vector<x*> n; // Vector para almacenar productos que coinciden con el nombre
        bool found = false; // Variable para indicar si se encontraron productos
        for (const auto& producto : pro) { // Iterar sobre cada producto en el vector 'pro'
            if (producto->getNombre() == nm) { // Si el nombre del producto coincide con el nombre buscado
                n.push_back(producto); // Añadir producto al vector
                found = true; // Producto encontrado
            }
        }
        if (!found) { // Si no se encontró ningún producto
            cout << "No encontrado." << endl; // Imprimir mensaje de error
        }
        return n; // Devolver vector de productos encontrados
    }


    vector<x*> InvBusCB(const string& co) const {
        vector<x*> b; // Vector para almacenar productos que coinciden con el código
        bool found = false; // Variable para indicar si se encontraron productos
        for (const auto& producto : pro) { // Iterar sobre cada producto en el vector 'pro'
            if (producto->getCodigo() == co) { // Si el código del producto coincide con el código buscado
                b.push_back(producto); // Añadir producto al vector
                found = true; // Producto encontrado
            }
        }
        if (!found) { // Si no se encontró ningún producto
            cout << "No encontrado." << endl; // Imprimir mensaje de error
        }
        return b; // Devolver vector de productos encontrados
    }

    vector<x*> InvBusC(const string& ct) const {
        vector<x*> c; // Vector para almacenar productos que coinciden con la categoría
        bool found = false; // Variable para indicar si se encontraron productos
        for (const auto& producto : pro) { // Iterar sobre cada producto en el vector 'pro'
            if (producto->getCategoria() == ct) { // Si la categoría del producto coincide con la categoría buscada
                c.push_back(producto); // Añadir producto al vector
                found = true; // Producto encontrado
            }
        }
        if (!found) { // Si no se encontró ningún producto
            cout << "No encontrado." << endl; // Imprimir mensaje de error
        }
        return c; // Devolver vector de productos encontrados
    }


    vector<x*> InvProV(const string& ct) const {
        vector<x*> c; // Vector para almacenar productos que coinciden con la categoría
        bool found = false; // Variable para indicar si se encontraron productos
        for (const auto& producto : pro) { // Iterar sobre cada producto en el vector 'pro'
            if (producto->getCategoria() == ct) { // Si la categoría del producto coincide con la categoría buscada
                c.push_back(producto); // Añadir producto al vector
                found = true; // Producto encontrado
            }
        }
        if (!found) { // Si no se encontró ningún producto
            cout << "No encontrado." << endl; // Imprimir mensaje de error
        }
        return c; // Devolver vector de productos encontrados
    }


    void InvPrV() const {
        time_t ahora; // Variable para almacenar el tiempo actual
        time(&ahora); // Obtener el tiempo actual

        tm fechaAhora; // Estructura para almacenar la fecha y hora actual
        localtime_s(&fechaAhora, &ahora); // Convertir 'ahora' a estructura 'tm'

        for (const auto& producto : pro) { // Iterar sobre cada producto en el vector 'pro'
            CComida* comida = dynamic_cast<CComida*>(producto); // Intentar convertir el producto a tipo 'CComida'
            if (comida) { // Si la conversión fue exitosa
                tm fv = comida->getFechaVencimiento(); // Obtener la fecha de vencimiento del producto
                time_t fechav = mktime(&fv); // Convertir la fecha de vencimiento a 'time_t'

                double ds = difftime(fechav, ahora); // Calcular la diferencia en segundos entre la fecha de vencimiento y la fecha actual
                int dv = static_cast<int>(ds / (60 * 60 * 24)); // Convertir la diferencia de segundos a días
                if (dv < 7 && dv > 0) { // Si el producto vence en menos de 7 días
                    cout << "El producto '" << comida->getNombre() << "' vence en menos de 7 días." << endl; // Imprimir mensaje de advertencia
                }
            }
        }
    }

    
    void InvMV() const {
        vector<CProducto*> cop = pro; // Crear una copia del vector de productos
        sort(cop.begin(), cop.end(), // Ordenar los productos por cantidad vendida
            [](CProducto* a, CProducto* b) {
                return a->getProductosVendidos() > b->getProductosVendidos(); // Comparar productos por cantidad vendida
            });
        cout << "Productos más vendidos:" << endl;
        for (int i = 0; i < min(3, static_cast<int>(cop.size())); ++i) { // Iterar sobre los 3 primeros productos o el total si es menor a 3
            cout << cop[i]->getNombre() << " - Cantidad vendida: " << cop[i]->getProductosVendidos() << endl; // Imprimir nombre y cantidad vendida del producto
        }
    }

    template<typename R>
    void InvOrdenar(R comp) {
        sort(pro.begin(), pro.end(), comp); // Ordenar el vector de productos usando el comparador 'comp'
    }

};
#endif GESTION_INVENTARIO_INVENTARIO
