/*Big O(N) ------->Final de Algoritmos y Programación 4 (Yorman Tobón)

->lista circular doblemente ligada
->Regex

" Divide un problema grande, en pequeñas partes y venceras " Anonimo.

*/
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <ctime>
#include <time.h>
#include <regex>

using namespace std;

struct Celda///////Creacion de la estructura de las Celdas en la lista.
{
    string placa, fecha, tipoVehiculo;

    Celda *siguiente;
    Celda *anterior;
} * inicio, *fin;

int menu();//Menu de opciones. 
bool existe(string);//Validación si existe la placa en los vehiculos ingresados.
string fechaLocal();//retorna dia/mes/año.
void insertarCelda();//Para el ingreso de cada vehiculo.
bool validarPlacaCarro(string);//Utilizando regex para validar la nomenclatura de los vehiculos.
bool validarPlacaMoto(string);//Utilizando regex para validar la nomenclatura de los vehiculos.
void mostrar();//Vehiculos en el parqueadero.
void eliminar();//Salida de los vehiculos.
void insertarVehiculo(string, string, string);//Para cargar los vehiculos que aun estan en el parqueadero del día antes.
void pasarListaArchivo();//vehiculos que quedan en el parqueadero para el otro día.
void pasarArchivoLista();//Para cargar los vehiculos que aun estan en el parqueadero del día antes.
void iniciar();//Para cargar los vehiculos que aun estan en el parqueadero del día antes.
void descargar();//vehiculos que quedan en el parqueadero para el otro día.
int pago(string);//Para el cierre de la caja.
void vaciar();//Limpiando la memoria RAM.

//variable para manejar la caja.
int Caja = 0;

//función central del programa.
int main()
{
    cout<<"--------------------Cargando informacion parqueadero-------------------------\n";
    iniciar();
    mostrar();
    system("pause");
    int op = 0;
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            insertarCelda();
            cout <<endl;
            mostrar();
             cout <<endl;

            system("pause");
            break;
        case 2:
            eliminar();
            cout <<endl;
            mostrar();
            cout <<endl;

            system("pause");
            break;
        case 3:
                    cout <<endl;

            cout << "saliendo..\n";
            break;

        default:
            break;
        }
    } while (op != 3);
    cout<<"\n\n--------------------Descargando informacion parqueadero-------------------------\n";
    descargar();
    cout<<"\n----------------------Vaciando RAM------------------------------------------------\n";
    vaciar();
    cout<<"\n----------------------Caja--------------------------------------------------------\n";
    cout << "\n\nEn el cierre de caja ahi un total de: $" << Caja << endl;
}

//returna true si la placa ya esta registrada.
bool existe(string placa)
{
    Celda *aux = inicio;
    if (aux != NULL)
    {
        do
        {
            if (placa == aux->placa)
            {
                return true;
            }
            aux = aux->siguiente;
        } while (aux != inicio);
    }
    return false;
}

//menu de opciones.
int menu()
{
    int op;
    cout << "------------------------Menu Principal------------------------\n";
    cout << "--------------------------------------------------------------\n";
    cout << "--------------------------------------------------------------\n";
    cout << "---1. Ingreso----------------------------------------\n";
    cout << "---2. Salida----------------------------------------\n";
    cout << "---3. Salir-----------------------------------------\n";
    cout << "--------------------------------------------------------------\n";
    cout << "---<1-2-3>--------------------------------------------\n";
    cin >> op;
    return op;
}

//Regex en las placas retorna true si esta correcta.
bool validarPlacaCarro(string placa)
{
    const regex expReg("[A-Z]{3}\\d{3}");
    return regex_match(placa, expReg);
}

//Regex en las placas retorna true si esta correcta.
bool validarPlacaMoto(string placa)
{
    const regex expresion("[A-Z]{3}\\d{2}[A-Z]");
    return regex_match(placa, expresion);
}

//ingreso de vehiculos en el parqueadero.
void insertarCelda()
{

    string placa, fecha = fechaLocal(), tipo;
    int tipoVehiculo;
    bool val = false; // la utilidad sera para validar que tipo de vehiculo ingresa al parqueadero

    cout << "\n-->Pon 1 para moto\n-->Pon 2 para carros\n";
    cin >> tipoVehiculo;
    if (tipoVehiculo == 1)
    {
        do
        {
            cout << "\nDigita la placa de la moto\n";
            cin >> placa;
            tipo = "moto";
        } while (!validarPlacaMoto(placa));
    }
    else if (tipoVehiculo == 2)
    {
        do
        {
            cout << "\nDigita la placa del automovil o camion\n";
            cin >> placa;
            cout << "\n-->Pon 1 para camion\n-->Pon 2 para automovil\n-->Pon 3 para camioneta\n";
            cin >> tipoVehiculo;
            if (tipoVehiculo == 1)
            {
                tipo = "camion";
            }
            else if (tipoVehiculo == 2)
            {
                tipo = "automovil";
            }
            else if (tipoVehiculo == 3)
            {
                tipo = "camioneta";
            }
            else
            {
                cout << "opcion invalida";
                val = true;
            }

        } while (!validarPlacaCarro(placa) or val);
    }

    if (existe(placa))
    {
        cout << "La placa del producto se encuentra registadro\nIntentalo nuevamente...\n";
    }
    else
    {

        Celda *nuevo = new Celda();
        Celda *aux1 = inicio;
        Celda *aux2 = NULL;

        nuevo->placa = placa;
        nuevo->tipoVehiculo = tipo;
        nuevo->fecha = fecha;

        while ((aux1 != fin))
        {
            aux2 = aux1;
            aux1 = aux1->siguiente;
        }
        if (aux1 == NULL)
        {

            inicio = fin = nuevo;
            nuevo->anterior = nuevo;
            nuevo->siguiente = nuevo;
        }
        else if (aux1 == inicio)
        {

            aux1->siguiente = nuevo;
            nuevo->siguiente = aux1;
            aux1->anterior = nuevo;
            nuevo->anterior = aux1;
            fin = nuevo;
        }
        else
        {
            fin->siguiente = nuevo;
            nuevo->siguiente = inicio;
            inicio->anterior = nuevo;
            nuevo->anterior = fin;
            fin = nuevo;
        }
    }
}

//Dia/Mes/Año del ingreso del vehiculo.
string fechaLocal()
{
    time_t rawtime;
    struct tm *timeinfo;
    char fech[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(fech, 80, "%d/%m/%y", timeinfo);

    return fech;
}

//Vehiculos en el parqueadero.
void mostrar()
{
        cout<<"\n\n--------------------Vehiculos en el parqueadero-------------------------\n";

    string fecha, placa, tipo;

    Celda *aux = inicio;
    if (aux == NULL)
    {
        cout << "\nParqueadero vacio...\n";
    }
    else
    {

        fecha = aux->fecha;
        placa = aux->placa;
        tipo = aux->tipoVehiculo;
        aux = aux->siguiente;

        cout << "\nFecha: " << fecha << "\nPlaca: " << placa << "\nTipoVehiculo: " << tipo << endl;

        while (aux != inicio)
        {
            fecha = aux->fecha;
            placa = aux->placa;
            tipo = aux->tipoVehiculo;
            aux = aux->siguiente;

            cout << "\nFecha: " << fecha << "\nPlaca: " << placa << "\nTipoVehiculo: " << tipo << endl;
        }
    }
    cout<<endl;
}

//retorna el valor de la hora dependiendo del vehiculo.
int pago(string tipo)
{

    ifstream archivo;
    int pago, pagoFinal;
    string nombre;

    archivo.open("tarifas.txt", ios::in);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo\n";
    }
    else
    {
        if (archivo.eof())
        {
            archivo >> nombre;
            archivo >> pagoFinal ;
        }
        else
        {
            archivo >> nombre;
            while (!archivo.eof())
            {
                archivo >> pago;
                if (nombre == tipo)
                {
                    pagoFinal = pago;
                }
                archivo >> nombre;
            }
        }
    }
    return pagoFinal;
}

//salida de los vehiculos.
void eliminar()
{
    string placa, tipo;
    Celda *aux1 = inicio;
    Celda *aux2 = NULL;
    cout << "\nDigite la placa del vehiculo a eliminar\n";
    cin >> placa;
    if (aux1 == NULL)
    {
        cout << "\nParqueadero vacio...\n";
    }
    else
    {

        if (fin == inicio)
        {
            inicio = fin = NULL;
            tipo=aux1->tipoVehiculo;
            delete aux1;
            cout << "Parqueadero vacio...\n";
            system("pause");
        }
        else
        {

            while ((aux1 != fin) and (aux1->placa != placa))
            {
                aux2 = aux1;
                aux1 = aux1->siguiente;
            }
            tipo = aux1->tipoVehiculo;
            if (aux1 == inicio)
            {

                inicio = aux1->siguiente;
                fin->siguiente = inicio;
                inicio->anterior = fin;
                delete aux1;
            }
            else if (aux1 == fin)
            {
                aux2->siguiente = inicio;
                inicio->anterior = aux2;
                fin = aux2;
                delete aux1;
            }
            else
            {
                Celda *aux3 = aux1->siguiente;
                aux2->siguiente = aux3;
                aux3->anterior = aux2;
                delete aux1;
            }
        }
    }

    int horas, cuota = pago(tipo);

    cout << "digita la cantidad de horas\n";
    cin >> horas;
    cout << horas << "*" << cuota << endl;
    Caja += horas * cuota;
}

//Para cargar los vehiculos en el sistema del dia anterior.
void insertarVehiculo(string fecha, string placa, string tipo)
{
    Celda *nuevo = new Celda();
    Celda *aux1 = inicio;
    Celda *aux2 = NULL;

    nuevo->placa = placa;
    nuevo->tipoVehiculo = tipo;
    nuevo->fecha = fecha;

    if (aux1 == NULL)
    {

        fin = nuevo;
        inicio = nuevo;
        nuevo->anterior = fin;
        fin->siguiente = nuevo;
    }
    else
    {

        while ((aux1 != fin))
        {
            aux2 = aux1;
            aux1 = aux1->siguiente;
        }
        if (aux1 == inicio)
        {

            aux1->siguiente = nuevo;
            nuevo->siguiente = aux1;
            aux1->anterior = nuevo;
            nuevo->anterior = aux1;
            fin = nuevo;
        }
        else
        {
            fin->siguiente = nuevo;
            nuevo->siguiente = inicio;
            inicio->anterior = nuevo;
            nuevo->anterior = fin;
            fin = nuevo;
        }
    }
}

//Guarda los vehiculos localmente que quedan en el parqueadero al cerrar.
void pasarListaArchivo()
{
    ofstream archivo;
    string placa, fecha, tipoVehiculo;
    int tiempoParqueado;
    Celda *aux = inicio;

    archivo.open("auxParqueadero.txt", ios::out | ios::app);
    system("pause");
    if (archivo.fail())
    {
        cout << "\nNo se puedo abrir el archivo.\n";
    }
    else
    {
        if (aux == NULL)
        {
            cout << "\nParqueadero vacio...\n";
            system("pause");
        }
        else
        {
            fecha = aux->fecha;
            placa = aux->placa;
            tipoVehiculo = aux->tipoVehiculo;

            archivo << fecha << "     " << placa << "    " << tipoVehiculo << endl;
            aux = aux->siguiente;
            while (aux != inicio)
            {
                fecha = aux->fecha;
                placa = aux->placa;
                tipoVehiculo = aux->tipoVehiculo;

                archivo << fecha << "     " << placa << "    " << tipoVehiculo << endl;
                aux = aux->siguiente;
            }
        }
        archivo.close();
        remove("Parqueadero.txt");
        rename("auxParqueadero.txt", "Parqueadero.txt");
    }
}

//Carga los vehiculos que quedaron el dia anterior.
void pasarArchivoLista()
{
    ifstream archivo;
    string placa, fecha, tipoVehiculo;
    Celda *aux = inicio;

    archivo.open("Parqueadero.txt", ios::in);
    if (!archivo.is_open())
    {
        cout << "\nNo se pudo abrir el archivo\n";
    }
    else
    {
        archivo >> fecha;
        while (!archivo.eof())
        {

            archivo >> placa;
            archivo >> tipoVehiculo;

            insertarVehiculo(fecha, placa, tipoVehiculo);
            archivo >> fecha;
        }
    }
    archivo.close();
}

//Carga los vehiculos que quedaron el dia anterior.
void iniciar()
{
    cout << "\n\nDe archivos a las listas\n";
    pasarArchivoLista();
    cout << "\nFin de archivos a las listas\n";
}

//Guarda los vehiculos localmente que quedan en el parqueadero al cerrar.
void descargar()
{
    cout << "\n\nDe listas a archivos\n";
    pasarListaArchivo();
    cout << "\nFin de listas a archivos\n";
}

//limpia la memoria RAM luego del cierre del programa
void vaciar() ////////////////////
{
    Celda *aux1 = inicio;
    if (inicio == NULL)
    {
        cout << "lista vacia\n";
    }
    else
    {
        Celda *aux = aux1;
            aux1 = aux1->siguiente;
            delete aux;
        while (aux1 != inicio)
        {
            Celda *aux = aux1;
            aux1 = aux1->siguiente;
            delete aux;
        }
        cout << "\nLa lista se vacio exitosamente\n";
    }
}