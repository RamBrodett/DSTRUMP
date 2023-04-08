//This is a tic tac toe game written in C designed for beginners
//(This doesn't contain the use of pointers or other more advanced C topics)
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char Board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);
void BORDERS(int n);
void MARGIN();

int main()
{
   char winner = ' ';
   char response = ' ';

   do
   {
      winner = ' ';
      response = ' ';
      resetBoard();

      while(winner == ' ' && checkFreeSpaces() != 0)
      {
         printBoard();

         playerMove();
         winner = checkWinner();
         if(winner != ' ' || checkFreeSpaces() == 0)
         {
            break;
         }

         computerMove();
         winner = checkWinner();
         if(winner != ' ' || checkFreeSpaces() == 0)
         {
            break;
         }
         system("cls");
      }
      system("cls");
      printBoard();
      printWinner(winner);

      printf("\nWould you like to play again? (Y/N): ");
      scanf("%c");
      scanf("%c", &response);
      response = toupper(response);
   } while (response == 'Y');

   printf("Thanks for playing!");
   system("pause");
   return 0;
}

void BORDERS(int n){
    int i;
  switch(n){
      
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

void resetBoard()
{
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         Board[i][j] = ' ';
      }
   }
}
void printBoard()
{
  MARGIN();
  BORDERS(1);
  MARGIN();
  printf("%c %c %c %c %c %c %c\n",186,Board[0][0],186,Board[0][1],186,Board[0][2],186);
  MARGIN();
  BORDERS(3);
  MARGIN();
  printf("%c %c %c %c %c %c %c\n",186,Board[1][0],186,Board[1][1],186,Board[1][2],186);
  MARGIN();
  BORDERS(3);
  MARGIN();
  printf("%c %c %c %c %c %c %c\n",186,Board[2][0],186,Board[2][1],186,Board[2][2],186);
  MARGIN();
  BORDERS(2);
}

int checkFreeSpaces()
{
   int freeSpaces = 9;

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         if(Board[i][j] != ' ')
         {
            freeSpaces--;
         }
      }
   }
   return freeSpaces;
}
void playerMove()
{
   int x;
   int y;

   do
   {
      printf("Enter row #(1-3): ");
      scanf("%d", &x);
      x--;
      printf("Enter column #(1-3): ");
      scanf("%d", &y);
      y--;

      if(Board[x][y] != ' ')
      {
         printf("Invalid move!\n");
      }
      else
      {
         Board[x][y] = PLAYER;
         break;
      }
   } while (Board[x][y] != ' ');
   
}
void computerMove()
{
   //creates a seed based on current time
   srand(time(0));
   int x;
   int y;

   if(checkFreeSpaces() > 0)
   {
      do
      {
         x = rand() % 3;
         y = rand() % 3;
      } while (Board[x][y] != ' ');
      
      Board[x][y] = COMPUTER;
   }
   else
   {
      printWinner(' ');
   }
}
char checkWinner()
{
   //check rows
   for(int i = 0; i < 3; i++)
   {
      if(Board[i][0] == Board[i][1] && Board[i][0] == Board[i][2])
      {
         return Board[i][0];
      }
   }
   //check columns
   for(int i = 0; i < 3; i++)
   {
      if(Board[0][i] == Board[1][i] && Board[0][i] == Board[2][i])
      {
         return Board[0][i];
      }
   }
   //check diagonals
   if(Board[0][0] == Board[1][1] && Board[0][0] == Board[2][2])
   {
      return Board[0][0];
   }
   if(Board[0][2] == Board[1][1] && Board[0][2] == Board[2][0])
   {
      return Board[0][2];
   }

   return ' ';
}
void printWinner(char winner)
{
   if(winner == PLAYER)
   {
      printf("YOU WIN!");
   }
   else if(winner == COMPUTER)
   {
      printf("YOU LOSE!");
   }
   else{
      printf("IT'S A TIE!");
   }
}
void MARGIN(){
    printf("%-40s"," ");
}