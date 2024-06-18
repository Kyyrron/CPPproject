#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QtOpenGL>
#include <global.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)// passage en paramètre de la fenêtre
                         // parente (null pour la fenêtre racine)

    , ui(new Ui::MainWindow) // création des widgets décrit dans fichier .ui
{
    ui->setupUi(this); // initialisation des widgets
    container = ui->myGLWidget; // Contains all our objets

    massDef = ui->massLine;
    xVelDef = ui->xSpeedLine;
    yVelDef = ui->ySpeedLine;

    massDef->setText("Define Mass - press enter");
    xVelDef->setText("Define X velocity - press enter");
    yVelDef->setText("Define Y velocity - press enter");

    connect(massDef, &QLineEdit::returnPressed, this, &MainWindow::massSelected);
    connect(xVelDef, &QLineEdit::returnPressed, this, &MainWindow::xVelSelected);
    connect(yVelDef, &QLineEdit::returnPressed, this, &MainWindow::yVelSelected);

    clear = ui->clearButton;
    connect(clear, &QPushButton::pressed, container, &GLWidget::clearAll);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, container, &GLWidget::animate);
    timer->start(sim::dt);
}

void MainWindow::massSelected()
{
    try{
        mass = std::stoi(massDef->text().toStdString());
    } catch (const std::invalid_argument &e)
    {
        return; // do nothing if error
    }
}

void MainWindow::xVelSelected()
{
    try{
        xVelocity = std::stoi(xVelDef->text().toStdString()) / 1000.;
    } catch (const std::invalid_argument &e)
    {
        return; // do nothing if error
    }
}

void MainWindow::yVelSelected()
{
    try{
        yVelocity = std::stoi(yVelDef->text().toStdString())/1000.;
    } catch (const std::invalid_argument &e)
    {
        return; // do nothing if error
    }
}

void MainWindow::instantiatePlanet(QPointF center)
{
    int radius = 10*log(mass)/2; // ln
    container->newPlanet(mass, radius, center, xVelocity, yVelocity);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) { // Left Button pressed
        //QMessageBox::information(this, "Mouse Pressed", "x : " + QString::number(event->position().x()));
        this->instantiatePlanet(QPointF(event->position().x(),
                                        event->position().y()));
    }
}
