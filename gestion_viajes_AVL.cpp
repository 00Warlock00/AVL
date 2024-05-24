#include <iostream>
#include <malloc.h>
#include <iomanip>
#include <sstream>
using namespace std;

struct nodo
{

    char destino[45];
    char matricula[4];
    char nombre[45];
    char identificacion[10];

    int value;
    int anio, mes, dia;
    int embarcacion;
    int altura;

    nodo *izq;
    nodo *der;
};

struct nodo *raiz, *sig, *aux, aux2;

int crearNodo()
{
    aux = (struct nodo *)malloc(sizeof(struct nodo));
    cout << " INGRESE MATRICULA DE LA EMBARCACIÓN\n ";
    cin >> aux->matricula;
    cout << " INGRESE NOMBRE DE SU EMBARCACIÓN\n";
    cin >> aux->nombre;
    cout << " AHORA LA FECHA:\n";
    cout << "\n";
    cout << " AÑO\n";
    cin >> aux->anio;
    cout << " MES\n ";
    cin >> aux->mes;
    cout << " DÍA\n";
    cin >> aux->dia;
    cout << " COSTO:\n";
    cin >> aux->value;
    cout << " DESTINO:\n";
    cin >> aux->destino;
    cout << "INGRESE LA CAPACIDAD DE SU EMBARCACION:\n";
    cin >> aux->embarcacion;
    cout << "\tSU IDENTIFICADOR UNICO ES: \n";
    cout << aux->identificacion = identificador(aux->matricula, aux->anio, aux->mes, aux->dia);

    aux->izq = NULL;
    aux->der = NULL;
    aux->altura = 1;
}

string identificador(const char *matricula, int anio, int mes, int dia)
{
    string identificador;
    identificador += matricula[0];
    identificador += matricula[1];
    identificador += to_string(anio); // Convierte el int a string

    // Rellena con ceros el mes y día si es necesario
    identificador += (mes < 10) ? "0" + to_string(mes) : to_string(mes);
    identificador += (dia < 10) ? "0" + to_string(dia) : to_string(dia);

    return identificador;
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

void inorden(struct nodo *nodo)
{
    if (nodo != NULL)
    {
        while (nodo->identificacion < aux->identificacion)
        {
            inorden(nodo->izq);
            cout <<nodo->identificacion << " ";
            inorden(nodo->der);
        }
    }
}

int main()
{
    raiz = NULL;
    int opc = 0;
    do
    {
        cout << "Menu de opciones" << endl;
        cout << "1. Registrar un nodo" << endl;
        cout << "2. Mostrar Arbol" << endl;
        cout << "3. Salir" << endl;
        cin >> opc;
        switch (opc)
        {
        case 1:
            crearNodo();
            raiz = insertar(raiz);
            break;
        case 2:
            cout << "PreOrden: ";
            preOrden(raiz);
            cout << endl;
            break;
        }
    } while (opc != 3);
    return 0;
}