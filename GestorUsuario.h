#ifndef GESTOR_USUARIOS_H
#define GESTOR_USUARIOS_H

#include "Usuario.h"
#include <vector>
#include <string>

bool cargarUsuarios(vector<Usuario> &lista, const string &rutaArchivo);
bool guardarUsuarios(const vector<Usuario> &lista, const string &rutaArchivo);

bool registrarUsuario(vector<Usuario> &lista, const Usuario &u, const string &rutaArchivo);
bool validarLogin(const vector<Usuario> &lista, const string &nombre, const string &pass);

#endif

