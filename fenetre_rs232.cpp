#include "fenetre_rs232.h"


///////////////////////////////////////////
// Creation de l'objet
RS232::RS232(QWidget *parent) : QDialog(parent)
{
        ui.setupUi(this);

  // on charge les donnees sur le disque dur
  charger();
}



///////////////////////////////////////////
// Fermer la fenetre et enregistrer
void RS232::on_pushButton_rs232_clicked()
{
  // on ferme la fenetre
  this->hide();

  // on sauve les resultats sur le disque dur
  sauver();

} 



///////////////////////////////////////////
// Sauver les donnees sur le disque dur
void RS232::sauver(void)
{

    if(QDir("config").exists() == false)
    {
        QDir().mkdir("config");
    }


    // recuperation des donnees
  QString value1 = ui.lineEdit->text(); 


  QFile file;
  file.setFileName("config/config_rs232.ini");
  if( file.exists() )
    file.remove();
  file.open(QIODevice::Append | QIODevice::Text );
  QTextStream out(&file);
  out << value1;    
  file.close();

} 


///////////////////////////////////////////
// Charger les donnees sur le disque dur
void RS232::charger(void)
{
  QFile file;
  file.setFileName("config/config_rs232.ini");
  if( !file.exists() )
    return;      

  // creation des variables
  QString value1 = "COM1"; 

  file.open(QIODevice::ReadOnly | QIODevice::Text );
  QTextStream in(&file);
  QString line;
  line = in.readLine(); 
  value1 = line;
  file.close();

  ui.lineEdit->setText(value1); 

} 


///////////////////////////////////////////
// Connexion a l'appareil
int RS232::connexion(QSerialPort *port)
{
  int retour = 0;

  // recuperation des donnees du port RS232
  QString nomport = ui.lineEdit->text();

  // si la connexion existe deja, on la ferme
  if(port != NULL)
  {
	   port->close(); // on ferme le port
       delete port;
       port = NULL;
  }

  // connexion
  if(port == NULL)
  {
       port = new QSerialPort(nomport);
  }

  // ouverture du port
  port->open(QIODevice::ReadWrite); // on ouvre le port

  // on regarde si le port est bien ouvert
  if(port->isOpen() != 1)
  {
	port->close();
    delete port;
    port = NULL;

    retour = -1;
    return retour;
  }
  else // le port est bien ouvert
  {
    // on remet tous les parametres pour etre sur qu'ils ont bien ete pris en compte
       port->setBaudRate(QSerialPort::Baud9600); //Vitesse de transfert = 9600 bauds

       port->setFlowControl(QSerialPort::NoFlowControl); // pas de control du flux

       port->setParity(QSerialPort::NoParity);  // contrôle de parité = aucune // pas de parite

       port->setDataBits(QSerialPort::Data8); // longueur des données = 8 bits

       port->setStopBits(QSerialPort::OneStop); // Stop bits = 1 bit

       port_local = port; // on fait une copie de l'adresse du pointeur

  }


  return retour;
} 



///////////////////////////////////////////
// Donne l'adresse du boitier
QString RS232::adresse(void)
{
  QFile file;
  file.setFileName("config/config_rs232.ini");
  if( !file.exists() )
    return "COM1";

  // creation des variables
  QString value1 = "COM1";

  file.open(QIODevice::ReadOnly | QIODevice::Text );
  QTextStream in(&file);
  QString line;
  line = in.readLine();
  value1 = line;
  file.close();

  return value1;

}
