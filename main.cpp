#include <iostream>
#include <string>
#include <iomanip>  // Para formatear decimales con setprecision
#include "Cafe.h"

using std::cout;
using std::cin;
using std::fixed;
using std::setprecision;

/**
 * @brief Muestra el menú principal de la aplicación.
 */
void mostrarMenuPrincipal()
{
    cout << "===== TecnoCafe - Menu Principal =====\n";
    cout << "1. Registrar producto al pedido\n";
    cout << "2. Ver resumen del pedido\n";
    cout << "3. Finalizar y pagar\n";
    cout << "4. Prediligenciar productos de demostracion\n";
    cout << "5. Mostrar producto mas caro del pedido\n";
    cout << "6. Eliminar un producto del pedido\n";
    cout << "-1. Salir\n";
    cout << "Seleccione una opcion: ";
}

/**
 * @brief Lee la opción del usuario en el menú principal con validación.
 * @return La opción elegida.
 */
int leerOpcionMenu()
{
    int opcion;
    cin >> opcion;
    while (!(opcion == -1 || (opcion >= 1 && opcion <= 6)))
    {
        cout << "Opcion invalida. Intente de nuevo: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> opcion;
    }
    return opcion;
}

/**
 * @brief Función principal.
 * Maneja el flujo general del programa.
 */
int main()
{
    // Arreglos estáticos para almacenar los productos del pedido
    int codigos[MAX_ITEMS] = {0};
    int cantidades[MAX_ITEMS] = {0};
    int cantidadItemsRegistrados = 0;

    int opcion = 0;
    do
    {
        mostrarMenuPrincipal();
        opcion = leerOpcionMenu();

        switch (opcion)
        {
        case 1: // Registrar producto
            registrarProducto(codigos, cantidades, cantidadItemsRegistrados);
            break;

        case 2: // Ver resumen
        {
            double subtotal = calcularSubtotalPedido(codigos, cantidades, cantidadItemsRegistrados);
            cout << fixed << setprecision(2);
            cout << "\nSubtotal actual: $" << subtotal << "\n\n";
            break;
        }

        case 3: // Finalizar y pagar
        {
            if (cantidadItemsRegistrados == 0)
            {
                cout << "\nNo hay productos en el pedido.\n\n";
                break;
            }
            double subtotal = calcularSubtotalPedido(codigos, cantidades, cantidadItemsRegistrados);
            int tipoUsuario = leerTipoUsuario();
            double porcentajeDescuento = obtenerPorcentajeDescuento(tipoUsuario);

            mostrarResumenPedido(codigos, cantidades, cantidadItemsRegistrados, porcentajeDescuento);
            double total = calcularTotal(subtotal, porcentajeDescuento);

            cout << fixed << setprecision(2);
            cout << "Total a pagar: $" << total << "\n\n";
            break;
        }

        case 4: // Demo
            prediligenciarProductosDemo(codigos, cantidades, cantidadItemsRegistrados);
            break;

        case 5: // Producto más caro
            mostrarProductoMasCaro(codigos, cantidades, cantidadItemsRegistrados);
            break;

        case 6: // Eliminar producto
            eliminarProducto(codigos, cantidades, cantidadItemsRegistrados);
            break;

        case -1:
            cout << "\nSaliendo del sistema. ¡Hasta pronto!\n";
            break;
        }
    }
    while (opcion != -1);

    return 0;
}
