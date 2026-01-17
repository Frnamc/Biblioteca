#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    setStyleSheet(
        "QDialog { background-color: #f3e5d8; }"
        "QPushButton { background-color: #6f4e37; color: white; padding: 8px; border-radius: 6px; }"
        "QLineEdit { padding: 6px; }"
        "background-color: #a04040; color: white; border-radius: 8px; font-weight: bold;"
        );
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnLogin_clicked()
{
    if (ui->txtUsuario->text() == "admin" &&
        ui->txtPassword->text() == "1234") {

        MainWindow *w = new MainWindow;
        w->show();
        close();
    } else {
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos");
    }
}
void LoginWindow::on_btnSalirLogin_clicked() {
    QMessageBox::StandardButton res = QMessageBox::question(this, "Salir",
                                                            "¿Deseas cerrar la aplicación?", QMessageBox::Yes | QMessageBox::No);

    if (res == QMessageBox::Yes) {
        qApp->quit();
    }
}
