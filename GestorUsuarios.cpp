#include "GestorUsuarios.h"
#include <fstream>
#include <iostream>

using namespace std;

bool cargarUsuarios(vector<Usuario> &lista, const string &rutaArchivo) {
    
    ifstream archivo(rutaArchivo.c_str());

    if (!archivo.is_open())
        return false; 

    lista.clear();
    Usuario temp;

    while (archivo >> temp.nombre >> temp.contrasena) {
        lista.push_back(temp);
    }

    archivo.close();
    return true;
}

bool guardarUsuarios(const vector<Usuario> &lista, const string &rutaArchivo) {
    
    ofstream archivo(rutaArchivo.c_str());

    if (!archivo.is_open())
        return false;

    
    for (size_t i = 0; i < lista.size(); i++) {
        archivo << lista[i].nombre << " " << lista[i].contrasena << endl;
    }

    archivo.close();
    return true;
}

bool registrarUsuario(vector<Usuario> &lista, const Usuario &u, const string &rutaArchivo) {
    lista.push_back(u); // Agrega a la memoria
    return guardarUsuarios(lista, rutaArchivo); // Guarda inmediatamente en el TXT
}

bool validarLogin(const vector<Usuario> &lista, const string &nombre, const string &pass) {
    for (size_t i = 0; i < lista.size(); i++) {
        if (lista[i].nombre == nombre && lista[i].contrasena == pass) {
            return true;
        }
    }
    return false;
}
