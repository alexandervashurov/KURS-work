#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_source_file_clicked();
    void on_button_destination_file_clicked();

    void on_button_archivate_clicked();

private:
    Ui::MainWindow *ui;
    QString source_file;
    QString destination_file;
    void try_activate_button_archivate();
};

#endif // MAINWINDOW_H
