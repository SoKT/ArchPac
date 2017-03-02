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

struct Packages
{
	char name[MaxWidth];
	int level;
	char dep[DepWidth];
	int xpos;
	int ypos;
};

int main()
{
	struct Packages pac[PacCount],pac2;
	int i=0;
//	char ichar[MaxWidth];
	string istring,itchar;
//-------------------------------------------------------------------------	
// Read file
    ifstream File("/home/ofit/.code/packages/01_02_2017/var/Packages.dat");
    while(getline(File, istring))
    {
		strcpy( pac[i].name, istring.c_str() );
		pac[i].level=1;
		i++;
	}        
    File.close();
    i=0;
    ifstream file("/home/ofit/.code/packages/01_02_2017/var/Required.dat");
    while(getline(file, istring))
    {
		strcpy( pac[i].dep, istring.c_str() );
		i++;
	}        
    file.close();
//-------------------------------------------------------------------------
// Count levels


//int wl=1; //wrong levels
int f=0;
//	cout << f << " ";
//while (wl==1)
//{
	f++;
//	wl=0;
	for ( int i = 0; i < PacCount; i++ )
	{
//		if (i==0)	cout << f << "\n";
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
						if (pac[i].level>=pac[z].level) 
						{
							pac[z].level=pac[i].level+1;
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
//}

//-------------------------------------------------------------------------	
// Sort Packages
	
for ( int i = 0; i < PacCount; i++ )
{
//	int min=i;
	for ( int j = i; j < PacCount; j++ )
	{
		if (pac[i].level>pac[j].level)
		{
//			min=j;
			pac2=pac[i];
			pac[i]=pac[j];
			pac[j]=pac2;
		}
	}
//	pac2=pac[i];
//	pac[i]=pac[min];
//	pac[min]=pac2;
}
//-------------------------------------------------------------------------	
// Create bitmap v

int xi=0;
int yi=0;
int ml=sqrt(PacCount)+1;
int bmx=ml*2*100;
int bmy=(ml+pac[0].level)*300;
//int xbitmap[][9000];
//xbitmap[bmx][bmy]=10;

// Set top-left squad positions

for ( int i = 0; i < PacCount; i++ )
{
	if((xi>=40)||(pac[i].level>pac[i-1].level))
	{
		xi=0;
		yi=yi+1;
	}
	pac[i].xpos=xi*200;
	pac[i].ypos=yi*300;
	xi++;
}

// zeroing bitmap

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
						int x1=pac[i].xpos+30;
						int y1=pac[i].ypos+40	;
						int x2=pac[z].xpos+30;
						int y2=pac[z].ypos+40;
						int dx=abs(x2-x1);
						int dy=abs(y2-y1);
//						cout << x1 << " " << x2<< endl;
						int f=1;
						if (x1>x2)
						f=-	1;
						int e=0;
						int de=dy;
						int y=y1;
						int x=x1;
						while (x!=x2)
						{	
							bitmap[x][y]=0;
							e=e+de;
							if(2*e>=dx)
							{
								y=y+1;
								e=e-dx;
							}
							x=x+f;
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
						
//-------------------------------------------------------------------------	
// Write bitmap

ofstream ofs("/home/ofit/.code/packages/01_02_2017/var/Bitmaple.dat");
for ( int j = 0; j < 10000; j++ )
{
	for ( int i = 0; i < 10000; i++ )
	{
		ofs << bitmap[i][j] << ' ';	
	}	
			ofs << "\n";	
}
ofs.close();
 



						



bitmap[1][100]=1;
cout << bitmap[1][100] << ' ' << bmx << ' ' << bmy << ' '<< endl;


for ( int i = 0; i < PacCount; i++ )
{
//	cout << pac[i].name << ',' << pac[i].level << ':' << pac[i].xpos << ',' << pac[i].ypos <<',' << i << "\n";

//cout << i << ':' << pac[i].name << ' '; 
//if (pac[i].level>pac	[i+1].level)		
//cout << "\n" << "\n";
}	
cout << "cgroup разобраться как ограничить колличество выделяемой памяти процессу"<<endl;
cout << "запуск приложения из субгруппы"<<endl; 
	return 0;
}	
