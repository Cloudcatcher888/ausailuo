/************************奥赛罗v3.0强化版**************************/
#include<iostream>
using namespace std;
#define PLAYER 1
#define COMPUTER -1


struct pan{
int a[8][8];//棋盘记录
int x,y;//前一个子的位置
};
struct pan mainpan;
struct pan trypan[8][8];
struct pan keep;
struct pan keep2;
struct pan keep3;
int keepi,keepj;
int t;
int tryer(struct pan n,int who,int step,int maxgoali,int maxgoalj,int maxgoal);
int change(struct pan n);
int doer(void);
int count(int goal,int i,int j,int who,struct pan n);
int difficulty;
int winflag;
void backup1();
void cheat1();
void backup2();
void cheat2();
int main()
{int i,j,tryee;

char inputx,inputy,outputx,line;
for(i=0;i<8;i++)//实际棋盘初始化
  {
   for(j=0;j<8;j++)
   {
           mainpan.a[i][j]=0;
   }
  }

  mainpan.a[3][3]=1;
    mainpan.a[3][4]=-1;
     mainpan.a[4][3]=-1;
      mainpan.a[4][4]=1;

 //难度选择
 cout<<"请选择难度：（1容易2普通3困难4高手5专家）";
        cin>>difficulty;
for(i=0;i<9;i++)//显示棋盘
        cout<<i<<"\t";
        cout<<endl<<endl;
        for(i=0;i<8;i++)
       {       line='A'+i;
               cout<<line<<"\t";
        for(j=0;j<8;j++)
       {
          if(mainpan.a[i][j]==1)
           cout<<"*"<<"\t";
           if(mainpan.a[i][j]==-1)
           cout<<"O"<<"\t";
           if(mainpan.a[i][j]==0)
           cout<<"-"<<"\t";
       }cout<<endl<<endl;
       }

for(int k=0;k<32;k++)
 {
        if(k%2==0)backup1();
        if(k%2==1)backup2();
     while(1)
     {
        cout<<"shurux:";//下棋
        cin>>inputx;

        cout<<"shuruy:";//下棋
        cin>>inputy;
        if(mainpan.a[inputx-'A'][inputy-'1']!=0&&!(inputx=='0'&&inputy=='0'))
              {
                cout<<"请重下"<<endl;
              }else break;
     }
       if(inputx=='0'&&inputy=='0')
       {
        if(k%2==0)cheat2();
        if(k%2==1)cheat1();
       }
        if(inputx>='A'&&inputx<='H'&&inputy>='1'&&inputy<='8')
        {mainpan.x=inputx-'A';
        mainpan.y=inputy-'1';

              mainpan.a[mainpan.x][mainpan.y]=1;//人下棋记录
         //人对棋盘产生影响
        t=change(mainpan);
        for(i=0;i<9;i++)//显示棋盘
        cout<<i<<"\t";
        cout<<endl<<endl;
        for(i=0;i<8;i++)
       {       line='A'+i;
               cout<<line<<"\t";
        for(j=0;j<8;j++)
       {
          if(mainpan.a[i][j]==1)
           cout<<"*"<<"\t";
           if(mainpan.a[i][j]==-1)
           cout<<"O"<<"\t";
           if(mainpan.a[i][j]==0)
           cout<<"-"<<"\t";
       }cout<<endl<<endl;
       }

       tryee=doer();
         if(tryee==-1)return 0;
         outputx=tryee/10+'A';
         cout<<"("<<outputx<<","<<(tryee%10+1)<<")"<<endl;
          }
        for(i=0;i<9;i++)//显示棋盘
        cout<<i<<"\t";
        cout<<endl<<endl;
        for(i=0;i<8;i++)
       {       line='A'+i;
               cout<<line<<"\t";
        for(j=0;j<8;j++)
       {if(mainpan.a[i][j]==1)
           {cout<<"*"<<"\t";
                if(k==31)winflag++;
           }
           if(mainpan.a[i][j]==-1)
           cout<<"O"<<"\t";
           if(mainpan.a[i][j]==0)
           cout<<"-"<<"\t";
       }cout<<endl<<endl;
       }
            if(t==0&&!(inputx=='0'&&inputy=='0'))cout<<"这个点不能下，请自觉悔棋（输入0，0）"<<endl;

 }if(winflag>32)cout<<"well,maybe the program still has some bugs";else cout<<"you were defeated by a disgusting program? maybe you'd better go to sleep";

 return 0;
}




//电脑思考
int tryer(struct pan n,int who,int step,int maxgoali,int maxgoalj,int maxgoal)
{       static int s=1;
        struct pan backup=n;//备份
        if(step==0)
return 0;
        int goal[8][8],i,j;
for(i=0;i<8;i++)//初始化goal数组
  {
   for(j=0;j<8;j++)
   {
           goal[i][j]=0;
   }
  }
  for(i=0;i<8;i++)
  {
   for(j=0;j<8;j++)
   {if(n.a[i][j]==0)
    {goal[i][j]=count(goal[i][j],i,j,who,n);
    n=keep;
    if(goal[i][j]>0){
                goal[i][j]-=tryer(n,0-who,step-1,maxgoali,maxgoalj,maxgoal);goal[i][j]++;
                if(((i==0)||(i==7)||(j==0)||(j==7))&&(goal[i][j]>0))goal[i][j]+=3;
                //if((i==1||i==6||j==1||j==6))goal[i][j]-=0.5;
                if(((i==0&&j==0)||(i==7&&j==0)||(i==0&&j==7)||(i==7&&j==7))&&(goal[i][j]>0))goal[i][j]+=10;
                if(goal[i][j]>maxgoal){maxgoal=goal[i][j];maxgoali=i;maxgoalj=j;}
                    }
    }n=backup;
   }

  }
  keepi=maxgoali;
  keepj=maxgoalj;
  return maxgoal;
}

//电脑下棋
int doer()
{       int maxgoali,maxgoalj,maxgoal=-100,i,j;
        maxgoal=tryer(mainpan,COMPUTER,difficulty+3,maxgoali,maxgoalj,maxgoal);
        if(maxgoal==-100){cout<<"you win";return -1;}
        maxgoali=keepi;
        maxgoalj=keepj;
        count(maxgoal,maxgoali,maxgoalj,COMPUTER,mainpan);//电脑下棋
        mainpan=keep;

  return (maxgoali*10+maxgoalj);
}



//人下棋
int change(struct pan n)
{int i=mainpan.x;
int j=mainpan.y;
int goal=0;
      goal=count(goal,i,j,PLAYER,n);
                n=keep;
             mainpan=n;
             return goal;
}



int count(int goal,int i,int j,int who,struct pan n)
{//up
        int temp=-1;//记录吃子数
 int i0=i,j0=j,k;
 do{
            if(i!=0)i--;else break;
            temp++;
            if(n.a[i][j]==who){

                        goal+=temp;for(k=i;k<=i0;k++){ if(((k==0)||(k==7)||(j==0)||(j==7))&&(goal>0))goal+=3;n.a[k][j]=who;}break;}//更新测试盘
    }while(n.a[i][j]==0-who);

//down

temp=-1;//记录吃子数
i=i0;j=j0;
        do{
            if(i!=7)i++;else break;
            temp++;
            if(n.a[i][j]==who){

                       goal+=temp;for(k=i0;k<=i;k++){if(((k==0)||(k==7)||(j==0)||(j==7))&&(goal>0))goal+=3;n.a[k][j]=who;}break;}//更新测试盘
    }while(n.a[i][j]==0-who);

//left

temp=-1;//记录吃子数
i=i0;j=j0;
        do{
            if(j!=0)j--;else break;
            temp++;
            if(n.a[i][j]==who){

                        goal+=temp;for(k=j;k<=j0;k++){if(((k==0)||(k==7)||(i==0)||(i==7))&&(goal>0))goal+=3;n.a[i][k]=who;}break;}//更新测试盘
    }while(n.a[i][j]==0-who);

//right
temp=-1;//记录吃子数
i=i0;j=j0;
        do{
            if(j!=7)j++;else break;
            temp++;
            if(n.a[i][j]==who){

                    goal+=temp;for(k=j0;k<=j;k++){ if(((k==0)||(k==7)||(i==0)||(i==7))&&(goal>0))goal+=3;n.a[i][k]=who;}break;}//更新测试盘
    }while(n.a[i][j]==0-who);

//upl
temp=-1;//记录吃子数
i=i0;j=j0;
        do{
            if(i!=0&&j!=0){j--;i--;}else break;
            temp++;
            if(n.a[i][j]==who){

                    goal+=temp;for(k=i;k<=i0;k++){if(((k==0)||(k==7)||(j+k-i==0)||(j+k-i==7))&&(goal>0))goal+=3;n.a[k][k+j-i]=who;}break;}//更新测试盘
    }while(n.a[i][j]==0-who);

//upr
temp=-1;//记录吃子数
 i=i0;j=j0;
        do{
            if(i!=0&&j!=7){j++;i--;}else break;
            temp++;
            if(n.a[i][j]==who){

                    goal+=temp;for(k=i;k<=i0;k++){if(((k==0)||(k==7)||(-j+k-i==0)||(-j+k-i==7))&&(goal>0))goal+=3;n.a[k][j-k+i]=who;}break;}//更新测试盘
    }while(n.a[i][j]==0-who);

//dowl
 temp=-1;//记录吃子数
i=i0;j=j0;
        do{
            if(i!=7&&j!=0){j--;i++;}else break;
            temp++;
            if(n.a[i][j]==who){goal+=temp;for(k=i0;k<=i;k++){if(((k==0)||(k==7)||(j0-k+i0==0)||(j0-k+i0==7))&&(goal>0))goal+=3;n.a[k][j0-k+i0]=who;}break;}//更新测试盘
    }while(n.a[i][j]==0-who);

//dowr
 temp=-1;//记录吃子数
 i=i0;j=j0;
        do{
            if(i!=7&&j!=7){j++;i++;}else break;
            temp++;
            if(n.a[i][j]==who){goal+=temp;for(k=i0;k<=i;k++){if(((k==0)||(k==7)||(j0+k-i0==0)||(j0+k-i0==7))&&(goal>0))goal+=3;n.a[k][j0+k-i0]=who;}break;}//更新测试盘
    }while(n.a[i][j]==0-who);
    keep=n;
    return goal;
}


void backup1()
{
      keep2=mainpan;
}
void cheat1()
{
        mainpan=keep2;
}
void backup2()
{
      keep3=mainpan;
}
void cheat2()
{
        mainpan=keep3;
}
