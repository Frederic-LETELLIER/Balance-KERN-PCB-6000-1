#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QThread>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QSerialPort> // RS232

class TPG300;

class RenderThread : public QThread
{
    Q_OBJECT

public:
  void run();

  TPG300 *pt; // pointeur vers TPG300
  int etat;

  // les evenements servent pour l'affichage a l'ecran
  virtual bool event(QEvent *evenement);
  QEvent *event1; // faire une mesure

};

#endif


