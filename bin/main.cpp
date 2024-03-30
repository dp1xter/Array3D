#include "Array3D.h"

int main() {
    Array3D mas = Array3D(10, 10, 10);
    Array3D mas1 = Array3D(10, 10, 10);
    mas[0][0][0] = 30;
    std::cout << mas[0][0][0];
}