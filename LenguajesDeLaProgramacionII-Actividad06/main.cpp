#include <iostream>
#include <vector>
#include <string>
#include "Inventario.h"
#include "FuncionesComparadoras.h"

using namespace std;

void menu() {
    cout << "==========================" << endl;
    cout << "1. Mostrar inventario" << endl;
    cout << "2. Ordenar por precio" << endl;
    cout << "3. Ordenar por nombre " << endl;
    cout << "4. Buscar por nombre" << endl;
    cout << "5. Buscar por codigo" << endl;
    cout << "6. Buscar por categoria" << endl;
    cout << "7. Productos proximos a vencer" << endl;
    cout << "8. Productos mas vendidos" << endl;
    cout << "9. Salir" << endl;
    cout << "==========================" << endl;
    cout << ">>";
}

int main() {
    // Crear productos
    CElectronico* p1 = new CElectronico("Laptop", "123456789", 1500.0, 10, "Electronicos", 12, "MarcaX");
    CRopa* p2 = new CRopa("Camiseta", "987654321", 25.0, 0, "Ropa", "M", "Algodon");
    vector<string> ingredientes1 = { "Harina", "Azucar", "Huevos" };
    tm FV1 = { 0, 0, 0, 15, 5, 124 }; // 15/06/2024
    CComida* p3 = new CComida("Pastel", "456789012", 30.0, 5, "Comida", ingredientes1, FV1);
    vector<string> ingredientes2 = { "Leche", "Azucar", "Fresa" };
    tm FV2 = { 0, 0, 0, 24, 5, 124 }; // 24/06/2024
    CComida* p4 = new CComida("Jugo de Fresa", "156789013", 25.0, 5, "Comida", ingredientes2, FV2);

    // Crear inventario y agregar productos
    CInventario<CProducto>* inventario = new CInventario<CProducto>();
    inventario->InvAgr(p1);
    inventario->InvAgr(p2);
    inventario->InvAgr(p3);
    inventario->InvAgr(p4);

    int opcion;
    do {
        menu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            // Mostrar inventario
            cout << "==========================" << endl;
            cout << "    INVENTARIO ACTUAL:" << endl;
            cout << "==========================" << endl;
            inventario->InvLis();
            break;
        case 2:
            // Ordenar por precio (ascendente)
            cout << "==========================" << endl;
            cout << "    ORDENADO POR PRECIO:" << endl;
            cout << "==========================" << endl;
            inventario->InvOrdenar(CompP);
            inventario->InvLis();
            break;
        case 3:
            // Ordenar por nombre (ascendente)
            cout << "==========================" << endl;
            cout << "    ORDENADO POR NOMBRE:" << endl;
            cout << "==========================" << endl;
            inventario->InvOrdenar(CompN);
            inventario->InvLis();
            break;
        case 4:
            // Buscar producto por nombre
        {
            string nombre;
            cout << "Ingrese el nombre del producto a buscar: ";
            getline(cin, nombre);
            vector<CProducto*> resultados = inventario->InvBusN(nombre);
            if (!resultados.empty()) {
                cout << "==========================" << endl;
                cout << "    RESULTADOS DE BÚSQUEDA POR NOMBRE:" << endl;
                cout << "==========================" << endl;
                for (auto& producto : resultados) {
                    producto->info();
                    cout << "--------------------------" << endl;
                }
            }
            else {
                cout << "No se encontraron productos con ese nombre." << endl;
            }
        }
        break;
        case 5:
        {
            string codigo;
            cout << "Ingrese el código del producto a buscar: ";
            getline(cin, codigo);
            vector<CProducto*> resultados = inventario->InvBusCB(codigo);
            if (!resultados.empty()) {
                cout << "==========================" << endl;
                cout << "    RESULTADOS DE BÚSQUEDA POR CÓDIGO:" << endl;
                cout << "==========================" << endl;
                for (auto& producto : resultados) {
                    producto->info();
                    cout << "--------------------------" << endl;
                }
            }
            else {
                cout << "No se encontró ningún producto con ese código." << endl;
            }
        }
        break;
        case 6:
        {
            string categoria;
            cout << "Ingrese la categoría del producto a buscar: ";
            getline(cin, categoria);
            vector<CProducto*> resultados = inventario->InvBusC(categoria);
            if (!resultados.empty()) {
                cout << "==========================" << endl;
                cout << "    RESULTADOS DE BÚSQUEDA POR CATEGORÍA:" << endl;
                cout << "==========================" << endl;
                for (auto& producto : resultados) {
                    producto->info();
                    cout << "--------------------------" << endl;
                }
            }
            else {
                cout << "No se encontraron productos en esa categoría." << endl;
            }
        }
        break;
        case 7:
            cout << "==========================" << endl;
            cout << "    PRODUCTOS PRÓXIMOS A VENCER:" << endl;
            cout << "==========================" << endl;
            inventario->InvPrV();
            break;
        case 8:
            cout << "==========================" << endl;
            cout << "    PRODUCTOS MÁS VENDIDOS:" << endl;
            cout << "==========================" << endl;
            inventario->InvMV();
            break;
        case 9:
            cout << "Adio" << endl;
            break;
        default:
            cout << "Ingrese de nuevo." << endl;
            break;
        }

        cout << endl;

    } while (opcion != 9);
    delete inventario;

    return 0;
}
