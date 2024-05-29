#include <iostream>
#include <malloc.h>
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

struct pasajero
{
    string nombre;

    pasajero *sig;
};

struct nodo
{

    char destino[45];
    int matricula[4];
    char nombre[45];
    int identificacion[10];

    int value;
    int anio, mes, dia;
    int embarcacion;
    int altura;
    nodo *izq;
    nodo *der;
};

struct nodo *raiz = NULL;
struct nodo *aux, *aux2;

// Función para validar el identificador
bool validarIdentificador(int identificador[])
{
    if (identificador == NULL)
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (identificador[i] < 0 || identificador[i] > 9)
        {
            return false;
        }
    }

    return true;
}

// Función para imprimir los detalles de un nodo
void imprimirNodo(nodo *nodoEncontrado)
{
    if (nodoEncontrado == NULL)
    {
        cout << "El nodo es nulo" << endl;
        return;
    }

    cout << "Identificación: ";
    for (int i = 0; i < 10; i++)
    {
        cout << nodoEncontrado->identificacion[i];
    }
    cout << endl;
    cout << "Matrícula: ";
    for (int i = 0; i < 4; i++)
    {
        cout << nodoEncontrado->matricula[i];
    }
    cout << endl;
    cout << "Nombre: " << nodoEncontrado->nombre << endl;
    cout << "Año: " << nodoEncontrado->anio << endl;
    cout << "Mes: " << nodoEncontrado->mes << endl;
    cout << "Día: " << nodoEncontrado->dia << endl;
    cout << "Costo: " << nodoEncontrado->value << endl;
    cout << "Destino: " << nodoEncontrado->destino << endl;
    cout << "Capacidad: " << nodoEncontrado->embarcacion << endl;
}

int obtenerAltura(struct nodo *n)
{
    if (n == NULL)
    {
        return 0;
    }
    return n->altura;
}

int mayor(int a, int b)
{
    return (a > b) ? a : b;
}

int obtenerBalance(struct nodo *n)
{
    if (n == NULL)
    {
        return 0;
    }
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

struct nodo *rotarDerecha(struct nodo *y)
{
    struct nodo *x = y->izq;
    struct nodo *T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

struct nodo *rotarIzquierda(struct nodo *x)
{
    struct nodo *y = x->der;
    struct nodo *T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y;
}

bool compararIdentificadores(int identificador1[], int identificador2[])
{
    for (int i = 0; i < 10; i++)
    {
        if (identificador1[i] < identificador2[i])
        {
            return true;
        }
        else if (identificador1[i] > identificador2[i])
        {
            return false;
        }
    }
    return false; // Si son iguales, se considera menor
}

struct nodo *insertar(struct nodo *nodo)
{
    if (nodo == NULL)
    {
        return aux;
    }

    if (compararIdentificadores(aux->identificacion, nodo->identificacion)) // Comparación por identificador
    {
        nodo->izq = insertar(nodo->izq);
    }
    else 
    {
        nodo->der = insertar(nodo->der);
    }
    

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && compararIdentificadores(aux->identificacion, nodo->izq->identificacion))
    {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && !compararIdentificadores(aux->identificacion, nodo->der->identificacion))
    {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && !compararIdentificadores(aux->identificacion, nodo->izq->identificacion))
    {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && compararIdentificadores(aux->identificacion, nodo->der->identificacion))
    {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void Inorden(nodo *raiz) //  ARREGLADO XD  se le cambio el apuntador anterior q era nodoactual y se rmplazo por raiz
{
    if (raiz != NULL)
    {
        Inorden(raiz->izq); // Recorrer subárbol izquierdo

        // Imprimir información del nodo actual en orden ascendente
        cout << "Nombre: " << raiz->nombre << endl;
        cout << "Identificación: ";
        for (int i = 0; i < 10; i++)
        {
            cout << raiz->identificacion[i];
        }
        cout << endl
             << endl;

        Inorden(raiz->der); // Recorrer subárbol derecho
    }
}
nodo* BuscarPorIdentificacion(nodo* r, int identificador[]) {
    if (r == NULL) {
        return NULL; // Si el árbol está vacío, no se encontró el identificador
    }

    bool sonIguales = true;
    for (int i = 0; i < 10; i++) {
        if (r->identificacion[i] != identificador[i]) {
            sonIguales = false;
            break;
        }
    }

    if (sonIguales) {
        return r; // Si los identificadores son iguales, se encontró el nodo
    }

    // Si no son iguales, buscar en el subárbol izquierdo o derecho, según corresponda
    if (compararIdentificadores(identificador, r->identificacion)) {
        return BuscarPorIdentificacion(r->izq, identificador);
    } else {
        return BuscarPorIdentificacion(r->der, identificador);
    }
}

void EliminarPorIdentificacion(nodo *raiz, int eliminar[])
{
    if (raiz == NULL)
    {
        return;
    }

    bool sonIguales = true;
    for (int i = 0; i < 10; i++)
    {
        if (raiz->identificacion[i] != eliminar[i])
        {
            sonIguales = false;
            break;
        }
    }

    if (sonIguales)
    {
        // Eliminar el nodo
        if (raiz->izq == NULL && raiz->der == NULL)
        {
            delete raiz;
            raiz = NULL;
        }
        else if (raiz->izq == NULL)
        {
            nodo *temp = raiz;
            raiz = raiz->der;
            delete temp;
        }
        else if (raiz->der == NULL)
        {
            nodo *temp = raiz;
            raiz = raiz->izq;
            delete temp;
        }
        else
        {
            nodo *temp = raiz->der;
            while (temp->izq != NULL)
            {
                temp = temp->izq;
            }
            // Copiar el identificador elemento por elemento
            for (int i = 0; i < 10; i++)
            {
                raiz->identificacion[i] = temp->identificacion[i];
            }
            EliminarPorIdentificacion(raiz->der, eliminar);
        }
    }
    else if (eliminar[0] < raiz->identificacion[0])
    {
        EliminarPorIdentificacion(raiz->izq, eliminar);
    }
    else
    {
        EliminarPorIdentificacion(raiz->der, eliminar);
    }
}
string generarIdentificadorUnico(string matricula, int anio, int mes, int dia)
{
    string identificador = "";

    // Extraer los dos primeros caracteres de la matrícula
    identificador = matricula.substr(0, 2);

    // Convertir año, mes y día a cadenas y concatenarlos con el identificador
    identificador += to_string(anio) + to_string(mes / 10) + to_string(mes % 10) + to_string(dia / 10) + to_string(dia % 10);

    return identificador;
}
void crearNodo()
{
    aux = (struct nodo *)malloc(sizeof(struct nodo));

    // Validar matrícula
    do
    {
        cout << " INGRESE MATRICULA DE LA EMBARCACION";
        cout << "LA MATRICULA ES DE 4 DIGITOS\n";

        cin >> aux->matricula[0];

    } while (aux->matricula[0] < 1000 || aux->matricula[0] > 9999); // Validar que la matrícula tenga 4 dígitos

    cout << " INGRESE NOMBRE DE SU EMBARCACION\n";
    cin.ignore();                                  // Agregar esta línea
    cin.getline(aux->nombre, sizeof(aux->nombre)); // Cambio aquí
    cout << " AHORA LA FECHA:\n\n";
    do
    {
        cout << "ANIO\n";
        cin >> aux->anio;
    } while (aux->anio != 2024);
    do
    {
        cout << "MES\n";
        cin >> aux->mes;
    } while (aux->mes < 1 || aux->mes > 12);
    do
    {
        cout << "DIA\n";
        cin >> aux->dia;
    } while (aux->dia < 1 || aux->dia > 31);
    cout << " COSTO:\n";
    cin >> aux->value;

    cout << " DESTINO:\n";
    cin.ignore();
    cin.getline(aux->destino, sizeof(aux->destino)); // para permitir ingresar cadenas con espacio
    do
    {
        cout << "INGRESE LA CAPACIDAD DE SU EMBARCACION:\n";
        cin >> aux->embarcacion;
    } while (aux->embarcacion < 1 || aux->embarcacion > 1000);

    cout << "\tSU IDENTIFICADOR UNICO ES: \n";

    string matriculaStr = "";
    for (int i = 0; i < 4; i++)
    {
        matriculaStr += to_string(aux->matricula[i]);
    }

    string identificadorUnico = generarIdentificadorUnico(matriculaStr, aux->anio, aux->mes, aux->dia);
    for (int i = 0; i < 10; i++)
    {
        aux->identificacion[i] = (i < (int)identificadorUnico.length()) ? identificadorUnico[i] - '0' : 0;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << aux->identificacion[i];
    }
    cout << endl;
    cout << "\n";

    aux->izq = NULL;
    aux->der = NULL;
    aux->altura = 1;
}
int main()
{
    raiz = NULL;
    int opc = 0;
    int identificador[10];
    int identificacion[10];

    do
    {
        cout << "\tMENU DE OPCIONES" << endl;
        cout << "1. Registrar nodo" << endl;
        cout << "2. Buscar un viaje por identificador" << endl;
        cout << "3. Listar todos los viajes" << endl;
        cout << "4. Eliminar un viaje por identificador" << endl;
        cout << "5. Registrar un pasajero en un viaje" << endl;
        cout << "6. Listar todos los pasajeros" << endl;
        cout << "7. Salir" << endl;
        cout << "Ingrese una opcion:\n";
        cin >> opc;

        switch (opc)
        {
        case 1:
            crearNodo();
            raiz = insertar(raiz);
            break;
        case 2:
             cout << "Ingrese el identificador del viaje a buscar: ";
            for (int i = 0; i < 10; i++)
            {
                cin >> identificador[i];
            }

            if (validarIdentificador(identificador))
            {
                nodo* nodoEncontrado = BuscarPorIdentificacion(raiz, identificador);
                if (nodoEncontrado != NULL)
                {
                    imprimirNodo(nodoEncontrado);
                }
                else
                {
                    cout << "El viaje no fue encontrado." << endl;
                }
            }
            else
            {
                cout << "El identificador ingresado no es válido." << endl;
            }
            break;
        case 3:
            cout << "Viajes registrados (Inorden):\n";
            Inorden(raiz);
            cout << endl;
            break;
        case 4:
            cout << "Eliminar un viaje:\n";
            cout << "Ingrese la identificación a eliminar: ";
            for (int i = 0; i < 10; i++)
            {
                cin >> identificacion[i];
            }

            if (validarIdentificador(identificacion) && BuscarPorIdentificacion(raiz, identificacion))
            {
                EliminarPorIdentificacion(raiz, identificacion);
                cout << "Viaje eliminado satisfactoriamente" << endl;
            }
            else
            {
                cout << "La identificación ingresada no existe" << endl;
            }
            break;
        case 5:
            // Implementar función para registrar un pasajero
            break;
        case 6:
            // Implementar función para listar todos los pasajeros
            break;
        case 7:
            cout << "Adiós" << endl;
            break;
        default:
            cout << "Opción inválida" << endl;
            break;
        }

        cout << endl;
    } while (opc != 7);

    return 0;
}