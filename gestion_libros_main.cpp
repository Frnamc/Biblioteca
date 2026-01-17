#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDate>
#include <QPushButton>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStyleSheet(
        "QMainWindow { background-color: #f3e5d8; }"
        "QPushButton { background-color: #6f4e37; color:white; padding:10px; border-radius:8px; font-weight: bold; }"
        "QPushButton:hover { background-color: #8b5e3c; }"
        );

    cargarLibrosIniciales();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarLibrosIniciales()
{
    ifstream archivo("libros.txt");
    if (archivo.good() && archivo.peek() != ifstream::traits_type::eof()) return;

    ofstream out("libros.txt");
    out << "001|Cien Años de Soledad|Gabriel Garcia Marquez|Realismo Mágico|Disponible|1967\n";
    out << "002|Pedro Páramo|Juan Rulfo|Novela|Prestado|1955\n";
    out << "003|Don Quijote|Miguel de Cervantes|Novela|Disponible|1605\n";
}

int MainWindow::generarNuevoID()
{
    ifstream archivo("libros.txt");
    int ultimoId = 0;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        ss >> ultimoId;
    }
    return ultimoId + 1;
}

void MainWindow::on_btnAgregar_clicked()
{
    bool ok;
    int anioActual = QDate::currentDate().year();

    QInputDialog d1(this);
    d1.setWindowTitle("Agregar"); d1.setLabelText("Título:");
    d1.setOkButtonText("Aceptar"); d1.setCancelButtonText("Cancelar");
    if(!d1.exec()) return;
    QString titulo = d1.textValue();
    if(titulo.isEmpty()) return;

    QInputDialog d2(this);
    d2.setWindowTitle("Agregar"); d2.setLabelText("Autor:");
    d2.setOkButtonText("Aceptar"); d2.setCancelButtonText("Cancelar");
    if(!d2.exec()) return;
    QString autor = d2.textValue();
    if(autor.isEmpty()) return;

    QInputDialog d3(this);
    d3.setWindowTitle("Agregar"); d3.setLabelText("Género:");
    d3.setOkButtonText("Aceptar"); d3.setCancelButtonText("Cancelar");
    if(!d3.exec()) return;
    QString genero = d3.textValue();
    if(genero.isEmpty()) return;

    QInputDialog d4(this);
    d4.setWindowTitle("Agregar"); d4.setLabelText("Estado:");
    d4.setComboBoxItems({"Disponible", "Prestado"});
    d4.setOkButtonText("Aceptar"); d4.setCancelButtonText("Cancelar");
    if(!d4.exec()) return;
    QString estado = d4.textValue();

    int anio = 0;
    do {
        anio = QInputDialog::getInt(this, "Agregar", "Año (1000 - " + QString::number(anioActual) + "):", anioActual, 1, 2026, 1, &ok);
        if(!ok) return;
        if(anio < 1000 || anio > anioActual) QMessageBox::warning(this, "Error", "Ese año no existe.");
    } while (anio < 1000 || anio > anioActual);

    ofstream out("libros.txt", ios::app);
    out << setfill('0') << setw(3) << generarNuevoID() << "|"
        << titulo.toStdString() << "|"
        << autor.toStdString() << "|"
        << genero.toStdString() << "|"
        << estado.toStdString() << "|"
        << anio << "\n";

    QMessageBox::information(this, "Éxito", "Libro agregado correctamente.");
}
