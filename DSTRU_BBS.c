/*
MP DSTRU
Modified 3b3 Grid Magic Square Game in Terminal
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
#define PSIZE 9
//-----------alias---------------
typedef int bul; //boolean type
typedef int sys; //system variable int
typedef int index;
//---------prototypes----------
void Board(sys[][MaxR]);
void Winner(int);
void GameOver(bul*,sys*,sys[][MaxR],sys[][MaxR],sys[][MaxR],
sys[][1],sys[][1],sys[][1]);
void COLORTEXT(int);
void WHoTURN(sys);
void BORDERS(int);
void getINPUT(int*,int*,int*,sys[][MaxR],sys[][MaxR],sys[MaxR],sys);
void RstEvtng(sys[][MaxR],sys[][MaxR],sys[][MaxR],sys[][MaxR],sys[][MaxR],
sys[][1],sys[][1],sys[][1],sys[MaxR],sys*,sys*,sys*,bul*);
void NextPlayerMove(sys[][MaxR],sys[][MaxR],sys[],sys[][MaxR],sys[][MaxR],sys[][MaxR],
sys[][1],sys[][1],sys[][1],sys*,sys*, int,int,int,sys*);
void board_WIN(int,sys[][MaxR]);

int main(){
    sys BOARD[MaxR][MaxR],OCC[MaxR][MaxR],One[1][MaxR],Two[1][MaxR],Three[1][MaxR],
    Four[MaxR][1],Five[MaxR][1],Six[MaxR][1],PEGS[PSIZE];
    bul Over,Response;
    sys ok,turn,next;
    int col,row,peg;
    char ch;

    do{
      Response = TRUE;
        system("cls");
        RstEvtng(BOARD,OCC,One,Two,Three,Four,Five,Six,PEGS,&ok,&turn,&next,&Over);
        while(!Over){
            getINPUT(&row,&col,&peg,BOARD,OCC,PEGS,turn);
            NextPlayerMove(BOARD,OCC,PEGS,One,Two,Three,Four,Five,Six,
            &ok,&next,row,col,peg,&turn);
            GameOver(&Over,&turn,One,Two,Three,Four,Five,Six);
        }
        Board(BOARD);
        printf("%-4sFINAL BOARD\n\n"," ");
        printf("Do you want to play again? [y/n]: ");
        do{
            fflush(stdin);
            scanf("%c",&ch);
        }while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N');
        if(ch=='N'||ch=='n'){
            Response = FALSE;
        }
    }while(Response==TRUE);
    COLORTEXT(4);
    printf("THANKS FOR PLAYING!\n");
    COLORTEXT(1);
    return 0;
}

//-------------------------------CORE FUNCTIONS-----------------------------------------------
//reset everything
void RstEvtng(sys Board[][MaxR],sys OCC[][MaxR],sys One[][MaxR],sys Two[][MaxR],sys Three[][MaxR],
sys Four[][1],sys Five[][1],sys Six[][1],sys PEGS[MaxR],sys*ok,sys*turn,sys*next,bul*Over){
    index i,j;
    for(i=0;i<MaxR;i++){
        for(j=0;j<3;j++){
            Board[i][j] = 0;
            OCC[i][j]=0;
        }
    }
    for(i=0;i<MaxR;i++){
        One[0][i]=0;
        Two[0][i]=0;
        Three[0][i]=0;
        Four[i][0]=0;
        Five[i][0]=0;
        Six[i][0]=0;
    }
    for(i=0;i<PSIZE;i++){
        PEGS[i]=i+1;
    }
    *ok = FALSE;
    *turn = TRUE;
    *next = FALSE;
    *Over = FALSE;
}
//game over
void GameOver(bul *over,sys *turn,sys One [][MaxR],sys Two[][MaxR],sys Three[][MaxR],
sys Four [][1],sys Five[][1],sys Six[][1]){
  index i;
  sys RESULT = 0;
  bul b1=0,b2=0,b3=0,b4=0,b5=0,b6=0,ls=0;
  sys sb1=0,sb2=0,sb3=0,sb4=0,sb5=0,sb6=0;
  for(i=0;i<3;i++){

    if(One[0][i]==0){
      b1 = 1;
    }
    else{
      sb1 += One[0][i];
      if(sb1>15){
        ls = 1;
      }
    }

    if(Two[0][i]==0){
      b2 = 1;
    }
    else{
      sb2 += Two[0][i];
      if(sb2>15){
        ls = 1;
      }
    }

    if(Three[0][i]==0){
      b3 = 1;
    }
    else{
      sb3 += Three[0][i];
      if(sb3>15){
        ls = 1;
      }
    }

    if(Four[i][0]==0){
      b4 = 1;
    }
    else{
      sb4 += Four[i][0];
      if(sb4>15){
        ls = 1;
      }
    }

    if(Five[i][0]==0){
      b5 = 1;
    }
    else{
      sb5 += Five[i][0];
      if(sb5>15){
        ls = 1;
      }
    }

    if(Six[i][0]==0){
      b6 = 1;
    }
    else{
      sb6 += Six[i][0];
      if(sb6>15){
        ls = 1;
      }
    }

  }  
  if((b1==0&&sb1<15)||(b2==0&&sb2<15)||(b3==0&&sb3<15)||(b4==0&&sb4<15)||
  (b5==0&&sb5<15)||(b6==0&&sb6<15)){
    RESULT = 1;
  }
  else if((b1==0&&sb1==15)&&(b2==0&&sb2==15)&&(b3==0&&sb3==15)&&(b4==0&&sb4==15)&&
  (b5==0&&sb5==15)&&(b6==0&&sb6==15)){
    if(ls == 0){
      RESULT = 2;
    }
  }
  if(RESULT==1){
    *over = TRUE;
    if (*turn == TRUE){
        Winner(1);
    }
    else{
      Winner(2);
    }
  }
  else if(RESULT==2){
    *over = TRUE;
    if (*turn == TRUE){
      Winner(2);
    }
    else{
      Winner(1);
    }
  }
  if(*over == FALSE){
    *turn = !(*turn);
  }
}
//take input
void getINPUT(int*row,int*col,int*peg,sys BOARD[][MaxR],sys OCC[][MaxR],sys PEGS[MaxR],sys turn){
    index i,j;
    int x,y,speg;
    bul found=0,end=0;
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
        do{
          x=0;
          printf("Pick: ");
          scanf("%1d",&x);
          if(x<1||x>3){
            COLORTEXT(2);
            printf("Enter a valid input!\n");
            COLORTEXT(1);
          }
          fflush(stdin);
        }while(x<1||x>3);
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
        do{
          y=0;
          printf("Pick: ");
          scanf("%1d",&y);
          if(y<1||y>3){
            COLORTEXT(2);
            printf("Enter a valid input!\n");
            COLORTEXT(1);
          }
          fflush(stdin);
        }while(y<1||y>3);
        fflush(stdin);
        for(i=0;i<MaxR;i++){
            for(j=0;j<MaxR;j++){
                if(OCC[i][j]==x*10+y){
                found = 1;
                }
            }
        }
        if(!found && (x ==1||x==2||x==3) &&(y ==1||y==2||y==3)){
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
        for(i=0;i<PSIZE;i++){
            if(PEGS[i]!=0)
                printf("%d ",PEGS[i]);
        }
        printf("\n");
        BORDERS(6);
        printf("Pick: ");
        scanf("%1d",&speg);
        fflush(stdin);
        for(i=0;i<PSIZE;i++)
        {
            if(speg == PEGS[i]){
                found = 1;
            }
        }
        if(found){
            end = 1;
            found = 0;
            *peg = speg;
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
//next player move
void NextPlayerMove(sys Board[][MaxR],sys OCC[][MaxR],sys PEGS[],sys One[][MaxR],sys Two[][MaxR],sys Three[][MaxR],
sys Four[][1],sys Five[][1],sys Six[][1],sys*ok,sys*next, int row,int col,int peg,sys* turn){
    index i,j;
    int position = row*10+col;
    //assign the first seen 0 value in array as occupied
    for(i=0;i<MaxR;i++){
        for(j=0;j<MaxR;j++){
            if(OCC[i][j]==0){
                OCC[i][j]=position;
                Board[row-1][col-1]= peg;
                *ok=!(*ok);
                j=MaxR;
                i=MaxR;
            }
        }
    }
    for(i=0;i<9;i++){
        if(peg==PEGS[i]){
        PEGS[i] = 0;
        i=9;
        }
    }
    if(*ok){
        if(position==11||position==12||position==13){
            One[0][col-1] = peg;
            *next = !(*next);
        }
        else if(position==21||position==22||position==23){
            Two[0][col-1]=peg;
            *next= !(*next);
        }
        else if(position==31||position==32||position==33){
            Three[0][col-1]=peg;
            *next= !(*next);
        }

        if(position==11||position==21||position==31){
            Four[row-1][0]=peg;
            *next =!(*next);
            *ok =!(*ok);
        }
        else if(position==12||position==22||position==32){
            Five[row-1][0]=peg;
            *next =!(*next);
            *ok =!(*ok);
        }
        else if(position==13||position==23||position==33){
            Six[row-1][0]=peg;
            *next =!(*next);
            *ok =!(*ok);
        }
    }
}



//--------------------------DISPLAYS------------------------------
//Winner display
void Winner(int i){
  switch(i){
    case 1:
      system("cls");
      BORDERS(6);
      COLORTEXT(5);
      printf("CONGRATULATION WINNER\n");
      printf("      PLAYER [2] \n");
      COLORTEXT(1);
      BORDERS(6);
      break;
    case 2: 
      system("cls");
      BORDERS(6);
      COLORTEXT(5);
      printf("CONGRATULATION WINNER\n");
      printf("      PLAYER [1] \n");
      COLORTEXT(1);
      BORDERS(6);
      break;
  }
   
}
//display who's turn
void WHoTURN(int turn){
  BORDERS(4);
  if(turn== TRUE)
    printf("%c \033[1;36mPlayer 1's turn \033[0m%c\n",186,186);
  else
    printf("%c \033[1;35mPlayer 2's turn \033[0m%c\n",186,186);
  BORDERS(5);  
}
//Borders
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
      for(i=0;i<21;i++) printf("%c",205);
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
//board
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
