#ifndef RUNNINGSTATE_H
#define RUNNINGSTATE_H

#include <graphics.h>
#include "Block.h"
#include<iostream>
class RunningState
{
public:
	int now_x;//当前方块左上角横坐标  
	int now_y;//当前方块左上角纵坐标
	
	int now_type;   //当前方块类型	
	int now_r;      //当前方块旋转状态
	COLORREF now_c;	//当前方块颜色

	int next_type;  //下一方块类型
	int next_r;     //下一方块旋转状态
	COLORREF next_c;//下一方块颜色
	
	int t;			 //当前自设备启动后的毫秒数					
	int timeGap;     //下落时间间隔
	int getNextBlock;//作为标志，指示是否在游戏区域绘制下一方块
	int gameOver;    //作为标志，指示本轮游戏是否结束
	int score;       //当前游戏分数
	int level;       //当前难度等级
	int counter;     //计数器，用于记录得分增加的次数，每满10次，难度等级加1
	
	int blockMap[10][15];         //方块图，记录已固定的方块
	int tempBlockMap[10][15];     //临时方块图
	COLORREF colorMap[10][15];    //方块颜色图，记录已固定的方块对应的颜色
	COLORREF tempColorMap[10][15];//临时方块颜色图
	
	COLORREF colors[7];//调色板
	
	
	RunningState(int x=0,int y=0,int _now_type=0,int _t=0,int _gap=1000,COLORREF _now_c=RED,int _r=1,int g_n=0,int g_o=0,int s=0,int _l=1,int _counter=0):colors{ RGB(255, 0, 0), RGB(255, 165, 0), RGB(255, 255, 0), RGB(0, 128, 0), RGB(0, 255, 255), RGB(0, 0, 255), RGB(128, 0, 128) }
	{
		now_x=x;
		now_y=y;
		now_type=_now_type;
		t=_t;
		timeGap=_gap;
		now_c=_now_c;
		now_r=_r;
		getNextBlock=g_n;
		gameOver=g_o;
		score=s;
		level=_l;
		counter=_counter;
	
		for (int j=0;j<=14;j++)
		{
			for (int i=0;i<=9;i++)
			{
				blockMap[i][j]=0;
				//std::cout<<mp[i][j]<<" ";
			}
			//std::cout<<std::endl;
		}
		for (int j=0;j<=14;j++)
		{
			for (int i=0;i<=9;i++)
			{
				tempBlockMap[i][j]=0;
			}
		}
		for (int j=0;j<=14;j++)
		{
			for (int i=0;i<=9;i++)
			{
				colorMap[i][j]=RED;
			}
		}
		for (int j=0;j<=14;j++)
		{
			for (int i=0;i<=9;i++)
			{
				tempColorMap[i][j]=RED;
			}
		}				
	}	
};

#endif