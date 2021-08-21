#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProgressBar>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); //ui setup code:

    //initialize progress bar
    ui->simProgressBar->setValue(0);
    ui->simProgressBar->setTextVisible(false); //hide % display of progress bar, for neatness

    //initializing spinboxes:

    ui->doubleSpinBox_percentInfectivity->setMaximum(50.00); //set maximum infectivity (minimum is 0)
    ui->doubleSpinBox_percentInfectivity->setValue(20.00); //set default display
    ui->doubleSpinBox_percentInfectivity->setSingleStep(0.50); //value increments by 0.50 while using arrows
    ui->doubleSpinBox_percentInfectivity->setDecimals(2); //sets value to display 2 decimal places

    ui->doubleSpinBox_percentLethality->setMaximum(50.00); //set maximum lethality
    ui->doubleSpinBox_percentLethality->setValue(0.30); //set default display
    ui->doubleSpinBox_percentLethality->setSingleStep(0.50); //value incremenets by 0.50 when using arrows
    ui->doubleSpinBox_percentLethality->setDecimals(2); //value is restricted to 2 decimal places

    ui->spinBox_population->setMinimum(10000); //setting min to 10K
    ui->spinBox_population->setMaximum(5000000); //setting max size to 5mil
    ui->spinBox_population->setValue(200000); //displays default value of 100K
    ui->spinBox_population->setSingleStep(10000); //changes how much each arrow click increments value

    ui->spinBox_dailyVaccines->setRange(0, 10000); //setting range of vaccines
    ui->spinBox_dailyVaccines->setValue(200); //setting default display
    ui->spinBox_dailyVaccines->setSingleStep(50); //setting increment value

    ui->spinBox_simDays->setRange(100, 1000); //setting range of days of runtime
    ui->spinBox_simDays->setValue(300); //setting default display
    ui->spinBox_simDays->setSingleStep(25); //setting increment value

    ui->doubleSpinBox_percentInfected->setMaximum(50.00); //set info of percentInfected spinbox
    ui->doubleSpinBox_percentInfected->setValue(0.0100);
    ui->doubleSpinBox_percentInfected->setSingleStep(0.50);
    ui->doubleSpinBox_percentInfected->setDecimals(4);

    ui->doubleSpinBox_percentImmune->setMaximum(50.00); //set info of percentImmune spinbox
    ui->doubleSpinBox_percentImmune->setValue(0.50);
    ui->doubleSpinBox_percentImmune->setSingleStep(0.50);
    ui->doubleSpinBox_percentImmune->setDecimals(4);

    ui->doubleSpinBox_percentSoPs->setMaximum(100.00); //set info of percent following SoPs
    ui->doubleSpinBox_percentSoPs->setValue(1.00);
    ui->doubleSpinBox_percentSoPs->setSingleStep(0.50);
    ui->doubleSpinBox_percentSoPs->setDecimals(4);

    //initialize checkboxes:
    ui->checkBox_infected->setChecked(true); //set infected graph to be on by default
    ui->checkBox_infected->setDisabled(true); //disable changing infected checkboxes, as graph would run empty otherwise
    ui->checkBox_deaths->setChecked(true); //set total deaths graph to be on by default
    ui->checkBox_sick->setChecked(false); //set all other statuses as off by default, can be turned on though
    ui->checkBox_healthy->setChecked(false);
    ui->checkBox_immune->setChecked(false);
    ui->checkBox_vaccinated->setChecked(false);

    ui->lineEdit_countryName->setText("[Name]"); //default name of country
}

MainWindow::~MainWindow() //destructor for window
{
    delete ui;
}

void MainWindow::on_submitParameters_clicked() //when the start simulation button is clicked
{
    ui->submitParameters->setEnabled(false); //temporarily set button to be disabled, to disallow creation
    //of multiple simulators/graphing windows

    //getting and setting values as needed
    int population = ui->spinBox_population->value();
    double percentInfected = ui->doubleSpinBox_percentInfected->value();
    double percentImmune = ui->doubleSpinBox_percentImmune->value();
    double percentSoPs = ui->doubleSpinBox_percentSoPs->value();
    QString countryName = ui->lineEdit_countryName->text();
    int dailyVaccines = ui->spinBox_dailyVaccines->value();
    int simDays = ui->spinBox_simDays->value();

    double lethalityPerDay = ui->doubleSpinBox_percentLethality->value();
    double infectivityPerDay = ui->doubleSpinBox_percentInfectivity->value();

    SimulatorRules* ptr; //create a dynamic rules object to set death and transmission chances
    ptr->setDeathChance(lethalityPerDay/100);
    ptr->setTransmissionChance(infectivityPerDay/100);

    //assign these bools value of associated checkboxes
    bool infected = ui->checkBox_infected->isChecked();
    bool death = ui->checkBox_deaths->isChecked();
    bool sick = ui->checkBox_sick->isChecked();
    bool healthy = ui->checkBox_healthy->isChecked();
    bool vaccinated = ui->checkBox_vaccinated->isChecked();
    bool immune = ui->checkBox_immune->isChecked();


    //dynamically creating a new simulator with constructor
    sim = new Simulator(countryName.toStdString(), dailyVaccines);
    //populate this new object
    sim->populate(population, percentInfected, percentImmune, percentSoPs);

    //running plotting logic
     int n = simDays; //run loop for determined number of days
       std::vector< int > x, y, z, s, h, v, im; //declaring vectors of various stats
       //x is days, all others are stats

       //set the progress bar to have a range corresponding to loop, increments to max alonside loop
       ui->simProgressBar->setRange(0, simDays);

       for(int i=0; i<n; i++) {
           if(plotting == true) //if terminate plotting button has not been pressed
           {
           x.push_back(i); //assigning values to plot
           if (infected == true) { y.push_back( sim->getCountry().getStats().getInfected() ); }
           if (death == true) { z.push_back( sim->getCountry().getStats().getDead() ); }
           if (sick == true) { s.push_back( sim->getCountry().getStats().getSick()); }
           if (healthy == true) { h.push_back( sim->getCountry().getStats().getHealthy());}
           if (vaccinated == true) { v.push_back( sim->getCountry().getStats().getVaccinated());}
           if (immune == true) { im.push_back( sim->getCountry().getStats().getImmune());}

           sim->passDay(); //pass day for each object

           matplotlibcpp::tight_layout(); //makes graph have a smaller layout

           matplotlibcpp::clf(); //clear previous plotting data

           // Plot line from given data. Color is selected automatically.
           if (infected == true) matplotlibcpp::named_plot("Active Infections", x, y);
           if (death == true) matplotlibcpp::named_plot("Total Deaths", x, z);
           if (sick == true ) matplotlibcpp::named_plot("Currently Sick", x, s);
           if (healthy == true ) matplotlibcpp::named_plot("Currently Healthy", x, h);
           if (immune == true ) matplotlibcpp::named_plot("Currently Immune", x, im);
           if (vaccinated == true ) matplotlibcpp::named_plot("Currently Vaccinated", x, v);

           matplotlibcpp::xlim(0, (simDays + simDays/10) ); //set x-axis limits, so that graph only scales
           //vertically during run time

           matplotlibcpp::xlabel("Days"); //label x-axis

           // Add graph title
           matplotlibcpp::title("COVID-19 Simulation - " + sim->getCountry().getName());

           // Enable legend.
           matplotlibcpp::legend();

           //continuously plot graph
           matplotlibcpp::pause(0.001);

           //set value of progress bar to current iteration of loop, runs progress bar as one would expect.
           ui->simProgressBar->setValue(i);
           }
           else break; //if plotting is false, stop plotting
       }

        delete sim; //clear simulator object, remake one next time program is started

        plotting = true; //ensure plotting is enabled for next set of parameters entered.

        ui->submitParameters->setEnabled(true); //re-enable button to allow for additional simulators
        ui->simProgressBar->setValue(0); //reset progressbar
}

void MainWindow::on_pushButton_pressed() //terminate plotting function
{ //if terminate plotting button is pressed
    plotting = false; //terminate plotting
}
