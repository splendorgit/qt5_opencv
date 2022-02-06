#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    void extraInitUI();
    void showImage(QString path);
    int last_value;


private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    QString currentImagePath;
    QGraphicsScene *imageScene;


private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionNext_triggered();

    void on_actionPrev_triggered();



    void on_horizontalSlider_valueChanged(int value);
    void on_resetSize_clicked();
};
#endif // MAINWINDOW_H
