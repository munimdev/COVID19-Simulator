#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Simulator.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "matplotlibcpp.h"
#include "Simulator.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Humans.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Simulator* sim; //create simulator within window application
    bool plotting; //for terminating plotting

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS: //slots are used to link interactible objects with code
    void on_submitParameters_clicked(); //when submit parameters button is clicked, run plotting
    void on_pushButton_pressed(); //terminate plotting button press

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
