#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
 
 
const int Bit=100;
const int DepWidth=1101;
const int PacCount=752;
const int MaxWidth=30;
int bitmap[10001][10001];
 
using namespace std;
 
struct Package
{
    char name[MaxWidth];
    char dep[DepWidth];
    int depAmount;
    int depNumber[DepWidth];
    int level;
    int xpos;
    int ypos;
};
 
 
void CountLevels(Package p[PacCount+1], int num)
{
    bool flag=true;
    for ( int i = 1; i < p[num].depAmount+1; i++ )
    {
        for ( int j = 1; j < p[p[num].depNumber[i]].depAmount+1; j++ )
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
 
 
void DrawLine( int x1, int y1, int x2, int y2)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    bitmap[x2][y2]=0;
    while(x1 != x2 || y1 != y2)
   {
        bitmap[x1][y1]=0;
        const int error2 = error * 2;
        //
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}
 
 
void SearchDep(Package p[PacCount+1])
{
    for ( int i = 1; i < PacCount+1; i++ )
    {
        p[i].depAmount=0;
    }
    for ( int i = 1; i < PacCount+1; i++ )
    {
        string itchar="";  
        int ij=strlen(p[i].dep);
        for ( int j = 0; j < ij+1; j++ )
        {                  
            if ((p[i].dep[j]==' ') || (j==ij))
            {              
                for ( int z = 1; z < PacCount+1; z++ )
                {
                    if (itchar==""){break;}
                    if (itchar==p[z].name)
                    {
                        p[i].depAmount=p[i].depAmount+1;
                        p[i].depNumber[p[i].depAmount]=z;
                        break;                                        
                    }
                }
                itchar="";
            }
            else
            {
                itchar=itchar+p[i].dep[j];
            }
        }
    }  
}  
   
   
int main()
{
    struct Package pac[PacCount+1],pac2;
    string istring,itchar;
    int i;
   
   
//-------------------------------------------------------------------------
// Read files
 
 
    ifstream File("/home/lubuntu/code/var/Packages.dat");
    i=1;
    while(getline(File, istring))
    {
        strcpy( pac[i].name, istring.c_str() );
        pac[i].level=1;
        i++;
    }        
    File.close();
 
 
    ifstream file("/home/lubuntu/code/var/Required.dat");
    i=1;
    while(getline(file, istring))
    {
        strcpy( pac[i].dep, istring.c_str() );
        i++;
    }        
    file.close();
 
 
//-------------------------------------------------------------------------
SearchDep(pac);
//-------------------------------------------------------------------------
// Count levels
 
 
    for ( int i = 1; i < PacCount+1; i++ )
    {
        CountLevels(pac, i);
    }
 
 
//-------------------------------------------------------------------------
// Sort Packages by level
 
 
    for ( int i = 1; i < PacCount+1; i++ )
    for ( int j = i; j < PacCount+1; j++ )
    {
        if (pac[i].level>pac[j].level)
        {
            pac2=pac[i];
            pac[i]=pac[j];
            pac[j]=pac2;
        }
    }
   
   
//-------------------------------------------------------------------------
SearchDep(pac);
//-------------------------------------------------------------------------
// Sort Packages by priority
 

for ( int i = 1; i < PacCount+1-40; i=i+40 )
for ( int j = 1; j < 40; j++ )
{
    for ( int z = j+1; z < 40; z++ )
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
 
 
for ( int i = 1; i < PacCount+1; i++ )
{
    if(xi>=40)
    {
        xi=0;
        yi=yi+1;
    }
    pac[i].xpos=xi*2*Bit;
    pac[i].ypos=yi*3*Bit;
    xi++;
}
 
	
xi=0;
yi=0;

	
for ( int i = 1; i < PacCount+1; i=i+2 )
{
	xi++;
    pac[i].xpos=(44-xi*2)*Bit;
    pac[i].ypos=yi*3*Bit+xi*20;
    pac[i+1].xpos=(44+xi*2)*Bit;
    pac[i+1].ypos=yi*3*Bit+xi*20;
    if(xi>=20)
    {
        xi=0;
        yi=yi+1;
    }
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
 
 
for ( int i = 1; i < PacCount+1; i++ )
{
    for ( int x = 0; x < 140; x++ )
    for ( int y = 0; y < 20; y++ )
    {
        bitmap[pac[i].xpos+30+x][pac[i].ypos+40+y]=0;
    }
}
 
for ( int i = 1; i < PacCount+1; i++ )
{
    for ( int x = 1; x < 139; x++ )
    for ( int y = 1; y < 19; y++ )
    {
        bitmap[pac[i].xpos+30+x][pac[i].ypos+40+y]=1;
    }
}
 
 
//-------------------------------------------------------------------------
// Write line from pac to dep
 
 
for ( int i = 1; i < PacCount+1; i++ )
{
    for ( int j = 1; j < pac[i].depAmount+1; j++ )
    {
        cout << i << ';' << pac[i].depNumber[j] << ' ';
        int x1=pac[i].xpos+170;
        int y1=pac[i].ypos+60;
        int x2=pac[pac[i].depNumber[j]].xpos+30;
        int y2=pac[pac[i].depNumber[j]].ypos+40;
        DrawLine(x2,y2,x1,y1);
    }  
    cout << endl;
}
 
 
//-------------------------------------------------------------------------
// Test result
 
 
 for ( int i = 1; i < PacCount+1; i++ )
{
    cout << pac[i].name << ',' << pac[i].level << ',' << pac[i].xpos <<',' << pac[i].ypos << ':';
    cout << "\n";
}
 
 
 /*
for ( int i = 1; i < PacCount+1; i++ )
{
    cout << pac[i].name << ',' << pac[i].level << ':';
    for ( int j = 1; j < pac[i].depAmount+1; j++ )
    {
        cout << pac[i].depNumber[j] << ' ';
    }
    cout << "\n";
}
 
 
//  DrawLine( x1, y1, x2, y2);
    DrawLine(200,400,100,100);
    DrawLine(100,500,100,100);     
    DrawLine(500,200,100,200);
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
 
}
