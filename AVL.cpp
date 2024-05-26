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

void validarMatricula(int matricula[])
{

    cout << "Ingrese la matricula (maximo 4 Digitos): ";
    cin >> matricula;
    if (matricula < 1000 || matricula > 9999)
    {
        cout << "LA MATRICULA DEBE SER DE 4 DIGITOS";
    }
    else
    {
        // Verificar si la matrícula ingresada tiene más de 4 dígitos
        int numDigitos = 0;
        int temp = matricula[0];

        while (temp != 0)
        {
            temp /= 10;
            numDigitos++;
        }

        if (numDigitos != 4)
        {
            cout << "La matricula debe tener exactamente 4 Digitos." << endl;
        }

        else
        {
            cout << "Entrada inválida. Intente nuevamente." << endl;
        }
    }

    void validarFecha(int &anio, int &mes, int &dia)
    {
        bool esValida = false;
        while (!esValida)
        {
            cout << " INGRESE EL ANIO\n";

            if (anio != 2024)
            {
                cout << " EL AÑO DEBE SER EL ACTUAL\n";
            }
            else
            {
                esValida = true;
                cout << " INGRESE EL MES\n";

                if (mes < 1 || mes > 12)
                {
                    cout << "EL MES DEBE SER DE 1 A 12\n";
                    esValida = false;
                }
                else
                {
                    cout << " INGRESE EL DIA\n";

                    if (dia < 1 || dia > 31)
                    {
                        cout << " EL DIA DEBE SER DE 1 A 31\n";
                        esValida = false;
                    }
                }
                else
                {
                    cout << "Entrada inválida. Intente nuevamente." << endl;
                    esValida = false;
                }
            }

            else
            {
                cout << "Entrada inválida. Intente nuevamente." << endl;
                esValida = false;
            }
        }

        else
        {
            cout << "Entrada inválida. Intente nuevamente." << endl;
        }
    }
}

// Función para validar el identificador
bool validarIdentificador(int identificador[])
{
    if (identificador == nullptr)
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
    if (nodoEncontrado == nullptr)
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

struct nodo *insertar(struct nodo *nodo)
{
    if (nodo == NULL)
    {
        return aux;
    }

    if (aux->value < nodo->value)
    {
        nodo->izq = insertar(nodo->izq);
    }
    else if (aux->value > nodo->value)
    {
        nodo->der = insertar(nodo->der);
    }
    else
    {
        return nodo;
    }

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && aux->value < nodo->izq->value)
    {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux->value > nodo->der->value)
    {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && aux->value > nodo->izq->value)
    {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux->value < nodo->der->value)
    {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void Inorden(nodo *aux3)
{

    if (aux3 != NULL)
    {
        Inorden(aux3->izq);
        cout << "Identificación: " << aux3->identificacion << endl;
        cout << endl;
        Inorden(aux3->der);
    }
}
nodo *BuscarPorIdentificacion(nodo *r, int identificador[])
{
    if (r == NULL)
    {
        return NULL;
    }
    else
    {
        bool sonIguales = true; // Inicializar sonIguales a true
        for (int i = 0; i < 10; i++)
        {
            if (r->identificacion[i] != identificador[i])
            {
                sonIguales = false;
                break;
            }
        }
        if (sonIguales)
        {
            return r; // Devuelve el puntero al nodo encontrado
        }
    }

    nodo *encontrado = BuscarPorIdentificacion(r->izq, identificador);
    if (encontrado != NULL)
    {
        return encontrado; // Devuelve el puntero al nodo encontrado en el subárbol izquierdo
    }
    else
    {
        return BuscarPorIdentificacion(r->der, identificador); // Busca en el subárbol derecho
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
void crearNodo()
{
    aux = (struct nodo *)malloc(sizeof(struct nodo));

    // Validar matrícula
    cout << " INGRESE MATRICULA DE LA EMBARCACIÓN (MAXIMO 4 DIGITOS)\n ";
    validarMatricula(aux->matricula);

    // Ingresar nombre de la embarcación
    cout << " INGRESE NOMBRE DE SU EMBARCACIÓN\n";
    cin.ignore();                                  // Agregar esta línea
    cin.getline(aux->nombre, sizeof(aux->nombre)); // Cambio aquí

    // Validar fecha
    cout << " AHORA LA FECHA:\n\n";
    validarFecha(aux->anio, aux->mes, aux->dia);

    cout << " COSTO:\n";
    cin >> aux->value;

    cout << " DESTINO:\n";
    cin.ignore();
    cin.getline(aux->destino, sizeof(aux->destino)); // para permitir ingresar cadenas con espacio

    cout << "INGRESE LA CAPACIDAD DE SU EMBARCACION:\n";
    cin >> aux->embarcacion;
    if (aux->embarcacion < 1 || aux->embarcacion > 1000)
    {
        cout << "Entrada inválida para la capacidad de la embarcación. Operación cancelada." << endl;
        free(aux);
        aux = NULL;
    }
    else
    {
        // Generar identificador único
        cout << "\tSU IDENTIFICADOR UNICO ES: \n";
        identificador(aux->matricula, aux->anio, aux->mes, aux->dia, aux->identificacion);
        cout << aux->identificacion << endl;
        cout << "\n";

        aux->izq = NULL;
        aux->der = NULL;
        aux->altura = 1;
    }
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
        cout << "Ingrese una opción: ";
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
                nodo *nodoEncontrado = BuscarPorIdentificacion(raiz, identificador);
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
