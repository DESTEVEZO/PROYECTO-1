#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen() {
    system("cls");
}

bool isKeyPressed(int key) {
    return GetAsyncKeyState(key) & 0x8000;
}



void moveCursorCircular(int& x, int& y, int consoleWidth, int consoleHeight) {


    if (x > consoleWidth) {
        x = 0;
    }

    else if (x < 0) {
        x = consoleWidth;
    }

    if (y > consoleHeight) {
        y = 0;
    }

    else if (y < 0) {
        y = consoleHeight;
    }
}



//DIBUJAR TRIANGULO

void drawTriangle(int x, int y, int base) {

    int height = base / 2 + 1;
    int width = base;
    // Calcular la posición inicial para centrar el triángulo horizontalmente
    int startX = x - (width / 2);
    for (int i = 0; i < width; ++i) {
        gotoxy(startX + i, y);
        cout << "*";
    }
    gotoxy(x, y - height + 1);
    cout << "*"; //
    for (int i = 1; i < height - 1; ++i) {
        gotoxy(startX + i, y - i);
        cout << "*";
        gotoxy(startX + width - i - 1, y - i);
        cout << "*";
    }
}

// DIBUJAR CUADRO

void drawSquare(int x, int y, int size) {

    for (int i = 0; i < size; ++i) {
        gotoxy(x + i, y);
        cout << "*";
        gotoxy(x + i, y + size - 1);
        cout << "*";
    }
    for (int i = 1; i < size - 1; ++i) {
        gotoxy(x, y + i);
        cout << "*";
        gotoxy(x + size - 1, y + i);
        cout << "*";
    }
}

//DIBUJAR RECTANGULO

void drawRectangle(int x, int y, int width, int height) {

    for (int i = 0; i < width; ++i) {
        gotoxy(x + i, y);
        cout << "*";
        gotoxy(x + i, y + height - 1);
        cout << "*";
    }
    for (int i = 1; i < height - 1; ++i) {
        gotoxy(x, y + i);
        cout << "*";
        gotoxy(x + width - 1, y + i);
        cout << "*";
    }
}

// DIBUJAR CIRCULO

void drawCircle(int x, int y, int radius) {

    for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
            if (abs(i * i + j * j - radius * radius) < radius) {
                gotoxy(x + i, y + j);
                cout << "*";
            }
        }
    }
}

//CONSOLA

int main() {

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;


    int centerX = consoleWidth / 2;
    int centerY = consoleHeight / 2;

    int x = centerX;
    int y = centerY;
    char keyPressed;
    char previousChar = ' ';

    cout << "Mueva el cursor con las flechas del teclado." << endl;
    cout << "Presione F12 para mostrar el menu de figuras." << endl;
    cout << "Presione Esc para salir del programa." << endl;
    cout << endl;

    do {

        gotoxy(x, y);
        cout << previousChar;

//CAPTURA DE TECLAS

        if (_kbhit()) {
            keyPressed = _getch();
            switch (keyPressed) {
                case 72:
                    previousChar = ' ';
                    y -= 1;
                    break;
                case 80:
                    previousChar = ' ';
                    y += 1;
                    break;
                case 75:
                    previousChar = ' ';
                    x -= 1;
                    break;
                case 77:
                    previousChar = ' ';
                    x += 1;
                    break;
            }

        //PANTALLA


            moveCursorCircular(x, y, consoleWidth, consoleHeight);
        }


        gotoxy(x, y);
        cout << ".";




        if (isKeyPressed(VK_F12)) {
            int figureOption;
            clearScreen();
            cout << "MENU" << endl;
            cout << "1. Triangulo" << endl;
            cout << "2. Cuadrado" << endl;
            cout << "3. Rectangulo" << endl;
            cout << "4. Circulo" << endl;
            cout << "Seleccione una opcion: ";
            cin >> figureOption;

            switch (figureOption) {
                case 1:
                    clearScreen();
                    cout << "Ingrese el tamaño de la base del triangulo: ";
                    int base;
                    cin >> base;
                    drawTriangle(x, y, base);
                    break;
                case 2:
                    clearScreen();
                    cout << "Ingrese el tamaño del cuadrado: ";
                    int squareSize;
                    cin >> squareSize;
                    drawSquare(x, y, squareSize);
                    break;
                case 3:
                    clearScreen();
                    cout << "Ingrese el tamaño de la base del rectangulo: ";
                    int rectWidth, rectHeight;
                    cin >> rectWidth;
                    cout << "Ingrese la altura del rectangulo: ";
                    cin >> rectHeight;
                    drawRectangle(x, y, rectWidth, rectHeight);
                    break;
                case 4:
                    clearScreen();
                    cout << "Ingrese el tamaño del radio del circulo: ";
                    int circleRadius;
                    cin >> circleRadius;
                    drawCircle(x, y, circleRadius);
                    break;
                default:
                    break;
            }
        }

        Sleep(30);
    } while (keyPressed != 27);
    return 0;
}
