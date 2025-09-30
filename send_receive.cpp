
/////////////////////////////////////////////
// Recevoir de l'appareil
QString TPG300::receive_rs232(void)
{

  QString valeur_retour = "";
  if(port == NULL)
  {
        valeur_retour = "Erreur - port NULL";
        return valeur_retour;
  }

  // on regarde s'il y a 18 octets a recuperer
  // Si ce n'est pas le cas, on quitte
  //qDebug("<debug> (receive_rs232) nb  caracteres recus disponibles : %d", port->bytesAvailable());
  if( port->bytesAvailable() <= 17)
      return "";

  // lecture d'une ligne
  char tableau[260];
  int i = port->readLine ( tableau, 200);
  qDebug("<debug> (receive_rs232) nb  caracteres recus : %d", i);
  if( i > 0) // c'est bon
    tableau[i] = '\0'; // on ferme le texte
  else // pas bon
    return "";
  

  //qDebug("<debug> (receive_rs232) valeur caractere 0 : %d", tableau[0]);
  //qDebug("<debug> (receive_rs232) valeur caractere 1 : %d", tableau[1]);
  //qDebug("<debug> (receive_rs232) valeur caractere 2 : %d", tableau[2]);
  //qDebug("<debug> (receive_rs232) valeur caractere 3 : %d", tableau[3]);
  //qDebug("<debug> (receive_rs232) valeur caractere 4 : %d", tableau[4]);
  //qDebug("<debug> (receive_rs232) valeur caractere 5 : %d", tableau[5]);
  //qDebug("<debug> (receive_rs232) valeur caractere 6 : %d", tableau[6]);


  QString la_commande = tableau;
  qDebug() << "<debug> (receive_rs232) caracteres recus : " << la_commande;

  return la_commande;
}
