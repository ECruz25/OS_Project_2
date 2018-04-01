#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mmu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QStringList table_header;
    int counter;
    MMU* mmu;
    ~MainWindow();

private slots:
    void on_save_program_button_clicked();

    void on_page_amount_save_btn_clicked();

    void on_setup_btn_clicked();

    void update_combo_box();

    void on_add_to_exec_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
