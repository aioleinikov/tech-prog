#include <iostream>
#include <cmath>
#include <vector>
#include <memory> // Для std::unique_ptr и std::make_unique

using namespace std;

// Абстрактный класс "Точка"
class Point {
protected:
    double x, y;

public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    virtual void draw() const = 0;
    virtual void erase() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;

    virtual ~Point() = default;
};

// Класс "Линия"
class Line : public Point {
protected:
    double x2, y2;

public:
    Line(double x1, double y1, double x2, double y2)
        : Point(x1, y1), x2(x2), y2(y2) {}

    void draw() const override {
        cout << "Рисуем Линию от (" << x << ", " << y << ") до (" << x2 << ", " << y2 << ")\n";
    }

    void erase() const override {
        cout << "Стираем Линию\n";
    }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
        x2 += dx;
        y2 += dy;
    }

    void rotate(double angle) override {
        double rad = angle * M_PI / 180.0;
        double newX2 = x + (x2 - x) * cos(rad) - (y2 - y) * sin(rad);
        double newY2 = y + (x2 - x) * sin(rad) + (y2 - y) * cos(rad);
        x2 = newX2;
        y2 = newY2;
    }
};

// Класс "Параллелограмм" с виртуальным наследованием
class Parallelogram : public virtual Point {
protected:
    double side1, side2;
    double angle; // В градусах

public:
    Parallelogram(double x, double y, double side1, double side2, double angle)
        : Point(x, y), side1(side1), side2(side2), angle(angle) {}

    void draw() const override {
        cout << "Рисуем Параллелограмм в точке (" << x << ", " << y << ") со сторонами " << side1 << " и " << side2 << " и углом " << angle << "\n";
    }

    void erase() const override {
        cout << "Стираем Параллелограмм\n";
    }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override {
        this->angle += angle;
    }
};

// Класс "Квадрат", наследующий от "Параллелограмма"
class Square : public Parallelogram {
public:
    Square(double x, double y, double side)
        : Parallelogram(x, y, side, side, 90) {}

    void draw() const override {
        cout << "Рисуем Квадрат в точке (" << x << ", " << y << ") со стороной " << side1 << "\n";
    }

    void erase() const override {
        cout << "Стираем Квадрат\n";
    }
};

// Класс "Ромб"
class Rhombus : public virtual Point {
protected:
    double diagonal1, diagonal2;

public:
    Rhombus(double x, double y, double diagonal1, double diagonal2)
        : Point(x, y), diagonal1(diagonal1), diagonal2(diagonal2) {}

    void draw() const override {
        cout << "Рисуем Ромб в точке (" << x << ", " << y << ") с диагоналями " << diagonal1 << ", " << diagonal2 << "\n";
    }

    void erase() const override {
        cout << "Стираем Ромб\n";
    }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override {
        // Поворот ромба вокруг его центра не меняет его вид, так что метод может остаться пустым
    }
};

// Класс "Прямоугольник"
class Rectangle : public Parallelogram {
public:
    Rectangle(double x, double y, double width, double height)
        : Parallelogram(x, y, width, height, 90) {}

    void draw() const override {
        cout << "Рисуем Прямоугольник в точке (" << x << ", " << y << ") с шириной " << side1 << " и высотой " << side2 << "\n";
    }

    void erase() const override {
        cout << "Стираем Прямоугольник\n";
    }
};

void displayMenu() {
    cout << "Выберите фигуру:\n";
    cout << "1. Линия\n";
    cout << "2. Квадрат\n";
    cout << "3. Прямоугольник\n";
    cout << "4. Параллелограмм\n";
    cout << "5. Ромб\n";
    cout << "0. Выход\n";
}

void displayActionMenu() {
    cout << "Выберите действие:\n";
    cout << "1. Нарисовать\n";
    cout << "2. Стереть\n";
    cout << "3. Передвинуть\n";
    cout << "4. Повернуть\n";
    cout << "0. Назад\n";
}

int main() {
    vector<unique_ptr<Point>> shapes;

    while (true) {
        displayMenu();
        int shapeChoice;
        cin >> shapeChoice;

        if (shapeChoice == 0) break;

        unique_ptr<Point> shape;
        switch (shapeChoice) {
            case 1: {
                double x1, y1, x2, y2;
                cout << "Введите координаты начала и конца линии (x1 y1 x2 y2): ";
                cin >> x1 >> y1 >> x2 >> y2;
                shape = unique_ptr<Point>(new Line(x1, y1, x2, y2));
                break;
            }
            case 2: {
                double x, y, side;
                cout << "Введите координаты левого нижнего угла и сторону квадрата (x y side): ";
                cin >> x >> y >> side;
                shape = unique_ptr<Point>(new Square(x, y, side));
                break;
            }
            case 3: {
                double x, y, width, height;
                cout << "Введите координаты левого нижнего угла, ширину и высоту прямоугольника (x y width height): ";
                cin >> x >> y >> width >> height;
                shape = unique_ptr<Point>(new Rectangle(x, y, width, height));
                break;
            }
            case 4: {
                double x, y, side1, side2, angle;
                cout << "Введите координаты левого нижнего угла, стороны и угол параллелограмма (x y side1 side2 angle): ";
                cin >> x >> y >> side1 >> side2 >> angle;
                shape = unique_ptr<Point>(new Parallelogram(x, y, side1, side2, angle));
                break;
            }
            case 5: {
                double x, y, diagonal1, diagonal2;
                cout << "Введите координаты центра и диагонали ромба (x y diagonal1 diagonal2): ";
                cin >> x >> y >> diagonal1 >> diagonal2;
                shape = unique_ptr<Point>(new Rhombus(x, y, diagonal1, diagonal2));
                break;
            }
            default:
                cout << "Неправильный выбор. Попробуйте еще раз.\n";
                continue;
        }

        while (true) {
            displayActionMenu();
            int actionChoice;
            cin >> actionChoice;

            if (actionChoice == 0) break;

            switch (actionChoice) {
                case 1:
                    shape->draw();
                    break;
                case 2:
                    shape->erase();
                    break;
                case 3: {
                    double dx, dy;
                    cout << "Введите смещение по x и y (dx dy): ";
                    cin >> dx >> dy;
                    shape->move(dx, dy);
                    break;
                }
                case 4: {
                    double angle;
                    cout << "Введите угол поворота: ";
                    cin >> angle;
                    shape->rotate(angle);
                    break;
                }
                default:
                    cout << "Неправильный выбор. Попробуйте еще раз.\n";
                    continue;
            }
        }
    }

    cout << "Программа завершена.\n";
    return 0;
}

