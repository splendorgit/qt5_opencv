#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    extraInitUI();
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::extraInitUI()
{
statusLabel = new QLabel(statusBar());
statusBar()->addPermanentWidget(statusLabel);
statusLabel ->setText("Ready");

imageScene =    new QGraphicsScene(this);
ui->graphicsView = new QGraphicsView(imageScene);
setCentralWidget(ui->graphicsView);
ui->toolBar_2->addWidget(ui->horizontalSlider);
ui->toolBar_2->addWidget(ui->sliderLabel);
ui->horizontalSlider->setValue(100);
ui->sliderLabel->setText("100%");

ui->toolBar_2->addWidget(ui->resetSize);
last_value = 100;

}

void MainWindow::on_actionOpen_triggered()
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


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionZoomIn_triggered()
{
    ui->graphicsView ->scale(1.25,1.25);
    ui->horizontalSlider->setValue(ui->horizontalSlider->value()*1.25);
}


void MainWindow::on_actionZoomOut_triggered()
{
    ui->graphicsView ->scale(0.8,0.8);
    ui->horizontalSlider->setValue(ui->horizontalSlider->value()*0.8);
}


void MainWindow::on_actionNext_triggered()
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


void MainWindow::on_actionPrev_triggered()
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
void MainWindow::showImage(QString path)
{
    imageScene ->clear();
    ui->graphicsView ->resetMatrix();
    QPixmap image(path);
    imageScene ->addPixmap(image);
    imageScene ->update();
    ui->graphicsView -> setSceneRect(image.rect());

    QString status = QString("%1, %2x%3, %4 Bytes").arg(path).arg(image.width()).arg(image.height()).arg(QFile(path).size());
    statusLabel ->setText(status);
    currentImagePath = path;
}




void MainWindow::on_horizontalSlider_valueChanged(int value)
{

    ui->sliderLabel->setText(QString::number(value) + "%");
    ui->graphicsView->scale(100.0/last_value,100.0/last_value);
    ui->graphicsView->scale(value/100.0,value/100.0);
    last_value = value;

}


void MainWindow::on_resetSize_clicked()
{
    ui->horizontalSlider->setValue(100);
   //ui->graphicsView->scale(100.0/last_value,100.0/last_value);
    //last_value = 100;

}

