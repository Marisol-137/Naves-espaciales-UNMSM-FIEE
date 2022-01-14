#include <iostream>
#include <windows.h>
#include <conio.h>
#include <list>
using namespace std;

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void gotoxy(int x, int y){
	  
	HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
	
}

void OcultarCursor(){
	
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cco;
	cco.dwSize = 2;
	cco.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon,&cco);
	
}

void pintar_limites(){
	for(int i = 2 ; i<72 ; i++){
		gotoxy(1,3); cout<<"\261";
		gotoxy(i,3); cout<<"\261";
		gotoxy(i,33); cout<<"\261";
		gotoxy(72,3); cout<<"\261";	
	}
	for(int i = 4;i<33; i++){
		gotoxy(1,33); cout<<"\261";
		gotoxy(1,i); cout<<"\261";
		gotoxy(72,i); cout<<"\261";
		gotoxy(72,33); cout<<"\261";
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
	gotoxy(x,y);  cout<<"    \101   "<<endl;
	gotoxy(x,y+1);cout<<"\314\315\301<O>\301\315\271";
	gotoxy(x,y+2);cout<<"  \310\276\304\276\274";
	gotoxy(x,y+3);cout<<"   \261 \261";

}

void NAVE::borrar(){
	gotoxy(x,y);   cout<<"        "<<endl;
	gotoxy(x,y+1); cout<<"         ";
	gotoxy(x,y+2); cout<<"        ";
	gotoxy(x,y+3); cout<<"      ";  

}
void NAVE::mover(){
	if(kbhit()){
		char tecla = getch();
		borrar();
		if(tecla == IZQUIERDA &&x>6)x=x-6;
		if(tecla == DERECHA &&x<58)x=x+6;
		if(tecla == ARRIBA &&y>6)y=y-6;
		if(tecla == ABAJO &&y<26)y=y+6;
		if(tecla == 'e')corazones--;
		pintar();
		pintar_corazones();
	}
	
}

void NAVE::pintar_corazones(){
	
	gotoxy(50,2);cout<<"VIDAS "<<vidas;
	gotoxy(60,2);cout<<"SALUD ";
	gotoxy(68,2);cout<<"     ";
	for (int i=0 ; i<corazones; i++){
		
		gotoxy(69+i,2); cout<<"\3";
	}

}
void NAVE::explocion(){
	if(corazones == 0){
		borrar();
		gotoxy(x,y); cout<<"  **"<<endl;
		gotoxy(x,y+1); cout<<"* *** *";
		gotoxy(x,y+2); cout<<" ****";
		gotoxy(x,y+3); cout<<"  **";
		
		Sleep(200);
		
		borrar();
		Sleep(200);
		gotoxy(x,y); cout<<"  * **"<<endl;
		gotoxy(x,y+1); cout<<"*** **  *";
		gotoxy(x,y+2); cout<<" ****  *";
		gotoxy(x,y+3); cout<<"  ** *";
		
		vidas--;
		corazones = 3;
		pintar_corazones();
		pintar();

	}
}

class NAV{
	int x,y;
public:
	NAV(int _x, int _y):x(_x),y(_y){}
	void pintar();
	void mover();
	void choque( NAVE &N);
	int X(){return x; }
	int Y(){return y; }

};

void NAV::pintar(){
	gotoxy(x,y);cout<<" \261";
	gotoxy(x,y+1);cout<<"(O)";
}

void NAV::mover(){
	gotoxy(x,y); cout<<"   ";
	gotoxy(x,y+1); cout<<"   ";
	y=y+1;
	if(y>30){
		x = rand()%60 + 2;
		y = 4;
		
	}
	pintar();
}

void NAV::choque( NAVE &N){
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

class BALA{
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
	gotoxy (x,y);cout<<"     ";
	if(y>4) y--;
	gotoxy (x,y);cout<<"\333   \333";
}

bool BALA::fuera(){
	if(y == 4) return true;
	else return false;
	
}
int main()
{
	system("color 2f");
	OcultarCursor();
	pintar_limites();
	NAVE N(23,28,3,3);
	N.pintar();
	N.pintar_corazones();
	
	list<NAV*> A;
	list<NAV*>::iterator itA;
	for(int i=0; i<3; i++){
		A.push_back(new NAV(rand()%60 + 2,rand()%4+4));
		
	}
	list<BALA*>B;
	list<BALA*>::iterator it;
	
	bool game_over = false;
	int puntos = 0;
	while(!game_over){
		
		gotoxy(4,2); cout<<"NIVEL 3       PUNTOS "<<puntos;
		if(kbhit())
		{
			char tecla = getch();
			if(tecla =='z')
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
				if(((*itA)->X() == (*it)->X()-2||(*itA)->X() == (*it)->X()-1||(*itA)->X() == (*it)->X()||(*itA)->X() == (*it)->X()+ 1||(*itA)->X()== (*it)->X()+ 3||(*itA)->X()== (*it)->X()+ 4||(*itA)->X() == (*it)->X()+ 5||(*itA)->X() == (*it)->X()+ 6) && ( (*itA)->Y() + 1 == (*it)->Y() || (*itA)->Y() == (*it)->Y() ))
				{
					gotoxy((*it)->X()-2,(*it)->Y());cout<<"   ";
					gotoxy((*it)->X()-2,(*it)->Y()+1);cout<<"   ";
					delete(*it);
					
					it = B.erase(it);
					
					A.push_back(new NAV(rand()%60 + 3, 4));
					gotoxy((*itA)->X()-2,(*itA)->Y());cout<<"         ";
					gotoxy((*itA)->X()-2,(*itA)->Y()+1);cout<<"         ";
					delete(*itA);
					itA = A.erase(itA);
					
					puntos+=10;
				}
			}
		}
		
		if(N.VID() == 0) game_over = true;
		N.explocion();
		N.mover();
		Sleep(50);
	}
	getch();
	return 0;
}
