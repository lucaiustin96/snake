#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;
int height = 25,
    width = 40,
    matrice[100][100],
    matricelee[100][100],
    xf, yf, x, y,
    lcoada,
    lsarpeint,
    dx[] = {0, 1, 0, -1},
    dy[] = {1, 0, -1, 0},
    dist,               //lungimea traseului
    capsarpeint,
    scor,
    viteza = 0;
bool game = 1;
struct jucatori{
    char info[100];
    int scor = 0;
}jucatori[10], aux;
struct sarpe{
    int x, y;
}sarpe[1000],           //coadaa sarpelui controlat de noi
traseu[1000],           //traseul de lungimea minima pe care merge sarpele inteligent
sarpeintel[1000],       //coada sarpelui inteligent
c[1000],                //coada de care se foloseste algoritmul lee
pi,                     //pozitia initiala
pf,                     //pozitia finala
ver,                    //folosita la lee
pnou;                   //flosita la lee
char dir;
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
            }
    while(prim <= ultim && matricelee[pf.x][pf.y] == 0)
    {
        ver = c[prim]; prim++;
        for(i = 0;i < 4; i++)
        {
            pnou.x = ver.x + dx[i];
            pnou.y = ver.y + dy[i];
            if(matricelee[pnou.x][pnou.y] == 0 && matrice[pnou.x][pnou.y] != 4)
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
    TraseuSarpeInteligent(xf, yf);
    capsarpeint = -1;
}
void SarpeInteligent()
{
    int x, y, i, prevx, prevy;
    //pozitia initiala = pozitia fructului
    pi.x = xf;
    pi.y = yf;
    //reactualizeaza pozitia sarpelui inteligent
    if(capsarpeint < dist)
    {
        //capul sarpelui inteligent se reactualizeaza la fiecare pas cu urmatoarea valoare din traseul minim
        pi.x = traseu[capsarpeint].x;
        pi.y = traseu[capsarpeint].y;
        //adauga pozitia initiala pe prima pozitie in coada sarpelui inteligent
        sarpeintel[0].x = pi.x;
        sarpeintel[0].y = pi.y;
        if(matrice[pi.x][pi.y] == 2)
            game = 0;
        else
            matrice[pi.x][pi.y] = 4;
        //pozitia elementelor din coada se reactualizeaza cu pozitia elementului din fata lor
        for(i = lsarpeint; i >= 1; i--)
        {
            sarpeintel[i] = sarpeintel[i-1];
            if(matrice[sarpeintel[i].x][sarpeintel[i].y] == 2)
                game = 0;
            else
                matrice[sarpeintel[i].x][sarpeintel[i].y] = 4;
        }
    }
    //in cazul in care capul sarpelui a mancat fructul, adaugam pe prima pozitie in coada pozitia in care se afla capul cand mananca fructul.
    else
    {
        sarpeintel[0].x = xf;
        sarpeintel[0].y = yf;
        if(matrice[xf][yf] == 2)
            game = 0;
        else
            matrice[xf][yf] = 4;
        //mutam coada dupa cum se deplaseaza capul
        for(i = lsarpeint; i >= 1; i--)
        {
            sarpeintel[i] = sarpeintel[i-1];
            if(matrice[sarpeintel[i].x][sarpeintel[i].y] == 2)
                game = 0;
            else
                matrice[sarpeintel[i].x][sarpeintel[i].y] = 4;
        }
        //crestem lungimea cozii si adaugam un fruct nou
        lsarpeint++;
        FructNou();
    }
    capsarpeint++;
}
void Sarpe()
{
    int i, j, prevx, prevy;
    prevx = x;
    prevy = y;
    for(i = 0; i <= lcoada; i++)
    {
        matrice[sarpe[i].x][sarpe[i].y] = 0;
    }
    //In cazul in care apelam functia de mai multe ori, fara codul de mai jos, sarpele va fi egal cu lungimea lui + nr de apleari.
    matrice[prevx][prevy] = 0;
    matricelee[prevx][prevy] = 0;
    switch(dir)
    {
        case 'w':
            x--;
            if(x == 0)
                x = height-2;
        break;
        case 'd':
            y++;
            if(y == width-1)
                y = 1;
        break;
        case 's':
            x++;
            if(x == height-1)
                x = 1;
        break;
        case 'a':
            y--;
            if(y == 0)
                y = width-2;
        break;
    }
    matrice[x][y] = 2;
    matricelee[x][y] = -1;
    //egaleaza prima valoare din coada sarpelui cu pozitia precedenta capului sarpelui
    sarpe[0].x = prevx;
    sarpe[0].y = prevy;
    //testeaza daca sarpele nu se omoara
    for(i = 0;i < lcoada; i++)
    {
         if(x == sarpe[i].x && y == sarpe[i].y)
            game = 0;
    }
    //muta coada sarpelui
    for(i = lcoada; i >= 1; i--)
    {
        sarpe[i] = sarpe[i-1];
        matrice[sarpe[i].x][sarpe[i].y] = 2;
    }
    //in cazul in care sarpele a mancat un fruct, creste scorul, adauga un alt fruct si creste lungimea cozii
    if(xf == x && yf == y)
    {
        scor = scor + 10;
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
                        else
                        {
                            cout << "-";
                        }
        }
    cout << '\n';
    }
    cout << "scor: " << scor;
}
void Initializare()
{
    int i, j;
    //bordam matricea pentru a evita ca sarpele inteligent sa iasa din matrice
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
    //aseaza sarpele inteligent pe mijlocul matricii
    x = height/2;
    y = width/2;
    lcoada = 0;
    matrice[x][y] = 2;
    matricelee[x][y] = 2;
    //genereaza pozitia de plecare a sarpelui inteligent
    pi.x = rand() % height;
    pi.y = rand() % width;
    matrice[pi.x][pi.y] = 4;
    capsarpeint = 0;
    FructNou();
}
void UtilizatorNou(int scor)
{
    char nume[100];
    int nrjucatori = 0, i;
    cin.get(nume, 100);
}
int ReturneazaScor(char jucator[100])
{
    int i, nr = 0;
    char numar[20];
    i = strlen(jucator);
    i--;
    while(jucator[i] != ' ')
        i--;
    strcpy(jucator, jucator+i+1);
    for(i = 0;i < strlen(jucator); i++)
        nr = nr * 10 + jucator[i] - '0';
    return nr;
}
void SortareJucatori()
{
    std::ifstream fin("tabel.txt");
    int njucatori = 0, gasit = 0, i;
    char citeste[100];
    while(fin.getline(citeste, 100))
    {
        strcpy(jucatori[njucatori].info,citeste);
        jucatori[njucatori].scor = ReturneazaScor(citeste);
        njucatori++;
    }
    while(gasit == 0)
    {
        gasit = 1;
        for(i = 0;i < njucatori-1; i++)
            if(jucatori[i].scor < jucatori[i+1].scor)
            {
               aux = jucatori[i];
               jucatori[i] = jucatori[i+1];
               jucatori[i+1] = aux;
               gasit = 0;
            }
    }
    fin.close();
    std::ofstream fout ("tabel.txt", std::ios::out | std::ios::trunc);
    for(i = 0;i < njucatori; i++)
        fout << jucatori[i].info << '\n';
    fout.close ();
}
void AfisareJucatori()
{
    int i = 0;
    system("cls");
    std::ifstream fin("tabel.txt");
    while(fin.getline(jucatori[i].info, 100))
    {
        cout << i+1 << ". " << jucatori[i].info << '\n';
        i++;
    }
    fin.close();
}
void Menu()
{
    system("cls");
    int i = 0, paritate = 0;
    cout << '\n';
    cout <<"           MENIU" << '\n';
    cout << '\n';
    cout <<"1.    Joc Nou"<<'\n';
    cout <<"2.    Clasament"<<'\n';
    cout <<"3.    Help"<<'\n';
    cout <<"4.    Setari"<<'\n';
    char alege;
    cin >> alege;
    switch(alege)
    {
        case '1':       //UTILIZATOR NOU
            system("cls");
            while(game)
            {
                Input();
                switch(viteza)
                {
                    case 0:
                        Sarpe();
                    break;
                    case 1:
                        Sarpe();
                        Sarpe();
                    break;
                    case 2:
                        Sarpe();
                        Sarpe();
                        Sarpe();
                    break;
                }
                SarpeInteligent();
                Play();
                Sleep(60);
                system("cls");
           }
        break;
        case '2':              //CLASAMENT
            SortareJucatori();
            AfisareJucatori();
        break;
        case '3':           //HELP
            system("cls");
            cout << "       PAGINA DE AJUTOR" << '\n' << '\n';
            cout<<"Jucatorul controleaza sarpele utilizand urmatoarele comenzi: "<<'\n';
            cout<<"-> W pentru a se deplasa in sus"<<'\n';
            cout<<"-> S pentru a se deplasa in jos"<<'\n';
            cout<<"-> A pentru a se deplasa la stanga"<< '\n';
            cout<<"-> D pentru a se deplasa la dreapta" << '\n';
            cout << "1. Menu" << '\n';
            cin >> alege;
            if(alege == '1')
            {
                Menu();
            }
        break;
        case '4':       //SETARI
            system("cls");
            cout << "Pagina Setari"<<'\n';
            cout << "1. Meniu | 2. Viteza" << '\n';
            cin >> alege;
            if(alege == '1')
            {
                Menu();
            }
            if(alege == '2')
            {
                cout << "0. viteza mica | 1. viteza medie | 2. viteza mare" <<'\n';
                cin >> viteza;
                Menu();
            }
        break;
    }
}
void PanouControl()
{
    Initializare();
    Menu();
}
int main()
{
    PanouControl();
    return 0;
}
