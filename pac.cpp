#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
 
 
const int DepWidth=1101;
const int PacCount=752;
const int MaxWidth=29;
int bitmap[10001][10001];
 
using namespace std;
 
struct Package
{
    char name[MaxWidth];
    char dep[DepWidth];
    int depAmount;
    int depNumber[DepWidth];
    int level;
    int priority;
    int xpos;
    int ypos;
};
 
 
void CountLevels(Package p[PacCount], int num)
{
	bool flag=true;
    for ( int i = 1; i < p[num].depAmount; i++ )
    {
		for ( int j = 1; j < p[p[num].depNumber[i]].depAmount; j++ )
		{
			if(p[p[num].depNumber[i]].depNumber[j]==num)
			{flag=false;}
		}
		if(flag==false)
		{
			if(p[p[num].depNumber[i]].level>p[num].level)
			{p[p[num].depNumber[i]].level=p[num].level;}
			else
			{p[num].level=p[p[num].depNumber[i]].level;}
		}
		if ((p[p[num].depNumber[i]].level<=p[num].level)&&(flag==true))
		{
			p[p[num].depNumber[i]].level=p[num].level+1;
			CountLevels(p,p[num].depNumber[i]);
		}
    }
}
 
int main()
{
    struct Package pac[PacCount],pac2;
    string istring,itchar;
    int i;
   
   
//-------------------------------------------------------------------------
// Read files
 
 
    ifstream File("/home/lubuntu/code/var/Packages.dat");
    i=0;
    while(getline(File, istring))
    {
        strcpy( pac[i].name, istring.c_str() );
        pac[i].level=1;
        pac[i].priority=0;
        pac[i].depAmount=0;
        i++;
    }        
    File.close();
 
 
    ifstream file("/home/lubuntu/code/var/Required.dat");
    i=0;
    while(getline(file, istring))
    {
        strcpy( pac[i].dep, istring.c_str() );
        i++;
    }        
    file.close();
 
 
//-------------------------------------------------------------------------
// Search deps
 
 
    for ( int i = 0; i < PacCount; i++ )
    {
        string itchar="";  
        int ij=strlen(pac[i].dep);
        for ( int j = 0; j < ij+1; j++ )
        {                  
            if ((pac[i].dep[j]==' ') || (j==ij))
            {              
                for ( int z = 0; z < PacCount; z++ )
                {
                    if (itchar==""){break;}
                    if (itchar==pac[z].name)
                    {
                        pac[i].depAmount=pac[i].depAmount+1;
                        pac[i].depNumber[pac[i].depAmount]=z;
                        break;                                         
                    }
                }
                itchar=""; 
            }
            else
            {
                itchar=itchar+pac[i].dep[j];
            }
        }
    }
 
 
//-------------------------------------------------------------------------
// Count levels
 
 
    for ( int i = 0; i < PacCount; i++ )
    {
		CountLevels(pac, i);
    }
 
 
//-------------------------------------------------------------------------	
// Sort Packages by level


for ( int i = 0; i < PacCount; i++ )
for ( int j = i; j < PacCount; j++ )
{
		if (pac[i].level>pac[j].level)
		{
			pac2=pac[i];
			pac[i]=pac[j];
			pac[j]=pac2;
		}
}


//-------------------------------------------------------------------------	
// Sort Packages by priority


for ( int i = 0; i < PacCount-40; i=i+40 )
for ( int j = 0; j < 39; j++ )
{
	for ( int z = j; z < 39; z++ )
	{
		if (pac[i+j].depAmount<pac[i+z].depAmount)
		{
			pac2=pac[i+j];
			pac[i+j]=pac[i+z];
			pac[i+z]=pac2;
		}
	}
}


//-------------------------------------------------------------------------	
// Create bitmap v


int xi=0;
int yi=0;
//int ml=sqrt(PacCount)+1;
//int bmx=ml*2*100;
//int bmy=(ml+pac[0].level)*300;
//int xbitmap[][9000];
//xbitmap[bmx][bmy]=10;

// Set top-left squad positions

for ( int i = 0; i < PacCount; i++ )
{
	if(xi>=40)
	{
		xi=0;
		yi=yi+1;
	}
	pac[i].xpos=xi*200;
	pac[i].ypos=yi*300;
	xi++;
}


for ( int i = 0; i < PacCount; i=i+2 )
{
	if(xi>=20)
	{
		xi=0;
		yi=yi+1;
	}
	pac[i].xpos=4800-xi*200;
	pac[i].ypos=4800+yi*300;
	pac[i+1].xpos=5000+xi*200;
	pac[i+1].ypos=4800+yi*300;
	xi++;
}


//-------------------------------------------------------------------------	
// zeroing bitmap v


for ( int i = 0; i < 10000; i++ )
for ( int j = 0; j < 10000; j++ )
{
	bitmap[i][j]=1;
}


//-------------------------------------------------------------------------	
// Write bitmap squad v


for ( int i = 0; i < PacCount; i++ )
{
	for ( int x = 0; x < 140; x++ )
	for ( int y = 0; y < 20; y++ )
	{
		bitmap[pac[i].xpos+30+x][pac[i].ypos+40+y]=0;
	}
}

for ( int i = 0; i < PacCount; i++ )
{
	for ( int x = 1; x < 139; x++ )
	for ( int y = 1; y < 19; y++ )
	{
		bitmap[pac[i].xpos+30+x][pac[i].ypos+40+y]=1;
	}
}


//-------------------------------------------------------------------------	
// Write bitmap depends


for ( int i = 0; i < PacCount; i++ )
{
	string itchar="";	
		int ij=strlen(pac[i].dep);
		for ( int j = 0; j < ij+1; j++ )
		{						
			if(pac[i].dep[j]=='N')
			{break;}			
			if ((pac[i].dep[j]==' ') || (j==ij))
			{					
				for ( int z = 0; z < PacCount; z++ )
				{
					if (itchar==""){break;}
					if (itchar==pac[z].name) 
					{						
						//write line from pac[i].xpos+170 pac[i].ypos+40 to pac[z].xpos+30 pac[z].ypos+60
						// Bresenham's line algorithm
						int x1=pac[i].xpos+170;
						int y1=pac[i].ypos+60;
						int x2=pac[z].xpos+30;
						int y2=pac[z].ypos+40;
						int dx=abs(x2-x1);
						int dy=abs(y2-y1);
						int fx=1;
						if (x1>x2)
						fx=-1;
						int fy=1;
						if (y1>y2)
						fy=-1;
						int e=0;
						if(abs(x2-x1)>abs(y2-y1))
						{
							int de=dy;
							int y=y1;
							for (int x = x1; x < x2; x=x+fx)
							{	
								bitmap[x][y]=0;
								e=e+de;
								if(2*e>=dx)
								{
									y=y+fy;
									e=e-dx;
								}
							}
						}
						else
						{
							int de=dx;
							int x=x1;
							for (int y = y1; y < y2; y=y+fy)
							{	
								bitmap[x][y]=0;
								e=e+de;
								if(2*e>=dy)
								{
									x=x+fx;
									e=e-dy;
								}
							}
						}
						
								
						if (pac[i].level>=pac[z].level) 
						{
//							pac[z].level=pac[i].level+1;
//							wl=1;
//							cout << f << "\n";
						}
						break;						
					}
				}
				itchar="";	
			}
			else
			{
				itchar=itchar+pac[i].dep[j];
			}
		}
}
	
/*	
						int x1=100;
						int y1=100;
						int x2=200;
						int y2=400;
						int dx=abs(x2-x1);
						int dy=abs(y2-y1);
						int fx=1;
						if (x1>x2)
						fx=-1;
						int fy=1;
						if (y1>y2)
						fy=-1;
						int e=0;
						if((x2-x1)>(y2-y1))
						{
							int de=dy;
							int y=y1;
							for (int x = x1; x < x2; x=x+fx)
							{	
								bitmap[x][y]=0;
								e=e+de;
								if(2*e>=dx)
								{
									y=y+fy;
									e=e-dx;
								}
							}
						}
						else
						{
							int de=dx;
							int x=x1;
							for (int y = y1; y < y2; y=y+fy)
							{	
								bitmap[x][y]=0;
								e=e+de;
								if(2*e>=dy)
								{
									x=x+fx;
									e=e-dy;
								}
							}
						}
	*/	

//-------------------------------------------------------------------------	
// Write bitmap


ofstream ofs("/home/lubuntu/code/var/Bitmaple.dat");
for ( int j = 0; j < 10000; j++ )
{
	for ( int i = 0; i < 10000; i++ )
	{
		ofs << bitmap[i][j] << ' ';	
	}	
			ofs << "\n";	
}
ofs.close();
 

//bitmap[1][100]=1;
//cout << bitmap[1][100] << ' ' << bmx << ' ' << bmy << ' '<< endl;


for ( int i = 0; i < PacCount; i++ )
{
//	cout << pac[i].name << ',' << pac[i].level << ',' << pac[i].priority << ':' << pac[i].xpos << ',' << pac[i].ypos <<',' << i << "\n";
}	


//-------------------------------------------------------------------------
// Test result
 
 
for ( int i = 0; i < PacCount; i++ )
{
    cout << pac[i].name << ',' << pac[i].level << ':';
    for ( int j = 1; j < pac[i].depAmount+1; j++ )
    {
//        cout << pac[i].depNumber[j] << ' ';
    }
    cout << "\n";
}
 
 
//-------------------------------------------------------------------------
// Tasks
 
 
cout << "cgroup разобраться как ограничить колличество выделяемой памяти процессу"<<endl;
cout << "запуск приложения из субгруппы"<<endl; 
cout << "приоритет v"<<endl;
cout << "сортировка по приоритету(колличество зависимостей) v"<<endl;
cout << "убрать отрисовку по уровням только по порядку v"<<endl;
cout << "отрисовка из центра по 2 пакета влево вправо v"<<endl;
cout << "съехала матрица вверх, нужно понять почему v"<<endl;
cout << "переписать отрисовку зависимостей"<<endl;


return 0;
}
