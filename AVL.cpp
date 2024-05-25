#include <iostream>
#include <malloc.h>
#include <iomanip>
#include <sstream>
using namespace std;

struct pasajero
{
    string nombre;

    pasajero *sig;
};

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
    pasajero *nuevo;
    nodo *izq;
    nodo *der;
};

struct nodo *raiz = NULL;
struct nodo *aux, *aux2;

void identificador(char *matricula, int anio, int mes, int dia, char *identificacion)
{
    sprintf(identificacion, "%c%c%04d%02d%02d", matricula[0], matricula[1], anio, mes, dia);
}

void crearNodo()
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
    identificador(aux->matricula, aux->anio, aux->mes, aux->dia, aux->identificacion);
    cout << aux->identificacion << endl;
    aux->izq = NULL;
    aux->der = NULL;
    aux->altura = 1;
}

int registrarPasajero(pasajero* cab)
{
    int subopc=0;
Inorden(raiz);
cab=(struct pasajero *)malloc(sizeof(struct pasajero));
cout<<" A QUE EMBARCACION DESEA REGISTRARSE\n";
cin>>

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
bool buscarNodoPorIdentificacion(nodo *r, string identificador)
{
    if (r == NULL)
    {
        return false;
    }
    if (r->identificacion == identificador)
    {
        return true;
    }
    return buscarNodoPorIdentificacion(r->izq, identificador) || buscarNodoPorIdentificacion(r->der, identificador);
}

int main()
{
    raiz = NULL;
    int opc = 0;
    string identificacion = "";
    do
    {
        cout << "\tMENU DE OPCIONES" << endl;
        cout << "1. REGISTRAR NODO" << endl;
        cout << "2. BUSCAR UN VIAJE POR IDENTIFICADOR" << endl;
        cout << "3. LISTAR TODOS LOS VIAJES" << endl;
        cout << "4. ELIMINAR UN VIAJE POR IDENTIFICADOR" << endl;
        cout << "5. REGISTRAR UN PASAJERO EN UN VIAJE" << endl;
        cout << "6. LISTAR TODOS LOS PASAJEROS" << endl;
        cout << "7. SALIR" << endl;
        cin >> opc;
        switch (opc)
        {
        case 1:
            crearNodo();
            raiz = insertar(raiz);
            break;
        case 2:
            buscarNodoPorIdentificacion(raiz, identificacion);
            break;
        case 3:
            cout << "INORDEN:\n ";
            Inorden(raiz);
            cout << endl;
            break;
        case 4:
            Inorden(raiz);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            cout << " BYE BYE\n ";
            break;
        default:
            cout << " OPCION INVALIDA\n";
            break;
        }
    } while (opc != 7);

    return 0;
}