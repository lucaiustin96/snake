#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
fstream file("tabel.txt", std::fstream::in | std::fstream::out | std::fstream::app);
int height = 20,
    width = 40,
    matrice[100][100];
struct jucatori{
    char nume[100];
    int scor = 0;
}jucatori[10];
void Initializare()
{
    int i, j;
    for(i = 0;i <= height; i++)
        matrice[i][0] = matrice[i][width-1] = -1;
    for(i = 0;i <= width; i++)
        matrice[0][i] = matrice[height-1][i] = -1;
}
void Play()
{
    int i, j;
    cout << "JOC NOU(N) | CLASAMENT(C)"<<'\n';
    for(i = 0;i < height; i++)
    {
        for(j = 0;j < width; j++)
            if(matrice[i][j] == -1)
                cout <<"#";
            else cout << " ";
    cout << '\n';
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
void PanouControl()
{
    char comenzi;
    cout << "JOC NOU(N) | CLASAMENT(C)"<<'\n';
    cin >> comenzi;
    if(comenzi == 'N')
    {
        bool game = 1;
        while(game)
        {
            Play();
            system("cls");
        }
    }
    if(comenzi == 'C')
        AfiseazaJucatori();
}
int main()
{
    Initializare();
    PanouControl();
    //UtilizatorNou(0);
    //AfiseazaJucatori();
    return 0;
}
