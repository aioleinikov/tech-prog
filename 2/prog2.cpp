#include <iostream>
#include <cstdlib>
#include <ctime>

class Vect {
private:
    int dim;
    double* b;
    static int count;

public:
    Vect(int d) : dim(d), b(new double[d]) { count++; }
    Vect(const Vect& other) : dim(other.dim), b(new double[other.dim]) {
        for (int i = 0; i < dim; ++i) {
            b[i] = other.b[i];
        }
        count++;
    }
    ~Vect() { delete[] b; count--; }

    int getDim() const { return dim; }
    double* getData() const { return b; }
    int getNum() const { return count; }

    void display() const {
        for (int i = 0; i < dim; ++i) {
            std::cout << b[i] << " ";
        }
        std::cout << std::endl;
    }

    Vect& operator=(const Vect& other) {
        if (this == &other) return *this;
        if (dim != other.dim) {
            delete[] b;
            dim = other.dim;
            b = new double[dim];
        }
        for (int i = 0; i < dim; ++i) {
            b[i] = other.b[i];
        }
        return *this;
    }

    Vect operator-() const {
        Vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = -b[i];
        }
        return result;
    }

    Vect operator+(const Vect& v) const {
        Vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = b[i] + v.b[i];
        }
        return result;
    }

    Vect operator-(const Vect& v) const {
        Vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = b[i] - v.b[i];
        }
        return result;
    }

    double operator*(const Vect& v) const {
        double result = 0;
        for (int i = 0; i < dim; ++i) {
            result += b[i] * v.b[i];
        }
        return result;
    }

    friend Vect operator*(double k, const Vect& v);
};

int Vect::count = 0;

Vect operator*(double k, const Vect& v) {
    Vect result(v.getDim());
    for (int i = 0; i < v.getDim(); ++i) {
        result.getData()[i] = k * v.getData()[i];
    }
    return result;
}

Vect operator*(const Vect& v, double k) {
    return k * v;
}

class Matr {
private:
    int dim;
    double** a;
    static int count;

public:
    Matr(int d) : dim(d), a(new double*[d]) {
        for (int i = 0; i < d; ++i) {
            a[i] = new double[d];
        }
        count++;
    }

    Matr(const Matr& other) : dim(other.dim), a(new double*[other.dim]) {
        for (int i = 0; i < dim; ++i) {
            a[i] = new double[dim];
            for (int j = 0; j < dim; ++j) {
                a[i][j] = other.a[i][j];
            }
        }
        count++;
    }

    ~Matr() {
        for (int i = 0; i < dim; ++i) {
            delete[] a[i];
        }
        delete[] a;
        count--;
    }

    int getDim() const { return dim; }
    double** getData() const { return a; }
    int getNum() const { return count; }

    void display() const {
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                std::cout << a[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    Matr& operator=(const Matr& other) {
        if (this == &other) return *this;
        if (dim != other.dim) {
            for (int i = 0; i < dim; ++i) {
                delete[] a[i];
            }
            delete[] a;
            dim = other.dim;
            a = new double*[dim];
            for (int i = 0; i < dim; ++i) {
                a[i] = new double[dim];
            }
        }
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                a[i][j] = other.a[i][j];
            }
        }
        return *this;
    }

    Matr operator-() const {
        Matr result(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                result.a[i][j] = -a[i][j];
            }
        }
        return result;
    }

    Matr operator+(const Matr& m) const {
        Matr result(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                result.a[i][j] = a[i][j] + m.a[i][j];
            }
        }
        return result;
    }

    Matr operator-(const Matr& m) const {
        Matr result(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                result.a[i][j] = a[i][j] - m.a[i][j];
            }
        }
        return result;
    }

    friend Matr operator*(double k, const Matr& m);
    friend Matr operator*(const Matr& m, double k);
    friend Matr operator*(const Matr& m1, const Matr& m2);
    friend Vect operator*(const Matr& m, const Vect& v);
};

int Matr::count = 0;

Matr operator*(double k, const Matr& m) {
    Matr result(m.dim);
    for (int i = 0; i < m.dim; ++i) {
        for (int j = 0; j < m.dim; ++j) {
            result.a[i][j] = k * m.a[i][j];
        }
    }
    return result;
}

Matr operator*(const Matr& m, double k) {
    return k * m;
}

Matr operator*(const Matr& m1, const Matr& m2) {
    if (m1.dim != m2.dim) {
        std::cerr << "Ошибка: Несовпадение размерностей для умножения матриц\n";
        exit(1);
    }

    Matr result(m1.dim);
    for (int i = 0; i < m1.dim; ++i) {
        for (int j = 0; j < m1.dim; ++j) {
            result.a[i][j] = 0;
            for (int k = 0; k < m1.dim; ++k) {
                result.a[i][j] += m1.a[i][k] * m2.a[k][j];
            }
        }
    }
    return result;
}

Vect operator*(const Matr& m, const Vect& v) {
    if (m.getDim() != v.getDim()) {
        std::cerr << "Ошибка: Несовпадение размерностей для умножения матрицы на вектор\n";
        exit(1);
    }

    Vect result(v.getDim());
    for (int i = 0; i < m.getDim(); ++i) {
        result.getData()[i] = 0;
        for (int j = 0; j < m.getDim(); ++j) {
            result.getData()[i] += m.getData()[i][j] * v.getData()[j];
        }
    }
    return result;
}

// Функция для генерации случайных чисел в диапазоне от min до max (включительно)
int getRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(nullptr)); // Инициализация генератора случайных чисел

    int dim;
    std::cout << "Введите размерность векторов и матриц: ";
    std::cin >> dim;

    // Создание и заполнение первого вектора случайными не нулевыми элементами
    Vect v1(dim);
    for (int i = 0; i < dim; ++i) {
        v1.getData()[i] = getRandom(0, 100);
    }

    // Создание и заполнение второго вектора случайными элементами
    Vect v2(dim);
    for (int i = 0; i < dim; ++i) {
        v2.getData()[i] = getRandom(0, 100);
    }

    // Создание и заполнение первой матрицы случайными элементами
    Matr m1(dim);
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            m1.getData()[i][j] = getRandom(0, 100);
        }
    }

    // Создание и заполнение второй матрицы случайными элементами
    Matr m2(dim);
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            m2.getData()[i][j] = getRandom(0, 100);
        }
    }

    // Вывод первого вектора и первой матрицы
    std::cout << "Сгенерированный первый вектор:" << std::endl;
    v1.display();
    std::cout << "Сгенерированный второй вектор:" << std::endl;
    v2.display();
    
    double scalar;
    std::cout << "Введите скаляр: ";
    std::cin >> scalar;
    Vect v_scalar_mul = v1 * scalar;
    std::cout << "Умножение вектора на скаляр: ";
    v_scalar_mul.display();
    
    double dot_product = v1 * v2;
    std::cout << "Скалярное произведение векторов: " << dot_product << std::endl;
    Vect v3 = -v1;
    Vect v4(dim);
    v4 = v1;
    std::cout << "Унарный минус вектора: ";
    v3.display();
    std::cout << "Присваивание первого вектора: ";
    v4.display();
    
    std::cout << "Сгенерированная первая матрица:" << std::endl;
    m1.display();
    std::cout << "Сгенерированная вторая матрица:" << std::endl;
    m2.display();
    
    Matr m_diff = m1 - m2;
    Matr m_scalar_mul = m1 * scalar;
    Matr m_product = m1 * m2;
    Matr m3 = -m1;
    Matr m4(dim);
    m4 = m1;

    std::cout << "Разность матриц: ";
    m_diff.display();
    std::cout << "Умножение матрицы на скаляр: ";
    m_scalar_mul.display();
    std::cout << "Произведение матриц: ";
    m_product.display();
    std::cout << "Унарный минус матрицы: ";
    m3.display();
    std::cout << "Присваивание первой матрицы второй: ";
    m4.display();

    Vect v5 = m1 * v1;
    std::cout << "Произведение матрицы на вектор: ";
    v5.display();

    return 0;
}


