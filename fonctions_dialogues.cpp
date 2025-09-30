

/////////////////////////////////////////////
// ARDUINO : lecture RS232
QString TPG300::commande_lecture(void)
{
  QString valeur_retour = "OK"; // par defaut, on met a OK
  if(port == NULL) // Il y a un probleme
  {
      valeur_retour = "Erreur - port NULL";
      return valeur_retour;
  }
  valeur_retour = receive_rs232();


  // on sort si rien n'a ete recu
  if (valeur_retour.length() != 18)
  {
      return "";
  }

/*
  char CR[2];
  CR[0] = '\x0D';  // CR
  CR[1] = '\0';  // fermeture
  QString string_cr = CR;
  char LF[2];
  LF[0] = '\x0A';  // LF
  LF[1] = '\0';   // fermeture de phrase
  QString string_lf = LF;
*/

  // On regarde si la mesure est differente de ce qui avait ete recu precedemment
  if (valeur_retour == poids_precedent)
  {
        return "";
  }
  else
  {
      poids_precedent = valeur_retour;
  }


  // Je supprimer les espaces
  valeur_retour.replace(QRegularExpression("\x20"), "");

  // Je remplace g par une tabulation + g
  valeur_retour.replace(QRegularExpression("g"), "Yg");
  valeur_retour.replace(QRegularExpression("Y"), "\x09");

  // je veux supprimer le CRCRLF dans mes phrases
  // on remplace d'abord par Z
  valeur_retour.replace(QRegularExpression("\x0D"), "X");
  valeur_retour.replace(QRegularExpression("\x0A"), "Z");
  valeur_retour.replace(QRegularExpression("X"), "");
  valeur_retour.replace(QRegularExpression("Z"), "\n");

  // On ajoute la date et l'heure au debut
  QDateTime date = QDateTime::currentDateTime();
  QString jour = date.toString("dd/MM/yyyy");
//  QString heure = date.toString("HH:mm:ss");
  QString heure = date.toString("HH:mm:ss.zzz");

  valeur_retour = jour + "\x09" + heure + "\x09" + valeur_retour;


  return valeur_retour;
}




