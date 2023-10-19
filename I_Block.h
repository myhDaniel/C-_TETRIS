#ifndef I_BLOCK_H
#define I_BLOCK_H

#include "Block.h"
#include <graphics.h>
#include<iostream>
class I_Block :public Block
{
private:
	int x;
	int y;
public:
	I_Block(int _x, int _y, COLORREF c, int rot) :Block(0, c, rot)
	{
		x = _x;
		y = _y;
	}
	void draw(int size)
	{
		if (rotationIndex == 1)
		{
			setfillcolor(color);
			fillrectangle(x, y, x + size, y + size);
			fillrectangle(x + size, y, x + 2 * size, y + size);
			fillrectangle(x + 2 * size, y, x + 3 * size, y + size);
			fillrectangle(x + 3 * size, y, x + 4 * size, y + size);
		}
		else if (rotationIndex == 2)
		{
			setfillcolor(color);
			fillrectangle(x, y, x + size, y + size);
			fillrectangle(x, y + size, x + size, y + 2 * size);
			fillrectangle(x, y + 2 * size, x + size, y + 3 * size);
			fillrectangle(x, y + 3 * size, x + size, y + 4 * size);
		}
	}
	void Clear(int size)
	{
		if (rotationIndex == 1)
		{
			clearrectangle(x, y, x + size, y + size);
			clearrectangle(x + size, y, x + 2 * size, y + size);
			clearrectangle(x + 2 * size, y, x + 3 * size, y + size);
			clearrectangle(x + 3 * size, y, x + 4 * size, y + size);
		}
		else if (rotationIndex == 2)
		{
			clearrectangle(x, y, x + size, y + size);
			clearrectangle(x, y + size, x + size, y + 2 * size);
			clearrectangle(x, y + 2 * size, x + size, y + 3 * size);
			clearrectangle(x, y + 3 * size, x + size, y + 4 * size);
		}
	}
	bool ifEmpty(int _x, int _y, int size, int(*blockMap)[15])
	{
		int sq_x[4];
		int sq_y[4];
		if (rotationIndex == 1)
		{
			for (int i = 0; i <= 3; i++)
			{
				sq_x[i] = _x / size + i;
			}
			for (int i = 0; i <= 3; i++)
			{
				sq_y[i] = _y / size;
			}
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
		else if (rotationIndex == 2)
		{
			for (int i = 0; i <= 3; i++)
			{
				sq_x[i] = _x / size;
			}
			for (int i = 0; i <= 3; i++)
			{
				sq_y[i] = _y / size + i;
			}
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
		return false;
	}
	void drawFinal(int _x, int _y, int size, int(*blockMap)[15], COLORREF(*colorMap)[15], COLORREF c)
	{
		
		int sq_x[4];
		int sq_y[4];
		if (rotationIndex == 1)
		{
			for (int i = 0; i <= 3; i++)
			{
				sq_x[i] = _x / size + i;
			}
			for (int i = 0; i <= 3; i++)
			{
				sq_y[i] = _y / size;
			}
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
			for (int i = 0; i <= 3; i++)
			{
				sq_x[i] = _x / size;
			}
			for (int i = 0; i <= 3; i++)
			{
				sq_y[i] = _y / size + i;
			}
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
			I_Block I(_x,_y,0,2);
			if (I.ifEmpty(_x,_y,size,blockMap))
				r=2;
		}
		else if (rotationIndex==2)
		{
			I_Block I(_x,_y,0,1);
			if (I.ifEmpty(_x,_y,size,blockMap))
				r=1;
		}
	}
};

#endif