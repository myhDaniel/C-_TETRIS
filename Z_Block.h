#ifndef Z_BLOCK_H
#define Z_BLOCK_H

#include "Block.h"
#include <graphics.h>
#include <iostream>
class Z_Block:public Block
{
private:
	int x;
	int y;
public:
	Z_Block(int _x,int _y,COLORREF c,int rot):Block(6,c,rot)
	{
		x=_x;
		y=_y;
	}
	void draw(int size)
	{
		if (rotationIndex==1)
		{
			setfillcolor(color);
			fillrectangle(x,y,x+size,y+size);
			fillrectangle(x+size,y,x+2*size,y+size);
			fillrectangle(x+size,y+size,x+2*size,y+2*size);
			fillrectangle(x+2*size,y+size,x+3*size,y+2*size);
		}
		else if (rotationIndex==2)
		{			
			setfillcolor(color);
			fillrectangle(x,y+size,x+size,y+2*size);
			fillrectangle(x,y+2*size,x+size,y+3*size);
			fillrectangle(x+size,y,x+2*size,y+size);
			fillrectangle(x+size,y+size,x+2*size,y+2*size);
		}		
	}
	void Clear(int size)
	{
		if (rotationIndex==1)
		{
			clearrectangle(x,y,x+size,y+size);
			clearrectangle(x+size,y,x+2*size,y+size);
			clearrectangle(x+size,y+size,x+2*size,y+2*size);
			clearrectangle(x+2*size,y+size,x+3*size,y+2*size);
		}
		else if (rotationIndex==2)
		{
			clearrectangle(x,y+size,x+size,y+2*size);
			clearrectangle(x,y+2*size,x+size,y+3*size);
			clearrectangle(x+size,y,x+2*size,y+size);
			clearrectangle(x+size,y+size,x+2*size,y+2*size);
		}	
	}
	bool ifEmpty(int _x,int _y,int size,int (*blockMap)[15])
	{
		int sq_x[4];
		int sq_y[4];
		if (rotationIndex==1)
		{
			sq_x[0]=_x/size;
			sq_x[1]=_x/size+1;
			sq_x[2]=_x/size+1;
			sq_x[3]=_x/size+2;
			
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
				if (blockMap[sq_x[i]][sq_y[i]])
				{
					return false;
				}					
			}

			return true;
		}
		else if (rotationIndex==2)
		{
			sq_x[0]=_x/size+1;
			sq_x[1]=_x/size+1;
			sq_x[2]=_x/size;
			sq_x[3]=_x/size;
			
			sq_y[0]=_y/size;
			sq_y[1]=_y/size+1;
			sq_y[2]=_y/size+1;
			sq_y[3]=_y/size+2;

			for (int i = 0; i < 4; ++i)
			{
				if (sq_x[i] < 0 || sq_x[i] > 9 || sq_y[i] > 14)
					return false;
				if (sq_y[i] < 0) 
					continue;
				if (blockMap[sq_x[i]][sq_y[i]])
					return false;
			}
			return true;			
		}
		return false;	
	}
	void drawFinal(int _x, int _y, int size, int(*blockMap)[15], COLORREF(*colorMap)[15], COLORREF c)
	{
		
		int sq_x[4];
		int sq_y[4];
		if (rotationIndex == 1)
		{
			sq_x[0]=_x/size;
			sq_x[1]=_x/size+1;
			sq_x[2]=_x/size+1;
			sq_x[3]=_x/size+2;
			
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
		else if (rotationIndex == 2)
		{
			sq_x[0]=_x/size+1;
			sq_x[1]=_x/size+1;
			sq_x[2]=_x/size;
			sq_x[3]=_x/size;
			
			sq_y[0]=_y/size;
			sq_y[1]=_y/size+1;
			sq_y[2]=_y/size+1;
			sq_y[3]=_y/size+2;
			for (int i = 0; i < 4; ++i)
			{
				if (sq_y[i] >= 0)
				{
					blockMap[sq_x[i]][sq_y[i]] = 1;
					colorMap[sq_x[i]][sq_y[i]] = c;
				}
			}			
		}
	}
	void rotate(int size,int (*blockMap)[15],int _x,int _y,int &r)
	{
		if (rotationIndex==1)
		{
			Z_Block Z(_x,_y,0,2);
			if (Z.ifEmpty(_x,_y,size,blockMap))
				r=2;
		}
		else if (rotationIndex==2)
		{
			Z_Block Z(_x,_y,0,1);
			if (Z.ifEmpty(_x,_y,size,blockMap))
				r=1;
		}
	}			
};

#endif