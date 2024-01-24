#include <iostream>
#include "SFML\Graphics.hpp"
#include <math.h>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include <vector>
#include <float.h>
using namespace sf;
using namespace std;

RenderWindow window(sf::VideoMode(1000, 1000), "SAT?");
Vector2f operator/(Vector2f b, float a)
{
    Vector2f c;
    c.x = b.x / a;
    c.y = b.y / a;
    return c;
}
Vector2f operator/(Vector2f a, Vector2f b)
{
    Vector2f c;
    c.x = a.x / b.x;
    c.y = a.y / b.x;
    return c;
}
Vector2f operator*(Vector2f a, Vector2f b)
{
    Vector2f c;
    c.x = b.x * a.x;
    c.y = b.y * a.y;
    return c;
}
Vector2f operator/=(Vector2f a, float b)
{
    Vector2f c;
    c.x = a.x / b;
    c.y = a.y / b;
    return c;
}
Vector2f operator-(Vector2f a, float b)
{
    Vector2f c;
    c.x = a.x - b;
    c.y = a.y - b;
    return c;
}
Vector2f operator*(Vector2f a, float b)
{
    Vector2f c;
    c.x = a.x * b;
    c.y = a.y * b;
    return c;
}

ostream& operator<<(ostream& o, Vector2f b)
{
    o << b.x << " " << b.y << "\n";
    return o;
}
ostream& operator << (ostream& o, Vector2f c[100])
{

    for (int i = 0; i < 100; i++)
    {
        o << c[i].x << " " << c[i].y << " ";
    }
    o << "\n";
    return o;
}
float dot(Vector2f vec, Vector2f vec2)
{
    float d = vec.x * vec2.x + vec.y * vec2.y;
    return d;
};
float mag(Vector2f vec)
{
    float m = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
    return m;
};
Vector2f norm(Vector2f vec)
{
    Vector2f v;
    v.x = vec.x;
    v.y = vec.y;
    v.x = v.x / mag(vec);
    v.y = v.y / mag(vec);
    return v;
};
Vector2f cross(Vector2f a, Vector2f b)
{
    // a.x a.y
    // b.x b.y
    Vector2f c;
    c.x = a.x * b.y - b.x * a.y;
    return c;
};
Vector2f matmul(Vector2f vec, float mat[2][2])
{
    Vector2f vec2;
    vec2.x = vec.x * mat[0][0] + vec.y * mat[0][1];
    vec2.y = vec.y * mat[1][0] + vec.y * mat[1][1];
    return vec2;
};

Vector2f proj(Vector2f a, Vector2f b)
{
    Vector2f p = b * (dot(a, b) / pow(mag(b), 2));
    return p;

}
class polygon
{
public:

};





void setVertices(Vector2f& vertex0, Vector2f& vertex1, Vector2f shapePositions[4], Vector2f shapePositions2[4], int a, Vector2f& side, Vector2f& direction, Vector2f origin, Vector2f origin2, Vector2f& determinedOrigin)
{
    if (a < 4)
    {
        vertex0 = shapePositions[a];
        determinedOrigin = origin;
    }
    else
    {
        vertex0 = shapePositions2[a - 4];
        determinedOrigin = origin2;
    }
    if (a == 3)
    {
        vertex1 = shapePositions[0];
    }
    if (a == 7)
    {
        vertex1 = shapePositions2[0];
    }

    if (a < 3)
    {
        vertex1 = shapePositions[a + 1];
    }
    if (a != 7 && a > 3)
    {
        vertex1 = shapePositions2[a - 3];
    }

    side = vertex0 + (vertex1 - vertex0) / 2;
    direction = side - determinedOrigin;

}
bool collide()
{
    Vector2f shapePositions[4] = { Vector2f(100,100),Vector2f(100,200), Vector2f(200,200), Vector2f(200,100) };
    Vector2f shapePositions2[4] = { Vector2f(150,150),Vector2f(150,250), Vector2f(250,250), Vector2f(250,150) };
    Vector2f origin(150, 150);
    Vector2f origin2(200, 200);
    Vector2f projectionArray[4];
    Vector2f projectionArray2[4];
    VertexArray VertexShape(LinesStrip, 5);
    VertexArray VertexShape2(LinesStrip, 5);
    VertexShape[0].position = shapePositions[0];
    VertexShape[1].position = shapePositions[1];
    VertexShape[2].position = shapePositions[2];
    VertexShape[3].position = shapePositions[3];
    VertexShape[4].position = shapePositions[0];
    VertexShape2[0].position = shapePositions2[0];
    VertexShape2[1].position = shapePositions2[1];
    VertexShape2[2].position = shapePositions2[2];
    VertexShape2[3].position = shapePositions2[3];
    VertexShape2[4].position = shapePositions2[0];
    for (int a = 0; a < 1; a++)
    {
        
        
        Vector2f determinedOrigin;
        Vector2f vertex0;
        Vector2f vertex1;
        Vector2f vertexSide;
        Vector2f vertexDirection;
        setVertices(vertex0, vertex1, shapePositions, shapePositions2, a, vertexSide, vertexDirection, origin, origin2, determinedOrigin);
       
       
       
        Vector2f vertexUnitDirection = norm(vertexDirection);
        Vector2f vertexIntersection = determinedOrigin + vertexUnitDirection * 100;
        Vector2f vertexNIntersection = determinedOrigin + vertexUnitDirection * -100;
        for (int b = 0; b < 8; b++)
        {
            CircleShape vertexPoints;
            VertexArray vertexInterLine(LineStrip,2);
            VertexArray vertexProjLine(LineStrip,2);

            Vector2f determinedOrigin0;
            Vector2f vertex00;
            Vector2f vertex10;
            Vector2f vertexSide0;
            Vector2f vertexDirection0;
            setVertices(vertex00, vertex10, shapePositions, shapePositions2, b, vertexSide0, vertexDirection0, origin, origin2, determinedOrigin0);
            Vector2f vertexProjection0 = proj(vertex00 - vertexNIntersection, vertexIntersection - vertexNIntersection);
            vertexPoints.setRadius(10);
            vertexPoints.setOrigin(Vector2f(10, 10));
            vertexPoints.setPosition(vertexProjection0 + vertexNIntersection);

            vertexInterLine[0].position = vertexNIntersection;
            vertexInterLine[1].position = vertexIntersection;
            vertexInterLine[0].color = Color::Red;
            vertexInterLine[1].color = Color::Red;

            vertexProjLine[0].position = vertex00;
            vertexProjLine[1].position = vertexProjection0 + vertexNIntersection;
            vertexProjLine[0].color = Color::Green;
            vertexProjLine[1].color = Color::Green;


            //window.draw(vertexPoints);
            //window.draw(vertexInterLine);
            //window.draw(vertexProjLine);
        }
        

    }
    window.draw(VertexShape);
    window.draw(VertexShape2);
    return true;
}
void checkMSC(Vector2f vertexShape[4],Vector2f originPosition,Vector2f mousePosition)
{
float avgShapeDistance = 0;
float mouseShapeDistance = 0;
for (int i = 0; i < 4; i++)
{
    float xDist = abs(vertexShape[i].x - originPosition.x);
    float yDist = abs(vertexShape[i].y - originPosition.y);
    float mxDist = abs(vertexShape[i].x - mousePosition.x);
    float myDist = abs(vertexShape[i].y - mousePosition.y);
    avgShapeDistance += (xDist + yDist);
    mouseShapeDistance += (mxDist + myDist);
}
if (avgShapeDistance == mouseShapeDistance)
{
    //cout << "yaya\n";
}
};
// return Math.sqrt(1 - Math.pow(x - 1, 2));
float ease(float x)
{
    return 1 - pow(1 - x, 3);
}
void positionEase(Vector2f start, Vector2f finish,  Clock clock, float duration)
{
    Time time = clock.getElapsedTime() / duration;
    float timeElapsed = time.asSeconds();
    if (timeElapsed < 1)
    {
        window.setPosition(Vector2i(start.x + (finish.x - start.x) * ease(timeElapsed),start.y + finish.y * ease(timeElapsed)));

    }
}
void sizeEase(Vector2f start, Vector2f finish, Clock clock, float duration)
{
    Time time = clock.getElapsedTime() / duration;
    float timeElapsed = time.asSeconds();
    if (timeElapsed < 1)
    {
        //window.setSize(Vector2f(start.x + finish.x * ease(timeElapsed), start.y + finish.y * ease(timeElapsed)));
        window.setSize(Vector2u(start.x + (finish.x - start.x) * ease(timeElapsed), start.y + finish.y * ease(timeElapsed)));
    }
}
int main()
{
   
    window.setFramerateLimit(100);
    Vector2f vertexPositions[4] = {Vector2f(450,450), Vector2f(450,550), Vector2f(550,550), Vector2f(550,450)};

    Vector2f originPosition = Vector2f(500, 500);
    bool mousePressed = false;
    Clock deltaClock;
    Clock clock;
    Time currentTime;
    float easingTime = 0;
    RectangleShape rectangle;
    rectangle.setSize(Vector2f(200, 100));
    rectangle.setPosition(500, 500);
    rectangle.setOrigin(100, 50);
    rectangle.setFillColor(Color::Red);
    Sleep(3000);
    clock.restart();
    while (window.isOpen())
    {
        
        
        currentTime = deltaClock.restart();
        cout << currentTime.asSeconds() * 50 << "\n";

        sf::Event evnt;

        
        while (window.pollEvent(evnt))
        {

            if (evnt.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (evnt.type == Event::MouseButtonReleased)
        {
            mousePressed = false;
        }
        
        Vector2f mousePosition = Vector2f(Mouse::getPosition().x, Mouse::getPosition().y);
        positionEase(Vector2f(500,800), Vector2f(0,500), clock, 2);
        sizeEase(Vector2f(0, 0), Vector2f(300, 700), clock, 2);
        window.clear();
        window.draw(rectangle);
        window.display();
    
      
    }
    return 0;
}