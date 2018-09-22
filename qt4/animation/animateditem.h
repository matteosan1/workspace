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

 #ifndef ANIMATEDPIXMAPITEM_H
 #define ANIMATEDPIXMAPITEM_H

 #include <QGraphicsItem>

 class AnimatedPixmapItem : public QGraphicsItem
 {
 public:
     AnimatedPixmapItem(const QList<QPixmap> &animation, QGraphicsScene *scene = 0);

     void setFrame(int frame);
     inline int frame() const
     { return currentFrame; }
     inline int frameCount() const
     { return frames.size(); }
     inline QPixmap image(int frame) const
     { return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap; }
     inline void setVelocity(qreal xvel, qreal yvel)
     { vx = xvel; vy = yvel; }
     inline qreal xVelocity() const
     { return vx; }
     inline qreal yVelocity() const
     { return vy; }

     QRectF boundingRect() const;
     QPainterPath shape() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

     void advance(int phase);

 private:
     struct Frame {
         QPixmap pixmap;
         QPainterPath shape;
         QRectF boundingRect;
     };

     int currentFrame;
     QList<Frame> frames;
     qreal vx, vy;
 };

 #endif
