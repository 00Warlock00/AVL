
#include <iostream>
#include <malloc.h>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cmath>
using namespace std;

struct pasajero
{
    string nombrep;

    pasajero *sig;
};
const int MAX_NOMBRE_EMBARCACION = 100; // Tamaño máximo permitido para el nombre de la embarcación

const int MAX_IDENTIFICADOR = 100; // Tamaño máximo permitido para el identificador
struct nodo
{

    char destino[45];
    int matricula[4];
    string nombre;
    int identificacion[MAX_IDENTIFICADOR];

    int capacidad;
    int value;
    int anio, mes, dia;
    int embarcacion;
    int altura;
    int numPasajeros;
    pasajero *inicioPasajeros;
    pasajero *finPasajeros;
    nodo *izq;
    nodo *der;
};

struct nodo *raiz = NULL;
struct nodo *aux, *aux2;
struct pasajero *cab;

void listarPasajeros(nodo *nodoEmbarcacion)
{
    if (nodoEmbarcacion == NULL)
    {
        // El árbol está vacío, no hay elementos para listar
        cout << "El árbol está vacío." << endl;
        return;
    }

    if (nodoEmbarcacion->inicioPasajeros == NULL)
    {
        cout << "No hay pasajeros registrados en esta embarcación." << endl;
        return;
    }
    cout << "Embarcación: " << nodoEmbarcacion->nombre << " (ID: " << nodoEmbarcacion->identificacion[0] << ")" << endl;
    pasajero *temp = nodoEmbarcacion->inicioPasajeros;
    int count = 1;
    while (temp != NULL)
    {
        cout << count << ". " << temp->nombrep << endl;
        temp = temp->sig;
        count++;
    }
}

void listarTodosLosPasajeros(nodo *nodolis)
{
    if (nodolis == NULL)
    {
        cout << "No hay embarcaciones registradas." << endl;
        return;
    }
    if (nodolis != NULL)
    {
        listarTodosLosPasajeros(nodolis->izq);
        listarPasajeros(nodolis);
    }

    listarTodosLosPasajeros(nodolis->der);
}
void imprimirNodo(nodo *nodoEncontrado)
{
    if (nodoEncontrado == NULL)
    {
        cout << "El nodo es nulo" << endl;
        return;
    }

    cout << "Identificador: " << nodoEncontrado->identificacion[0] << endl;
    cout << "Matrícula: " << nodoEncontrado->matricula[0] << endl;

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

bool compararIdentificadores(int identificador1, int identificador2)
{
    return identificador1 < identificador2;
}

struct nodo *insertar(struct nodo *nodo)
{
    if (nodo == NULL)
    {
        return aux;
    }

    if (compararIdentificadores(aux->identificacion[0], nodo->identificacion[0])) // Comparación por identificador
    {
        nodo->izq = insertar(nodo->izq);
    }
    else
    {
        nodo->der = insertar(nodo->der);
    }

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && compararIdentificadores(aux->identificacion[0], nodo->izq->identificacion[0]))
    {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && !compararIdentificadores(aux->identificacion[0], nodo->der->identificacion[0]))
    {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && !compararIdentificadores(aux->identificacion[0], nodo->izq->identificacion[0]))
    {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && compararIdentificadores(aux->identificacion[0], nodo->der->identificacion[0]))
    {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void Inorden(nodo *raizz)
{
    if (raizz != NULL)
    {
        Inorden(raizz->izq); // Recorrer subárbol izquierdo

        // Imprimir información del nodo actual en orden ascendente
        cout << "Nombre: " << raizz->nombre << endl;
        cout << "Identificador: " << raizz->identificacion[0] << endl;
        cout << endl;

        Inorden(raizz->der); // Recorrer subárbol derecho
    }
}

nodo *BuscarPorIdentificador(nodo *raiz, int idt)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->identificacion[0] == idt)
        return raiz;

    if (idt < raiz->identificacion[0])
        return BuscarPorIdentificador(raiz->izq, idt);

    return BuscarPorIdentificador(raiz->der, idt);
}

void EliminarPorIdentificacion(nodo *tallo, int eliminar[])
{
    if (tallo == NULL)
    {
        return;
    }

    bool sonIguales = true;
    for (int i = 0; i < 10; i++)
    {
        if (tallo->identificacion[i] != eliminar[i])
        {
            sonIguales = false;
            break;
        }
    }

    if (sonIguales)
    {
        // Eliminar el nodo
        if (tallo->izq == NULL && tallo->der == NULL)
        {
            delete tallo;
            tallo = NULL;
        }
        else if (tallo->izq == NULL)
        {
            nodo *temp = tallo;
            tallo = tallo->der;
            delete temp;
        }
        else if (tallo->der == NULL)
        {
            nodo *temp = raiz;
            tallo = tallo->izq;
            delete temp;
        }
        else
        {
            nodo *temp = tallo->der;
            while (temp->izq != NULL)
            {
                temp = temp->izq;
            }
            // Copiar el identificador elemento por elemento
            for (int i = 0; i < 10; i++)
            {
                tallo->identificacion[i] = temp->identificacion[i];
            }
            EliminarPorIdentificacion(tallo->der, eliminar);
        }
    }
    else if (eliminar[0] < raiz->identificacion[0])
    {
        EliminarPorIdentificacion(tallo->izq, eliminar);
    }
    else
    {
        EliminarPorIdentificacion(tallo->der, eliminar);
    }
}
int generarIdentificadorUnico(int matricula, int anio, int mes, int dia)
{
    int identificador = 0;

    int xx = matricula / 100;
    identificador = xx * 100000000 + anio * 10000 + mes * 100 + dia;

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
    cin.ignore();
    cin>>aux->nombre; 

    

    cout << " AHORA LA FECHA:\n";
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

    aux->identificacion[0] = generarIdentificadorUnico(aux->matricula[0], aux->anio, aux->mes, aux->dia);
    cout << aux->identificacion[0] << endl;
    cout << "\n";

    aux->izq = NULL;
    aux->der = NULL;
    aux->altura = 1;
    aux->inicioPasajeros = NULL;
    aux->finPasajeros = NULL;
    aux->numPasajeros = 0;
}

void registrarpasajero(nodo *raiz, int identificado[])
{

    cout << " nodos disponibles: " << endl;
    Inorden(raiz);

    int identificadore;
    cout << "Ingrese el identificador de la embarcacion a registrar sus pasajeros: ";
    cin >> identificadore;

    // Buscar el nodo con el identificador proporcionado
    nodo *nodoEncontrado = BuscarPorIdentificador(raiz, identificadore);

    if (nodoEncontrado == NULL)
    {
        cout << "No se encontró la embarcación con el identificador proporcionado." << endl;
        return;
    }

    if (nodoEncontrado->numPasajeros >= nodoEncontrado->embarcacion)
    {
        cout << "La embarcacion ha alcanzado su capacidad maxima." << endl;
        return;
    }

    char opcion;
    do
    {
        cab = (struct pasajero *)malloc(sizeof(struct pasajero));
        cout << "Ingrese el nombre del pasajero: ";
        cin.ignore();
        getline(cin, cab->nombrep);
        cab->sig = NULL;
        if (nodoEncontrado->inicioPasajeros == NULL)
        {
            nodoEncontrado->inicioPasajeros = cab;
            nodoEncontrado->finPasajeros = cab;
        }
        else
        {
            nodoEncontrado->finPasajeros->sig = cab;
            nodoEncontrado->finPasajeros = cab;
        }

        nodoEncontrado->numPasajeros++;
        cout << "Pasajero registrado exitosamente." << endl;

        cout << "¿Desea registrar otro pasajero? (s/n): ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');
}

int main()
{
    
    int opc = 0;

    int idb=0;
    int identificador[MAX_IDENTIFICADOR];
    int identificacion[MAX_IDENTIFICADOR];
    string nombrePasajero;
    do
    {
        cout << "\tMENU DE OPCIONES" << endl;
        cout << "1. Registrar nodo" << endl;
        cout << "2. Buscar un nodo por identificador" << endl;
        cout << "3. Listar todos los nodos" << endl;
        cout << "4. Eliminar un nodo por identificador" << endl;
        cout << "5. Registrar un pasajero en un nodo" << endl;
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
        {
            int idb;
            cout << "Ingrese el identificador a buscar: ";
            cin >> idb;

            nodo *nodoEncontrado = BuscarPorIdentificador(raiz, idb);

            if (nodoEncontrado != NULL)
            {
                cout << "Nodo encontrado:" << endl;
                imprimirNodo(nodoEncontrado);
            }
            else
            {
                cout << "No se encontró ningún nodo con ese identificador." << endl;
            }
            break;
        }
        case 3:
            cout << "nodos registrados (Inorden):\n";
            Inorden(raiz);
            cout << endl;
            break;

        case 4:

            break;

        case 5:

            registrarpasajero(raiz, identificador);
            break;
        case 6:
            // Implementar función para listar todos los pasajeros
            cout << "Listando todos los pasajeros:" << endl;
            listarTodosLosPasajeros(raiz);
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