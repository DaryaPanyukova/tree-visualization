#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QWheelEvent>
#include "AVL.cpp"
#include <cmath>
#include "RB.cpp"
#include "Treap.cpp"
#include "Zooming.cpp"
#include "Node.h"
#include "Splay_.cpp"
#include <algorithm>


double radius = 25;
double diameter = 2 * radius;

double dy = 100;
double dx = 50;

int Width = 100000;
int Height = 10000;

QBrush redBrush(Qt::red);
QBrush blackBrush(Qt::black);
QPen blackpen(Qt::black);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_AVL = new QGraphicsScene(this);
    scene_RB = new QGraphicsScene(this);
    scene_Treap = new QGraphicsScene(this);    
    scene_Splay= new QGraphicsScene(this);

    ui->graphicsView_AVL->setScene(scene_AVL);
    ui->graphicsView_RB->setScene(scene_RB);
    ui->graphicsView_Treap->setScene(scene_Treap);    
    ui->graphicsView_Splay->setScene(scene_Splay);

    Graphics_view_zoom* zoomAVL = new Graphics_view_zoom(ui->graphicsView_AVL);
    zoomAVL->set_modifiers(Qt::NoModifier);

    Graphics_view_zoom* zoomRB = new Graphics_view_zoom(ui->graphicsView_RB);
    zoomRB->set_modifiers(Qt::NoModifier);

    Graphics_view_zoom* zoomTreap = new Graphics_view_zoom(ui->graphicsView_Treap);
    zoomTreap->set_modifiers(Qt::NoModifier);


    Graphics_view_zoom* zoomSplay = new Graphics_view_zoom(ui->graphicsView_Splay);
    zoomSplay->set_modifiers(Qt::NoModifier);

    ui->graphicsView_AVL->setDragMode(QGraphicsView::ScrollHandDrag);    
    ui->graphicsView_RB->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView_Treap->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView_Splay->setDragMode(QGraphicsView::ScrollHandDrag);

}

MainWindow::~MainWindow()
{
    delete ui;
}

std::pair <int, int> DrawTree (QGraphicsScene* &scene, node_AVL* ptr, double y, int x_circle) {
    if (ptr == nullptr) return std::make_pair(-1, -1);

    std::pair <int,int> left = DrawTree(scene, ptr->left, y + dy, x_circle);

    QString type = "AVL";
    int x = left.second + dx;
    if (left.second == -1) x = x_circle;
    Node *my_node = new Node(x, y, diameter, blackpen, blackBrush, ptr->data, type);
    scene->addItem(my_node);

    QString text = QString::number(ptr->data);

    int size = 14;
    if (text.size() >= 4)
        size = 14 - 1.7* (text.size() - 2);
    if (text.size() == 7)
        size = 6;
    if (text.size() >= 8)
        size = 5;
    QFont Font("Franklin Gothic Medium", size);

    QGraphicsTextItem *lable = scene->addText(text, Font);

    int coordX = x + radius - 5*text.size() - 7;
    lable->setPos(std::max(x, coordX) , y + radius -  size * 1.3);
    lable->setDefaultTextColor(Qt::white);

    if (left.first != -1) {
        QGraphicsLineItem* line= scene->addLine(x + radius, y + radius + 10, left.first + radius,
                                                y +  dy + radius, blackpen);
        line -> setZValue(-1);
     }

     std::pair <int,int> right = DrawTree(scene, ptr->right, y + dy, x + dx);

     if (right.first != -1) {
         QGraphicsLineItem* line= scene->addLine(x + radius, y + radius + 10, right.first + radius,
                                                 y +  dy + radius, blackpen);
         line -> setZValue(-1);
     }

     return std::make_pair(x, std::max(std::max(x, left.second), right.second));
}
std::pair <int, int> DrawTree (QGraphicsScene* &scene, node_RB* ptr, double y, int x_circle) {
    if (ptr == nullptr) return std::make_pair(-1, -1);

    std::pair <int,int> left = DrawTree(scene, ptr->left, y + dy, x_circle);

    QString type = "RB";
    int x = left.second + dx;
    if (left.second == -1) x = x_circle;

    QBrush brush = blackBrush;
    if (ptr->color == RED) {
        brush = redBrush;
    }
    Node *my_node = new Node(x, y, diameter, blackpen, brush, ptr->data, type);
    scene->addItem(my_node);


    QString text = QString::number(ptr->data);

    int size = 14;
    if (text.size() >= 4)
        size = 14 - 1.7* (text.size() - 2);
    if (text.size() == 7)
        size = 6;
    if (text.size() >= 8)
        size = 5;
    QFont Font("Franklin Gothic Medium", size);

    QGraphicsTextItem *lable = scene->addText(text, Font);

    int coordX = x + radius - 5*text.size() - 7;
    lable->setPos(std::max(x, coordX) , y + radius -  size * 1.3);
    lable->setDefaultTextColor(Qt::white);

    if (left.first != -1) {
        QGraphicsLineItem* line= scene->addLine(x + radius, y + radius + 10, left.first + radius,
                                                y +  dy + radius, blackpen);
        line -> setZValue(-1);
     }

     std::pair <int,int> right = DrawTree(scene, ptr->right, y + dy, x + dx);

     if (right.first != -1) {
         QGraphicsLineItem* line= scene->addLine(x + radius, y + radius + 10, right.first + radius,
                                                 y +  dy + radius, blackpen);
         line -> setZValue(-1);
     }

     return std::make_pair(x, std::max(std::max(x, left.second), right.second));
}
std::pair <int, int> DrawTree (QGraphicsScene* &scene, node_Treap* ptr, double y, int x_circle) {
    if (ptr == nullptr) return std::make_pair(-1, -1);

    std::pair <int,int> left = DrawTree(scene, ptr->left, y + dy, x_circle);

    QString type = "Treap";
    int x = left.second + dx;
    if (left.second == -1) x = x_circle;
    Node *my_node = new Node(x, y, diameter, blackpen, blackBrush, ptr->key, type);
    scene->addItem(my_node);

    QString text = QString::number(ptr->key);

    int size = 14;
    if (text.size() >= 4)
        size = 14 - 1.7* (text.size() - 2);
    if (text.size() == 7)
        size = 6;
    if (text.size() >= 8)
        size = 5;
    QFont Font("Franklin Gothic Medium", size);

    QGraphicsTextItem *lable = scene->addText(text, Font);

    int coordX = x + radius - 5*text.size() - 7;
    lable->setPos(std::max(x, coordX) , y + radius -  size * 1.3);
    lable->setDefaultTextColor(Qt::white);

    if (left.first != -1) {
        QGraphicsLineItem* line= scene->addLine(x + radius, y + radius + 10, left.first + radius,
                                                y +  dy + radius, blackpen);
        line -> setZValue(-1);
     }

     std::pair <int,int> right = DrawTree(scene, ptr->right, y + dy, x + dx);

     if (right.first != -1) {
         QGraphicsLineItem* line= scene->addLine(x + radius, y + radius + 10, right.first + radius,
                                                 y +  dy + radius, blackpen);
         line -> setZValue(-1);
     }

     return std::make_pair(x, std::max(std::max(x, left.second), right.second));
}
std::pair <int, int> DrawTree (QGraphicsScene* &scene, node_Splay* ptr,  double y, int x_circle) {
    if (ptr == nullptr) return std::make_pair(-1, -1);

    std::pair <int,int> left = DrawTree(scene, ptr->left, y + dy, x_circle);

    QString type = "Splay";
    int x = left.second + dx;
    if (left.second == -1) x = x_circle;
    Node *my_node = new Node(x, y, diameter, blackpen, blackBrush, ptr->data, type);
    scene->addItem(my_node);

    QString text = QString::number(ptr->data);

    int size = 14;
    if (text.size() >= 4)
        size = 14 - 1.7* (text.size() - 2);
    if (text.size() == 7)
        size = 6;
    if (text.size() >= 8)
        size = 5;
    QFont Font("Franklin Gothic Medium", size);

    QGraphicsTextItem *lable = scene->addText(text, Font);

    int coordX = x + radius - 5*text.size() - 7;
    lable->setPos(std::max(x, coordX) , y + radius -  size * 1.3);
    lable->setDefaultTextColor(Qt::white);

    if (left.first != -1) {
        QGraphicsLineItem* line= scene->addLine(x + radius, y + radius + 10, left.first + radius,
                                                y +  dy + radius, blackpen);
        line -> setZValue(-1);
     }

     std::pair <int,int> right = DrawTree(scene, ptr->right, y + dy, x + dx);

     if (right.first != -1) {
         QGraphicsLineItem* line= scene->addLine(x + radius, y + radius + 10, right.first + radius,
                                                 y +  dy + radius, blackpen);
         line -> setZValue(-1);
     }

     return std::make_pair(x, std::max(std::max(x, left.second), right.second));
}

/*void DrawTree(QGraphicsScene* &scene, node_AVL* ptr, double dx, double y, int x_circle) {
    if (ptr == nullptr) return;
    // QGraphicsEllipseItem *ellipse = scene->addEllipse(x_circle, y, diameter, diameter, blackpen, blackBrush);

    QString type = "AVL";
    Node *my_node = new Node(x_circle, y, diameter, blackpen, blackBrush, ptr->data, type);
    scene->addItem(my_node);

    QString text = QString::number(ptr->data);
    QFont Font("Franklin Gothic Medium", 14);

    QGraphicsTextItem *lable = scene->addText(text, Font);

    lable->setPos(x_circle + radius - 7*text.size(), y + radius - 7);
    lable->setDefaultTextColor(Qt::white);

    double dx_cur = dx/2;
    if (ptr->left != nullptr) {
        double x = x_circle - dx_cur;
        QGraphicsLineItem* line= scene->addLine(x_circle + radius - 10, y + radius + 23, x + radius,
                                                y +  dy + radius, blackpen);
        DrawTree(scene, ptr->left, dx_cur, y + dy, x);
    }
    if (ptr->right != nullptr) {
        double x = x_circle + dx_cur;
        QGraphicsLineItem* line= scene->addLine(x_circle + radius + 10, y + radius + 23, x + radius,
                                                y +  dy + radius, blackpen);
        DrawTree(scene, ptr->right, dx_cur, y + dy, x);
    }
}*/
/*void DrawTree(QGraphicsScene* &scene, node_RB* ptr, double dx, double y, int x_circle) {
    if (ptr == nullptr) return;

    QBrush Brush;
    if (ptr->color == BLACK) Brush = blackBrush;
    else Brush = redBrush;
    QString type = "RB";
    Node *my_node = new Node(x_circle, y, diameter, blackpen, Brush, ptr->data, type);
    scene->addItem(my_node);


    QString text = QString::number(ptr->data);
    QFont Font("Franklin Gothic Medium", 14);

    QGraphicsTextItem *lable = scene->addText(text, Font);

    lable->setPos(x_circle + radius - 7*text.size(), y + radius - 7);
    lable->setDefaultTextColor(Qt::white);

    double dx_cur = dx/2;
    if (ptr->left != nullptr) {
        double x = x_circle - dx_cur;
        QGraphicsLineItem* line= scene->addLine(x_circle + radius - 10, y + radius + 23, x + radius,
                                                y +  dy + radius, blackpen);
        DrawTree(scene, ptr->left, dx_cur, y + dy, x);
    }
    if (ptr->right != nullptr) {
        double x = x_circle + dx_cur;
        QGraphicsLineItem* line= scene->addLine(x_circle + radius + 10, y + radius + 23, x + radius,
                                               y +  dy + radius, blackpen);
        DrawTree(scene, ptr->right, dx_cur, y + dy, x);
    }
}*/
/*void DrawTree(QGraphicsScene* &scene, node_Treap* ptr, double dx, double y, int x_circle) {
    if (ptr == nullptr) return;

    QString type = "Treap";
    Node *my_node = new Node(x_circle, y, diameter, blackpen, blackBrush, ptr->key, type);
    scene->addItem(my_node);

    QString text = QString::number(ptr->key);
    QFont Font("Franklin Gothic Medium", 14);

    QGraphicsTextItem *lable = scene->addText(text, Font);

    lable->setPos(x_circle + radius - 7*text.size(), y + radius - 7);
    lable->setDefaultTextColor(Qt::white);

    double dx_cur = dx/2;
    if (ptr->left != nullptr) {
        double x = x_circle - dx_cur;
        QGraphicsLineItem* line= scene->addLine(x_circle + radius, y + radius + 10, x + radius,
                                                y +  dy + radius, blackpen);
        DrawTree(scene, ptr->left, dx_cur, y + dy, x);
    }
    if (ptr->right != nullptr) {
        double x = x_circle + dx_cur;
        QGraphicsLineItem* line= scene->addLine(x_circle + radius, y + radius + 10, x + radius,
                                                y +  dy + radius, blackpen);
        DrawTree(scene, ptr->right, dx_cur, y + dy, x);
    }
}*/
/*void DrawTree(QGraphicsScene* &scene, node_Splay* ptr, double dx, double y, int x_circle) {
    if (ptr == nullptr) return;

    QString type = "Splay";
    Node *my_node = new Node(x_circle, y, diameter, blackpen, blackBrush, ptr->data, type);
    scene->addItem(my_node);

    QString text = QString::number(ptr->data);
    QFont Font("Franklin Gothic Medium", 14);

    QGraphicsTextItem *lable = scene->addText(text, Font);

    lable->setPos(x_circle + radius - 7*text.size(), y + radius - 7);
    lable->setDefaultTextColor(Qt::white);

    double dx_cur = dx/2;
    if (ptr->left != nullptr) {
        double x = x_circle - dx_cur;
        QGraphicsLineItem* line= scene->addLine(x_circle + radius, y + radius + 10, x + radius,
                                                y +  dy + radius, blackpen);
        DrawTree(scene, ptr->left, dx_cur, y + dy, x);
    }
    if (ptr->right != nullptr) {
        double x = x_circle + dx_cur;
        QGraphicsLineItem* line= scene->addLine(x_circle + radius, y + radius + 10, x + radius,
                                                y +  dy + radius, blackpen);
        DrawTree(scene, ptr->right, dx_cur, y + dy, x);
    }
}*/


int Random(int a, int b) {
    if (a > 0) return a + rand() % (b - a);
    else return a + rand() % (abs(a) + b);
}
int Read_InsertSome(QString &type) {
    bool bOk;
    QString inp = QInputDialog::getText(0, "Insert N nodes",
        QString("Insert N nodes belonging to [a; b] \n \n"), QLineEdit::Normal, type, &bOk);
    if (bOk)
    {
        int value = inp.toInt();
        return value;
    } else {
        return -1;
    }
}

void MainWindow:: Synchronize(int num, QString type) {
    ui ->textEdit_insertAVL->clear();
    ui ->textEdit_insertRB->clear();
    ui ->textEdit_insertTreap->clear();
    ui ->textEdit_insertSplay->clear();

    ui ->textEdit_deleteAVL->clear();
    ui ->textEdit_deleteRB->clear();
    ui ->textEdit_deleteTreap->clear();
    ui ->textEdit_deleteSplay->clear();

    scene_AVL->clear();
    scene_RB->clear();
    scene_Treap->clear();
    scene_Splay->clear();

    if (type == "Delete All") {
        DeleteTree(root_AVL);
        root_AVL = nullptr;

        DeleteTree(root_RB);
        root_RB = nullptr;

        DeleteTree(root_Treap);
        root_Treap = nullptr;

        DeleteTree(root_Splay);
        root_Splay = nullptr;

        return;
    }
    else if (type == "Insert") {
        if (!FindElem(root_AVL, num))  Insert(num, root_AVL);
        if (!FindElem(root_RB, num))Insert(num, root_RB, root_RB);
        if (!FindElem(root_Treap, num))Insert(num, root_Treap);
        if (!FindElem(root_Splay, num))Insert(root_Splay, root_Splay, num);
    }
    else if (type == "Delete") {
        for (auto elem: deleteAVL) {
              if (FindElem(root_AVL, elem))  Delete(elem, root_AVL);
              if (FindElem(root_RB, elem))  Delete(elem, root_RB);
              if (FindElem(root_Treap, elem)) Delete(elem, root_Treap);
              if (FindElem(root_Splay, elem)) Delete(root_Splay, elem);
        }
        for (auto elem: deleteRB) {
            if (FindElem(root_AVL, elem))  Delete(elem, root_AVL);
            if (FindElem(root_RB, elem))  Delete(elem, root_RB);
            if (FindElem(root_Treap, elem)) Delete(elem, root_Treap);
            if (FindElem(root_Splay, elem)) Delete(root_Splay, elem);
        }
        for (auto elem: deleteTreap) {
            if (FindElem(root_AVL, elem))  Delete(elem, root_AVL);
            if (FindElem(root_RB, elem))  Delete(elem, root_RB);
            if (FindElem(root_Treap, elem)) Delete(elem, root_Treap);
            if (FindElem(root_Splay, elem)) Delete(root_Splay, elem);
        }
        for (auto elem: deleteSplay) {
            if (FindElem(root_AVL, elem))  Delete(elem, root_AVL);
            if (FindElem(root_RB, elem))  Delete(elem, root_RB);
            if (FindElem(root_Treap, elem)) Delete(elem, root_Treap);
            if (FindElem(root_Splay, elem)) Delete(root_Splay, elem);
        }
        deleteAVL.clear();
        deleteRB.clear();
        deleteTreap.clear();
        deleteSplay.clear();
    }
    else if (type == "Insert Some") {
        QString s = "N";
        int N = Read_InsertSome(s);
        if (N == -1) return;

        s = "a";
        int a = Read_InsertSome(s);
        if (a == -1) return;

        s = "b";
        int b = Read_InsertSome(s);
        if (b == -1) return;

        while (N--) {
            int num = Random(a, b);

            if (FindElem(root_AVL, num)) {
                N+=1;
            } else {
                Insert(num, root_AVL);
                if (!FindElem(root_RB, num))Insert(num, root_RB, root_RB);
                if (!FindElem(root_Treap, num))Insert(num, root_Treap);
                if (!FindElem(root_Splay, num))Insert(root_Splay, root_Splay, num);
            }
        }
    }
    DrawTree(scene_AVL, root_AVL, Height/2, Width/2  - 75);
    DrawTree(scene_RB, root_RB, Height/2, Width/2  - 75);
    DrawTree(scene_Splay, root_Splay, Height/2, Width/2  - 75);
    DrawTree(scene_Treap, root_Treap, Height/2, Width/2  - 75);
}

void MainWindow::on_button_insertAVL_clicked()
{
    QString input = ui->textEdit_insertAVL ->toPlainText();
    ui->textEdit_insertAVL->clear();
    int num = input.toInt();

    if (ui->checkBox -> isChecked()) {
        QString type = "Insert";
        Synchronize(num, type);
        return;
    }
    Insert(num, root_AVL);

    scene_AVL->clear();
   // scene_AVL->setSceneRect(0,0, Width, Height);

  //  double dx = std::pow(2, root_AVL->height) * 25;
    DrawTree(scene_AVL, root_AVL, Height/2, Width/2  - 75);
}
void MainWindow::on_button_insertRB_clicked()
{

    QString input = ui->textEdit_insertRB ->toPlainText();
    ui->textEdit_insertRB->clear();
    int num = input.toInt();

    if (ui->checkBox -> isChecked()) {
        QString type = "Insert";
        Synchronize(num, type);
        return;
    }

    if (FindElem(root_RB, num)) return;
    scene_RB->clear();
    //scene_RB->setSceneRect(0, 0, width,this->height());

    Insert(num, root_RB, root_RB);

    // int height = GetHeight(root_RB);
   // double dx = std::pow(2, height) * 25;
    DrawTree(scene_RB, root_RB, Height/2, Width/2  - 75);
}
void MainWindow::on_button_insertTreap_clicked()
{
    QString input = ui->textEdit_insertTreap ->toPlainText();
    ui->textEdit_insertTreap->clear();
    int num = input.toInt();

    if (ui->checkBox -> isChecked()) {
        QString type = "Insert";
        Synchronize(num, type);
        return;
    }
    scene_Treap->clear();
    // scene_Treap->setSceneRect(0, 0, width,this->height());
    Insert(num, root_Treap);


   // int height = GetHeight(root_Treap);
   // double dx = std::pow(2, height) * 25;
  //  double dx = 30;
    DrawTree(scene_Treap, root_Treap, Height/2, Width/2  - 75);
}
void MainWindow::on_button_insertSplay_clicked()
{
    QString input = ui->textEdit_insertSplay ->toPlainText();
    ui->textEdit_insertSplay->clear();
    int num = input.toInt();

    if (ui->checkBox -> isChecked()) {
        QString type = "Insert";
        Synchronize(num, type);
        return;
    }

    scene_Splay->clear();
    Insert(root_Splay, root_Splay, num);

    // int height = GetHeight(root_Splay);
   // double dx = std::pow(2, height) * 25;
   // double dx = 30;
    DrawTree(scene_Splay, root_Splay, Height/2, Width/2  - 75);

}

void MainWindow::on_button_deleteAVL_clicked()
{
    QString input = ui->textEdit_deleteAVL ->toPlainText();
    ui->textEdit_deleteAVL->clear();

    int num;
    num = input.toInt();
    if (input.size() > 0) deleteAVL.push_back(num);

    if (ui->checkBox -> isChecked()) {
        QString type = "Delete";
        Synchronize(num, type);
        return;
    }

    /*
    if (input == "0") {
        num = 0;
    } else {
        num = input.toInt();
        input = "not a zero";
    }
    if (num == 0) {
        if  (input != "not a zero") {
            if (FindElem(root_AVL, num)) {
                 Delete(num, root_AVL);
            }
        }
    } else if (FindElem(root_AVL, num)) {
        Delete(num, root_AVL);
    }*/

    for (auto elem: deleteAVL) {
          Delete(elem, root_AVL);
    }
    deleteAVL.clear();

    scene_AVL->clear();
    if (root_AVL == nullptr) return;

    // scene_AVL->setSceneRect(0,0,width,this->height());
    //double dx = std::pow(2, root_AVL->height) * 25;
    DrawTree(scene_AVL, root_AVL, Height/2, Width/2  - 75);
}
void MainWindow::on_button_deleteRB_clicked()
{
    scene_RB->clear();
    QString input = ui->textEdit_deleteRB ->toPlainText();
    ui->textEdit_deleteRB->clear();

    int num;
    num = input.toInt();
    if (input.size() > 0) deleteRB.push_back(num);

    if (ui->checkBox -> isChecked()) {
        QString type = "Delete";
        Synchronize(num, type);
        return;
    }
    /*if (input == "0") {
        num = 0;
    } else {
        num = input.toInt();
        input = "not a zero";
    }

    if (num == 0) {
        if  (input != "not a zero") {
            if (FindElem(root_RB, num)) {
                 Delete(num, root_RB);
            }
        }
    } else if (FindElem(root_RB, num)) {
        Delete(num, root_RB);
    }*/

    for (auto elem: deleteRB) {
          Delete(elem, root_RB);
    }
    deleteRB.clear();

    // int height = GetHeight(root_RB);
  //  double dx = std::pow(2, height) * 25;
    DrawTree(scene_RB, root_RB, Height/2, Width/2  - 75);
}
void MainWindow::on_button_deleteTreap_clicked()
{
    scene_Treap->clear();
    // scene_Treap->setSceneRect(0,0,width,this->height());

    QString input = ui->textEdit_deleteTreap ->toPlainText();
    ui->textEdit_deleteTreap->clear();

    int num;
    num = input.toInt();
    if (input.size() > 0) deleteTreap.push_back(num);

    if (ui->checkBox -> isChecked()) {
        QString type = "Delete";
        Synchronize(num, type);
        return;
    }
    /*if (input == "0") {
        num = 0;
    } else {
        num = input.toInt();
        input = "not a zero";
    }

    if (num == 0) {
        if  (input != "not a zero") {
            if (FindElem(root_Treap, num)) {
                 Delete(num, root_Treap);
            }
        }
    } else if (FindElem(root_Treap, num)) {
        Delete(num, root_Treap);
    }*/

    for (auto elem: deleteTreap) {
          Delete(elem, root_Treap);
    }
    deleteTreap.clear();

    // int height = GetHeight(root_Treap);
    //double dx = std::pow(2, height) * 25;
    DrawTree(scene_Treap, root_Treap, Height/2, Width/2  - 75);
}
void MainWindow::on_button_deleteSplay_clicked()
{
    scene_Splay->clear();

    QString input = ui->textEdit_deleteSplay ->toPlainText();
    ui->textEdit_deleteSplay->clear();

    int num;
    num = input.toInt();
    if (input.size() > 0) deleteSplay.push_back(num);

    if (ui->checkBox -> isChecked()) {
        QString type = "Delete";
        Synchronize(num, type);
        return;
    }
    /*if (input == "0") {
        num = 0;
    } else {
        num = input.toInt();
        input = "not a zero";
    }
    if (num == 0) {
        if  (input != "not a zero") {
            if (FindElem(root_Splay, num)) {
                 Delete(root_Splay, num);
            }
        }
    } else if (FindElem(root_Splay, num)) {
       Delete(root_Splay, num);
    }*/

    for (auto elem: deleteSplay) {
         Delete(root_Splay, elem);
    }
    deleteSplay.clear();

    //int height = GetHeight(root_Splay);
    //double dx = std::pow(2, height) * 25;
    //double dx
    DrawTree(scene_Splay, root_Splay, Height/2, Width/2  - 75);
}


void MainWindow::on_button_delete_all_AVL_clicked()
{
    if (ui->checkBox -> isChecked()) {
        QString type = "Delete All";
        Synchronize(-1, type);
        return;
    }
    scene_AVL->clear();
    DeleteTree(root_AVL);
    root_AVL = nullptr;
}
void MainWindow::on_button_delete_all_RB_clicked()
{
    if (ui->checkBox -> isChecked()) {
        QString type = "Delete All";
        Synchronize(-1, type);
        return;
    }
    scene_RB->clear();
    DeleteTree(root_RB);
    root_RB = nullptr;
}
void MainWindow::on_button_delete_all_Treap_clicked()
{
    if (ui->checkBox -> isChecked()) {
        QString type = "Delete All";
        Synchronize(-1, type);
        return;
    }
    scene_Treap->clear();
    DeleteTree(root_Treap);
    root_Treap = nullptr;
}
void MainWindow::on_button_delete_all_Splay_clicked()
{
    if (ui->checkBox -> isChecked()) {
        QString type = "Delete All";
        Synchronize(-1, type);
        return;
    }
    scene_Splay->clear();
    DeleteTree(root_Splay);
    root_Splay = nullptr;
}


void MainWindow::on_button_insertSomeAVL_clicked()
{
    if (ui->checkBox -> isChecked()) {
        QString type = "Insert Some";
        Synchronize(-1, type);
        return;
    }
    QString s = "N";
    int N = Read_InsertSome(s);
    if (N == -1) return;

    s = "a";
    int a = Read_InsertSome(s);
    if (a == -1) return;

    s = "b";
    int b = Read_InsertSome(s);
    if (b == -1) return;

    while (N--) {
        int num = Random(a, b);

        if (FindElem(root_AVL, num)) {
            N+=1;
        } else {
            Insert(num, root_AVL);
        }
    }

    scene_AVL->clear();

  //  scene_AVL->setSceneRect(0,0, Width, Height);
   // double dx = std::pow(2, root_AVL->height) * 25;
    DrawTree(scene_AVL, root_AVL, Height/2, Width/2  - 75);
}
void MainWindow::on_button_insertSomeRB_clicked()
{
    if (ui->checkBox -> isChecked()) {
        QString type = "Insert Some";
        Synchronize(-1, type);
        return;
    }
    QString s = "N";
    int N = Read_InsertSome(s);
    if (N == -1) return;

    s = "a";
    int a = Read_InsertSome(s);
    if (a == -1) return;

    s = "b";
    int b = Read_InsertSome(s);
    if (b == -1) return;

    while (N--) {
        int num = Random(a, b);

        if (FindElem(root_RB, num)) {
            N+=1;
        } else {
            Insert(num, root_RB, root_RB);
        }
    }


    scene_RB->clear();
    DrawTree(scene_RB, root_RB, Height/2, Width/2  - 75);
}
void MainWindow::on_button_insertSomeTreap_clicked()
{
    if (ui->checkBox -> isChecked()) {
        QString type = "Insert Some";
        Synchronize(-1, type);
        return;
    }
    QString s = "N";
    int N = Read_InsertSome(s);
    if (N == -1) return;

    s = "a";
    int a = Read_InsertSome(s);
    if (a == -1) return;

    s = "b";
    int b = Read_InsertSome(s);
    if (b == -1) return;

    while (N--) {
        int num = Random(a, b);

        if (FindElem(root_Treap, num)) {
            N+=1;
        } else {
            Insert(num, root_Treap);
        }
    }

    scene_Treap->clear();
  //  scene_AVL->setSceneRect(0,0, Width, Height);
   //  int height = GetHeight(root_Treap);
    //double dx = std::pow(2, height) * 25;
    //double dx = 40;
    DrawTree(scene_Treap, root_Treap, Height/2, Width/2  - 75);
}
void MainWindow::on_button_insertSomeSplay_clicked()
{
    if (ui->checkBox -> isChecked()) {
        QString type = "Insert Some";
        Synchronize(-1, type);
        return;
    }
    QString s = "N";
    int N = Read_InsertSome(s);
    if (N == -1) return;

    s = "a";
    int a = Read_InsertSome(s);
    if (a == -1) return;

    s = "b";
    int b = Read_InsertSome(s);
    if (b == -1) return;


    while (N--) {
        int num = Random(a, b);

        if (FindElem(root_Splay, num)) {
            N+=1;
        } else {
            Insert(root_Splay, root_Splay, num);
        }
    }

    scene_Splay->clear();
    // int height = GetHeight(root_Splay);
   // double dx = std::pow(2, height) * 25;
  //  double dx = 40;
    DrawTree(scene_Splay, root_Splay, Height/2, Width/2  - 75);
}
