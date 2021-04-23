#include <iostream>
#include <math.h>

struct Point
{
    Point(double X, double Y) : x(X), y(Y){};
    double x;
    double y;
}; //Simple Point structure

int main()
{
    double mi, ro,ni ;
    int i;
    ;
    const double PI = 3.14159;
    std::cout << "input: centro x | centro y | radio | indice de vertice de inicio" << std::endl;
    std::cin >> mi >> ni >> ro >> i;
    Point Autor(mi, ni);
    std::cout << "COPIAR A PARTIR DE AQUI\n"
              << std::endl;
    std::cout << mi << "f, " << ni << "f, "
              << "0.0f, // " << i << std::endl;
    i++;
    for (double angle = 0, j = i; angle <= 2 * PI; angle += 0.1, j++)
        std::cout << (Autor.x + ro * cos(angle)) << "f, " << (Autor.y + ro * sin(angle)) << "f, "
                  << "0.0f, // " << j << std::endl;
    int q = i + 62;
    for (int j = i; j < q; j++)
    {
        std::cout << i - 1 << ", " << j << ", " << j + 1 << "," << std::endl;
    }
    std::cout << i - 1 << ", " << q << ", " << i << "," << std::endl;
}