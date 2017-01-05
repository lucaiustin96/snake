#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;
fstream file("tabel.txt", std::fstream::in | std::fstream::out | std::fstream::app);
int height = 25,
    width = 40,
    matrice[100][100],
    xf, yf, x, y,
    lcoada;
struct jucatori{
    char nume[100];
    int scor = 0;
}jucatori[10];
struct sarpe{
    int x, y;
}sarpe[100], aux;
char dir;
void Initializare()
{
    int i, j;
    for(i = 0;i <= height; i++)
        matrice[i][0] = matrice[i][width-1] = -1;
    for(i = 0;i <= width; i++)
        matrice[0][i] = matrice[height-1][i] = -1;
    x = height/2;
    y = width/2;
    lcoada = 0;
    matrice[x][y] = 2;
}
void FructNou()
{
    int i;
    xf = rand() % height;
    yf = rand() % width;
    if(xf == 0 || xf == height)
        xf = rand() % height;
    if(yf == 0 || yf == width)
        yf = rand() % width;
    for(i = 0; i < lcoada; i++)
    {
        if(xf == sarpe[i].x && yf == sarpe[i].y)
        {
            xf = rand() % height;
            yf = rand() % width;
        }
    }
    matrice[xf][yf] = 3;
}
void Sarpe()
{
    int i;
    switch(dir)
    {
        case 'w':
            x--;
        break;
        case 'd':
            y++;
        break;
        case 's':
            x++;
        break;
        case 'a':
            y--;
        break;
    }
    sarpe[0].x = x;
    sarpe[0].y = y;
    matrice[sarpe[0].x][sarpe[0].y] = 2;
    for(i = lcoada+1; i >= 1; i--)
    {
        sarpe[i] = sarpe[i-1];
        matrice[sarpe[i].x][sarpe[i].y] = 2;
    }
    if(xf == x && yf == y)
    {
        FructNou();
        lcoada++;
    }
}
void Input()
{
    if(_kbhit())
        dir = _getch();
}
void Play()
{
    int i, j;
    for(i = 0;i < height; i++)
    {
        for(j = 0;j < width; j++)
        {
            if(matrice[i][j] == -1)
                cout <<"#";
                else if(matrice[i][j] == 2)
                    {
                       cout <<"O";
                       matrice[i][j] = 0;
                    }
                    else if(matrice[i][j] == 3)
                        cout <<"F";
                        else cout << " ";
        }

    cout << '\n';
    }
}
void PanouControl()
{
    bool game = 1;
    FructNou();
    while(game)
    {
        if(dir == 'x')
            game = 0;
        Input();
        Sarpe();
        Play();
        Sleep(50);
        system("cls");
    }
}
void AfiseazaJucatori()
{
    file.seekg (0, ios::beg);
    int i = 0;
    while(file.getline(jucatori[i].nume, 100))
    {
        cout << i+1 << ". " << jucatori[i].nume << '\n';
        i++;
    }
}
void UtilizatorNou(int scor)
{
    char nume[100];
    int nrjucatori = 0, i;
    cin.get(nume, 100);
    file << nume << '\n';
}
int main()
{
    Initializare();
    PanouControl();
    return 0;
}
