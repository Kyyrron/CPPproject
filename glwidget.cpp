#include "GLWidget.h"
#include <QMessageBox>
#include <QTimer>
#include <global.h>
#include <QOpenGLFunctions>
#include <QPaintEvent>
#include <vector>
#include <algorithm> // pour std::remove_if
#include <unordered_set> // pour std::unordered_set

#include <iostream>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    elapsed = 0;
    setFixedSize(700, 700);
    setAutoFillBackground(false);

    brush = QBrush(Qt::red); // fill
    pen = QPen(Qt::black); // outlines
    pen.setWidth(2);
}

void GLWidget::clearAll()
{
    planets.clear();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    const QRect & rect = event->rect();
    QPainter painter;
    painter.begin(this);
    painter.eraseRect(rect);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, event);
    painter.end();
}

void GLWidget::paint(QPainter* painter, QPaintEvent *event)
{
    painter->save(); // save state
    painter->translate(2,-80);
    painter->setBrush(brush);
    painter->setPen(pen);

    std::vector<int> toDestroy;
    std::vector<Planet> toCreate;

    for(auto& planet : planets)
    {
        // todo : forces de contact, ajouter vecteur force dans la bonne direction pile opposé à celui actuel.
        for(auto& planet2 : planets)
        {
            double dist = planet.distanceTo(planet2);

            if (planet.id != planet2.id && dist < planet.radius + planet2.radius + 2) // not the same object
            {
            // Collision -> merging planets

                auto find1 = std::find(toDestroy.begin(), toDestroy.end(), planet.id);
                auto find2 = std::find(toDestroy.begin(), toDestroy.end(), planet.id);

                if (find1 == toDestroy.end() && find2 == toDestroy.end()) // the planets are not already merging : let's do it
                {

                    int totalMass = planet.mass + planet2.mass;

                    int newRadius = 10*log(totalMass)/2; // merging

                    QPointF newCenter = (planet.center * planet.mass + planet2.center * planet2.mass)/totalMass;
                    //QPointF newCenter = QPointF((planet.center.x() + planet2.center.x())/2, (planet.center.y() + planet2.center.y())/2);

                    QPointF newSpeed = (planet.velocity * planet.mass + planet2.velocity * planet2.mass)/totalMass;

                    Planet newOne = Planet(newRadius, totalMass, newCenter, newSpeed, lastId++);

                    toDestroy.push_back(planet.id);
                    toDestroy.push_back(planet2.id);
                    toCreate.push_back(newOne);
                }
            }

            else if (dist>0 && planet.id != planet2.id)
            {
                double F = sim::g_constant * planet.mass * planet2.mass / (dist*dist) ;

                double dx = planet2.center.x() - planet.center.x();
                double dy = planet2.center.y() - planet.center.y();

                float cosTheta = dx / dist;
                float sinTheta = dy / dist;

                double Fx = F*cosTheta;
                double Fy = F*sinTheta;

                planet.velocity.ry() += sim::dt * Fy/planet.mass;
                planet.velocity.rx() += sim::dt * Fx/planet.mass;
            }
        }
        planet.center.rx() += sim::dt/2 * planet.velocity.x();
        planet.center.ry() += sim::dt/2 * planet.velocity.y();
        painter->drawEllipse(planet.center, planet.radius, planet.radius);
    }

    std::unordered_set<int> idsSet(toDestroy.begin(), toDestroy.end());

    planets.erase(std::remove_if(planets.begin(), planets.end(),
                                 [&idsSet](const Planet& planet) {
                                     return idsSet.find(planet.id) != idsSet.end();
                                 }), planets.end());

    toDestroy.clear();

    for (auto& planet : toCreate)
    {
       planets.push_back(planet);
    }
    painter->restore();
}

void GLWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void GLWidget::newPlanet(int mass, int radius, QPointF center, float xVelocity, float yVelocity)
{
    planets.push_back(Planet(radius, mass, center, QPointF(xVelocity,yVelocity), lastId++));
    update(); // calls paintEvent
}

