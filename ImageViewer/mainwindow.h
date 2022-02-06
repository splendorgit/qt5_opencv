#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QToolBar>
#include <QSlider>
#include <QPushButton>


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
    void initUI();
    void showImage( QString path);



private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *viewMenu;

    QToolBar *fileToolbar;
    QToolBar *viewToolbar;


    QAction *openAction;
    QAction *exitAction;

    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *nextImageAction;
    QAction *prevImageAction;


    QGraphicsScene *imageScene;
    QGraphicsView *imageView;

    QStatusBar *mainStatusBar;
    QLabel  *mainStatusLabel;

    QString currentImagePath;

private slots:

    void OpenImage();
    void ZoomInImage();
    void ZoomOutImage();
    void NextImage();
    void PrevImage();

};
#endif // MAINWINDOW_H
