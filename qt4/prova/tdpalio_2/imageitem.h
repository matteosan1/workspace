//
// C++ Interface: imageitem
//
// Description: 
//
//
// Author: Matteo Sani <matteo.sani@cern.ch>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <qcanvas.h>
#include <qpixmap.h>
#include <qpainter.h>

/**
	@author Matteo Sani <matteo.sani@cern.ch>
*/
class ImageItem : public QCanvasRectangle {
public:
    ImageItem(QPixmap, QCanvas*);
    ~ImageItem();
    int rtti() const { return 1974; }
protected:
    void drawShape(QPainter &);

private:
    QPixmap pixmap;

};

#endif
