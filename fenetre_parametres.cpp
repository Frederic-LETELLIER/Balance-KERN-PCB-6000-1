#include "fenetre_parametres.h"


///////////////////////////////////////////
// Creation de l'objet
PARAMETRES::PARAMETRES(QWidget *parent) : QDialog(parent)
{
        ui.setupUi(this);

  // on charge les donnees sur le disque dur
  charger();
}



///////////////////////////////////////////
// Fermer la fenetre et enregistrer
void PARAMETRES::on_pushButton_clicked()
{
  // on ferme la fenetre
  this->hide();

  // on sauve les resultats sur le disque dur
  sauver();

} 



///////////////////////////////////////////
// Sauver les donnees sur le disque dur
void PARAMETRES::sauver(void)
{


    if(QDir("config").exists() == false)
    {
        QDir().mkdir("config");
    }


    // recuperation des donnees
  QString value1 = ui.lineEdit->text(); 

  QFile file;
  file.setFileName("config/config_parametres.ini");
  if( file.exists() )
    file.remove();
  file.open(QIODevice::Append | QIODevice::Text );
  QTextStream out(&file);
  out << value1;    
  file.close();

} 


///////////////////////////////////////////
// Charger les donnees sur le disque dur
void PARAMETRES::charger(void)
{
  QFile file;
  file.setFileName("config/config_parametres.ini");
  if( !file.exists() )
    return;      

  // creation des variables
  int value1 = 100; // 100 ms - valeur par defaut

  file.open(QIODevice::ReadOnly | QIODevice::Text );
  QTextStream in(&file);
  QString line;
  line = in.readLine(); 
  value1 = line.toInt();
  file.close();

  ui.lineEdit->setText(QString::number(value1)); 
} 


///////////////////////////////////////////
// Donne le temps d'attente entre 2 mesures
int PARAMETRES::communique_delai(void)
{
  QString value1 = ui.lineEdit->text();
  int valeur = value1.toInt();

  if(valeur >= 1) // on impose au moins 1 ms de delai
    return valeur;
  else
    return 1; // 1 seconde

}


