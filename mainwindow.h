#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "GLWidget.h"
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;     // Ui::MainWindow : classe généré automatiquement à
                            // partir d’un fichier .ui décrivant l’interface

    int mass = 10;
    float xVelocity = 0.;
    float yVelocity = 0.;

    GLWidget* container; // Contains all our planets

    QLineEdit* massDef;
    QLineEdit* yVelDef;
    QLineEdit* xVelDef;
    QPushButton* clear;

    float getDistance(QPointF planet1, QPointF planet2);
    void instantiatePlanet(QPointF center);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void massSelected();
    void xVelSelected();
    void yVelSelected();
};
#endif // MAINWINDOW_H
