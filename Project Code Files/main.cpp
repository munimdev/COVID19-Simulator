#include <QApplication>
#include <QDialog>
#include "mainwindow.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include "matplotlibcpp.h"
#include "Simulator.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Humans.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //create an application object
    MainWindow w; //create a window object
    w.show(); //display the window object
    a.exec(); //wait for application to close
    return 0; //end program
}
