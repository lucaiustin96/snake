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
    matricelee[100][100],
    xf, yf, x, y,
    lcoada,
    lsarpeint,
    dx[] = {0, 1, 0, -1},
    dy[] = {1, 0, -1, 0},
    dist,
    capsarpeint;
struct jucatori{
    char nume[100];
    int scor = 0;
}jucatori[10];
struct sarpe{
    int x, y;
}sarpe[100],traseu[1000], sarpeintel[1000], c[1000], aux, pi, pf, ver, pnou;
char dir;

void Initializare()
{
    int i, j;
    for(i = 0;i <= height; i++)
    {
        matrice[i][0] = matrice[i][width-1] = -1;
        matricelee[i][0] = matricelee[i][width-1] = -1;
    }
    for(i = 0;i <= width; i++)
    {
        matrice[0][i] = matrice[height-1][i] = -1;
        matricelee[0][i] = matricelee[height-1][i] = -1;
    }
    x = height/2;
    y = width/2;
    lcoada = 0;
    matrice[x][y] = 2;
    matricelee[x][y] = 2;
    pi.x = rand() % height;
    pi.y = rand() % width;
    matrice[pi.x][pi.y] = 4;
    capsarpeint = 0;
}
void Lee()
{
    int prim, ultim, i, j;
    prim = ultim = 0;
    c[0] = pi;
    pf.x = xf;
    pf.y = yf;
    for(i = 0;i < height; i++)
        for(j = 0;j < width; j++)
            {
               if(matricelee[i][j] != -1)
                matricelee[i][j] = 0;
                if(matrice[i][j] == 4)
                    matrice[i][j] = 0;
            }

    while(prim <= ultim && matricelee[pf.x][pf.y] == 0)
    {
        ver = c[prim]; prim++;
        for(i = 0;i < 4; i++)
        {
            pnou.x = ver.x + dx[i];
            pnou.y = ver.y + dy[i];
            if(matricelee[pnou.x][pnou.y] == 0)
            {
                matricelee[pnou.x][pnou.y] = matricelee[ver.x][ver.y] + 1;
                ultim++; c[ultim] = pnou;
            }
        }
    }
}
void TraseuSarpeInteligent(int x, int y)
{
    int i;
    if(x != pi.x || y != pi.y)
    {
        for(i = 0;i < 4; i++)
        {
            if(matricelee[x][y] - matricelee[x - dx[i]][y-dy[i]] == 1)
            {
                TraseuSarpeInteligent(x - dx[i], y - dy[i]);
                //matrice[x - dx[i]][y - dy[i]] = 4;
                traseu[dist].x = x - dx[i];
                traseu[dist].y = y - dy[i];
                dist++;
                break;
            }
        }
    }
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
    dist = 0;
    Lee();
    TraseuSarpeInteligent(pf.x, pf.y);
    capsarpeint = 0;
}
void SarpeInteligent()
{
    int x, y, i;
    pi.x = xf;
    pi.y = yf;
    if(capsarpeint < dist)
    {
        matrice[traseu[capsarpeint].x][traseu[capsarpeint].y] = 4;
        pi.x = traseu[capsarpeint].x;
        pi.y = traseu[capsarpeint].y;
        for(i = lsarpeint; i >= 1; i--)
        {
            sarpeintel[i] = sarpeintel[i-1];
            if((sarpeintel[i-1].x > 0 && sarpeintel[i-1].x < height) && (sarpeintel[i-1].y > 0 && sarpeintel[i-1].y < width))
                matrice[sarpeintel[i-1].x][sarpeintel[i-1].y] = 4;
        }
        sarpeintel[0].x = traseu[capsarpeint].x;
        sarpeintel[0].y = traseu[capsarpeint].y;
        matrice[sarpeintel[0].x][sarpeintel[0].y] = 4;
    }
    else
    {
        matrice[xf][yf] = 0;
            lsarpeint++;
        FructNou();
    }
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
    matricelee[sarpe[0].x][sarpe[0].y] = -1;
    for(i = lcoada+1; i >= 1; i--)
    {
        sarpe[i] = sarpe[i-1];
        matrice[sarpe[i].x][sarpe[i].y] = 2;
        matricelee[sarpe[i].x][sarpe[i].y] = -1;
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
                       matricelee[i][j] = 0;
                    }
                    else if(matrice[i][j] == 3)
                        cout <<"F";
                        else if(matrice[i][j] == 4)
                        {
                            cout << "#";
                            matrice[i][j] = 0;
                        }

                            else cout << " ";
        }

    cout << '\n';
    }
}
void PanouControl()
{
    bool game = 1, viteza = 0;
    FructNou();
    while(game)
    {
        if(dir == 'x')
            game = 0;
        Input();
        Sarpe();
        SarpeInteligent();
        if(viteza == 0)
        {
            capsarpeint++;
            viteza = 1;
        }
        else viteza = 0;
        Play();
        Sleep(30);
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
