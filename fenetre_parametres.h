#ifndef PARAMETRES_H
#define PARAMETRES_H

#include "ui_fenetre_parametres.h"
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QSerialPort> // RS232

class PARAMETRES : public QDialog
{
    Q_OBJECT

public:
    PARAMETRES(QWidget *parent = 0);

    Ui::PARAMETRES ui; // interface graphique
  
    void sauver(void); // sauvegarder les resultats sur le disque dur
    void charger(void); // charger les resultats se trouvant sur le disque dur
    int communique_delai(void); // delai d'attente entre 2 mesures

private slots:
    void on_pushButton_clicked();  // sauver et fermer

  
};

#endif
