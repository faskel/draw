#include <iostream>
#include <GL/freeglut.h>
#include <vector>
using  namespace std;

class Drawable {
public:
    virtual void draw()=0;

    virtual string show()=0;
};

class Point : public Drawable {
    float x;
    float y;
public:
    string show() override {
        string s;
        s="<objects>\n";
        s+="    <point name=\"Point\" >";
        s+="        <pos x=";s+=x;s+=">";
        s+="    </point>";
        s+="<objects>";
        return s;
    }

    void draw() override {
        glPointSize(10.0f);
        glColor3f(1,1,0);
        glBegin(GL_POINTS);
        glVertex3f(x,y,-5.0f);
        glEnd();
    }

    Point(float x, float y) : x(x), y(y) {}

    Point() {
        x = 0;
        y = 0;
    }

    float getX() const {
        return x;
    }

    void setX(int x) {
        Point::x = x;
    }

    float getY() const {
        return y;
    }

    void setY(int y) {
        Point::y = y;
    }
};

class Square : public Drawable {
    float x;
    float y;
    float w;
    float h;
public:
    string show() override {
        string s;
        s="<objects>\n";
        s+="    <point name=\"Sqare\" >";
        s+="        <pos x=";s+=x;s+=">";
        s+="    </point>";
        s+="<objects>";
        return s;
    }

    void draw() override {
        glColor3f(1,0,0);
        glBegin(GL_QUADS);
        glVertex3f(x,y,-5.0f);
        glVertex3f(x+w,y,-5.0f);
        glVertex3f(x+w,y+h,-5.0f);
        glVertex3f(x,y+h,-5.0f);
        glEnd();
    }

    Square(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

    Square() {
        x = 0;
        y = 0;
        w = 0;
        h = 0;
    }

    float getX() const {
        return x;
    }

    void setX(int x) {
        Square::x = x;
    }

    float getY() const {
        return y;
    }

    void setY(int y) {
        Square::y = y;
    }

    float getW() const {
        return w;
    }

    void setW(int w) {
        Square::w = w;
    }

    float getH() const {
        return h;
    }

    void setH(int h) {
        Square::h = h;
    }

};

vector<Drawable*> *objects;


void changeSize(int w, int h) {
    // предупредим деление на ноль
    // если окно сильно перетянуто будет
    if(h == 0)
        h = 1;
    float ratio = static_cast<float>(1.0 * w / h);

    // используем матрицу проекции
    glMatrixMode(GL_PROJECTION);

    // Reset матрицы
    glLoadIdentity();

    // определяем окно просмотра
    glViewport(0, 0, w, h);

    // установить корректную перспективу.
    gluPerspective(45,ratio,1,1000);

    // вернуться к модели
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    for (auto &object : *objects)
        object->draw();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    objects=new vector<Drawable*>();
    Drawable *s=new Square(0,0,2,2);
    Drawable *s2=new Square(-1,-1,1,1);
    Drawable *p=new Point(-0.5f,-0.5f);
    Drawable *p2=new Point(-0.3f,-0.3f);
    objects->push_back(s);
    objects->push_back(s2);
    objects->push_back(p);
    objects->push_back(p2);
    // инициализация
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("Урок 2");

    // регистрация
    glutDisplayFunc(renderScene);

    // Новая функция изменения размеров окна
    glutReshapeFunc(changeSize);

    // основной цикл
    glutMainLoop();
}