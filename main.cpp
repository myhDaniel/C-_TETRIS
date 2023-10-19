#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <string>

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "GameData.h"
#include "GameBG.h"
#include "ControlBG.h"
#include "RunningState.h"
#include "User.h"

#include "Block.h"
#include "I_Block.h"
#include "J_Block.h"
#include "L_Block.h"
#include "O_Block.h"
#include "S_Block.h"
#include "T_Block.h"
#include "Z_Block.h"
#include<iostream>
using namespace std;

int main()
{
	//初始化各项数据：用户偏好、游戏数据、运行数据
	InitUser init;
	init.setInit();
	GameData data(init.gameSize);
	GameBG gameBG;
	ControlBG controlBG;
	RunningState run(data.getGameSize_x() / 2, 0, 0, 0, 1000, BLUE, 1, 0, 0, 0,1,0);	
		
	//进入游戏：载入游戏首页、绘制游戏窗口、循环播放背景音乐
	init.initStart(data.getWin_x(),data.getWin_y());
	initgraph(data.getWin_x(), data.getWin_y());
	init.playMusic();
	srand(time(0));
	setbkmode(TRANSPARENT);	

	//游戏开始
	while (true)
	{	
		//清空方块图
		for (int i=0;i<=14;i++)
		{
			for (int j=0;j<=9;j++)
			{
				run.blockMap[j][i]=0;
			}
		}
		//清空方块颜色图
		for (int i=0;i<14;i++)
		{
			for (int j=0;j<=9;j++)
			{
				run.colorMap[j][i]=0;
			}
		}
		//生成下一个方块类型和旋转状态
		run.next_type=rand()%7;
		if (run.next_type==3)
		{
			run.next_r=1;
		}
		else if (run.next_type==0||run.next_type==4||run.next_type==6)
		{
			run.next_r=1+rand()%2;
		}
		else
		{
			run.next_r=1+rand()%4;
		}
		//生成下一个方块颜色		
		int i=rand()%7;
		run.next_c=run.colors[i];
		//重置页面状态：游戏结束标志、得分面板、难度等级面板、方块下落状态
		run.gameOver=0;
		run.score=0;
		run.counter=0;
		run.level=1;
		run.timeGap=1000;
		//开始当前方块下落
		while (!run.gameOver)
		{
			//获取当前方块各项数据
			run.now_x=data.getGameSize_x() / 2-data.getBlockSize();
			run.now_y=(-4)*data.getBlockSize();
			run.getNextBlock=0;
			run.now_type=run.next_type;
			run.now_r=run.next_r;
			run.now_c=run.next_c;
			//生成下一方块各项数据
			run.next_type=rand()%7;
			if (run.next_type==3)
			{
				run.next_r=1;
			}
			else if (run.next_type==0||run.next_type==4||run.next_type==6)
			{
				run.next_r=1+rand()%2;
			}
			else
			{
				run.next_r=1+rand()%4;
			}
			i=rand()%7;
			run.next_c=run.colors[i];							
			while(!run.getNextBlock)
			{
				//插入游戏区域和控制区域背景图片
				BeginBatchDraw();//与下面的FlushBatchDraw()和EndBatchDraw()搭配使用，消除闪屏现象
				gameBG.addImage(data.getWin_x(),data.getWin_y(),init.bgPictureNum);
				controlBG.drawPreviewZone(data.getPre_x(),data.getPre_y(),data.getPreSize(),data.getBlockSize());
				//设置双指针，p1代表下一方块，p2代表当前方块
				Block* p1=NULL;
				Block* p2=NULL;

				//绘制下一个方块
				switch(run.next_type)
				{
					case 0:p1=new I_Block(data.getPre_x(),data.getPre_y(),run.next_c,run.next_r);break;
					case 1:p1=new J_Block(data.getPre_x(),data.getPre_y(),run.next_c,run.next_r);break;
					case 2:p1=new L_Block(data.getPre_x(),data.getPre_y(),run.next_c,run.next_r);break;
					case 3:p1=new O_Block(data.getPre_x(),data.getPre_y(),run.next_c,run.next_r);break;
					case 4:p1=new S_Block(data.getPre_x(),data.getPre_y(),run.next_c,run.next_r);break;
					case 5:p1=new T_Block(data.getPre_x(),data.getPre_y(),run.next_c,run.next_r);break;
					case 6:p1=new Z_Block(data.getPre_x(),data.getPre_y(),run.next_c,run.next_r);break;
																																	
				}
				p1->draw(data.getBlockSize());	
				
				//输出目前得分
				controlBG.drawScoreZone(data.getScore_x(),data.getScore_y(),data.getScoreSize());
				char str1[32];
				sprintf_s(str1,32,"%d",run.score*1000);
				COLORREF tempc=getcolor();
				setcolor(WHITE);
				RECT r1={data.getScore_x()+data.getBlockSize(),data.getScore_y()+data.getBlockSize(),data.getScore_x()+3*data.getBlockSize(),data.getScore_y()+2*data.getBlockSize()};
				drawtext(str1,&r1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				setcolor(tempc);

				//更新并输出当前难度等级
				if (run.counter>=10)
				{
					if (run.timeGap>200)
					{
						run.timeGap=run.timeGap-200;
						run.level=run.level+run.counter/10;
						run.counter=0;
					}
				}
				controlBG.drawLevelZone(data.getLevel_x(),data.getLevel_y(),data.getLevelSize());
				char str2[2];
				sprintf_s(str2,2,"%d",run.level);
				tempc=getcolor();
				setcolor(WHITE);
				RECT r2={data.getLevel_x()+data.getBlockSize(),data.getLevel_y()+2*data.getBlockSize(),data.getLevel_x()+3*data.getBlockSize(),data.getScore_y()+3*data.getBlockSize()};		
				drawtext(str2,&r2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				setcolor(tempc);
										
				//绘制已固定方块
				for (int i=0;i<=9;i++)
				{
					for (int j=0;j<=14;j++)
					{
						if (run.blockMap[i][j])
						{
							setfillcolor(run.colorMap[i][j]);
							fillrectangle(i*data.getBlockSize(), j*data.getBlockSize(), i*data.getBlockSize()+ data.getBlockSize(), j*data.getBlockSize()+ data.getBlockSize());
						}
					}
				}
							
				//绘制当前方块
				switch(run.now_type)
				{
					case 0:p2=new I_Block(run.now_x,run.now_y,run.now_c,run.now_r);break;
					case 1:p2=new J_Block(run.now_x,run.now_y,run.now_c,run.now_r);break;
					case 2:p2=new L_Block(run.now_x,run.now_y,run.now_c,run.now_r);break;
					case 3:p2=new O_Block(run.now_x,run.now_y,run.now_c,run.now_r);break;
					case 4:p2=new S_Block(run.now_x,run.now_y,run.now_c,run.now_r);break;
					case 5:p2=new T_Block(run.now_x,run.now_y,run.now_c,run.now_r);break;
					case 6:p2=new Z_Block(run.now_x,run.now_y,run.now_c,run.now_r);break;
				}					
				p2->draw(data.getBlockSize());
				
				FlushBatchDraw();
				
				//自动下降
				int newtime = GetTickCount();
				if (newtime - run.t >= run.timeGap)  
				{
					run.t = newtime;
					if (!p2->moveDown(data.getBlockSize(), run.blockMap, run.now_x, run.now_y))
					{
						run.getNextBlock = 1;
						p2->drawFinal(run.now_x, run.now_y, data.getBlockSize(), run.blockMap, run.colorMap, p2->getColor());
						p2->clearLine(run.blockMap, run.tempBlockMap, run.colorMap, run.tempColorMap, run.score,run.counter);
						if (p2->ifOver(run.blockMap))
							run.gameOver = 1;
				
					}
				}
				//移动当前方块
				if (_kbhit())  //判断是否有键按下
				{
					switch (_getch())
					{
						case 0xE0: //方向键
						{
							switch (_getch())
							{
								case 72: //上键：旋转 
								{
									if (p2->getType() == 3)//O型方块无需旋转
									{
										break;
									}
									else if (p2->getType() == 0 || p2->getType() == 4 || p2->getType() == 6)//I型、S型、Z型方块只有2种旋转方式
									{
										p2->Clear(data.getBlockSize());
										p2->rotate(data.getBlockSize(),run.blockMap,run.now_x,run.now_y,run.now_r);
									}
									else//其余类型方块均有4种旋转方式
									{
										p2->Clear(data.getBlockSize());
										p2->rotate(data.getBlockSize(),run.blockMap,run.now_x,run.now_y,run.now_r);
									}
									break;
								}
								case 75: //左键：左移
								{
									p2->Clear(data.getBlockSize());
									p2->moveLeft(data.getBlockSize(), run.blockMap, run.now_x, run.now_y);
									break;
								}
								case 77: //右键：右移 
								{
									p2->Clear(data.getBlockSize());
									p2->moveRight(data.getBlockSize(), run.blockMap, run.now_x, run.now_y);
									break;
								}
								case 80: //下键：下移
								{
									p2->Clear(data.getBlockSize());
									p2->moveDown(data.getBlockSize(),run.blockMap,run.now_x,run.now_y);
									if (!p2->moveDown(data.getBlockSize(), run.blockMap, run.now_x, run.now_y))
									{
										run.getNextBlock = 1;
										p2->drawFinal(run.now_x, run.now_y, data.getBlockSize(), run.blockMap, run.colorMap, p2->getColor());
										p2->clearLine(run.blockMap, run.tempBlockMap, run.colorMap, run.tempColorMap, run.score,run.counter);
										if (p2->ifOver(run.blockMap))
											run.gameOver = 1;

											
									}				
									break;
								}
							}
							break;
						}       
						case ' '://空格键
						{
							controlBG.popPauseBar();//弹出暂停窗口
							break;
						}	
					}
				}
					//释放双指针内存
					delete p1;
					delete p2;
			}
		}
		EndBatchDraw();
		//将当前用户得分存档并弹出游戏结束窗口
		UserRecord u(init.ID,run.score);
		controlBG.popGameOver(u.getId(),u.getScore(),data.getBlockSize());
	}
	_getch();
	closegraph();
	return 0;
}


