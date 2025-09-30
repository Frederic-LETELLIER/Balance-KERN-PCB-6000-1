#include "threadtpg300.h"

#include "tpg300.h"

void RenderThread::run()
{
  etat = 0;

  // on lance une boucle infinie
  while(1)
  {

    if(etat == 0)
    {
      QEventLoop evtLoop;
      QTimer::singleShot(100, &evtLoop, SLOT(quit())); // 100 ms d'attente
      evtLoop.exec();

      if(pt->ui.centralwidget->isVisible() == false) // on regarde si la fenetre principale est visible
      {
          qDebug("<debug> (RenderThread) Erreur, fenetre principale non visible");
          QApplication::quit();
      }
    }


    else if(etat == 1)
    {
      QThread::msleep(pt->fenetre_parametres.communique_delai());   // delai d'attente en ms
      event1 = new QEvent((QEvent::Type)(1)); // Faire la mesure
      QCoreApplication::postEvent(this,event1);      
    }

  } // fin du while(1)

}


///////////////////////////////////////////
// se declenche quand des evenements sont recus
bool RenderThread::event(QEvent *evenement)
{
  if( evenement->type() == (QEvent::Type)(1))
    pt->mesure(); // Lance la mesure

  return true;
}
