#ifndef TPG300_H
#define TPG300_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QSerialPort> // RS232
#include <QEventLoop> // pauses

#include "ui_tpg300.h" // interface graphique
#include "fenetre_rs232.h" // fenetre de configuration RS232
#include "fenetre_parametres.h" // fenetre de configuration de la mesure
#include "threadtpg300.h" // gestion du thread pour les mesures

class TPG300 : public QMainWindow
{
  Q_OBJECT

// variables et fonctions
public:
  TPG300(QWidget *parent = 0); // constructeur

  Ui::TPG300 ui; // interface graphique principale
  RS232 fenetre_rs232; // fenetre pour configurer la connexion RS232
  PARAMETRES fenetre_parametres; // fenetre pour configurer la mesure

  QSerialPort *port; // sert a communiquer par le port serie

  RenderThread thread; // le thread qui lit les donnees de mesure

  QString poids_precedent;


  void affichage_moniteur(QString la_commande); // permet d'afficher sur le moniteur

  // envoi et reception
  QString receive_rs232(void); // recevoir une ligne de l'appareil
  void mesure(void); // On realise une mesure des pressions

  // les fonctions de dialogue
  QString commande_lecture(void); // ARDUINO RS232


  QString nom_file; // nom du fichier de stockage des donnees
  QDateTime date_init; // heure de debut


// les elements du UI
public slots:
  void on_pushButton_1_1_clicked();  // configuration RS232
  void on_pushButton_1_2_clicked();  // configuration Parametres
  void on_pushButton_1_3_clicked();  // connexion a l'appareil

};

#endif
