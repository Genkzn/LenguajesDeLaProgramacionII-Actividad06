
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

    void InvModSM(const string& cod, int cc) {//modificar el stock mediante codigo, donde cc es la cantidad de productos que el usuario quiere adquirir
        bool encontrado = false;
        for (auto& producto : pro) {
            if (producto->getCodigo() == cod) {
                encontrado = true;
                producto->ProVenta(cc); // Intenta vender la cantidad especificada
                break; // Una vez encontrado y procesado, salimos del bucle
            }
        }
        if (!encontrado) {
            cout << "Producto no encontrado." << endl;
        }
    }

    vector<x*> InvBusN(const std::string& nm) const {
        std::vector<x*> n;
        bool found = false;
        for (const auto& producto : pro) {
            if (producto->getNombre() == nm) {
                n.push_back(producto);
                found = true;
            }
        }
        if (!found) {
            cout << "No encontrado." << endl;
        }
        return n;
    }

    vector<x*> InvBusCB(const string& co) const {
        vector<x*> b;
        bool found = false;
        for (const auto& producto : pro) {
            if (producto->getCodigo() == co) {
                b.push_back(producto);
                found = true;
            }
        }
        if (!found) {
            cout << "No encontrado." << endl;
        }
        return b;
    }

    vector<x*> InvBusC(const string& ct) const {
        vector<x*> c;
        bool found = false;
        for (const auto& producto : pro) {
            if (producto->getCategoria() == ct) {
                c.push_back(producto);
                found = true;
            }
        }
        if (!found) {
            cout << "No encontrado." << endl;
        }
        return c;
    }

    vector<x*> InvProV(const string& ct) const {
        vector<x*> c;
        bool found = false;
        for (const auto& producto : pro) {
            if (producto->getCategoria() == ct) {
                c.push_back(producto);
                found = true;
            }
        }
        if (!found) {
            cout << "No encontrado." << endl;
        }
        return c;
    }
    void InvPrV() const { // Productos próximos a vencer
        time_t ahora;
        time(&ahora);

        tm fechaAhora;
        localtime_s(&fechaAhora, &ahora);

        for (const auto& producto : pro) {
            CComida* comida = dynamic_cast<CComida*>(producto);
            if (comida) {
                tm fv = comida->getFechaVencimiento();
                time_t fechav = mktime(&fv);

                double ds = difftime(fechav, ahora);
                int dv = static_cast<int>(ds / (60 * 60 * 24)); // Convertir segundos a días
                if (dv < 7 and dv>0) {
                    cout << "El producto '" << comida->getNombre() << "' vence enmenos de 7 dias." << endl;
                }
            }
        }
    }
    void InvMV() const { //imprime los 3 productos mas vendidos
        vector<CProducto*> cop = pro;
        sort(cop.begin(), cop.end(),
            [](CProducto* a, CProducto* b) {
                return a->getProductosVendidos() > b->getProductosVendidos();
            });
        cout << "Productos mas vendidos:" << endl;
        for (int i = 0; i < min(3, static_cast<int>(cop.size())); ++i) {
            cout << cop[i]->getNombre() << " - Cantidad vendida: " << cop[i]->getProductosVendidos() << endl;
        }
    }

    template<typename R>
    void InvOrdenar(R comp) { //Ordena por campo
        sort(pro.begin(), pro.end(), comp);
    }

};
#endif GESTION_INVENTARIO_INVENTARIO