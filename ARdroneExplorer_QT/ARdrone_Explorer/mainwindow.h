#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <path_window.h>
#include "mythread.h"
#include "dataworker.h"

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
    void on_but_startros_clicked();

    void on_but_stopros_clicked();

    void on_but_takeoff_clicked();

    void on_but_land_clicked();

    void on_but_forward_clicked();

    void on_but_backward_clicked();

    void on_but_left_clicked();

    void on_but_right_clicked();

    void on_but_hover_clicked();

    void on_but_reset_clicked();

    void on_but_nothover_clicked();

    void on_but_flattrim_clicked();

    void on_but_path_clicked();

    void data_process_output();

    void data_process_error();

    void on_but_datalog_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    Path_window *path_window;
    QProcess *data_process;
    MyThread *mythread;

    QThread *DataWorkerThread;
    DataWorker *cDataWorker;


    int loop_time = 0;
    double_t last_time;
    double_t new_vx;
    double_t new_vy;
    double_t last_vx;
    double_t last_vy;
    double_t old_x;
    double_t old_y;
    double_t new_x;
    double_t new_y;
    double_t new_time;
};

#endif // MAINWINDOW_H
