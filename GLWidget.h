#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QOpenGLFunctions>

struct Planet {
    int radius;
    int mass;
    QPointF center;
    QPointF velocity;

    int id;

    Planet(int r, int m, QPointF c, QPointF v, int i)
        : radius(r), mass(m), center(c), velocity(v), id(i) {}

    double distanceTo(const Planet& other) const {
        double dx = other.center.x() - center.x();
        double dy = other.center.y() - center.y();
        return std::sqrt(dx * dx + dy * dy);
    }
};

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget* parent);

public slots:
    void animate();
    void newPlanet(int mass, int radius, QPointF center, float xVelocity, float yVelocity);
    void clearAll();

protected:
    void initializeGL() override
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(0.11f, 0.0f, 0.76f, 1.0f);
    }

    // Sets up a QPainter for the paint() function
    void paintEvent(QPaintEvent *event) override; // Called with update()
    void paint(QPainter *painter, QPaintEvent *event);

    void paintGL() override
    {
        // Draw the scene:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClear(GL_COLOR_BUFFER_BIT);
    }

private:
    int elapsed; // Since the timer last timed out
    std::vector<Planet> planets; // Our planets

    QBrush brush;
    QPen pen;

    int lastId =0;
};

#endif // GLWIDGET_H
