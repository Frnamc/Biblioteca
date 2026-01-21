#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDate>
#include <QPushButton>
#include <fstream>
#include <sstream>
#include <iomanip>

void MainWindow::on_btnMostrar_clicked()
{
    ifstream archivo("libros.txt");
    string linea;
    QString lista;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string id, tit, aut, gen, est, anio;

        getline(ss, id, '|');
        getline(ss, tit, '|');
        getline(ss, aut, '|');
        getline(ss, gen, '|');
        getline(ss, est, '|');
        getline(ss, anio, '|');

        lista += "ID: " + QString::fromStdString(id) + " [" + QString::fromStdString(est) + "]\n";
        lista += "Libro: " + QString::fromStdString(tit) + "\n";
        lista += "Autor: " + QString::fromStdString(aut) + "\n";
        lista += "Género: " + QString::fromStdString(gen) + " (" + QString::fromStdString(anio) + ")\n";
        lista += "------------------------------------------\n";
    }
    archivo.close();

    if(lista.isEmpty()) lista = "No hay libros.";
    QMessageBox::information(this, "Lista de Libros", lista);
}

void MainWindow::on_btnModificar_clicked()
{
    bool ok;
    int anioActual = QDate::currentDate().year();
    int idBusca = QInputDialog::getInt(this, "Modificar", "ID del libro:", 1, 1, 999, 1, &ok);
    if (!ok) return;

    ifstream archivo("libros.txt");
    string linea;
    string contenido = "";
    bool hallado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string sid, stit, saut, sgen, sest, sAn;

        getline(ss, sid, '|');
        getline(ss, stit, '|');
        getline(ss, saut, '|');
        getline(ss, sgen, '|');
        getline(ss, sest, '|');
        getline(ss, sAn, '|');

        if (sid.empty()) continue;
        int idAct = stoi(sid);

        if (idAct == idBusca) {
            hallado = true;

            QMessageBox msg;
            msg.setWindowTitle("Modificar");
            msg.setText("¿Qué desea modificar de: " + QString::fromStdString(stit) + "?");
            QPushButton *btnTodo = msg.addButton("Todo", QMessageBox::ActionRole);
            QPushButton *btnEstado = msg.addButton("Solo Estado", QMessageBox::ActionRole);
            QPushButton *btnCance = msg.addButton("Cancelar", QMessageBox::RejectRole);
            msg.exec();

            string nT = stit, nA = saut, nG = sgen, nE = sest, nAn = sAn;

            if (msg.clickedButton() == btnCance) {
                archivo.close();
                return;
            }

            if (msg.clickedButton() == btnTodo) {
                QInputDialog d1(this);
                d1.setWindowTitle("Modificar"); d1.setLabelText("Nuevo Título:"); d1.setTextValue(QString::fromStdString(stit));
                d1.setOkButtonText("Aceptar"); d1.setCancelButtonText("Cancelar");
                if(!d1.exec()) return;
                nT = d1.textValue().toStdString();

                QInputDialog d2(this);
                d2.setWindowTitle("Modificar"); d2.setLabelText("Nuevo Autor:"); d2.setTextValue(QString::fromStdString(saut));
                d2.setOkButtonText("Aceptar"); d2.setCancelButtonText("Cancelar");
                if(!d2.exec()) return;
                nA = d2.textValue().toStdString();

                QInputDialog d3(this);
                d3.setWindowTitle("Modificar"); d3.setLabelText("Nuevo Género:"); d3.setTextValue(QString::fromStdString(sgen));
                d3.setOkButtonText("Aceptar"); d3.setCancelButtonText("Cancelar");
                if(!d3.exec()) return;
                nG = d3.textValue().toStdString();

                QInputDialog d4(this);
                d4.setWindowTitle("Modificar"); d4.setLabelText("Estado:");
                d4.setComboBoxItems({"Disponible", "Prestado"});
                d4.setOkButtonText("Aceptar"); d4.setCancelButtonText("Cancelar");
                if(!d4.exec()) return;
                nE = d4.textValue().toStdString();

                int anTemp = 0;
                do {
                    anTemp = QInputDialog::getInt(this, "Modificar", "Nuevo Año:", stoi(sAn), 1000, anioActual, 1, &ok);
                    if(!ok) return;
                } while (anTemp < 1000 || anTemp > anioActual);
                nAn = to_string(anTemp);

            } else if (msg.clickedButton() == btnEstado) {
                QInputDialog d4(this);
                d4.setWindowTitle("Modificar"); d4.setLabelText("Cambiar Estado:");
                d4.setComboBoxItems({"Disponible", "Prestado"});
                d4.setOkButtonText("Aceptar"); d4.setCancelButtonText("Cancelar");
                if(!d4.exec()) return;
                nE = d4.textValue().toStdString();
            }

            stringstream mod;
            mod << setfill('0') << setw(3) << idAct << "|"
                << nT << "|" << nA << "|" << nG << "|" << nE << "|" << nAn;
            contenido += mod.str() + "\n";

        } else {
            contenido += linea + "\n";
        }
    }
    archivo.close();

    if (hallado) {
        ofstream out("libros.txt");
        out << contenido;
        QMessageBox::information(this, "Éxito", "Cambios guardados.");
    } else {
        QMessageBox::warning(this, "Error", "ID no encontrado.");
    }
}
