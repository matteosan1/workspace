/****************************************************************************
 **
 ** Copyright (C) 2006-2007 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License version 2.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of
 ** this file.  Please review the following information to ensure GNU
 ** General Public Licensing requirements will be met:
 ** http://trolltech.com/products/qt/licenses/licensing/opensource/
 **
 ** If you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
 ** or contact the sales department at sales@trolltech.com.
 **
 ** In addition, as a special exception, Trolltech gives you certain
 ** additional rights. These rights are described in the Trolltech GPL
 ** Exception version 1.0, which can be found at
 ** http://www.trolltech.com/products/qt/gplexception/ and in the file
 ** GPL_EXCEPTION.txt in this package.
 **
 ** In addition, as a special exception, Trolltech, as the sole copyright
 ** holder for Qt Designer, grants users of the Qt/Eclipse Integration
 ** plug-in the right for the Qt/Eclipse Integration to link to
 ** functionality provided by Qt Designer and its related libraries.
 **
 ** Trolltech reserves all rights not expressly granted herein.
 **
 ** Trolltech ASA (c) 2007
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

 /*
  * KAsteroids - Copyright (c) Martin R. Jones 1997
  *
  * Part of the KDE project
  */

 #ifndef __KAST_TOPLEVEL_H__
 #define __KAST_TOPLEVEL_H__

 #include <q3mainwindow.h>
 #include <q3dict.h>
 #include <qmap.h>
 //Added by qt3to4:
 #include <QShowEvent>
 #include <QHideEvent>
 #include <QKeyEvent>

 #include "view.h"

 class KALedMeter;
 class QLCDNumber;

 class KAstTopLevel : public Q3MainWindow
 {
     Q_OBJECT
 public:
     KAstTopLevel( QWidget *parent=0, const char *name=0 );
     virtual ~KAstTopLevel();

 private:
     void playSound( const char *snd );
     void readSoundMapping();
     void doStats();

 protected:
     virtual void showEvent( QShowEvent * );
     virtual void hideEvent( QHideEvent * );
     virtual void keyPressEvent( QKeyEvent *event );
     virtual void keyReleaseEvent( QKeyEvent *event );

 private slots:
     void slotNewGame();

     void slotShipKilled();
     void slotRockHit( int size );
     void slotRocksRemoved();

     void slotUpdateVitals();

 private:
     KAsteroidsView *view;
     QLCDNumber *scoreLCD;
     QLCDNumber *levelLCD;
     QLCDNumber *shipsLCD;

     QLCDNumber *teleportsLCD;
 //    QLCDNumber *bombsLCD;
     QLCDNumber *brakesLCD;
     QLCDNumber *shieldLCD;
     QLCDNumber *shootLCD;
     KALedMeter *powerMeter;

     bool   sound;
     Q3Dict<QString> soundDict;

     // waiting for user to press Enter to launch a ship
     bool waitShip;
     bool isPaused;

     int shipsRemain;
     int score;
     int level;
     bool showHiscores;

     enum Action { Launch, Thrust, RotateLeft, RotateRight, Shoot, Teleport,
                     Brake, Shield, Pause, NewGame  };

     QMap<int,Action> actions;
 };

 #endif
