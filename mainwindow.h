#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_button_insertRB_clicked();

    void on_button_insertAVL_clicked();

    void on_button_deleteAVL_clicked();

    void on_button_deleteRB_clicked();

    void on_button_insertTreap_clicked();

    void on_button_deleteTreap_clicked();

    void on_button_delete_all_AVL_clicked();

    void on_button_delete_all_RB_clicked();

    void on_button_delete_all_Treap_clicked();

    void on_button_insertSomeAVL_clicked();

    void on_button_insertSomeRB_clicked();

    void on_button_insertSomeTreap_clicked();

    void on_button_insertSplay_clicked();

    void on_button_delete_all_Splay_clicked();

    void on_button_deleteSplay_clicked();

    void on_button_insertSomeSplay_clicked();

    void Synchronize(int, QString);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene_AVL;
    QGraphicsScene *scene_RB;
    QGraphicsScene *scene_Treap;
    QGraphicsScene *scene_Splay;
};
#endif // MAINWINDOW_H
