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

 #include "animateditem.h"

 #include <QtGui/qbitmap.h>
 #include <QtGui/qpainter.h>

 AnimatedPixmapItem::AnimatedPixmapItem(const QList<QPixmap> &animation,
                                        QGraphicsScene *scene)
     : QGraphicsItem(0, scene), currentFrame(0), vx(0), vy(0)
 {
     for (int i = 0; i < animation.size(); ++i) {
         QPixmap pixmap = animation.at(i);
         Frame frame;
         frame.pixmap = pixmap;
         QPainterPath path;
         path.addRegion(pixmap.createHeuristicMask());
         frame.shape = path;
         frame.boundingRect = path.controlPointRect();
         frames << frame;
     }
 }

 void AnimatedPixmapItem::setFrame(int frame)
 {
     if (!frames.isEmpty()) {
         prepareGeometryChange();
         currentFrame = frame % frames.size();
     }
 }

 void AnimatedPixmapItem::advance(int phase)
 {
     if (phase == 1 && !frames.isEmpty()) {
         setFrame(currentFrame + 1);
         if (vx || vy)
             moveBy(vx, vy);
     }
 }

 QRectF AnimatedPixmapItem::boundingRect() const
 {
     return frames.at(currentFrame).boundingRect;
 }

 QPainterPath AnimatedPixmapItem::shape() const
 {
     return frames.at(currentFrame).shape;
 }

 void AnimatedPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                QWidget *widget)
 {
     painter->drawPixmap(0, 0, frames.at(currentFrame).pixmap);
 }