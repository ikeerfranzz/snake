#define FRAME_RATE 180
#define ANCHO 20
#define ALTO 10

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "keyboard.h"

struct Position
{
    int fila;
    int columna;
};


void main()
{
    srand(time(NULL));

    char tablero[ALTO][ANCHO];
    int score = 0;
    Position posCabeza;
    posCabeza.fila = ALTO / 2;
    posCabeza.columna = ANCHO / 2;
    Position posAnteriorCabeza = posCabeza;

    std::vector<Position> cola;

    Position dirMovimiento;
    dirMovimiento.fila = 0;
    dirMovimiento.columna = 0;

    Position fruta;

    fruta.fila = rand() % ALTO;
    fruta.columna = rand() % ANCHO;
    while (fruta.fila == posCabeza.fila && fruta.columna == posCabeza.columna)
    {
        fruta.fila = rand() % ALTO;
        fruta.columna = rand() % ANCHO;
    }


    for (size_t i = 0; i < ALTO; i++)
    {
        for (size_t j = 0; j < ANCHO; j++)
        {
            tablero[i][j] = ' ';
        }
    }
    tablero[posCabeza.fila][posCabeza.columna] = 'X';
    tablero[fruta.fila][fruta.columna] = 'O';

    bool bGameOver = false;

    //While game is not over execute game loop
    while (!bGameOver)
    {
        posAnteriorCabeza = posCabeza;

        //movimiento
        if (IsWPressed() && dirMovimiento.fila == 0)
        {
            dirMovimiento.columna = 0;
            dirMovimiento.fila = -1;
        }
        if (IsAPressed() && dirMovimiento.columna == 0)
        {
            dirMovimiento.fila = 0;
            dirMovimiento.columna = -1;
        }
        if (IsSPressed() && dirMovimiento.fila == 0)
        {
            dirMovimiento.columna = 0;
            dirMovimiento.fila = 1;
        }
        if (IsDPressed() && dirMovimiento.columna == 0)
        {
            dirMovimiento.fila = 0;
            dirMovimiento.columna = 1;
        }
        // X = X0 + V
        posCabeza.fila = posCabeza.fila + dirMovimiento.fila;
        posCabeza.columna = posCabeza.columna + dirMovimiento.columna;
        tablero[posAnteriorCabeza.fila][posAnteriorCabeza.columna] = ' ';
        tablero[posCabeza.fila][posCabeza.columna] = 'X';

        //colision con muros
        if (posCabeza.fila >= ALTO || posCabeza.fila < 0 || posCabeza.columna >= ANCHO || posCabeza.columna < 0)
        {
            bGameOver = true;
            continue;
        }

        //colision con cola
        for (size_t i = 0; i < cola.size(); i++)
        {
            Position elementoCola = cola[i];
            if (posCabeza.fila == elementoCola.fila && posCabeza.columna == elementoCola.columna)
            {
                bGameOver = true;
                continue;
            }
        }

        if (fruta.fila == posCabeza.fila && fruta.columna == posCabeza.columna)
        {
            //crecer cola
            if (cola.empty())
            {
                cola.push_back(posAnteriorCabeza);
            }
            else
            {
                //cola.push_back(cola[cola.size() - 1]);
                cola.push_back(cola.back());
            }

            //respawn fruta
            fruta.fila = rand() % ALTO;
            fruta.columna = rand() % ANCHO;
            while (fruta.fila == posCabeza.fila && fruta.columna == posCabeza.columna)
            {
                fruta.fila = rand() % ALTO;
                fruta.columna = rand() % ANCHO;
            }
            tablero[fruta.fila][fruta.columna] = 'O';

            //score
            score += 15;
        }

        if (!cola.empty())
        {
            Position ultimo = cola.back();
            tablero[ultimo.fila][ultimo.columna] = ' ';
            for (size_t i = cola.size() - 1; i > 0; i--)
            {
                cola[i] = cola[i - 1];

            }
            cola[0] = posAnteriorCabeza;
        }

        for (size_t i = 0; i < cola.size(); i++)
        {
            Position p = cola[i];
            tablero[p.fila][p.columna] = 'x';
        }

        score += 1 * cola.size();


        //print
        std::cout << "Score: " << score << std::endl;
        for (size_t i = 0; i < ANCHO + 2; i++)
        {
            std::cout << '-';
        }
        std::cout << std::endl;
        for (size_t i = 0; i < ALTO; i++)
        {
            std::cout << '|';
            for (size_t j = 0; j < ANCHO; j++)
            {
                std::cout << tablero[i][j];
            }
            std::cout << '|';
            std::cout << std::endl;
        }
        for (size_t i = 0; i < ANCHO + 2; i++)
        {
            std::cout << '-';
        }

        //Sleep main thread to control game speed execution
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));
        system("cls");

    }

    std::cout << "GAME OVER!" << std::endl;
    std::cout << "Score: " << score << std::endl;

}