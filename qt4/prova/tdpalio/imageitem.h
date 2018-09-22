/*
#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QCanvas>
#include <QPixmap>
#include <QPainter>

class ImageItem : public Q3CanvasRectangle {
public:
    ImageItem(QPixmap, Q3Canvas*);
    ~ImageItem();
    int rtti() const { return 1974; }

protected:
    void drawShape(QPainter &);

private:
    QPixmap pixmap;

};

#endif
*/