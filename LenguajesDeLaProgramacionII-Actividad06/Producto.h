#ifndef GESTION_INVENTARIO_PRODUCTO
#define GESTION_INVENTARIO_PRODUCTO

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class CProducto {
private:
    string nom; //nombre
    string cod; //codigo de barras
    float pre; //precio
    int sto; //stock
    string cat; //categoria
    int pv; //productos vendidos

public:
    CProducto(const string& nombre, const string& codigo, float precio, int stock, const string& categoria)
        : nom(nombre), cod(codigo), pre(precio), sto(stock), cat(categoria), pv(0) {}

    // Getters
    string getNombre() const { return nom; }
    string getCodigo() const { return cod; }
    float getPrecio() const { return pre; }
    int getStock() const { return sto; }
    string getCategoria() const { return cat; }
    int getProductosVendidos() const { return pv; }

    // Setters
    void setNombre(const string& nombre) { nom = nombre; }
    void setCodigo(const string& codigo) { cod = codigo; }
    void setPrecio(double precio) { pre = precio; }
    void setStock(int stock) { sto = stock; }
    void setCategoria(const string& categoria) { cat = categoria; }
    void setProductosVendidos(int x) { pv = x; }

    void ProVenta(int cantidad) {
        if (cantidad <= sto) {
            this->sto -= cantidad;
            this->pv += cantidad;
            cout << "Venta realizada. Stock actualizado: " << sto << endl;
        }
        else {
            cout << "No hay suficiente stock para realizar la venta." << endl;
        }
    }
    virtual void info() const {
        cout << "Nombre: " << nom << endl;
        cout << "Codigo: " << cod << endl;
        cout << "Precio: " << pre << endl;
        cout << "Stock: " << sto << endl;
        cout << "Categoria: " << cat << endl;
    }

    virtual ~CProducto() {}
};

class CElectronico : public CProducto {
private:
    int gar; //garantia
    string mar; //marca

public:
    CElectronico(const string& nombre, const string& codigo, float precio, int stock, const string& categoria,
        int garantia, const string& marca)
        : CProducto(nombre, codigo, precio, stock, categoria), gar(garantia), mar(marca) {}

    // Getters
    int getGarantia() const { return gar; }
    string getMarca() const { return mar; }

    void info() const override {
        CProducto::info();
        cout << "Garantia: " << gar << endl;
        cout << "Marca: " << mar << endl;
    }
};

class CRopa : public CProducto {
private:
    string tal; //talla 
    string mat; //material

public:
    CRopa(const string& nombre, const string& codigo, float precio, int stock, const string& categoria,
        const string& talla, const string& material)
        : CProducto(nombre, codigo, precio, stock, categoria), tal(talla), mat(material) {}

    // Getters
    string getTalla() const { return tal; }
    string getMaterial() const { return mat; }

    void info() const override {
        CProducto::info();
        cout << "Talla: " << tal << endl;
        cout << "Material: " << mat << endl;
    }
};

class CComida : public CProducto {
private:
    vector<string> ing; // ingredientes
    tm feVen; //fecha de vencimiento 

public:
    CComida(const string& nombre, const string& codigo, float precio, int stock, const string& categoria,
        const vector<string>& ingredientes, const tm& fechaVencimiento)
        : CProducto(nombre, codigo, precio, stock, categoria), ing(ingredientes), feVen(fechaVencimiento) {}

    // Getters
    vector<string> getIngredientes() const { return ing; }
    tm getFechaVencimiento() const { return feVen; }

    void info() const override {
        CProducto::info();
        cout << "Ingredientes: ";
        for (const auto& ingrediente : ing) {
            cout << ingrediente << ", ";
        }
        cout << endl;
        cout << "Fecha de vencimiento: " << feVen.tm_mday << "/" << feVen.tm_mon + 1 << "/" << feVen.tm_year + 1900 << endl;
    }
};

#endif // GESTION_INVENTARIO_PRODUCT