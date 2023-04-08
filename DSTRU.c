/*
MP DSTRU
Modified 3b3 Grid Game in Terminal
Members: 
  @ BERNAL, LIAM RYLEY GUMATAY
  @ BRODETT, RAM DAVID MARCIAL
  @ SALVADOR, JARYLL PENA
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//----------macros---------------
#define FALSE 0
#define TRUE 1
#define MaxR 3
//-----------alias---------------
typedef int bul; //boolean type
typedef int sys; //system variable int
typedef int index;
//---------prototypes----------
void Board(sys[][MaxR]);
void Winner();
void GameOver();
void COLORTEXT(int);
void WHoTURN(sys);
void getINPUT(int*,int*,int*,sys[][MaxR],sys,sys[][MaxR],int[],sys);
void RstEverything(sys[][MaxR],sys[][MaxR],bul*,
sys[],sys[],sys[],sys[],sys[],sys[],sys*,int[],sys*,
sys*,sys*);
void NextPlayerMove(sys[][MaxR],sys[][MaxR],int[],sys[],sys[],sys[],
sys[],sys[],sys[],sys*,sys*,sys*, int row,int col,int peg);
void BORDERS(int);

int main(){
  index i,j;
  //VAR INITIALIZATION
                          //  TOP     MID     BOT
  sys BOARD [MaxR][MaxR] = {{0,0,0},{0,0,0},{0,0,0}};
                          // L,C,R   L,C,R   L,C,R 
  sys OCC [MaxR][MaxR] ={{0,0,0},{0,0,0},{0,0,0}};
  bul over = FALSE;
  sys One [MaxR] = {0,0,0};
  sys Two [MaxR] = {0,0,0};
  sys Three [MaxR] = {0,0,0};
  sys Four [MaxR] = {0,0,0};
  sys Five [MaxR] = {0,0,0};
  sys Six [MaxR] = {0,0,0};
  sys PegSize = 9;
  int PEGS[9]={1,2,3,4,5,6,7,8,9};
  sys ok = FALSE;
  sys turn = TRUE;
  sys next = FALSE;
  int row,col,peg;
  bul RESPONSE;

  //-------------------START OF GAME---------------
  do
  {
    //RstEverything(BOARD,OCC,&over,One,Two,Three,Four,Five,
    //Six,&PegSize,PEGS,&ok,&turn,&next);

    while(!over){
      getINPUT(&row,&col,&peg,OCC,turn,BOARD,PEGS,PegSize);
      NextPlayerMove(BOARD,OCC,PEGS,One,Two,Three,Four,Five,Six,&ok,
      &turn,&next,row,col,peg);
    }

  } while(RESPONSE == TRUE);
  
  
  //-----test------
  system("pause");
  return 0;
}
// ---------------------CORE FUNCTIONS------------------------

/* @param1 - peg
   @param2 - row pos
   @param3 - col pos
   @param4 - system variables
*/
void NextPlayerMove(sys Board[][MaxR],sys OCC [][MaxR],int PEGS[],sys One [],sys Two [],sys Three[],
sys Four [],sys Five[],sys Six[],sys *ok,sys *turn,sys *next, int row,int col,int peg){
  index i,j;
  int position = row*10+col;
  //assign the pos as occ
  for(i=0;i<MaxR;i++){
    for(j=0;j<MaxR;j++){
      if(OCC[i][j]==0){
        OCC[i][j] = position;
        j = MaxR;
        i = MaxR;
      }
    }
  }
  Board[row-1][col-1]= peg; //assign peg to board pos
  //remove the peg in available PEGS
  for(i=0;i<9;i++){
    if(peg==PEGS[i]){
      PEGS[i] = 0;
      i=9;
    }
  }
  *ok = !(*ok);

  if(ok&&position==11||position==12||position==13)
  {
    for(i=0;i<3;i++){
      if(One[i]==0){
        One[i]=peg;
        i=3;
      }
    }
    *next = !(*next);
  }//t
  if(ok&&position==21||position==22||position==23){
    for(i=0;i<3;i++){
      if(Two[i]==0){
        Two[i]=peg;
        i=3;
      }
    }
    *next = !(*next);
  }//m
  if(ok&&position==31||position==32||position==33){
    for(i=0;i<3;i++){
      if(Three[i]==0){
        Three[i]=peg;
        i=3;
      }
    }
    *next = !(*next);
  }//b
  if(ok&&next&&position==11||position==21||position==31){
    for(i=0;i<3;i++){
      if(Four[i]==0){
        Four[i]=peg;
        i=3;
      }
    }
    *next = !(*next);
    *ok = !(*ok);

  }//l
  if(ok&&next&&position==12||position==22||position==32){
    for(i=0;i<3;i++){
      if(Five[i]==0){
        Five[i]=peg;
        i=3;
      }
    }
    *next = !(*next);
    *ok = !(*ok);
  }//c
  if(ok&&next&&position==13||position==23||position==33){
    for(i=0;i<3;i++){
      if(Six[i]==0){
        Six[i]=peg;
        i=3;
      }
    }
    *next = !(*next);
    *ok = !(*ok);
  }//r

  system("pause");
  for(i=0;i<3;i++) printf("%d ",One[i]);
  printf("\n");
  for(i=0;i<3;i++) printf("%d ",Two[i]);
  printf("\n");
  for(i=0;i<3;i++) printf("%d ",Three[i]);
  printf("\n");
  for(i=0;i<3;i++) printf("%d ",Four[i]);
  printf("\n");
  for(i=0;i<3;i++) printf("%d ",Five[i]);
  printf("\n");
  for(i=0;i<3;i++) printf("%d ",Six[i]);
  printf("\n");
  system("pause");
}
/*
  board ==     1    2    3
             --------------           VALUES OF OCCUPIED [i][j]  
          1 | 1,1  1,2  1,3               11   12   13
          2 | 2,1  2,2  2,3         -->   21   22   23
          3 | 3,1  3,2  3,3               31   32   33
*/          

void WHoTURN(int turn){
  BORDERS(4);
  if(turn)
    printf("%c \033[1;36mPlayer 1's turn \033[0m%c\n",186,186);
  else
    printf("%c \033[1;35mPlayer 2's turn \033[0m%c\n",186,186);
  BORDERS(5);  
}

void RstEverything(sys BOARD[][MaxR],sys OCC[][MaxR],bul*over,sys One[],
sys Two[],sys Three[],sys Four[],sys Five[],sys Six[],sys*Pegsize,int PEGS[],
sys*ok,sys*turn,sys*next){
  index i,j;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      BOARD[i][j] = 0;
    }
  }
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      OCC[i][j] = 0;
    }
  }
  *over = FALSE;
  for(j=0;j<3;j++){
    One[j] = 0;
  }
  for(j=0;j<3;j++){
    Two[j] = 0;
  }
  for(j=0;j<3;j++){
    Three[j] = 0;
  }
  for(j=0;j<3;j++){
    Four[j] = 0;
  }
  for(j=0;j<3;j++){
    Five[j] = 0;
  }
  for(j=0;j<3;j++){
    Six[j] = 0;
  }
  *Pegsize = 9;
  for(j=0;j<9;j++){
    PEGS[j] = j+1;
  }
  *ok = FALSE;
  *turn = TRUE;
  *next = FALSE;
}



//------------------GET INPUTS----------------------

//TO GET VALID INPUTS
void getINPUT(int*row,int*col,int*PEG,sys OCC[][MaxR],sys turn,sys BOARD[][MaxR],int PEGS[],sys PegSize){
  int x,y,peg;
  index i,j;
  bul found = 0,end = 0;
  //get valid coordinates
  do{
    Board(BOARD);
    WHoTURN(turn);
    printf("ENTER ROW\n");
    BORDERS(6);
    printf("[1] %-6s ROW\n","TOP");
    printf("[2] %-6s ROW\n","MIDDLE");
    printf("[3] %-6s ROW\n","BOTTOM");
    BORDERS(6);
    printf("Pick: ");
    scanf("%1d",&x);
    fflush(stdin);
    system("cls");
    Board(BOARD);
    WHoTURN(turn);
    printf("ENTER COL\n");
    BORDERS(6);
    printf("[1] %-6s COL\n","LEFT");
    printf("[2] %-6s COL\n","CENTER");
    printf("[3] %-6s COL\n","RIGHT");
    BORDERS(6);
    printf("Selected row [%d,COl]\n",x);
    printf("Pick: ");
    scanf("%1d",&y);
    fflush(stdin);
    for(i=0;i<MaxR;i++){
      for(j=0;j<MaxR;j++){
        if(OCC[i][j]==x*10+y){
          found = 1;
        }
      }
    }
    if(!found){
      end = 1;
      *row = x;
      *col = y;
    }
    else {
      found = 0;
      COLORTEXT(2);
      printf("Already occupied enter valid coordinates.\n");
      COLORTEXT(1);
      printf("PRESS ANY KEY TO CONTINUE");
      getch();
    }
    system("cls");
  }while(!end);
  end = 0;
  //get valid peg
  do{
    Board(BOARD);
    WHoTURN(turn);
    printf("ENTER PEG\n");
    BORDERS(6);
    printf("Selected row/col [%d,%d]\n",x,y);
    printf("Available Pegs: ");
    for(i=0;i<PegSize;i++){
      if(PEGS[i]!=0)
        printf("%d ",PEGS[i]);
    }
    printf("\n");
    BORDERS(6);
    printf("Pick: ");
    scanf("%1d",&peg);
    fflush(stdin);
    for(i=0;i<PegSize;i++)
    {
      if(peg == PEGS[i]){
        found = 1;
      }
    }
    if(found)
    {
      end = 1;
      found = 0;
      *PEG = peg;
    }
    else{
      COLORTEXT(2);
      printf("Peg already used enter a valid one.\n");
      COLORTEXT(1);
      printf("PRESS ANY KEY TO CONTINUE");
      getch();
    }
    system("cls");
  }while(!end);
}



//-----------------DISPLAY FUNCTIONS-----------------------

void BORDERS(int n){
  index i;
  switch(n){
    //case 1-3for board
    case 1: //up divider
      printf("%c",201);
      for(i=0;i<11;i++){
        if (i==3||i==7)
          printf("%c",203);
        else
          printf("%c",205);
      }
      printf("%c\n",187); 
      break;
    case 2: //bottom divider
      printf("%c",200);
      for(i=0;i<11;i++){
        if (i==3||i==7)
          printf("%c",202);
        else
          printf("%c",205);
      }
      printf("%c\n",188);
      break;
    case 3: //middle divider
      printf("%c",204);
      for(i=0;i<3;i++) printf("%c",205);
      printf("%c",206);
      for(i=0;i<3;i++) printf("%c",205);
      printf("%c",206);
      for(i=0;i<3;i++) printf("%c",205);
      printf("%c\n",185);
      break;
    //case 4 onwards for other display  
    case 4: //up divider for displays
      printf("%c",201);
      for(i=0;i<17;i++) printf("%c",205);
      printf("%c\n",187); 
      break; 
    case 5: //bottom divider
      printf("%c",200);
      for(i=0;i<17;i++) printf("%c",205);
      printf("%c\n",188);
      break;
    case 6: //straight divider
      for(i=0;i<19;i++) printf("%c",205);
      printf("\n");
      break;      
  }
}
//for colors
void COLORTEXT(int num){
  switch (num){
    case 1://reset
      printf("\033[0m");
      break;
    case 2://red
      printf("\033[1;31m");
      break;
    case 3: //cyan
      printf("\033[1;36m");
      break;
    case 4://yellow
      printf("\033[1;33m");
      break;
    case 5://green
      printf("\033[1;32m");
      break;
    case 6: //purple
      printf("\033[1;35m");
      break;    
    }
}

// ------------------BOARD FUNCTIONS----------------
void Board(sys BOARD[][MaxR]){
  printf("%-3s"," ");
  BORDERS(1);
  //---------top------------------
  printf("%-3s"," ");
  printf("%c ",186);
  if(BOARD[0][0]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[0][0]);
  printf("%c ",186);
  if(BOARD[0][1]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[0][1]);
  printf("%c ",186);
  if(BOARD[0][2]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[0][2]);
  printf("%c\n",186);
  printf("%-3s"," ");
  BORDERS(3);
  //---------mid------------------
  printf("%-3s"," ");
  printf("%c ",186);
  if(BOARD[1][0]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[1][0]);
  printf("%c ",186);
  if(BOARD[1][1]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[1][1]);
  printf("%c ",186);
  if(BOARD[1][2]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[1][2]);
  printf("%c\n",186);
  printf("%-3s"," ");
  BORDERS(3);
  //-------------bot----------------
  printf("%-3s"," ");
  printf("%c ",186);
  if(BOARD[2][0]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[2][0]);
  printf("%c ",186);
  if(BOARD[2][1]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[2][1]);
  printf("%c ",186);
  if(BOARD[2][2]==0)
    printf("  ");
  else
    printf("%1d ",BOARD[2][2]);
  printf("%c\n",186);
  printf("%-3s"," ");
  BORDERS(2);
}

//----------------DEBUGING FUNCTIONS-----------------

/* DEBUGING
for(i=0;i<MaxR;i++){
    for(j=0;j<MaxR;j++){
      printf("%d ",OCC[i][j]);
    }
    printf("\n");
  }
*/
