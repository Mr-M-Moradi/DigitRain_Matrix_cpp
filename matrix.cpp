#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include <math.h>

#define MAXMAT 50
#define TEXTSTY 0
#define TEXTSZ 1
#define FLUK 1
#define SPEED 1
#define XGAP 1
#define YGAP 1
#define COLORS 4
#define TAILCL 8
/*1->Green 2->Red 3->Blue*/
int MATCOLOR=1;


int XPOSS[200];
int YPOSS[200];
void GetXYPOSS();
void grayscale(int in=4);


class mat{
 public:
  int X,Y,S,ec,tc;
  char ch;
  int MYFLUK;
 mat();
 void setmat(int x=0,int s=1000);
 void drawmat();
 void erasemat();
 void changechar();
 void move();
 ~mat();
};


mat::mat(){
 X=0;
 Y=0;
 S=1000;
 ch=rand()%9+48; //ch=random(255);
}


void mat::setmat(int x,int s){
 //int color=random(3);
 X=x;
 S=s;
 Y=0;
 MYFLUK=random(FLUK);
 if(MYFLUK==0||MYFLUK==1)
  MYFLUK=2;
 ec=random(COLORS)+1;
 tc=TAILCL+random(TAILCL);

 settextstyle(TEXTSTY,0,TEXTSZ);
 setusercharsize(4, 3, 4,3 );
 ch=rand()%9+48; //ch=random(255);
}


void mat::drawmat(){
 char c[2];
 c[1]='\0';
 c[0]=ch;
 setfillstyle(1,0);
 bar(X,Y,X+textwidth("W"),Y+textheight("W"));
 setcolor(tc);
 outtextxy(X,Y,c);
 //delay(1);
}


void mat::erasemat(){
 char c[2];
 c[1]='\0';
 c[0]=ch;
 setfillstyle(1,0);
 bar(X,Y-textheight("W"),X+textwidth("W"),Y);
 setcolor(ec);
 outtextxy(X,Y-textheight("W"),c);
}


void mat::changechar()
{
 ch=1+rand()%9+48; //ch=random(255);
}


void mat::move(){
 int y=YPOSS[random(480/textheight("W"))];
 int i;
 drawmat();
 delay(S);
 erasemat();
 changechar();
 setfillstyle(1,0);
 bar(X,y,X+textwidth("W")+XGAP,y+textheight("W")+YGAP);//+textwidth("W")/2);
 Y=Y+(random(MYFLUK))*textheight("W")+1;
 for(i=1;i<2;i++){
  if(Y>getmaxy()+textheight("W"))
  {
   setmat(XPOSS[random(640/textwidth("W"))],random(SPEED));
  }
 }
}


mat::~mat()
{
}


class mymatclass{
 private:
  mat m[MAXMAT];
 public:
  mymatclass();
  void startall();
  void moveall();
  ~mymatclass();
};


mymatclass::mymatclass()
{
}
void mymatclass::startall(){
 int i;
 for(i=0;i<MAXMAT;i++)
 {
  m[i].setmat(XPOSS[random(640/textwidth("W"))],random(SPEED));
 }
}


void mymatclass::moveall(){
 int i;
 for(i=0;i<MAXMAT;i++)
 {
  m[i].move();
 }
}


mymatclass::~mymatclass()
{
}



main(){
 int gd=DETECT,gm=0; initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

 struct time t;
 int mydelay=5; //delay
 int cursec;
 //settextstyle(TEXTSTY,0,TEXTSZ);

 grayscale();
 GetXYPOSS();
 gettime(&t);

 cursec=t.ti_sec;
 mymatclass mc;
 randomize();
 mc.startall();

 while(!kbhit()){
  /*gettime(&t);                   //If you include this code the
  if(t.ti_sec==0)                  //
   cursec=0;                       //
  if((t.ti_sec-cursec)==mydelay){  //color of the matrix rain will
    MATCOLOR=random(4);            //
    grayscale(random(4));          //
    cursec=t.ti_sec;               //change randomly
  }*/
  mc.moveall();
 }

  closegraph();
  restorecrtmode();
  return (0);
}


void GetXYPOSS(){
 int i;
 XPOSS[0]=YPOSS[0]=0;
 for(i=1;i<640/textwidth("W");i++) //textwidth("W") moshakhas shodan tedad satr va soton ba tagsim arz kool br arz yek charecter
 {
  XPOSS[i]=XPOSS[i-1]+textwidth("W")+XGAP;//+textwidth("W")/2; //XGAP fasele bine soton
 }
 for(i=1;i<480/textheight("W");i++)
 {
  YPOSS[i]=YPOSS[i-1]+textheight("W")+YGAP;//+textwidth("W")/2; //YGAP fasele bine satre
 }
}


void grayscale(int in){
  int i;
  struct palettetype pal;
  getpalette(&pal);

  if(MATCOLOR==1)
  {
   for (i=0; i<pal.size ;i++)
   setrgbpalette(pal.colors[i], i*2, i*in, i);
  }
  if(MATCOLOR==2)
  {
   for (i=0; i<pal.size ;i++)
   setrgbpalette(pal.colors[i], i*in, i, i);
  }
  if(MATCOLOR==3)
  {
   for (i=0; i<pal.size ;i++)
   setrgbpalette(pal.colors[i], i, i, i*in);
  }
}
