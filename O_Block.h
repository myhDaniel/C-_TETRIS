#ifndef O_BLOCK_H
#define O_BLOCK_H

#include "Block.h"
#include <graphics.h>
class O_Block:public Block
{
private:
	int x;
	int y;
public:
	O_Block(int _x,int _y,COLORREF c,int rot):Block(3,c,rot)
	{
		x=_x;
		y=_y;
	}
	void draw(int size)
	{
		setfillcolor(color);
		fillrectangle(x,y,x+size,y+size);
		fillrectangle(x+size,y,x+2*size,y+size);
		fillrectangle(x,y+size,x+size,y+2*size);
		fillrectangle(x+size,y+size,x+2*size,y+2*size);		
	}
	void Clear(int size)
	{
		clearrectangle(x,y,x+size,y+size);
		clearrectangle(x+size,y,x+2*size,y+size);
		clearrectangle(x,y+size,x+size,y+2*size);
		clearrectangle(x+size,y+size,x+2*size,y+2*size);		
	}
	bool ifEmpty(int _x,int _y,int size,int (*mp)[15])
	{
		int sq_x[4];
		int sq_y[4];
		
		sq_x[0]=_x/size;
		sq_x[1]=_x/size+1;
		sq_x[2]=_x/size;
		sq_x[3]=_x/size+1;
			
		sq_y[0]=_y/size;
		sq_y[1]=_y/size;
		sq_y[2]=_y/size+1;
		sq_y[3]=_y/size+1;
			
		for (int i = 0; i < 4; ++i)
		{
			if (sq_x[i] < 0 || sq_x[i] > 9 || sq_y[i] > 14)
				{
					return false;
				}
			if (sq_y[i] < 0) 
				{
					continue;
				}
			if (mp[sq_x[i]][sq_y[i]])
				{
					return false;
				}					
		}
		return true;
	}	
	void drawFinal(int _x, int _y, int size, int(*blockMap)[15], COLORREF(*colorMap)[15], COLORREF c)
	{
		
		int sq_x[4];
		int sq_y[4];

		sq_x[0]=_x/size;
		sq_x[1]=_x/size+1;
		sq_x[2]=_x/size;
		sq_x[3]=_x/size+1;
			
		sq_y[0]=_y/size;
		sq_y[1]=_y/size;
		sq_y[2]=_y/size+1;
		sq_y[3]=_y/size+1;
		
		for (int i = 0; i < 4; ++i)
		{
			if (sq_y[i] >= 0)
			{
				blockMap[sq_x[i]][sq_y[i]] = 1;
				colorMap[sq_x[i]][sq_y[i]] = c;
			}
		}
	}
		
};

#endif