/*
MP DSTRU
Modified 3b3 Grid Game in Terminal
Members: 
          @ BERNAL, LIAM RYLEY GUMATAY
          @ BRODETT, RAM DAVID MARCIAL
          @ SALVADOR, JARYLL PENA
*/

#include <stio.h>
#include <stdlib.h>
#include <conio.h>
//---------macros------
#define FALSE = 0 
#define TRUE = 1
//---------alias-------
typedef int bul; //boolean 
//---------------------
void NextPlayerMove(int,);
void board(); //print board
void DisWinner(); //display winner
void GameOver();

int main(){
  char Board[3][3];
  bul ok,next,turn;
  int One,Two,Three,Four,Five,Six;
  int Peg = {1,2,3,4,5,6,7,8,9};
  int UPEG[9]; // unused peg //make this as a reference of what can be used.

          
  ok = FALSE;
  next = FALSE;
  turn = TRUE;

  
  InitBoard();
  
  return 0;
}

void board(){
  
}

//freeing board for use later
void InitBoard(){
  int i,j;
  for(i = 0; i < 3; i++){
       for(j = 0; j < 3; j++){
          Board3b3[i][j] = ' ';
       }
   }
}

//for printing board
void Board(){
  BORDERS(1);
  printf("%c %c %c %c %c %c %c",186,Board[0][0],186,Board[0][1],186,Board[0][2],186);
  BORDERS(3);
  printf("%c %c %c %c %c %c %c",186,Board[1][0],186,Board[1][1],186,Board[1][2],186);
  BORDERS(3);
  printf("%c %c %c %c %c %c %c",186,Board[2][0],186,Board[2][1],186,Board[2][2],186);
  BORDERS(2);
}

//for displaying winner
void DisWinner(){
  
}

void BORDERS(int n){
  switch(){
      
    case 1: //up divider
      printf("%c",201);
      for(i=0;i<11;i++) printf("%c",205);
      printf("%c\n",187); 
      break;
      
    case 2: //bottom divider
      printf("%c",200);
      for(i=0;i<11;i++) printf("%c",205);
      printf("%c\n",188);
      break;
      
    case 3: //middle divider
      printf("%c",204);
      for(i=0;i<3;i++) printf("%c",205);
      printf("%c",206);
      for(i=0;i<3;i++) printf("%c",205);
      printf("%c",206);
      for(i=0;i<3;i++) printf("%c",205);
      printf("%c\n",188);
      break;
  }
}

void NextPlayerMove(int,){

}

int GameOver(int over){
     if(){
     }
     else if(){
     }
     else if(){
     }
     else if(){
     }     
     return  !over; 
}
