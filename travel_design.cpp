#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<iostream>
#include<bits/stdc++.h>
#include<string>
#include<windows.h>
#include<graphics.h> 
using namespace std;
typedef struct lists
{	string seq;//��Σ�������Ϊ3λ����Ϊ0��ͷ����ͨ��ʽΪ������1��ͷ��ͨ��ʽΪ�𳵣�2��ͷ��ͨ��ʽΪ�ɻ� 
	int start_pos;//ʼ��վ 
	float start_time;//����ʱ�� 
	int arrive_pos;//�յ�վ 
    float arrive_time;//����ʱ�� 
/********���ж�Ӧ����*********/
/**********0��������************/
/**********1���ɶ���************/
/**********2��������************/
/**********3���Ͼ���**********/
/**********4���Ϻ���************/
/**********5��֣����************/
/**********6�����ݵ�************/
/**********7��������************/
/**********8��������************/
/**********9��ӥ̶��********/
}lists;
typedef struct travellers
{
	int start_choice;/*ѡ������*/ 
	int arrive_choice;/*ѡ����յ�*/ 
	int plan_choice;/*ѡ������в��ԣ�0Ϊ���ٷ��ղ��ԣ�1Ϊ��ʱ���ٲ���*/ 
	int timerequir;/*ʱ�����Ʋ�������������ʱ��*/ 
 } travellers; 
ifstream in("a.txt");/*��a.txt�����복�α�*/ 
ofstream ou("client.txt");/*��client.txt�������־�ļ�*/ 
int citythrough[50];//��¼�����ĳ��� 
int citycount=0; //��¼�����ĳ��е����� 
lists tab[167];
int mainstack[15];
int coumainsta=1;//��ջ���е����� 
int cousupsta=0;//��ջ���е����� 
float minrisk=9999;//��С����ֵ 
string number[50];//��¼��ͨ���ߵ���� 
int timespend[50];//ÿһС��·�����ĵ�ʱ�� 
int stopway[50]; //ÿ������ͣ����ʱ�� 
int timesum=0;//���õ���ʱ�� 
int timesum1=0;
float systemhour;//��¼ϵͳʱ�� 
float stt;
float temphour;
int flags=0;//��ʶ������;�л���ͣ���ڳ����� 
int jishu=1;//������־���ʱ���еļ��� 
int timescounts=0;//������־���ʱʱ��ļ��� 
int sleeptime=10000;
mouse_msg msg = { 0 };
typedef struct gro
{
	int group[15];
	int len=10;
}gro;
typedef struct grous
{
	gro g[30];
}grous;
int jud(int x)/*���ڲ��Һ���·�ߵ��ж�*/ 
{
	for(int i=0;i<coumainsta;i++)
	{
		if(x==mainstack[i])
		return 1;
	}
	return 0;
}
float cityrisk(int seq2)/*��¼���еķ���ֵ*/ 
{
	switch(tab[seq2].start_pos)
	{
		case 0:
		case 6:
		case 7:
		case 9:
			return 0.2;
		case 1:
		case 5:
		case 8:
		    return 0.5;
		case 2:
		case 3:
		case 4:
			return 0.9;
	}
}
float risksums(float sum,int seq2,int seq2before,int flag)/*��ɸ��ӹ��ܣ���¼�ܵķ���ֵ*/ 
{
	float time1;
	float time2;
if(flag==1)
{
if(tab[seq2before].arrive_time>tab[seq2].start_time)
time2=(tab[seq2].start_time+24)-tab[seq2before].arrive_time;
else
time2=tab[seq2].start_time-tab[seq2before].arrive_time;
}
else time2=0;
if(tab[seq2].arrive_time<tab[seq2].start_time)
time1=(tab[seq2].arrive_time+24)-tab[seq2].start_time;
else
time1=tab[seq2].arrive_time-tab[seq2].start_time;
switch(tab[seq2].seq[0])
{
	case '0':
		sum=sum+time1*2.0*cityrisk(seq2)+time2*cityrisk(seq2);
		break;
	case '1':
		sum=sum+time1*5.0*cityrisk(seq2)+time2*cityrisk(seq2);
		break;
	case '2':
		sum=sum+time1*9.0*cityrisk(seq2)+time2*cityrisk(seq2);
		break;
}
	return sum;
}
void cityprint(int citythrough)/*���ݳ��е��������������������е�����*/ 
{
	switch(citythrough)
	{
			case 0:
				cout<<"����"<<endl;
				break;
			case 1:
				cout<<"�ɶ�"<<endl;
				break;
			case 2:
				cout<<"����"<<endl;
				break;
			case 3:
				cout<<"�Ͼ�"<<endl;
				break;
			case 4:
				cout<<"�Ϻ�"<<endl;
				break;
			case 5:
				cout<<"֣��"<<endl;
				break;
			case 6:
				cout<<"����"<<endl;
				break;
			case 7:
				cout<<"����"<<endl;
				break;
			case 8:
				cout<<"����"<<endl;
				break;
			case 9:
				cout<<"ӥ̶"<<endl;
				break;
	}

}
void logcityprint(int citythrough)/*���ݳ��е��������־����������е�����*/ 
{
	switch(citythrough)
	{
			case 0:
				ou<<"����"<<endl;
				break;
			case 1:
				ou<<"�ɶ�"<<endl;
				break;
			case 2:
				ou<<"����"<<endl;
				break;
			case 3:
				ou<<"�Ͼ�"<<endl;
				break;
			case 4:
				ou<<"�Ϻ�"<<endl;
				break;
			case 5:
				ou<<"֣��"<<endl;
				break;
			case 6:
				ou<<"����"<<endl;
				break;
			case 7:
				ou<<"����"<<endl;
				break;
			case 8:
				ou<<"����"<<endl;
				break;
			case 9:
				ou<<"ӥ̶"<<endl;
				break;
	}
}
void graphcityprint(int citythrough,char *x)/*��ͼ�ν�����д����������*/ 
{
	switch(citythrough)
	{
			case 0:
				strcpy(x,"����");
				break;
			case 1:
				strcpy(x,"�ɶ�");
				break;
			case 2:
				strcpy(x,"����");
				break;
			case 3:
				strcpy(x,"�Ͼ�");
				break;
			case 4:
				strcpy(x,"�Ϻ�");
				break;
			case 5:
				strcpy(x,"֣��");
				break;
			case 6:
				strcpy(x,"����");
				break;
			case 7:
				strcpy(x,"����");
				break;
			case 8:
				strcpy(x,"����");
				break;
			case 9:
				strcpy(x,"ӥ̶");
				break;
	}
 } 
DWORD WINAPI interpret_key(LPVOID IpParamter)//�������̺߳���,���ڶ�̬��ѯ��ģ�� 
{
	char c=getchar();//��ȡ�������� 
	if(c=='c')
	{
		cout<<"��ǰʱ��Ϊ"<<(int)systemhour%24<<endl;
	if(systemhour-temphour<timespend[jishu]&&flags==0)
	{
		cout<<"��ǰ�����Ϊ"<<number[jishu]<<"�Ľ�ͨ������"<<endl;
	}
    else if((systemhour-temphour<stopway[jishu]&&flags==1)||timescounts==timesum)
    {
    	cout<<"��ǰ��";
    	cityprint(citythrough[jishu]);
	}
	else
	cout<<"���ڽ�ͨ���ߺͳ��еĽ��Ӵ�"<<endl;
	}
	if(c=='f')
	{sleeptime/=2;//���� 
	cout<<"�ο��ٶȼӿ�1��,�����ӳ�ʱ��Ϊ"<<sleeptime<<"����"<<endl;
    }
	if(c=='s')  
	{sleeptime*=2;//����
	cout<<"�ο��ٶȼ���1��,�����ӳ�ʱ��Ϊ"<<sleeptime<<"����"<<endl;
    }

}
void printcondition()/*��־�ļ����ģ��*/ 
{
	systemhour=stt;
	temphour=systemhour;
	cout<<"�ο��ѳ�����������Ҫ��ѯ��ʱ���ο͵�״̬��������Сдc��ĸ���ɲ�ѯ,����f�ɶ��οͼ���1��������s�ɶ��οͼ���1������ʼ�ٶ�Ϊ��ʵ10���ӦϵͳһСʱ"<<endl; 
	while(timescounts<=timesum)
	{
	  HANDLE hThread1 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/ 
	   HANDLE hThread2 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	    HANDLE hThread3 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	     HANDLE hThread4 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	      HANDLE hThread5 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	       HANDLE hThread6 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	        HANDLE hThread7 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	         HANDLE hThread8 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	          HANDLE hThread9 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	           HANDLE hThread10 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/
	            HANDLE hThread11 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/ 
	            HANDLE hThread12 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/ 
	            HANDLE hThread13 = CreateThread(NULL, 0, interpret_key, NULL, 0, NULL);/*�������߳̾��*/ 
	ou<<"��ǰʱ��Ϊ"<<(int)systemhour%24<<endl;
	if(systemhour-temphour<timespend[jishu]&&flags==0)/*flagsΪ0����ʱ�ÿ��ڽ�ͨ������*/ 
	{
		ou<<"��ǰ�����Ϊ"<<number[jishu]<<"�Ľ�ͨ������"<<endl;
	}
	else if(systemhour-temphour>=timespend[jishu]&&flags==0)
	{
	  flags=1;
	  temphour=systemhour;
	  jishu++;
    }
    if((systemhour-temphour<stopway[jishu]&&flags==1)||timescounts==timesum)/*flagsΪ0����ʱ�˿��ڳ�����ͣ��*/ 
    {
    	ou<<"��ǰ��";
    	logcityprint(citythrough[jishu]);
	}
	else if(systemhour-temphour>=stopway[jishu]&&flags==1)
	{
		flags=0;
		ou<<"��ǰ�����Ϊ"<<number[jishu]<<"�Ľ�ͨ������"<<endl;
		temphour=systemhour;
	}
	timescounts++;
	systemhour++;
	Sleep(sleeptime);/*˯�ߺ���*/ 
    }
    cout<<"�ο��ѵ���Ŀ�ĵأ���ѯ����"<<endl; 
}
void leastrisk(int start,int end)/*��С���ղ��Ժ���*/ 
{
 mainstack[coumainsta]=start;
 int temp[15];
 grous grou;
 for(int i=0,j=0;i<10;i++,j++)
 {
 	if(i==start)
 	{
 		j--;
 		continue;
	 }
	 temp[j]=i;
 }
 temp[9]=-1;
 for(int i=0;i<10;i++)
 {
 	grou.g[cousupsta].group[i]=temp[i];
 }
 while(coumainsta!=0)
 { 
 	if(grou.g[cousupsta].group[0]!=-1)
 	{
 		mainstack[++coumainsta]=grou.g[cousupsta].group[0];
 		grou.g[cousupsta].len--;
 		for(int j=0;j<grou.g[cousupsta].len;j++)
 		{
 			grou.g[cousupsta].group[j]=grou.g[cousupsta].group[j+1];
		 }
 		
	 }
	 else
	 {  while(coumainsta>=1&&grou.g[cousupsta].group[0]==-1)
	 	{
		coumainsta--;
	 	cousupsta--;
	    }
	    if(coumainsta>0)
	    {
	    	mainstack[++coumainsta]=grou.g[cousupsta].group[0];
	    	grou.g[cousupsta].len--;
 		for(int j=0;j<grou.g[cousupsta].len;j++)
 		{
 			grou.g[cousupsta].group[j]=grou.g[cousupsta].group[j+1];
		 }
		}
	 }
	 for(int i=0,j=0;i<10;i++,j++)
   {
 	if(i==mainstack[coumainsta]||jud(i)==1)
 	 {
 		j--;
 		if(i==9)
 		{
		 temp[j]=-1;
		 grou.g[++cousupsta].len=j+1;
	    }
 		continue;
	 }
	 temp[j]=i;
	 if(i==9)
	 {
	  temp[j+1]=-1;
	  grou.g[++cousupsta].len=j+2;
     }
   }
 for(int i=0;i<grou.g[cousupsta].len;i++)
 {
 	grou.g[cousupsta].group[i]=temp[i];
 }
 if(mainstack[coumainsta]==end)/*��ʱ�Ѿ��ҵ���һ��·�ߣ��������ж��Ƿ�Ϊ��С���յ�·�ߣ�����ǣ����¼��·�ߡ�����ֵ�������ĵ�ʱ��*/ 
 {float risksum=0;
 int curren_num;
 int numbertemp=1;
 int timesumtemp=0;
 int timespendcount=1;
 int timestoptemp[50]={0};
 int timestopcount=2;
 string temp2[50];
 int timetemp[50];
 float sttp;
 	    if(coumainsta!=2) 
 	    {
		 for(int ks=1;ks<coumainsta;ks++)
 	    {
 		for(int r=0;r<166;r++)
 		{
 			if(tab[r].start_pos==mainstack[ks]&&tab[r].arrive_pos==mainstack[ks+1])
 			{ 
			     if(ks!=1)
				 {
				 risksum=risksums(risksum,r,curren_num,1);
			     }
			     else if(ks==1)risksum=risksums(risksum,r,r,0);
 				 temp2[numbertemp++]=tab[r].seq;
 				 if(tab[r].arrive_time>tab[r].start_time)
 				 timetemp[timespendcount++]=tab[r].arrive_time-tab[r].start_time;
 				 else
 				 timetemp[timespendcount++]=tab[r].arrive_time-tab[r].start_time+24;
 				 if(ks!=1)
				  {
				  	if(tab[r].start_time<tab[curren_num].arrive_time)
				  	timestoptemp[timestopcount++]=tab[r].start_time-tab[curren_num].arrive_time+24;
				  	else
				  	timestoptemp[timestopcount++]=tab[r].start_time-tab[curren_num].arrive_time;
				   } 
				  if(ks==1)
				  sttp=tab[r].start_time;
				 	curren_num=r;
 				 break;
			 }
		 }
		}
 		for(int sss=1;sss<coumainsta;sss++)
		{
			if(sss!=1)
			timesumtemp+=timestoptemp[sss];  
			timesumtemp+=timetemp[sss];
		}
		if(risksum<minrisk&&risksum>0)
	    {timesum=timesumtemp;
         minrisk=risksum;
         stt=sttp;
		for(int ss=1;ss<=coumainsta;ss++)
		{
			citythrough[ss]=mainstack[ss];
			if(ss!=coumainsta)
			{
			number[ss]=temp2[ss];
			timespend[ss]=timetemp[ss];
			 if(ss!=1)
		    {
		    	stopway[ss]=timestoptemp[ss];
			}
		    }

		}
				citycount=coumainsta; 
	    }
	    }
	 	coumainsta--;
	 	cousupsta--;
	 	while(coumainsta>=1&&grou.g[cousupsta].group[0]==-1)
	 	{
		coumainsta--;
	 	cousupsta--;
	    }
 }
}
}
void timelimit(int start,int end,int time)/*����������leastrisk�������ƣ����Ƕ���һ����ж�ʱ�������*/ 
{
 mainstack[coumainsta]=start;
 int temp[15];
 grous grou;
 for(int i=0,j=0;i<10;i++,j++)
 {
 	if(i==start)
 	{
 		j--;
 		continue;
	 }
	 temp[j]=i;
 }
 temp[9]=-1;
 for(int i=0;i<10;i++)
 {
 	grou.g[cousupsta].group[i]=temp[i];
 }
 while(coumainsta!=0)
 { 
 	if(grou.g[cousupsta].group[0]!=-1)
 	{
 		mainstack[++coumainsta]=grou.g[cousupsta].group[0];
 		grou.g[cousupsta].len--;
 		for(int j=0;j<grou.g[cousupsta].len;j++)
 		{
 			grou.g[cousupsta].group[j]=grou.g[cousupsta].group[j+1];
		 }
 		
	 }
	 else
	 {  while(coumainsta>=1&&grou.g[cousupsta].group[0]==-1)
	 	{
		coumainsta--;
	 	cousupsta--;
	    }
	    if(coumainsta>0)
	    {
	    	mainstack[++coumainsta]=grou.g[cousupsta].group[0];
	    	grou.g[cousupsta].len--;
 		for(int j=0;j<grou.g[cousupsta].len;j++)
 		{
 			grou.g[cousupsta].group[j]=grou.g[cousupsta].group[j+1];
		 }
		}
	 }
	 for(int i=0,j=0;i<10;i++,j++)
   {
 	if(i==mainstack[coumainsta]||jud(i)==1)
 	 {
 		j--;
 		if(i==9)
 		{
		 temp[j]=-1;
		 grou.g[++cousupsta].len=j+1;
	    }
 		continue;
	 }
	 temp[j]=i;
	 if(i==9)
	 {
	  temp[j+1]=-1;
	  grou.g[++cousupsta].len=j+2;
     }
   }
 for(int i=0;i<grou.g[cousupsta].len;i++)
 {
 	grou.g[cousupsta].group[i]=temp[i];
 }
 if(mainstack[coumainsta]==end)
 {float risksum=0;
 int curren_num;
 int numbertemp=1;
 int timesumtemp=0;
 int timespendcount=1;
 int timestoptemp[50];
 int timestopcount=2;
 string temp2[50];
 int timetemp[50];
 float sttp;
 		if(coumainsta!=2) 
 	    {
		 for(int ks=1;ks<coumainsta;ks++)
 	    {
 		for(int r=0;r<166;r++)
 		{
 			if(tab[r].start_pos==mainstack[ks]&&tab[r].arrive_pos==mainstack[ks+1])
 			{ 
			     if(ks!=1)
				 {
				 risksum=risksums(risksum,r,curren_num,1);
			     }
			     else if(ks==1)risksum=risksums(risksum,r,r,0);
 				 temp2[numbertemp++]=tab[r].seq;
 				 if(tab[r].arrive_time>tab[r].start_time)
 				 timetemp[timespendcount++]=tab[r].arrive_time-tab[r].start_time;
 				 else
 				 timetemp[timespendcount++]=tab[r].arrive_time-tab[r].start_time+24;
 				  if(ks!=1)
				  {
				  	if(tab[r].start_time<tab[curren_num].arrive_time)
				  	timestoptemp[timestopcount++]=tab[r].start_time-tab[curren_num].arrive_time+24;
				  	else
				  	timestoptemp[timestopcount++]=tab[r].start_time-tab[curren_num].arrive_time;
				   } 
				   if(ks==1)
				   sttp=tab[r].start_time;
				    curren_num=r;
 				 break;
			 }
		}
		}
 		for(int sss=1;sss<coumainsta;sss++)
		{
			if(sss!=1)
			timesumtemp+=timetemp[sss]+timestoptemp[sss];
			else
			timesumtemp+=timetemp[sss];
		}
		if(timesumtemp<=time)/*�ж�ʱ���Ƿ�����˿͵�Ҫ��������������ж��Ƿ�����С���գ�����ֱ����ȥ*/ 
	    {
		if(risksum<minrisk&&risksum>0)
	    {timesum=timesumtemp;
	    stt=sttp;
         minrisk=risksum;
		for(int ss=1;ss<=coumainsta;ss++)
		{
			citythrough[ss]=mainstack[ss];
			if(ss!=coumainsta)
			{
			number[ss]=temp2[ss];
			timespend[ss]=timetemp[ss];
		    }
		    if(ss!=1)
		    {
		    	stopway[ss]=timestoptemp[ss];
			}
		}
				citycount=coumainsta; 
	    }
	    }
	    }
	 	coumainsta--;
	 	cousupsta--;
	 	while(coumainsta>=1&&grou.g[cousupsta].group[0]==-1)
	 	{
		coumainsta--;
	 	cousupsta--;
	    }
	}
 }
}
void printway()/*��·���ģ��*/ 
{cout<<"������·Ϊ��"<<endl; 
	for(int i=2;i<=citycount;i++)
	{
		if(i==2)cout<<"��";
		else if(i==citycount)cout<<"���";
		else cout<<"Ȼ��"; 
		cout<<"������";
		cityprint(citythrough[i]);
		cout<<"�˴ͨ�����Ϊ"<<number[i-1]<<endl; 
		cout<<"�����;��ʱΪ"<<timespend[i-1]<<"Сʱ"<<endl; 
		if(i!=citycount)
		cout<<"�ڳ�վ�ȴ���"<<stopway[i]<<"Сʱ"<<endl;
	}
	cout<<"�ܹ���ʱΪ"<<timesum<<"Сʱ"<<endl;
}
void graphcity(int citythrough,int &positionx,int &positiony)/*���ݳ��е���ŵõ�������ͼ�ν����е�λ��*/ 
{
	switch(citythrough)
	{
			case 0:
				positionx=219;
				positiony=240;
				break;
			case 1:
				positionx=209;
				positiony=245;
				break;
			case 2:
			    positionx=299;
				positiony=157;
				break;
			case 3:
				positionx=330;
				positiony=206;
				break;
			case 4:
				positionx=340;
				positiony=228;
				break;
			case 5:
				positionx=292;
				positiony=210;
				break;
			case 6:
				positionx=318;
				positiony=186;
				break;
			case 7:
				positionx=311;
				positiony=220;
				break;
			case 8:
				positionx=359;
				positiony=82;
				break;
			case 9:
				positionx=309;
				positiony=268;
				break;
	}
}
void setbar(PIMAGE img1)/*����ͼ�ν����еĸ�������ģ��*/ 
{
	getimage(img1, "1.jpg", 500, 500);
 	putimage(0, 0, img1);
 	setbkcolor(WHITE);
 	setfillcolor(RED);
 	bar(50,400,150,450);
 	setfont(25, 0, "��Բ");
	outtextxy(50,420,"��������");
	setfillcolor(RED);
 	bar(300,400,450,450);
 	setfont(25, 0, "��Բ");
	outtextxy(300,420,"��ʱ��������"); 
	setfillcolor(RED);
	bar(450,50,530,100);
	setfont(25, 0, "��Բ");
	outtextxy(450,60,"�ر�");
	setfont(25, 0, "��Բ");
	outtextxy(450,136,"ʱ�̣�");
	setfont(25, 0, "��Բ");
	outtextxy(458,195,"��ǰ�ڣ�");
	setfont(25, 0, "��Բ");
	outtextxy(151,360,"������ѡ��Ĳ���");
} 
void draw(travellers tra)/*���������ͼ�λ���*/ 
{
	 	 	initgraph(620, 500);/*��ʼ��ͼ��*/ 
 	int positionx1;//ͼ�ν����г��еĺ����� 
    int positiony1;//ͼ�ν����г��е������� 
    int positionx2;//ͼ�ν����г��еĺ����� 
    int positiony2;//ͼ�ν����г��е������� 
    int cjishu=1; 
 	PIMAGE img1 = newimage();
 	setbar(img1);
	int flagg=0;
	int flagss=0;
	char timestr[5];
	char citystr[20]; 
	char *numberstring=new char[10];
    for (; is_run(); delay_fps(60))
    {
    		while (mousemsg())
		{
			msg = getmouse(); //ʱ�̼�¼���Ķ��� 
		}
		if (msg.is_left() && msg.is_down())/*������ĵ��*/ 
		{
			if (msg.x >= 50 && msg.y >= 400 && msg.x <= 150 && msg.y <= 450&&flagg==0) //�������� 
			{
			leastrisk(tra.start_choice,tra.arrive_choice);
			cout<<"��С������ֵΪ"<<minrisk<<endl;
			printway(); 
			flagg=1;}
			if(msg.x >= 300 && msg.y >= 400 && msg.x <= 450 && msg.y <= 450&&flagg==0)//��ʱ��������
			{cout<<"��ѡ���Ϊ��ʱ���ٷ��ղ���,����������������ʱ��:"<<endl;
			  cin>>tra.timerequir;
			  timelimit(tra.start_choice,tra.arrive_choice,tra.timerequir);
 	          if(minrisk==9999)
	          cout<<"��������ʱ��̫�̣�����Ӧ��·"<<endl; 
	          else
	          {
	          	cout<<"��С������ֵΪ"<<minrisk<<endl;
			    printway(); 
			  }
			flagg=1;
		    }
		    if(flagg==1)
		    {
		    systemhour=stt;
			int timespendcount=0;
			graphcity(citythrough[cjishu],positionx1,positiony1);
			graphcity(citythrough[cjishu+1],positionx2,positiony2);
			int xposition=abs(positionx1-positionx2)/timespend[cjishu];
			int yposition=abs(positiony1-positiony2)/timespend[cjishu];
			while(timescounts<timesum)
			{
			itoa((int)systemhour%24,timestr,10);
			outtextxy(500,136,timestr);
			if(flagss==1)
			{graphcityprint(citythrough[cjishu],citystr);
				outtextxy(460,230,citystr); 
				outtextxy(460,300,"��һվ��");
				graphcityprint(citythrough[cjishu+1],citystr);
				outtextxy(460,330,citystr);
			}
			if(flagss==0)
			{
				outtextxy(460,230,"���Ϊ");
				numberstring=(char *)number[cjishu].data();
				outtextxy(544,230,numberstring);
				outtextxy(460,260,"�Ľ�ͨ������");
				outtextxy(460,300,"��һվ��");
				graphcityprint(citythrough[cjishu+1],citystr);
				outtextxy(460,330,citystr);
				
			}
			setcolor(RED);//ͼ�������Ǻ�ɫ�ı߿� 
            circle(positionx1,positiony1,5);
            if(flagss==1)
            {
            	timespendcount++;
            	if(timespendcount>=stopway[cjishu])
            	{
            		timespendcount=0;
            		flagss=0;
				}
			}
            if(flagss==0)
			{
			if(positionx1<positionx2)
			{
			positionx1+=xposition;
		    }
			else
			positionx1-=xposition;
			if(positiony1<positiony2)
			positiony1+=yposition;
			else
			positiony1-=yposition;
			timespendcount++;
		    }
			if(timespendcount>timespend[cjishu]&&flagss==0)
			{
				timespendcount=0;
				cjishu++;
				graphcity(citythrough[cjishu],positionx1,positiony1);
				graphcity(citythrough[cjishu+1],positionx2,positiony2);
				 xposition=abs(positionx1-positionx2)/timespend[cjishu];
			     yposition=abs(positiony1-positiony2)/timespend[cjishu];
			     flagss=1;
			     timescounts--;
			}
			Sleep(1000);
			cleardevice();
	        setbar(img1);
			if(timescounts==timesum-1)
			{
			  circle(positionx1,positiony1,5);
			  graphcityprint(citythrough[cjishu+1],citystr);
			  outtextxy(460,230,citystr);
			  outtextxy(460,260,"����Ŀ�ĵ�");
			itoa((int)systemhour%24,timestr,10);
			outtextxy(500,136,timestr);
		    }
		    			timescounts++;
			systemhour++;
		    }
		}
		}
			if (msg.x >= 450 && msg.y >= 50 && msg.x <=530 && msg.y <= 100)/*����رհ�ť�ر�ͼ��*/ 
 	{if(msg.is_left()){
				closegraph();
			}
	 }
	}
 }  
int main()/*������*/ 
{
   int is=0;
   if(in!=0)
{
    while(in.eof()==false)/*��txt�ļ��е����ݼ�¼���ṹ����*/ 
    {
        in>>tab[is].seq>>tab[is].start_pos>>tab[is].start_time>>tab[is].arrive_pos>>tab[is].arrive_time;
        is++;
    }
}
travellers tra;
cout<<"��ѡ�����������㣬��ﵽ���յ��Լ�������в��ԺͲ�ѯ��ʽ��0/���ٷ��գ�1/��ʱ���ٷ��գ�2/ͼ���ѯ��"<<endl;
ou<<"���������㣬��ﵽ���յ��Լ�������в���Ϊ"<<endl;
cin>>tra.start_choice>>tra.arrive_choice>>tra.plan_choice;
ou<<tra.start_choice<<" "<<tra.arrive_choice<<" "<<tra.plan_choice<<endl;
if(tra.plan_choice==0)/*ѡ�����ٷ��ղ���*/ 
{cout<<"��ѡ���Ϊ���ٷ��ղ���"<<endl; 
	leastrisk(tra.start_choice,tra.arrive_choice);
	cout<<"��С������ֵΪ"<<minrisk<<endl;
	printway();/*�����·*/ 
	printcondition(); /*��־����Ͷ�̬��ѯ*/ 
 } 
 else if(tra.plan_choice==1)/*ѡ����ʱ��С���ղ���*/ 
 {cout<<"��ѡ���Ϊ��ʱ���ٷ��ղ���,����������������ʱ��:"<<endl;
 ou<<"����������ʱ��Ϊ";
  cin>>tra.timerequir; 
  ou<<tra.timerequir<<endl;
 	timelimit(tra.start_choice,tra.arrive_choice,tra.timerequir);
 	if(minrisk==9999)
	 cout<<"��������ʱ��̫�̣�����Ӧ��·"<<endl;
	 else 
 	 {	
		 	cout<<"��С������ֵΪ"<<minrisk<<endl;
	printway();/*�����·*/
	printcondition();/*��־����Ͷ�̬��ѯ*/ 
	} 
 }
 else if(tra.plan_choice==2) /*ͨ��ͼ����ʾ�ο͵�������·*/ 
 {
	cout<<"��ѡ����ͼ���ѯ���в���"<<endl; 
	draw(tra);/*�����ÿ�ѡ�����ͼ��*/ 

 }
 else
  	cout<<"ѡ������в���ֻ��Ϊ0��1��2������������"<<endl;/*����ѡ�����������Ҫ�����������*/
 in.close();/*�ر��ļ�*/ 
 ou.close();
	return 0;
 }

