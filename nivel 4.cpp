#include<conio.h>
#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<list>
using namespace std;

#define IZQUIERDA 75
#define DERECHA 77
#define ARRIBA 72
#define ABAJO 80


void gotoxy(int x, int y)
{
	  
	HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
	
}

void OcultarCursor()
{
	
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cco;
	cco.dwSize = 2;
	cco.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon,&cco);
	
}
void pintar_limites()
{
	for(int i = 2 ; i<72 ; i++){
		gotoxy(1,3); cout<<"\261";
		gotoxy(i,3); cout<<"\261";
		gotoxy(i,33); cout<<"\261";
		gotoxy(72,3); cout<<"\261";
	}
	for(int i = 4;i<33; i++)
	{
		gotoxy(1,3); cout<<"\261"; 
		gotoxy(1,i); cout<<"\261";
		gotoxy(72,i); cout<<"\261";
		gotoxy(77,33); cout<<"\261";
	}

}
class NAVE{
	int x,y;
	int corazones;
	int vidas;
public:
	NAVE(int _x, int _y, int _corazones, int _vidas): x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
	int X(){return x; }
	int Y(){return y; }
	int VID(){return vidas; }
	void COR(){corazones--; }
	void pintar();
	void borrar();
	void mover();
	void pintar_corazones();
	void explocion();

};

void NAVE::pintar(){
	gotoxy(x,y); cout<<"    \101   "<<endl;
	gotoxy(x,y+1); cout<<"\314\315\301<O>\301\315\271";
	gotoxy(x,y+2); cout<<"  \310\276\304\276\274";
	gotoxy(x,y+3); cout<<"   \261 \261";
	
}

void NAVE::borrar(){
	gotoxy(x,y); cout<<"        "<<endl;
	gotoxy(x,y+1); cout<<"         ";
	gotoxy(x,y+2); cout<<"        ";
	gotoxy(x,y+3); cout<<"      ";                    
}
void NAVE::mover()
{
	if(kbhit()){
		char tecla = getch();
		borrar();
		if(tecla == IZQUIERDA &&x>6)x=x-6;
		if(tecla == DERECHA &&x<58)x=x+7;
		if(tecla == ARRIBA &&y>6)y=y-2;
		if(tecla == ABAJO &&y<26)y=y+4;
		if(tecla == 'e')corazones--;
		pintar();
		pintar_corazones();
	}
}
void NAVE::pintar_corazones()
{
	
	gotoxy(50,2); cout<<"VIDAS "<<vidas;
	gotoxy(64,2); cout<<"SALUD ";
	gotoxy(70,2); cout<<"     ";
	for (int i=0 ; i<corazones; i++){
		
		gotoxy(70+i,2); cout<<"\3";
	}

}

void NAVE::explocion()
{
	if(corazones == 0){
		borrar();
		gotoxy(x,y);  cout<<"       ";
		gotoxy(x,y+1);cout<<" GAMER ";
		gotoxy(x,y+2);cout<<" OVER  ";
		Sleep(500);
		
		borrar();
		gotoxy(x,y);  cout<<"/ 00 /";
		gotoxy(x,y+1);cout<<" FFF ";
		gotoxy(x,y+2);cout<<"/ 00 /";
		Sleep(500);
		borrar();
		vidas--;
		corazones = 3;
		pintar_corazones();
		pintar();

	}
}
class NAV
{
	int x,y;
public:
	NAV(int _x, int _y):x(_x),y(_y){}
	void pintar();
	void mover();
	void choque( NAVE &N);
	int X(){return x; }
	int Y(){return y; }

};
void NAV::pintar()
{
	gotoxy(x,y+1);cout<<"*";
}
void NAV::mover()
{
	gotoxy(x,y); cout<<" ";
	gotoxy(x,y+1); cout<<" ";
	y=y+2;
	if(y>30){
		x = rand()%60 + 2;
		y = 4;
		
	}
	pintar();
}
void NAV::choque( NAVE &N)
{
	if (x >=N.X() && x <N.X()+6 && y >=N.Y()&& y<= N.Y() +2)
	{
		N.COR();
		N.borrar();
		N.pintar();
		N.pintar_corazones();
		x=rand()%60 + 4;
		y = 4;
		
	}
	
}
class BALA
{
	int x,y;
public:
	BALA( int _x, int _y): x(_x),y(_y){}
	int X(){return x; }
	int Y(){return y; }
	void mover();
	bool fuera();

};
void BALA::mover()
{
	gotoxy (x,y);cout<<"         ";
	if(y>4) y--;
	gotoxy (x,y);cout<<"o   o";
}

bool BALA::fuera(){
	if(y == 4) return true;
	else return false;
	
}

int main()
{
	system("color 57");
	OcultarCursor();
	NAVE N(33,19,3,3);
	N.pintar();
	pintar_limites();
	N.pintar_corazones();
	
	list<NAV*> A;
	list<NAV*>::iterator itA;
	for(int i=0; i<4; i++){
		A.push_back(new NAV(rand()%60 + 2,rand()%4 +4));
		
	}
	list<BALA*>B;
	list<BALA*>::iterator it;
	
	bool game_over = false;
	int puntos = 0;
	while(!game_over){
		
		gotoxy(4,2); cout<<"NIVEL 4       PUNTOS "<<puntos;
		if(kbhit())
		{
			char tecla = getch();
			if(tecla =='z'|| tecla == 'Z')
			B.push_back(new BALA(N.X() +2 , N.Y() - 1));

		}
		for(it = B.begin(); it !=B.end();it ++)
		{
			(*it)->mover();
			if((*it)->fuera()){
				gotoxy((*it)->X(), (*it)->Y());cout<<"      ";
				gotoxy((*it)->X(), (*it)->Y()+1);cout<<"      ";
				
				delete(*it);
				it = B.erase(it);
			}
		}
		for(itA = A.begin(); itA != A.end(); itA++){
			(*itA)->mover();
			(*itA)->choque(N);
			
		} 
		for(itA = A.begin(); itA != A.end(); itA++){
			for(it = B.begin(); it != B.end(); it++){
				if((*itA)->X() == (*it)->X() && ( (*itA)->Y() + 1 == (*it)->Y() || (*itA)->Y() == (*it)->Y() ))
				{
					gotoxy((*it)->X(),(*it)->Y());cout<<" ";
					delete(*it);
					it = B.erase(it);
					
					A.push_back(new NAV(rand()%60 + 3, 4));
					gotoxy((*itA)->X(),(*itA)->Y());cout<<" ";
					delete(*itA);
					itA = A.erase(itA);
					
					puntos+=5;
				}
			}
		}
		
		if(N.VID() == 0) game_over = true;
		N.explocion();
		N.mover();
		Sleep(50);
	}
	Sleep(200);
	gotoxy(33,20); printf("SIGUIENTE NIVEL");
	
	getch();
	return 0;
	
}
