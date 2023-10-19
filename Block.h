#ifndef BLOCK_H
#define BLOCK_H

class Block
{
protected:
	int blockType;    //方块类型
	COLORREF color;	  //方块颜色
	int rotationIndex;//方块旋转状态
public:
	//Block类构造函数
	Block(int a = 0, COLORREF b = RED, int c = 0)
	{
		blockType = a;
		color = b;
		rotationIndex = c;
	}
	// 绘制方块
	virtual void draw(int) {}; //一般绘制
	virtual void drawFinal(int, int, int, int(*)[15], COLORREF(*)[15], COLORREF) {};//最终状态（即方块已不可移动）绘制	
	//清除方块
	virtual void Clear(int) {};
	//判断是否可在指定位置绘制方块
	virtual bool ifEmpty(int, int, int, int(*)[15]) { return 0; };
	
	//方块行为：左移、右移、下移、旋转	
	void moveLeft(int size, int(*blockMap)[15], int& _x, int& _y)
	{
		if (ifEmpty(_x - size, _y, size, blockMap))
			_x -= size;
	}
	void moveRight(int size, int(*blockMap)[15], int& _x, int& _y)
	{
		if (ifEmpty(_x + size, _y, size, blockMap))
			_x += size;
	}
	bool moveDown(int size, int(*blockMap)[15], int& _x, int& _y)
	{
		if (ifEmpty(_x, _y+size, size, blockMap))
		{
			_y += size;
			return 1;
		}
		return 0;
	}
	virtual void rotate(int,int (*)[15],int,int,int &){};
	
	//判断当前状态下首行是否已经存在方块，即本轮游戏是否结束
	bool ifOver(int(*blockMap)[15])
	{
		for (int i = 0; i < 10; ++i)
		{
			if (blockMap[i][0])
				return true;
		}
		return false;
	}	
	//以下函数用于判断某一行是否已满，若该行已满则清行并增加得分
	void clearLine(int(*blockMap)[15], int(*tempBlockMap)[15], COLORREF(*colorMap)[15], COLORREF(*tempColorMap)[15], int& score,int &counter)
	{
		for (int j = 0; j <= 14; j++)
		{
			for (int i = 0; i <= 9; i++)
			{
				tempBlockMap[i][j] = 0;
			}
		}
		for (int j = 0; j <= 14; j++)
		{
			for (int i = 0; i <= 9; i++)
			{
				tempColorMap[i][j] = 0;
			}
		}
		int _j = 14;
		for (int j = 14; j >= 0; --j)
		{
			int cnt = 0;
			for (int i = 0; i < 10; ++i)
				if (blockMap[i][j])
					++cnt;
			if (cnt != 10)
			{
				for (int i = 0; i < 10; ++i)
				{
					tempBlockMap[i][_j] = blockMap[i][j];
					tempColorMap[i][_j] = colorMap[i][j];
				}
				_j--;
			}
			else
			{		
				score++;
				counter++;
			}
				
		}
		for (int j = 0; j < 15; ++j)
			for (int i = 0; i < 10; ++i)
			{
				blockMap[i][j] = tempBlockMap[i][j];
				colorMap[i][j] = tempColorMap[i][j];
			}
	}
	//以下成员函数用于访问数据成员
	int getType()
	{
		return blockType;
	}
	COLORREF getColor()
	{
		return color;
	}
	int getRotation()
	{
		return rotationIndex;
	}
};

#endif