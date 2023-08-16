#include <iostream>
#include <sstream>
#include <fstream>
#define NOMBRE_ARCHIVO "data.csv"
using namespace std;

const int MAX_PERSONAS = 10;  // Número máximo de personas en el array
struct Persona {
    double cbu;
    string nombre;
    string apellido;
    string dni;
    double fondos;
    double pin;
};

//Funciones
int leerCSV(Persona personas[], const string& archivo);
double verificarUsuario(Persona personas[],double cbu, int maxPersonas, int& encontrado);
bool compararPin(double pin, double pinIngresado);
void guardarCSV(const Persona personas[], int numPersonas, const string& archivo);
void retirarDinero(Persona personas[], int encontrado);
void depositarDinero(Persona personas[], int encontrado);
void transferirDinero(Persona personas[], int encontrado, int maxPersonas);

int main() {
    string archivoCSV = "data.csv";
    Persona personas[MAX_PERSONAS];
    int numPersonas = leerCSV(personas, archivoCSV);

    double usuarioCBU;
    double usuarioPIN;
    int intentos = 5;

    // Bienvenida al usuario
    cout << "Bienvenido al Cajero Grupo15" << endl;

    // Verificar el CBU y PIN
    do {
        int posicionUsuario = 0;
        // Solicitar el CBU y PIN al usuario
        cout << "Ingrese su CBU: ";
        cin >> usuarioCBU;

        cout << "Ingrese su PIN: ";
        cin >> usuarioPIN;
        cout << endl;

        double pinCorrecto = verificarUsuario(personas, usuarioCBU, numPersonas, posicionUsuario);

        if (compararPin(pinCorrecto, usuarioPIN)) {
            // Acceso exitoso, mostrar el menú
            int opcion;
            while (true) {
                cout << "\n--- Menú ---" << endl;
                cout << "1. Ver balance" << endl;
                cout << "2. Retirar dinero" << endl;
                cout << "3. Depositar dinero" << endl;
                cout << "4. Transferir dinero" << endl;
                cout << "5. Salir" << endl;

                cout << "Ingrese el número de opción: ";
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        // Lógica para mostrar el balance
                        cout << "Su balance es: " << personas[posicionUsuario - 1].fondos << endl;
                        break;
                    case 2:
                        // Lógica para retirar dinero
                        retirarDinero(personas, posicionUsuario);
                        guardarCSV(personas, numPersonas, archivoCSV);
                        break;
                    case 3:
                        // Lógica para depositar dinero
                        depositarDinero(personas, posicionUsuario);
                        guardarCSV(personas, numPersonas, archivoCSV);
                        break;
                    case 4:
                        // Lógica para transferir dinero
                        transferirDinero(personas, posicionUsuario, numPersonas);
                        guardarCSV(personas, numPersonas, archivoCSV);
                        break;
                    case 5:
                        // Salir del menú actual
                        break;
                    default:
                        cout << "Opción inválida. Por favor, ingrese un número válido del menú." << endl;
                        break;
                }

                // Salir del bucle si se seleccionó la opción 5
                if (opcion == 5) {
                    break;
                }
            }
        } else {
            intentos--;

            cout << "El CBU y/o PIN son incorrectos. Acceso denegado." << endl;
            cout << "Intentelo de nuevo, intentos restantes: " << intentos << endl;
        }
    } while (intentos > 0);

    cout << "Ha agotado el número de intentos permitidos. Hasta luego." << endl;

    return 0;
}

int leerCSV(Persona personas[], const string& archivo) {
    ifstream entrada(archivo);
    string linea;
    int contador = 0;

    // Saltar la primera línea (encabezados)
    getline(entrada, linea);

    while (getline(entrada, linea) && contador < MAX_PERSONAS) {
        stringstream stream(linea);
        string cbu, nombre, apellido, dni, fondos, pin;

        getline(stream, cbu, ',');
        personas[contador].cbu = stod(cbu);

        getline(stream, nombre, ',');
        personas[contador].nombre = nombre;

        getline(stream, apellido, ',');
        personas[contador].apellido = apellido;

        getline(stream, dni, ',');
        personas[contador].dni = dni;

        getline(stream, fondos, ',');
        personas[contador].fondos = stod(fondos);

        getline(stream, pin, ',');
        personas[contador].pin = stod(pin);

        contador++;
    }

    entrada.close();
    return contador;  // Devolver el número de personas leídas
}



double verificarUsuario(Persona personas[],double cbu, int maxPersonas, int& encontrado){
    bool bandera = false;
    while (!bandera && encontrado<maxPersonas){
        if (personas[encontrado].cbu == cbu)
        {
            bandera=true;
        }
        encontrado++;
    }
    return personas[encontrado-1].pin;
}

bool compararPin(double pin, double pinIngresado){
    bool coincide = false;
    if (pin==pinIngresado)
    {
        coincide = true;
    }
    return coincide;
}

void retirarDinero(Persona personas[], int encontrado){
    double retiro;
    cout<<"Ingrese la cantidad de dinero que desea retirar:";
    cin>>retiro;
    cout<<endl;
    if (personas[encontrado-1].fondos>=retiro)
    {
        personas[encontrado-1].fondos=personas[encontrado-1].fondos - retiro;
        cout<<"Retiro de dinero exitoso"<<endl;
    }else
    {
        cout<<"Ingrese un monto menor o igual al que tenga en su cuenta, sus fondos son de: "<<personas[encontrado-1].fondos <<endl;
    }
    
}

void depositarDinero(Persona personas[], int encontrado){
    double deposito;
    cout<<"Ingrese la cantidad de dinero que desea depositar:";
    cin>>deposito;
    personas[encontrado-1].fondos=personas[encontrado-1].fondos + deposito;
}

void transferirDinero(Persona personas[], int encontrado, int maxPersonas){
    double transferir;
    double cbuTrf;
    string siono;
    string siono2;
    
    do{
        siono2="no";
        cout<<"Ingrese el CBU de la cuenta a la que desea transferirle dinero:";
        cin>>cbuTrf;
        cout<<endl;
        cout<<"¿El CBU: "<<cbuTrf<<" es correcto? Ingrese 'si' o 'no'"<<endl;
        cin>>siono;
    
        if(siono != "si" && siono != "SI" && siono != "Si"){
            cout<<"¿Desea intentar nuevamente? Ingrese 'si' o 'no'"<<endl;
            cin>>siono2;
        }

    }while (siono2 != "no" && siono2 != "NO" && siono2 != "No");

    if (siono=="si" || siono=="SI" || siono=="Si")
    {
        int encontradoSecond=0;
        bool bandera = false;
        while (!bandera && encontradoSecond<maxPersonas){
            if (personas[encontradoSecond].cbu == cbuTrf)
            {
                bandera=true;
            }
            encontradoSecond++;
        }

        cout<<"Ingrese la cantidad de dinero que desea transferir:";
        cin>>transferir;
        if (bandera)
        {
            if (personas[encontrado-1].fondos>=transferir)
            {
                personas[encontradoSecond-1].fondos = personas[encontradoSecond-1].fondos+transferir;
                personas[encontrado-1].fondos = personas[encontrado-1].fondos-transferir;            
                cout<<"Transferencia de dinero exitosa!!"<<endl;
            }else
            {
                cout<<"Ingrese un monto menor o igual al que tenga en su cuenta. Sus fondos son de: "<<personas[encontrado-1].fondos <<endl;
            }

        }else
        {
            if (personas[encontrado-1].fondos>=transferir)
            {
                personas[encontrado-1].fondos = personas[encontrado-1].fondos-transferir;            
                cout<<"Transferencia de dinero exitosa"<<endl;
            }else
            {
                cout<<"Ingrese un monto menor o igual al que tenga en su cuenta. Sus fondos son de: "<<personas[encontrado-1].fondos <<endl;
            }
        }
    }
}

void guardarCSV(const Persona personas[], int numPersonas, const string& archivo) {
    ofstream salida(archivo);

    salida << "cbu,nombre,apellido,dni,fondos,pin" << endl;

    for (int i = 0; i < numPersonas; i++) {
        salida  << personas[i].cbu << ","
                << personas[i].nombre << ","
                << personas[i].apellido << ","
                << personas[i].dni << ","
                << personas[i].fondos << ","
                << personas[i].pin << endl;
    }

    salida.close();
}

