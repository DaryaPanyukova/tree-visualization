#ifndef NODE_H
#define NODE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QVector>

QVector <int> deleteAVL;
QVector <int> deleteRB;
QVector <int> deleteTreap;
QVector <int> deleteSplay;

class Node : public QGraphicsItem {
public:
    int x, y, diameter, key;
    QPen pen;
    QBrush brush;
    bool Pressed;
    QString type;

    Node(int x0, int y0, int d, QPen p, QBrush b, int k, QString &t)
    {
        Pressed = false;
        x = x0;
        y = y0;
        diameter = d;
        brush = b;
        pen = p;
        key = k;
        type = t;
    }

    QRectF boundingRect() const
    {
        return QRectF(x, y, diameter, diameter);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget)
    {
        QRectF rec = boundingRect();
        if (Pressed) {
            QColor blue(102, 0, 51);
            QPen pen_pressed(blue, 3);
            QBrush brush_pressed(blue);
            painter->setPen(pen_pressed);
            painter->setBrush(brush_pressed);
            painter->drawEllipse(rec);
        }
        else {
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawEllipse(rec);
        }
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        if (Pressed) {
            Pressed = false;
            QString type = this->type;
            int k = this->key;
            if (type == "AVL") {
                deleteAVL.erase(std::remove(deleteAVL.begin(), deleteAVL.end(), k), deleteAVL.end());
            } else if (type == "RB") {
                deleteRB.erase(std::remove(deleteRB.begin(), deleteRB.end(), k), deleteRB.end());
            } else if (type == "Treap") {
                deleteTreap.erase(std::remove(deleteTreap.begin(), deleteTreap.end(), k), deleteTreap.end());
            } else if (type == "Splay") {
                deleteSplay.erase(std::remove(deleteSplay.begin(), deleteSplay.end(), k), deleteSplay.end());
            }
        }
        else {
            QString type = this->type;
            int k = this->key;
            Pressed = true;
            if (type == "AVL") {
                deleteAVL.push_back(k);
            } else if (type == "RB") {
                deleteRB.push_back(k);
            } else if (type == "Treap") {
                deleteTreap.push_back(k);
            } else if (type == "Splay") {
                deleteSplay.push_back(k);
            }
         }


        update();
        QGraphicsItem::mousePressEvent(event);

    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        Pressed = false;
        update();
        QGraphicsItem::mouseReleaseEvent(event);


    }

};


#endif // NODE_H
