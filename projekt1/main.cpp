#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"
const int ROZMIAR_PLANSZY = 15; // szerokość = wysokość
const int POZYCJA_X_NAPISU = 1; // mierzona w znakach od lewej krawędzi
const int POZYCJA_Y_NAPISU = 1; // mierzona w liniach od górnej krawędzi
const int POZYCJA_X_PLANSZY = 2;    // mierzona w liniach od górnej krawędzi
const int POZYCJA_Y_PLANSZY = 62;   // mierzona w znakach od lewej krawędzi
const int ROZMIAR_PULI = 7; //rozmiar puli kafelkow


/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */

int plansza0[ROZMIAR_PLANSZY][ROZMIAR_PLANSZY] = {  {52,32,32,57,32,32,32,52,32,32,32,57,32,32,52},//domyslna plansza
                                                    {32,0x0C,32,32,32,49,32,32,32,49,32,32,32,0x0C,32},
                                                    {32,32,0x0C,32,32,32,57,32,57,32,32,32,0x0C,32,32},
                                                    {57,32,32,0x0C,32,32,32,57,32,32,32,0x0C,32,32,57},
                                                    {32,32,32,32,0x0C,32,32,32,32,32,0x0C,32,32,32,32},
                                                    {32,49,32,32,32,49,32,32,32,49,32,32,32,49,32},
                                                    {32,32,57,32,32,32,57,32,57,32,32,32,57,32,32},
                                                    {52,32,32,57,32,32,32,0x0C,32,32,32,57,32,32,52},
                                                    {32,32,57,32,32,32,57,32,57,32,32,32,57,32,32},
                                                    {32,49,32,32,32,49,32,32,32,49,32,32,32,49,32},
                                                    {32,32,32,32,0x0C,32,32,32,32,32,0x0C,32,32,32,32},
                                                    {57,32,32,0x0C,32,32,32,57,32,32,32,0x0C,32,32,57},
                                                    {32,32,0x0C,32,32,32,57,32,57,32,32,32,0x0C,32,32},
                                                    {32,0x0C,32,32,32,49,32,32,32,49,32,32,32,0x0C,32},
                                                    {52,32,32,57,32,32,32,52,32,32,32,57,32,32,52} };
int plansza[ROZMIAR_PLANSZY][ROZMIAR_PLANSZY];  //aktualnaja plansza
int pula0[ROZMIAR_PULI] = { 97,97,111,99,100,103,116 }; //domyslna pula kafelkow
int pula[ROZMIAR_PULI]; //aktualnaja pula kafelkow
int slowo[ROZMIAR_PULI];    //wprowadzane slowo


bool pole_puste(int x, int y){
    if ((plansza[x][y] == 32) || (plansza[x][y] == 49) || (plansza[x][y] == 52) || (plansza[x][y] == 57) || (plansza[x][y] == 0x0C)){
        return true;
    } else return false;
}

void wyswietlanie_legendy(int x, int y){
   	int k = 0;

	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU);
	cputs("SCRABBLE");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 1);
	cputs("Eliza Sinkevich, 171682");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 2);
	cputs("Punkty: (a),(b),(c),(d),(e)");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 3);
	cputs("strzalki przemieszczanie sie kursorem po polach planszy");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 4);
	cputs("q       wyjscie z programu");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 5);
	cputs("n       nowa gra");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 6);
	cputs("enter   potwierdzenie wyboru i zakonczenie ruchu");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 7);
	cputs("esc     anulowanie biezacej akcji");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 8);
	cputs("i       rozpoczecie wstawiania nowego slowa");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 9);
	cputs("o       zmiana orientacji umieszczanego na planszy slowa");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 10);
	cputs("w       wymiana kafelkow");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 11);
	cputs("s       zapisanie stanu gry");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 12);
	cputs("l       odczytanie stanu gry");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 13);
	cputs("t       tryb nauk");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 14);
	cputs("1,2,3,4,5,6,7   zaznaczanie kafelkow do wymiany");
	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 15);
	cputs("backspace       kasowanie ostatnio wpisanej litery");

	gotoxy(POZYCJA_X_NAPISU, POZYCJA_Y_NAPISU + 16);
	putch(x+2);
	gotoxy(POZYCJA_X_NAPISU + 1, POZYCJA_Y_NAPISU + 16);
	k = y-2;
	if (y>=12){
        putch(49);
        k = y-12;
    }else putch(32);
    gotoxy(POZYCJA_X_NAPISU + 2, POZYCJA_Y_NAPISU + 16);
    putch(48+k);
    gotoxy(POZYCJA_X_NAPISU + 8, POZYCJA_Y_NAPISU + 16);
    cputs("pozycja kursora");

    for (int i = 0; i <= ROZMIAR_PULI * 2 ; i++){      //ramka puli
        gotoxy(POZYCJA_X_NAPISU + i, POZYCJA_Y_NAPISU + 17);
        cputs("-");
		gotoxy(POZYCJA_X_NAPISU + i, POZYCJA_Y_NAPISU + 19);
		cputs("-");
    }

	for (int i = 0; i < ROZMIAR_PULI; i++){
        gotoxy(POZYCJA_X_NAPISU + i*2, POZYCJA_Y_NAPISU + 18);
        cputs("|");
        gotoxy(POZYCJA_X_NAPISU + i*2 + 1, POZYCJA_Y_NAPISU + 18);
        putch(pula[i]);
        gotoxy(POZYCJA_X_NAPISU + i*2 + 1, POZYCJA_Y_NAPISU + 20);
        putch(i+49);
    }
    gotoxy(POZYCJA_X_NAPISU + ROZMIAR_PULI*2, POZYCJA_Y_NAPISU + 18);
    cputs("| pula kafelkow");
}

void granicy_planszy(){
    int k = 0;

    // rysuemy granicy planszy
    for (int i = 0; i <= ROZMIAR_PLANSZY + 1; i++){
        gotoxy(POZYCJA_Y_PLANSZY + i, POZYCJA_X_PLANSZY);                         //gorna granica
        cputs("-");
        gotoxy(POZYCJA_Y_PLANSZY + i, POZYCJA_X_PLANSZY + ROZMIAR_PLANSZY + 1);   //dolna granica
        cputs("-");
    }
    for (int i = 1; i <= ROZMIAR_PLANSZY; i++){
        gotoxy(POZYCJA_Y_PLANSZY, POZYCJA_X_PLANSZY + i);                         //boczne granicy
        cputs("|");
        gotoxy(POZYCJA_Y_PLANSZY + ROZMIAR_PLANSZY + 1, POZYCJA_X_PLANSZY + i);
        cputs("|");

        gotoxy(POZYCJA_Y_PLANSZY - 1, POZYCJA_X_PLANSZY + i );                    //wspolrzedne planscy
        if (i>=10){
            k = i-10;
            putch(48+k);
            gotoxy(POZYCJA_Y_PLANSZY - 2, POZYCJA_X_PLANSZY + i );
            putch(49);
        }else putch(48+i);
        gotoxy(POZYCJA_Y_PLANSZY + ROZMIAR_PLANSZY + 3, POZYCJA_X_PLANSZY + i );
        if (i>=10){
            k = i-10;
            putch(48+k);
            gotoxy(POZYCJA_Y_PLANSZY + ROZMIAR_PLANSZY + 2, POZYCJA_X_PLANSZY + i );
            putch(49);
        }else putch(48+i);
        gotoxy(POZYCJA_Y_PLANSZY + i , POZYCJA_X_PLANSZY - 1);
        putch(64+i);
        gotoxy(POZYCJA_Y_PLANSZY + i , POZYCJA_X_PLANSZY + ROZMIAR_PLANSZY + 2);
        putch(64+i);
    }
}


void wypelniamy_plansze(){
    clrscr();
    for (int i = 0; i < ROZMIAR_PLANSZY; i++)
        for (int j = 0; j < ROZMIAR_PLANSZY; j++){
            plansza[i][j] = plansza0[i][j];
            gotoxy(POZYCJA_Y_PLANSZY + j + 1, POZYCJA_X_PLANSZY + i + 1);
            if (plansza0[i][j] != 32){
                textbackground(plansza0[i][j] - 48);
                putch(32);
                textbackground(BLACK);
            }
            else putch(plansza[i][j]);
        }
}



int main() {

	int kolejnosc[ROZMIAR_PULI];    //kolejnosc wybranych kafelkow
    int x = POZYCJA_Y_PLANSZY+1, y = POZYCJA_X_PLANSZY+1;   // wspolrzedne na ekranie
	int zn = 0, zero = 0;
	int pomylka = 0;
	int plan = 0, litera = -1;
	int ip = y - POZYCJA_X_PLANSZY - 1; //  wspolrzedne na planszy
	int jp = x - POZYCJA_Y_PLANSZY - 1; //
	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used
#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle sets the window title
	//settitle("First name, Last Name, Student number");
	settitle("Eliza Sinkevich 171682");
	// czarny kolor tla
	textbackground(BLACK);
	// czyscimy ekran
	clrscr();
	// ustawiamy kolor tekstu
	textcolor(WHITE);

	do {
		ip = y - POZYCJA_X_PLANSZY - 1;
		jp = x - POZYCJA_Y_PLANSZY - 1;
        gotoxy(POZYCJA_Y_PLANSZY , POZYCJA_X_PLANSZY + ROZMIAR_PLANSZY + 3);   //pozycia komunikatu
        cputs("        ");  //kasowanie komunikatu
        gotoxy(x, y);

        for (int i = 0; i < ROZMIAR_PULI; i++){
            pula[i] = pula0[i]; //kopia dla mozliwosci poprawiania bledu
        }

		//esli klavisz n - wypelnienie domyslna plansze
		if (plan == 1) {
            wypelniamy_plansze();
            plan = 0;
            textbackground(BLACK);
		}


		if (litera == 0){
            for (int i = 0; i < ROZMIAR_PULI; i++){
                kolejnosc[i] = -1;   //kasowanie kolejnosci wybranych kafelkow
                slowo[i] = 32;   //wypelnienie spacjami nowego slowa
            }

            do {
                ip = y - POZYCJA_X_PLANSZY - 1;
                jp = x - POZYCJA_Y_PLANSZY - 1;

                zn = getch();
                if ((zn > 0x40 && zn < 0x5b) || (zn > 0x60 && zn < 0x7b)) { //wpisana litera
                    slowo[litera] = zn; //zapisuemy litere w slowo
                    textbackground(RED);    //litery nie ma w puli
                    for (int i = 0; i < ROZMIAR_PULI; i++){
                        if ((pula[i] == zn) && pole_puste(ip,jp) ) {
                            kolejnosc[litera] = i;
                            pula[i] = 32;   //usuwamy kafelek z puli
                            textbackground(GREEN);
                            break;
                        }
                    }
                    plansza[ip][jp] = zn;   //umieszczamy litere na planszy
                    gotoxy(x,y);
                    putch(zn);  //piszemy litere
                    litera++;
                    x++;

                }
                else if (zn == 8 && litera > 0){  //poprawianie bledu
                    litera--;
                    x--;
                    gotoxy(x,y);
                    slowo[litera] = 32;
                    pula[kolejnosc[litera]] = pula0[kolejnosc[litera]]; //zwracamy litere do puli
                    textbackground(plansza0[ip][jp-1] - 48);  //kolor domyslnej planszy
                    plansza[ip][jp] = 32;
                    putch(plansza[ip][jp]);
                    gotoxy(x,y);
                    textbackground(BLACK);

                }
            } while (zn != 13 && litera < ROZMIAR_PULI);
            for (int i = 0; i < litera; i++){
                //putch(i+48);
                //putch(kolejnosc[i]+48);
                if (kolejnosc[i] == -1){
                    pomylka = 1;
                    break;

                }
            }
            if (pomylka == 1){
                textbackground(RED);
                gotoxy(POZYCJA_Y_PLANSZY , POZYCJA_X_PLANSZY + ROZMIAR_PLANSZY + 3);   //pozycia komunikatu
                cputs("Pomylka!");  //komunikat o bledzie
                gotoxy(x,y);
                textbackground(BLACK);
            }
            else {
               //przesuwanie, zmiana orientacii slowa
               //potwierdzenie wyboru, anulowanie procesu

            }

            litera = -1; //
            textbackground(BLACK);
		}

        wyswietlanie_legendy(x, y);
        granicy_planszy();

		gotoxy(x,y);

		zero = 0;
		zn = getch();

		if (zn == 0) {
			zero = 1;		    // jeїeli tak, to czytamy
			zn = getch();		// kolejny znak wiedz№c juї,
			if ((zn == 0x48) && (ip > 0)) y--;   // їe bкdzie to znak specjalny
			else if ((zn == 0x50) && (ip < ROZMIAR_PLANSZY - 1)) y++;
			else if ((zn == 0x4b) && (jp > 0)) x--;
			else if ((zn == 0x4d) && (jp < ROZMIAR_PLANSZY - 1)) x++;
		}
		else if ((zn == 0x6e) || (zn == 0x4e)) plan = 1;    //nowa gra n ili N
        else if ((zn == 0x69) || (zn == 0x49)) litera = 0;  //umieszczenie kafelka z litera (e), slowa (f)
		//else if ((zn == 0x30) || (zn == 0x31)) cyfra = zn;   //cyfry 0 ili 1
	} while (zn != 'q');

	return 0;
	}
