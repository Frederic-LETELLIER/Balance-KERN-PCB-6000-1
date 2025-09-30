#ifndef RS232_H
#define RS232_H

#include "ui_fenetre_rs232.h"
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QSerialPort> // RS232

class RS232 : public QDialog
{
    Q_OBJECT

public:
    RS232(QWidget *parent = 0);

    Ui::RS232 ui; // interface graphique
  
    void sauver(void); // sauvegarder les resultats sur le disque dur
    void charger(void); // charger les resultats se trouvant sur le disque dur

    int connexion(QSerialPort *port); // permet de se connecter a l'appareil

    QString adresse(void); // permet d'avoir l'adresse du boitier
    QSerialPort *port_local; // port qui sert pour les echanges RS232

private slots:
    void on_pushButton_rs232_clicked();  // sauver et fermer
  
};

#endif

