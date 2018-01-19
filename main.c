#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
enum TheObjects {SPACE,PLAYER,BARIER,LASTBAR};
enum BallMovments{DOWN,UP,STILL};
enum Shape{HAVE,NEED};
enum LengthOrHight{WIDTH,HIGHT};
#define jump BallMaxReng/4
#define FieldLength 23
#define FieldWidth 70
#define BallMaxReng 20
#define UserDefualtPlace 4
#define UserDefualtHight FieldLength+PlayerRadious+1
int DoNeedNewShape,PlayerLives=3,UserScore=0;
int ShapeISMovingUp;
int BarHieght,BarWidth,BarSpace,BarArrInd;
int ShapeGenerationRate=2;
int jumpHieght=0,jumpingTo=0;

void CheckPlayer(int TF[][FieldWidth]);
void ShapeMove(int TF[][FieldWidth],int turn);
void ShapeGenerator(int TF[][FieldWidth],int turn);
void FieldPrinter(int TF[][FieldWidth]);
void SetTheFieldDefualt(int TF[][FieldWidth]);
void PlayerDefualtPlace(int TF[][FieldWidth]);
void SetAllFirst(int TF[][FieldWidth]);
void BallMove(int TF[][FieldWidth],int turn);
int FindBallPlace(int TF[][FieldWidth],int LenOrHi);
char UserInputGrab();
void MapAssign(int TF[][FieldWidth],int turn);
void SetTheLastLine(int TF[][FieldWidth]);
void IntroductionMade();

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void UserScoreCal(int TF[][FieldWidth])
{
    if(TF[FieldLength-1][0]==BARIER&&TF[FieldLength-1][1]==SPACE)
        UserScore++;
}
int main()
{
    int i=0;
    int TheField[FieldLength+1][FieldWidth];
    system("mode con: cols=74 lines=26");
    system("title CS_PROJ     Coded By Ali Mahdavi");
    hidecursor();
    IntroductionMade();
    SetAllFirst(TheField);
    while(i>-1)
    {
        MapAssign(TheField,i);
        if (PlayerLives==0)
        {   Safheh[ToopH-2][ToopW] = BAZIKON;
    Safheh[ToopH][ToopW-2] = BAZIKON;
            printf(" You Lost sorry try again !!!\n\n\n\tPress any key to exit");
            break;
        }
        else
            printf("You Have %d Lives to spare\nyou passed %d walls",PlayerLives,UserScore);//need to work on
            i++;
    }
    getchar();
    return 0;
}
void IntroductionMade()
{
    printf("This  Game Has been Coded By Ali Mahdavi\n\nBe Aware that Your Controller Will be Space Bar : ");
    ShapeGenerationRate=2;
    printf("\nYour Speed Set To %d \n\nPlease Enter Any Key to start the Game",ShapeGenerationRate);
    getch();
}
void SetTheLastLine(int TF[][FieldWidth])
{
    int i=0;
    for(i=0;i<FieldWidth;i++)
    {
        TF[FieldLength][i]=LASTBAR;
    }
}
void MapAssign(int TF[][FieldWidth],int turn)
{
    ShapeGenerator(TF,turn);
    ShapeMove(TF,turn);
    BallMove(TF,turn);
    CheckPlayer(TF);
    FieldPrinter(TF);
}
char UserInputGrab()
{
    if(kbhit())
    {
        return getch();
    }
    return '0';   Safheh[ToopH-2][ToopW] = BAZIKON;
    Safheh[ToopH][ToopW-2] = BAZIKON;
}
int FindBallPlace(int TF[][FieldWidth],int LenOrHi)
{
    int i,j;
    for(j=0;j<FieldLength;j++)
    {
        for(i=0;i<FieldWidth;i++)
        {
            if(TF[j][i]==PLAYER)
            {
                if(LenOrHi==HIGHT)
                    return FieldLength-j;
                else
                    return i;
            }
        }

    }
}
void BallMove(int TF[][FieldWidth],int turn)
{
    char UserInput=UserInputGrab();
    int i,j;
    if((UserInput==72||UserInput==' ')&&jumpingTo==0&&ShapeISMovingUp==STILL)
    {
        jumpHieght+=jump;
        jumpingTo+=jump;
        ShapeISMovingUp=UP;
    }
    else if((UserInput==72||UserInput==' ')&&jumpingTo>0&&FindBallPlace(TF,HIGHT)<BallMaxReng&&jumpingTo<BallMaxReng&&ShapeISMovingUp==UP)
    {
        jumpHieght+=jump;
        jumpingTo+=jump;
    }
    if((UserInput==77||UserInput=='d')&&FindBallPlace(TF,WIDTH)<FieldWidth/2)
    {
        for (i =0; i < FieldLength; i++) {
            for(j=FieldWidth-1;j>-1;j--)
            {
                if(TF[i][j]==PLAYER)
                {
                    TF[i][j]=SPACE;
                    TF[i][j+1]=PLAYER;
                }
            }
        }
    }
    if((UserInput==75||UserInput=='a')&&FindBallPlace(TF,WIDTH)>UserDefualtPlace)
    {
        for (i =0; i < FieldLength; i++) {
            for(j=0;j<FieldWidth;j++)
            {
                if(TF[i][j]==PLAYER)
                {
                    TF[i][j]=SPACE;
                    TF[i][j-1]=PLAYER;
                }
            }
        }
    }
    if(jumpHieght>=0&&turn%ShapeGenerationRate==0&&ShapeISMovingUp==UP)
    {
        int shapeMoved=0;
        for (i =(FieldLength-jumpingTo); i < FieldLength; i++) {
            for(j=0;j<FieldWidth;j++)
            {

                if(TF[i][j]==PLAYER)
                {
                    TF[i][j]=SPACE;
                    TF[i-1][j]=PLAYER;
                    shapeMoved=1;
                }
                if((FindBallPlace(TF,HIGHT)>=BallMaxReng||TF[FieldLength-jumpingTo][FindBallPlace(TF,WIDTH)]==PLAYER))
                {
                    ShapeISMovingUp=DOWN;
                }
            }
        }
        if(shapeMoved)
        {
            jumpHieght--;
        }
    }
    else if (ShapeISMovingUp==DOWN&&turn%ShapeGenerationRate==0)
    {
        for (i = FieldLength-1; i >-1 ; i--) {
            for(j=0;j<FieldWidth;j++)
            {
                if (TF[i][j]==PLAYER)
                {
                    TF[i][j]=SPACE;
                    TF[i+1][j]=PLAYER;
                }
                if (TF[FieldLength-1][j]==PLAYER)
                {
                    ShapeISMovingUp=STILL;
                    jumpHieght=0;
                    jumpingTo=0;
                }
            }
        }
    }
}
void SetAllFirst(int TF[][FieldWidth])
{
    DoNeedNewShape=NEED;
    ShapeISMovingUp=STILL;
    jumpHieght=0;
    jumpingTo=0;
    BarArrInd=0;
    srand(time(NULL));
    SetTheFieldDefualt(TF);
    SetTheLastLine(TF);
    PlayerDefualtPlace(TF);
}
void PlayerDefualtPlace(int TF[][FieldWidth])
{
    const PlayerRadious=1.2;
    int i,j;
    for(i=0;i<FieldLength;i++)
    {
        for(j=0;j<FieldWidth;j++)
        {
            double distance = sqrt((double)(i-UserDefualtHight)*(i-UserDefualtHight) + (j-UserDefualtPlace)*(j-UserDefualtPlace));
            if (distance<PlayerRadious+0.5)
            {
               TF[i][j]=PLAYER;
            }
        }
    }
}
void SetTheFieldDefualt(int TF[][FieldWidth])
{
    int i,j;
    for (i=0;i<FieldLength;i++)
        for(j=0;j<FieldWidth;j++)
            TF[i][j]=0;
}
void FieldPrinter(int TF[][FieldWidth])
{
    int i,j;
    system("cls");
    //printf("\033[1;1H");
    for(i=0;i<=FieldLength;i++)
    {
        for (j = 0; j < FieldWidth; ++j) {
            switch (TF[i][j])
            {
                case SPACE:
                    printf(" ");
                    break;
                case PLAYER:
                    printf("*");
                    break;
                case BARIER:
                case LASTBAR:
                    printf("#");
                    break;
            }
        }
        printf("\n");
    }
}
void ShapeGenerator(int TF[][FieldWidth],int turn)///////
{
 if (turn%ShapeGenerationRate==0)
 {
     int i;
     if(DoNeedNewShape==NEED)
      {
         const int HMin = 9, Hmax = 15, WMax = 8, WMin = 5, SMin = 20, SMax = 40;
         BarHieght = rand() % (Hmax - HMin + 1) + HMin;
         BarWidth = rand() % (WMax - WMin + 1) + WMin;
         BarSpace = rand() % (SMax - SMin + 1) + SMin;
         DoNeedNewShape = HAVE;
     }
     if(BarArrInd<BarWidth && DoNeedNewShape==HAVE)
     {
         for (i =FieldLength-1 ; i >(FieldLength-(BarHieght)) ; i--)
             TF[i][FieldWidth-1]=BARIER;
         BarArrInd++;
     }
     else if(BarArrInd<(BarSpace+BarWidth) && DoNeedNewShape==HAVE)
     {
         for (i =FieldLength-1 ; i >(FieldLength-(BarHieght)) ; i--)
             TF[i][FieldWidth-1]=SPACE;
         BarArrInd++;
     }
     else if (BarArrInd==(BarSpace+BarWidth) && DoNeedNewShape==HAVE)
     {
         BarArrInd=0;
         DoNeedNewShape=NEED;
     }
 }
}
void ShapeMove(int TF[][FieldWidth],int turn)
{
    if (turn%ShapeGenerationRate==0)
    {
        int i,j;
        for (i = 0; i < FieldLength; i++)
        {
            for(j=0;j<FieldWidth;j++)
            {
                if(TF[i][j]==BARIER)
                {
                    TF[i][j]=SPACE;
                    if(j!=0)
                        TF[i][j-1]=BARIER;
                }
            }
        }
        UserScoreCal(TF);
    }
}
void CheckPlayer(int TF[][FieldWidth])
{
    int i,j;
    for (i = FieldLength-1; i >-1 ; i--)
    {
        for(j=0;j<FieldWidth;j++)
        {
            if(TF[i][j]==PLAYER&&(TF[i][j+1]==BARIER||(TF[i+1][j]==BARIER&&TF[i+1][j+1]==BARIER&&!ShapeISMovingUp)))
            {
                PlayerLives--;
                SetAllFirst(TF);
                break;
            }
        }
    }
}
