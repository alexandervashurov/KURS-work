#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <haffman.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->source_file = "";
    this->destination_file = "";
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_source_file_clicked()
{
    this->source_file = QFileDialog::getOpenFileName(this, tr("Choose source file"));
    ui->label_source_file->setText(this->source_file);
    this->try_activate_button_archivate();
}

void MainWindow::on_button_destination_file_clicked()
{
    this->destination_file = QFileDialog::getSaveFileName(this, tr("Choose destination file"));
    ui->label_destination_file->setText(this->destination_file);
    this->try_activate_button_archivate();
}

void MainWindow::try_activate_button_archivate()
{
    if (this->source_file.length() > 0 && this->destination_file.length() > 0)
        ui->button_archivate->setEnabled(true);
}

void MainWindow::on_button_archivate_clicked()
{
    haffman worker;
    worker.archivate(this->source_file.toStdString(), this->destination_file.toStdString());
    QString filename=this->source_file,temp=".extracted";
    int i=filename.size()-1;
    while(i>=0 && filename.at(i)!=tr("."))
        i--;

        filename.insert(i,temp);
    worker.unarchivate(this->destination_file.toStdString(),filename.toStdString() );
    QMessageBox::about(this,"","Archivate complete!");
}
