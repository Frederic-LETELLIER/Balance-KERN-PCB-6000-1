#include "tpg300.h"

#include "send_receive.cpp" // Fonctions pour envoyer et recevoir
#include "fonctions_dialogues.cpp" // Fonctions de dialogue avec le TPG300

TPG300::TPG300(QWidget *parent) : QMainWindow(parent)
{
  ui.setupUi(this); // chargement de l'interface graphique

  port = NULL; // initialisation du port serie

  poids_precedent = ""; // initialisation du poids

  if(QDir("data").exists() == false)
  {
      QDir().mkdir("data");
  }

  // creation du thread qui met a jour les valeurs
  thread.pt = this; // on donne le pointeur vers TPG300
  thread.start();

}


/////////////////////////////////////////////
// Configuration de la connexion RS232
/////////////////////////////////////////////
void TPG300::on_pushButton_1_1_clicked()
{
  // on affiche la fenetre
  fenetre_rs232.show();
}



/////////////////////////////////////////////
// Configuration des parametres
/////////////////////////////////////////////
void TPG300::on_pushButton_1_2_clicked()
{
    // on affiche la fenetre
    fenetre_parametres.show();
}

/////////////////////////////////////////////
// Connexion a l'appareil
/////////////////////////////////////////////
void TPG300::on_pushButton_1_3_clicked()
{
  // on efface le moniteur
  ui.textEdit_2_1->clear();

  // affiche sur le Moniteur que l'on a appuye sur le bouton connexion
  affichage_moniteur("Ouverture du port de communication");

  int erreur;
  // on configure le port de communication
  erreur = fenetre_rs232.connexion(port); // permet de se connecter a l'appareil

  if(erreur == -1)
  {
    affichage_moniteur("==> Erreur de connexion");
    thread.etat = 0;
    return;
  }
  else
  {
      port = fenetre_rs232.port_local;
  }

  QDateTime date = QDateTime::currentDateTime();
  date_init = date;

  ui.lineEdit_1_5->setText(date.toString( "dd/MM/yyyy - HH:mm:ss") ); // Date et heure de depart
  nom_file = "data/data_balanceKERN_" + date.toString( "yyyy-MM-dd_HH-mm-ss") + ".txt";
  ui.textEdit_1_1->insertPlainText( "./" + nom_file + "\n" ); // Nom du fichier d'enregistrement
  ui.textEdit_1_1->insertPlainText( "./data/data_balanceKERN_current.txt" ); // Nom du fichier d'enregistrement
  ui.lineEdit_1_7->setText( date.toString( "dd/MM/yyyy - HH:mm:ss") );

  // On complete le fichier de mesures
  QFile file;
  file.setFileName("data/data_balanceKERN_" + date.toString( "yyyy-MM-dd_HH-mm-ss") + ".txt");
  file.open(QIODevice::Append | QIODevice::Text );
  QTextStream out(&file);

  affichage_moniteur("Date et heure de depart ==> " + date.toString( "dd/MM/yyyy - HH:mm:ss") );
  //out << "Date et heure de depart : " << date.toString( "dd/MM/yyyy - HH:mm:ss") << Qt::endl;
  out << "Temps ecoule (s)" << "\x09" << "Date" << "\x09" << "Heure" << "\x09" << "Poids" << Qt::endl;
  //out << Qt::endl;
  //out << Qt::endl;

  int i=0;

  affichage_moniteur("");
  //out << Qt::endl;

  // on laise un delai de 1 s pour que l'appareil prenne en compte
  //QEventLoop evtLoop;
  //QTimer::singleShot(1000, &evtLoop, SLOT(quit())); // 1000 ms d'attente
  //evtLoop.exec();

  //QString get_pressa1 = commande_lecture();
  //ui.lineEdit_1_1->setText(get_pressa1 );
  // on remplace les espaces par des tabulations dans la ligne des pressions
  //get_pressa1 = get_pressa1.replace(" ", "\x09");

  //out << get_pressa1 << Qt::endl;
  
  file.close();


  thread.etat = 1; // demarrage des mesures du thread
}



/////////////////////////////////////////////
// Affichage sur le moniteur
void TPG300::affichage_moniteur(QString la_commande)
{
  ui.textEdit_2_1->insertPlainText( la_commande.toLatin1() + "\n" ); 
}


/////////////////////////////////////////////
// Mesure des pressions
/////////////////////////////////////////////
void TPG300::mesure(void)
{

  QDateTime date = QDateTime::currentDateTime();
  int temps_ecoule = date_init.secsTo(date);

  // on affiche l'heure
  ui.lineEdit_1_7->setText( date.toString( "dd/MM/yyyy - HH:mm:ss") );

  // on fait les mesures du flux helium
  QString get_pressa1 = commande_lecture();

  if(get_pressa1 != "")
  {
    // on affiche les resultats
    ui.lineEdit_1_1->setText(get_pressa1 );

    // on remplace les espaces par des tabulations dans la ligne des pressions
    get_pressa1 = get_pressa1.replace(" ", "\x09");


    // On complete le fichier de mesures
    QFile file;
    file.setFileName(nom_file);
    file.open(QIODevice::Append | QIODevice::Text );
    QTextStream out(&file);
    out << QString::number(temps_ecoule) << "\x09" << get_pressa1;
    //out << get_pressa1 << Qt::endl; // pas besoin de mettre le retour a la ligne
    file.close();
  }

  if(ui.centralwidget->isVisible() == false) // on regarde si la fenetre principale est visible
  {
      qDebug("<debug> (mesure) Erreur, fenetre principale non visible ==> on quitte le programme");
      QApplication::quit();
  }

}
