#include <iostream>
#include <malloc.h>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cmath>
#include<conio.h>
#include<string>

using namespace std;

struct pasajero
{
    char nombrep[45];

    pasajero *sig;
};

struct nodo
{

    char destino[45];
    int matricula[4];
    char nombre[45];
    long long int identificacion[10];

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
        // El √°rbol est√° vac√≠o, no hay elementos para listar
        cout << "EL ARBOL ESTA VACIO." << endl;
        return;
    }

    if (nodoEmbarcacion->inicioPasajeros == NULL)
    {
        cout << "NO HAY PASAJEROS REGISTRADOS EN ESTA EMBARCACION." << endl;
        return;
    }
    cout << "EMBARCACION: " << nodoEmbarcacion->nombre << " (ID: " << nodoEmbarcacion->identificacion[0] << ")" << endl;
    pasajero *temp = nodoEmbarcacion->inicioPasajeros;
    int count = 1;
    while (temp != NULL)
    {
        cout << count << ". " << temp->nombrep << endl;
        temp = temp->sig;
        count++;
    }
}

void listarTodosLosPasajeros(nodo *nodolis) {
    if (nodolis != NULL) {
        listarTodosLosPasajeros(nodolis->izq);
        listarPasajeros(nodolis);
        listarTodosLosPasajeros(nodolis->der); // Agregar este recorrido
    }
}

void imprimirNodo(nodo *nodoEncontrado)
{
    if (nodoEncontrado == NULL)
    {
        cout << "EL NODO ES NULO" << endl;
        return;
    }

    cout << "IDENTIFICADOR: " << nodoEncontrado->identificacion[0] << endl;
    cout << "MATRICULA: " << nodoEncontrado->matricula[0] << endl;

    cout << endl;
    cout << "NOMBRE: " << nodoEncontrado->nombre << endl;
    cout << "ANIO: " << nodoEncontrado->anio << endl;
    cout << "MES: " << nodoEncontrado->mes << endl;
    cout << "DIA: " << nodoEncontrado->dia << endl;
    cout << "COSTO: " << nodoEncontrado->value << endl;
    cout << "DESTINO: " << nodoEncontrado->destino << endl;
    cout << "CAPACIDAD: " << nodoEncontrado->embarcacion << endl;
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

bool compararIdentificadores(long long int identificador1,long long  int identificador2)
{
    return identificador1 < identificador2;
}

struct nodo *insertar(struct nodo *nodo)
{
    if (nodo == NULL)
    {
        return aux;
    }

    if (compararIdentificadores(aux->identificacion[0], nodo->identificacion[0])) // Comparaci√≥n por identificador
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
        Inorden(raizz->izq); // Recorrer sub√°rbol izquierdo

        // Imprimir informaci√≥n del nodo actual en orden ascendente
        cout << "NOMBRE: " << raizz->nombre << endl;
        cout << "IDENTIFICADOR: " << raizz->identificacion[0] << endl;
        cout << endl;

        Inorden(raizz->der); // Recorrer sub√°rbol derecho
    }
}

nodo *BuscarPorIdentificador(nodo *raiz, long long int idt)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->identificacion[0] == idt)
        return raiz;

    if (idt < raiz->identificacion[0])
        return BuscarPorIdentificador(raiz->izq, idt);

    return BuscarPorIdentificador(raiz->der, idt);
}
nodo *obtenerSucesor(nodo *n)
{
    nodo *temp = n->der;
    while (temp->izq != NULL)
    {
        temp = temp->izq;
    }
    return temp;
}

struct nodo *eliminar(struct nodo *raiz, long long int idt) {
    if (raiz == NULL) {
        cout << "NO SE ENCONTRO UNA EMBARCACION CON ESE IDENTIFICADOR." << endl;
        return raiz; // Retorna NULL si no se encuentra el nodo
    }

    if (idt < raiz->identificacion[0]) {
        raiz->izq = eliminar(raiz->izq, idt);
    } else if (idt > raiz->identificacion[0]) {
        raiz->der = eliminar(raiz->der, idt);
    } else {
        // Nodo con el ID encontrado
        if (raiz->izq == NULL || raiz->der == NULL) {
            struct nodo *temp = raiz->izq ? raiz->izq : raiz->der;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            // Nodo con dos hijos
            struct nodo *temp = obtenerSucesor(raiz);
            struct nodo *padreTemp = raiz;
            while (padreTemp->der != temp) {
                padreTemp = padreTemp->der;
            }

            // Copiar los datos del sucesor al nodo actual
            raiz->identificacion[0] = temp->identificacion[0];
            strcpy(raiz->nombre, temp->nombre);
            // ... (copiar otros campos)

            // Eliminar el sucesor (que ahora est· duplicado en el nodo actual)
            if (padreTemp == raiz) {
                raiz->der = eliminar(raiz->der, temp->identificacion[0]);
            } else {
                padreTemp->izq = eliminar(padreTemp->izq, temp->identificacion[0]);
            }
        }
    }

    // Si el ·rbol estaba vacÌo despuÈs de eliminar el nodo, retornar NULL
    if (raiz == NULL) {
        return raiz;
    }

    // Actualizar la altura y rebalancear el ·rbol (igual que antes)
    raiz->altura = 1 + mayor(obtenerAltura(raiz->izq), obtenerAltura(raiz->der));
    int balance = obtenerBalance(raiz);

    // REBALANCEAR DESPUES DE ELIMINAR UN NODO.
    if (balance > 1 && obtenerBalance(raiz->izq) >= 0) {
        return rotarDerecha(raiz);
    }
    if (balance < -1 && obtenerBalance(raiz->der) <= 0) {
        return rotarIzquierda(raiz);
    }
    if (balance > 1 && obtenerBalance(raiz->izq) < 0) {
        raiz->izq = rotarIzquierda(raiz->izq);
        return rotarDerecha(raiz);
    }
    if (balance < -1 && obtenerBalance(raiz->der) > 0) {
        raiz->der = rotarDerecha(raiz->der);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

long long int generarIdentificadorUnico(int matricula, int anio, int mes, int dia)
{
    long long int identificador = 0;

    int xx = matricula / 100;
    identificador = (long long)xx * 100000000 + anio * 10000 + mes * 100 + dia;

    return identificador;
}

void crearNodo()
{
    
    aux = (struct nodo *)malloc(sizeof(struct nodo));

    // Validar matr√≠cula
    do
    {
        cout << " INGRESE MATRICULA DE LA EMBARCACION";
        cout << "LA MATRICULA ES DE 4 DIGITOS\n";

        cin >> aux->matricula[0];

    } while (aux->matricula[0] < 1000 || aux->matricula[0] > 9999); // Validar que la matr√≠cula tenga 4 d√≠gitos
    cout << " INGRESE NOMBRE DE SU EMBARCACION\n";
    cin.ignore();
    cin.getline(aux->nombre, sizeof(aux->nombre)); 

    cout << " AHORA LA FECHA:\n";
    cout<<endl;
    do
    {
        cout << "ANIO\n(DEBE SER EL ACTUAL)\n";
        cin >> aux->anio;
    } while (aux->anio != 2024);
    do
    {
        cout << "MES\n(1-12)\n";
        cin >> aux->mes;
    } while (aux->mes < 1 || aux->mes > 12);
    do
    {
        cout << "DIA\n(1-31)\n";
        cin >> aux->dia;
    } while (aux->dia < 1 || aux->dia > 31);
    cout << " COSTO:\n";
    cin >> aux->value;

    cout << " DESTINO:\n";
    cin.ignore();
    cin.getline(aux->destino, sizeof(aux->destino)); // para permitir ingresar cadenas con espacio
    		
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
    system("pause");
}

void registrarpasajero(nodo *raiz, long long int identificado[])
{

    cout << " NODOS DISPONIBLES: " << endl;
    Inorden(raiz);
    system("pause");

   long long  int identificadore;
    cout << "INGRESE EL IDENTIFICADOR AL CUAL DESEA REGISTRAR SU PASAJERO: ";
    cin >> identificadore;

    // Buscar el nodo con el identificador proporcionado
    nodo *nodoEncontrado = BuscarPorIdentificador(raiz, identificadore);

    if (nodoEncontrado == NULL)
    {
        cout << "NO SE ENCONTRO UNA EMBARCACION CON ESE IDENTIFICADOR." << endl;
        return;
    }

    if (nodoEncontrado->numPasajeros > nodoEncontrado->embarcacion)
    {
        cout << "LA CAPACIDAD DE LA EMBARCACION ESTA COMPLETA." << endl;
        return;
    }

    char opcion;
    do
    {
        cab = (struct pasajero *)malloc(sizeof(struct pasajero));
        cout << "INGRESE NOMBRE DEL PASAJERO: ";
        cin.ignore();
        cin.getline(cab->nombrep, sizeof(cab->nombrep)); 
        cab->sig = NULL;
        if (nodoEncontrado->inicioPasajeros == NULL) {
            nodoEncontrado->inicioPasajeros = cab;
            nodoEncontrado->finPasajeros = cab; // Inicializar finPasajeros aquÌ
        } else {
            nodoEncontrado->finPasajeros->sig = cab;
            nodoEncontrado->finPasajeros = cab; // Actualizar finPasajeros aquÌ
        }

        nodoEncontrado->numPasajeros++;
        cout << "PASAJERO REGISTRADO EXITOSAMENTE." << endl;

        cout << "ø DESEA AGREGAR OTRO PASAJERO ? (s/n):\n ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S' && nodoEncontrado->numPasajeros < nodoEncontrado->embarcacion); // Verificar capacidad
}

int main()
{
    
    int opc = 0;
raiz=NULL; 
    long long int idb=0;
    long long int identificador[10];
    long long int identificacion[10];
    string nombrePasajero;
    do
    {
        cout << "\tMENU DE OPCIONES" << endl;
        cout << "1. REGISTRAR NODO" << endl;
        cout << "2. BUSCAR UN NODO POR IDENTIFICADOR" << endl;
        cout << "3. LISTAR TODOS LOS NODOS (INORDEN)" << endl;
        cout << "4. ELIMINAR UN NODO POR IDENTIFICADOR" << endl;
        cout << "5. REGISTRAR UN PASAJERO EN UN NODO" << endl;
        cout << "6. LISTAR TODOS LOS PASAJEROS" << endl;
        cout << "7. SALIR" << endl;
        cout << "INGRESE UNA OPCION:\n";
        cin >> opc;

        switch (opc)
        {
        case 1:
            crearNodo();
            raiz = insertar(raiz);
            break;
        case 2:
        {
            long long int idb;
            cout << "INGRESE IDENTIFICADOR A BUSCAR: ";
            cin >> idb;

            nodo *nodoEncontrado = BuscarPorIdentificador(raiz, idb);

            if (nodoEncontrado != NULL)
            {
                cout << "NODO ENCONTRADO:" << endl;
                imprimirNodo(nodoEncontrado);
               
            }
            else
            {
                cout << "NO SE HA ENCONTRADO NINGUN NODO CON ESE IDENTIFICADOR." << endl;
            }
            break;
        }
        case 3:
            cout << "NODOS REGISTRADOS (Inorden):\n";
            Inorden(raiz);
            cout << endl;
            break;
            system("pause");

        case 4: {
    long long int idEliminar;
    cout << "INGRESE EL IDENTIFICADOR DEL NODO A ELIMINAR: ";
    cin >> idEliminar;

    raiz = eliminar(raiz, idEliminar); 
    if (raiz != NULL) {
        cout << "NODO ELIMINADO EXITOSAMENTE." << endl;
    }
    break;
}
		
        case 5:{
		
            registrarpasajero(raiz, identificador);
            break;
        }
        case 6:{
		
            // Implementar funci√≥n para listar todos los pasajeros
            cout << "LISTANDO TODOS LOS PASAJEROS: " << endl;
            listarTodosLosPasajeros(raiz);
            break;
            system("pause");
        }
        case 7:
            cout << "BYE BYE" << endl;
            break;
        default:
            cout << "OPCION INVALIDA" << endl;
            break;
        }

        cout << endl;
    } while (opc != 7);

    return 0;
}

