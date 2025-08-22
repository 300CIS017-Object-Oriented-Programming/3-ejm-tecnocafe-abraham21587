//
// Created by lenovo on 20/08/2025.
//
#include "Cafe.h"

/**
 * @brief Muestra la carta de productos con sus precios.
 */
void mostrarCartaProductos()
{
    cout << "\n--- Carta de productos ---\n";
    cout << "1. Tinto       $" << PRECIO_TINTO << "\n";
    cout << "2. Cappuccino  $" << PRECIO_CAPPUCCINO << "\n";
    cout << "3. Pandebono   $" << PRECIO_PANDEBONO << "\n";
    cout << "4. Sandwich    $" << PRECIO_SANDWICH << "\n";
}

/**
 * @brief Solicita al usuario el código del producto.
 * @return Código de producto válido.
 */
int leerCodigoProducto()
{
    cout << "Ingrese el codigo del producto (1-4): ";
    int codigo;
    cin >> codigo;
    while (codigo < 1 || codigo > 4)
    {
        cout << "Codigo inválido. Intente de nuevo (1-4): ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> codigo;
    }
    return codigo;
}

/**
 * @brief Solicita al usuario la cantidad del producto.
 * @return Cantidad válida (1-20).
 */
int leerCantidadProducto()
{
    cout << "Ingrese la cantidad (1-20): ";
    int cantidad;
    cin >> cantidad;
    while (cantidad < 1 || cantidad > 20)
    {
        cout << "Cantidad invalida. Intente de nuevo (1-20): ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> cantidad;
    }
    return cantidad;
}

/**
 * @brief Devuelve el precio del producto según su código.
 *        Incluye validación para que nunca retorne valores negativos.
 * @param codigoProducto Código del producto.
 * @return Precio positivo o 0 si el código no existe.
 */
int obtenerPrecioPorCodigo(int codigoProducto)
{
    int precio = 0;
    switch (codigoProducto)
    {
    case 1: precio = PRECIO_TINTO; break;
    case 2: precio = PRECIO_CAPPUCCINO; break;
    case 3: precio = PRECIO_PANDEBONO; break;
    case 4: precio = PRECIO_SANDWICH; break;
    default: precio = 0; break;
    }
    return (precio > 0) ? precio : 0;
}

/**
 * @brief Devuelve el nombre del producto según su código.
 */
string obtenerNombreProducto(int codigoProducto)
{
    switch (codigoProducto)
    {
    case 1: return "Tinto";
    case 2: return "Cappuccino";
    case 3: return "Pandebono";
    case 4: return "Sándwich";
    default: return "Desconocido";
    }
}

/**
 * @brief Registra un producto en el pedido.
 */
void registrarProducto(int codigos[], int cantidades[], int& cantidadItemsRegistrados)
{
    if (cantidadItemsRegistrados >= MAX_ITEMS)
    {
        cout << "No es posible registrar más ítems en el pedido.\n";
        return;
    }
    mostrarCartaProductos();
    int codigo = leerCodigoProducto();
    int cantidad = leerCantidadProducto();

    // Si ya existe, acumular
    for (int i = 0; i < cantidadItemsRegistrados; i++)
    {
        if (codigos[i] == codigo)
        {
            cantidades[i] += cantidad;
            cout << "Producto actualizado: " << obtenerNombreProducto(codigo)
                 << " x" << cantidades[i] << " (cantidad acumulada)\n\n";
            return;
        }
    }

    // Si es nuevo, registrar
    codigos[cantidadItemsRegistrados] = codigo;
    cantidades[cantidadItemsRegistrados] = cantidad;
    cantidadItemsRegistrados++;

    cout << "Producto agregado: " << obtenerNombreProducto(codigo)
         << " x" << cantidad << "\n\n";
}

/**
 * @brief Calcula el subtotal de todos los productos del pedido.
 */
double calcularSubtotalPedido(const int codigos[], const int cantidades[], int cantidadItemsRegistrados)
{
    double subtotal = 0.0;
    for (int i = 0; i < cantidadItemsRegistrados; i++)
    {
        int precioUnitario = obtenerPrecioPorCodigo(codigos[i]);
        subtotal += precioUnitario * cantidades[i];
    }
    return subtotal;
}

/**
 * @brief Solicita al usuario el tipo de cliente.
 * @return Número correspondiente al tipo de usuario.
 */
int leerTipoUsuario()
{
    cout << "Tipo de usuario (1=Estudiante, 2=Profesor, 3=Visitante, 4=Administrador): ";
    int tipo;
    cin >> tipo;
    while (tipo < 1 || tipo > 4)
    {
        cout << "Opción inválida. Intente de nuevo (1-4): ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> tipo;
    }
    return tipo;
}

/**
 * @brief Devuelve el descuento correspondiente según el usuario.
 */
double obtenerPorcentajeDescuento(int tipoUsuario)
{
    if (tipoUsuario == 1) return DESCUENTO_ESTUDIANTE;
    if (tipoUsuario == 2) return DESCUENTO_PROFESOR;
    if (tipoUsuario == 3) return DESCUENTO_VISITANTE;
    if (tipoUsuario == 4) return DESCUENTO_ADMIN;
    return 0.0;
}

/**
 * @brief Calcula el total aplicando el descuento.
 */
double calcularTotal(double subtotal, double porcentajeDescuento)
{
    return subtotal * (1.0 - porcentajeDescuento);
}

/**
 * @brief Muestra el resumen completo del pedido.
 */
void mostrarResumenPedido(const int codigos[], const int cantidades[], int cantidadItemsRegistrados,
                          double porcentajeDescuento)
{
    cout << "\n===== Resumen del Pedido =====\n";
    double subtotal = 0.0;
    for (int i = 0; i < cantidadItemsRegistrados; i++)
    {
        string nombre = obtenerNombreProducto(codigos[i]);
        int precio = obtenerPrecioPorCodigo(codigos[i]);
        double parcial = precio * cantidades[i];
        subtotal += parcial;
        cout << "- " << nombre << " x" << cantidades[i] << " = $" << parcial << "\n";
    }
    cout << "Subtotal: $" << subtotal << "\n";
    cout << "Descuento aplicado: " << (porcentajeDescuento * 100) << "%\n";
}

/**
 * @brief Carga productos de ejemplo al pedido.
 */
void prediligenciarProductosDemo(int codigos[], int cantidades[], int & cantidadItemsRegistrados)
{
    cantidadItemsRegistrados = 0;

    codigos[0] = 1; cantidades[0] = 2; // 2 Tintos
    codigos[1] = 2; cantidades[1] = 1; // 1 Cappuccino
    codigos[2] = 3; cantidades[2] = 3; // 3 Pandebonos
    codigos[3] = 4; cantidades[3] = 1; // 1 Sándwich

    cantidadItemsRegistrados = 4;

    cout << "\nSe han cargado productos de ejemplo en el pedido:\n";
    cout << "- 2 Tintos\n";
    cout << "- 1 Cappuccino\n";
    cout << "- 3 Pandebonos\n";
    cout << "- 1 Sándwich\n\n";
}

/**
 * @brief Muestra el producto más caro dentro del pedido actual.
 */
void mostrarProductoMasCaro(const int codigos[], const int cantidades[], int cantidadItemsRegistrados)
{
    if (cantidadItemsRegistrados == 0)
    {
        cout << "No hay productos en el pedido.\n";
        return;
    }

    int indiceMax = 0;
    double maxPrecio = obtenerPrecioPorCodigo(codigos[0]) * cantidades[0];

    for (int i = 1; i < cantidadItemsRegistrados; i++)
    {
        double precio = obtenerPrecioPorCodigo(codigos[i]) * cantidades[i];
        if (precio > maxPrecio)
        {
            maxPrecio = precio;
            indiceMax = i;
        }
    }

    cout << "Producto más caro: " << obtenerNombreProducto(codigos[indiceMax])
         << " x" << cantidades[indiceMax]
         << " = $" << maxPrecio << "\n";
}

/**
 * @brief Elimina un producto del pedido según su código.
 */
void eliminarProducto(int codigos[], int cantidades[], int& cantidadItemsRegistrados)
{
    if (cantidadItemsRegistrados == 0)
    {
        cout << "No hay productos para eliminar.\n";
        return;
    }

    cout << "Ingrese el código del producto a eliminar: ";
    int codigo;
    cin >> codigo;

    for (int i = 0; i < cantidadItemsRegistrados; i++)
    {
        if (codigos[i] == codigo)
        {
            cout << "Eliminando " << obtenerNombreProducto(codigo) << "...\n";
            for (int j = i; j < cantidadItemsRegistrados - 1; j++)
            {
                codigos[j] = codigos[j + 1];
                cantidades[j] = cantidades[j + 1];
            }
            cantidadItemsRegistrados--;
            return;
        }
    }
    cout << "Producto no encontrado en el pedido.\n";
}
