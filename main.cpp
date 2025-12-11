#include <iostream>
#include <vector>
#include <cstdlib> 
#include "GestorUsuarios.h"

using namespace std;

int main() {
    vector<Usuario> usuarios;
    string archivo = "usuarios.txt";

    cargarUsuarios(usuarios, archivo);

    int opcion;

    do {
        system("cls"); 
        cout << "=== GESTION DE USUARIOS ===" << endl;
        cout << "1. Registrar usuario nuevo" << endl;
        cout << "2. Iniciar Sesion (Login)" << endl;
        cout << "3. Salir" << endl;
        cout << "===========================" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Usuario nuevo;
            cout << "\n[REGISTRO]" << endl;
            cout << "Ingrese Nombre: ";
            cin >> nuevo.nombre;
            cout << "Ingrese Contrasena: ";
            cin >> nuevo.contrasena;

            if(registrarUsuario(usuarios, nuevo, archivo)) {
                cout << "-> Usuario registrado y guardado en " << archivo << " exitosamente.\n";
            } else {
                cout << "-> Error al guardar en el archivo.\n";
            }

        } else if (opcion == 2) {
            string nombre, pass;
            cout << "\n[LOGIN]" << endl;
            cout << "Usuario: ";
            cin >> nombre;
            cout << "Contrasena: ";
            cin >> pass;

            if (validarLogin(usuarios, nombre, pass)) {
                cout << "-> Bienvenido al sistema, " << nombre << "!\n";
            } else {
                cout << "-> Error: Usuario o contrasena incorrectos.\n";
            }

        } else if (opcion == 3) {
            cout << "Saliendo del programa...\n";
        } else {
            cout << "Opcion invalida.\n";
        }

        if (opcion != 3) {
            cout << "\n";
            system("pause"); 
        }

    } while (opcion != 3); 

    return 0;
}
