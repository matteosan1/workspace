//
// C++ Implementation: imageitem
//
// Description: 
//
//
// Author: Matteo Sani <matteo.sani@cern.ch>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "imageitem.h"

ImageItem::ImageItem(QPixmap p, QCanvas *c)
 : QCanvasRectangle(c), pixmap(p) {
    setSize(pixmap.width(), pixmap.height());
}

ImageItem::~ImageItem()
{}

void ImageItem::drawShape(QPainter &p) {
    p.drawPixmap(int(x()), int(y()), pixmap);
}

