#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCore>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();

    //
    connect(exitAction, SIGNAL(triggered(bool)), QApplication::instance(),SLOT(quit()));
    connect(openAction, SIGNAL(triggered(bool)), this,SLOT(OpenImage()));
    connect(zoomInAction, SIGNAL(triggered(bool)), this,SLOT(ZoomInImage()));
    connect(zoomOutAction, SIGNAL(triggered(bool)), this,SLOT(ZoomOutImage()));
    connect(nextImageAction, SIGNAL(triggered(bool)), this,SLOT(NextImage()));
    connect(prevImageAction, SIGNAL(triggered(bool)), this,SLOT(PrevImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initUI()
{
    this ->resize(800,600);

    //Setup Menubar
    fileMenu = menuBar()->addMenu("&File");
    viewMenu = menuBar()->addMenu("&View");

    //Setup Toolbar
    fileToolbar = addToolBar("File");
    viewToolbar = addToolBar("View");



    // Menu actions
    openAction = new QAction ("&Open", this);
    fileMenu ->addAction(openAction);
    fileToolbar -> addAction(openAction);

    exitAction = new QAction ("&Exit", this);
    fileMenu ->addAction(exitAction);
    fileToolbar -> addAction(exitAction);



    zoomInAction = new QAction ("&Zoom In", this);
    viewMenu ->addAction(zoomInAction);
    viewToolbar -> addAction(zoomInAction);

    zoomOutAction = new QAction ("&Zoom Out", this);
    viewMenu ->addAction(zoomOutAction);
    viewToolbar -> addAction(zoomOutAction);


    nextImageAction = new QAction ("&Next", this);
    viewMenu ->addAction(nextImageAction);
    viewToolbar -> addAction(nextImageAction);

    prevImageAction = new QAction ("&Prev", this);
    viewMenu ->addAction(prevImageAction);
    viewToolbar -> addAction(prevImageAction);

    //
    imageScene =    new QGraphicsScene(this);
    imageView =     new QGraphicsView(imageScene);
    setCentralWidget(imageView);

    //setup status bar

    mainStatusBar = statusBar();
    mainStatusLabel = new QLabel(mainStatusBar);
    mainStatusBar -> addPermanentWidget(mainStatusLabel);
    mainStatusLabel ->setText("Status");

}

void MainWindow :: OpenImage()
{
    std::cout << "Clicked Open" << std::endl;
    QFileDialog dialog(this);
    dialog.setWindowTitle("Open Image");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg *.jpeg)"));
    QStringList filePaths;
    if (dialog.exec())
    {
        filePaths = dialog.selectedFiles();
        std::cout << "showImage" << std::endl;
        showImage(filePaths.at(0));

    }

}

void MainWindow::showImage(QString path)
{
    imageScene ->clear();
    imageView ->resetMatrix();
    QPixmap image(path);
    imageScene ->addPixmap(image);
    imageScene ->update();
    imageView -> setSceneRect(image.rect());

    QString status = QString("%1, %2x%3, %4 Bytes").arg(path).arg(image.width()).arg(image.height()).arg(QFile(path).size());
    mainStatusLabel ->setText(status);
    currentImagePath = path;

}

void MainWindow::ZoomInImage()
{
    imageView ->scale(1.25,1.25);

}

void MainWindow::ZoomOutImage()
{
    imageView ->scale(0.8,0.8);

}

void MainWindow::NextImage()
{
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters  << "*.png" << "*.bmp" << "*.jpg" << "*.jpeg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    int idx = fileNames.indexOf(QRegExp(QRegExp::escape(current.fileName())));
    int no_of_image = fileNames.size()-1;
    if(idx < no_of_image) {
        showImage(dir.absoluteFilePath(fileNames.at(idx + 1)));
    } else {
            QMessageBox::information(this, "Information", "Current image is the last one.");
    }

}

void MainWindow::PrevImage()
{
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters << "*.png" << "*.bmp" << "*.jpg" << "*.jpeg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    int idx = fileNames.indexOf(QRegExp(QRegExp::escape(current.fileName())));
    if(idx > 0) {
        showImage(dir.absoluteFilePath(fileNames.at(idx - 1)));
    } else {
            QMessageBox::information(this, "Information", "Current image is the first one.");
    }



}

