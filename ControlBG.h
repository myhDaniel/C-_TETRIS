#ifndef CONTROLBG_H
#define CONTROLBG_H

#include <graphics.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "Block.h"
#include "GameData.h"
#include "User.h"
class ControlBG
{
public:	
	//绘制预览区域的背景图
	void drawPreviewZone(int preview_x,int preview_y,int previewSize,int blocksize)
	{
		
		IMAGE img;
		loadimage(&img,"frame.jpg",previewSize+2*blocksize,previewSize+2*blocksize);
		putimage(preview_x-blocksize,preview_y-blocksize,&img);
	}
	//绘制得分区域背景图
	void drawScoreZone(int score_x,int score_y,int scoreSize)
	{
		IMAGE img;
		loadimage(&img,"score.jpg",scoreSize,scoreSize/2);
		putimage(score_x,score_y,&img);
	}
	//绘制难度等级区域背景图
	void drawLevelZone(int level_x,int level_y,int levelSize)
	{
		IMAGE img;
		loadimage(&img,"level.jpg",levelSize,levelSize/2);
		putimage(level_x,level_y,&img);
	}
	//弹出暂停窗口
	void popPauseBar()
	{
		HWND hWnd = GetConsoleWindow(); 
	
	    int result = MessageBox(hWnd, "Game paused: Continue?", "Notice", MB_OKCANCEL | MB_ICONINFORMATION);
	
	    if (result == IDOK) 
	    {
			//选择“确定”则继续游戏
	    }
	    else if (result == IDCANCEL) 
	    {
	    	//选择“取消”则退出游戏窗口
			exit(0);
	    }
	}
	//追加用户得分记录
	void Append(char *id,int score)
	{
		std::ofstream appendfile("Users_Records",std::ios::binary|std::ios::app);
		if (!appendfile)
		{
			std::cout<<"Failed to open file to append"<<std::endl;
			exit(0);
		}
		UserRecord u(id,score);
		appendfile.write(reinterpret_cast<const char*>(&u),sizeof(u));
		appendfile.close();
	}
	//本机用户得分排序
	void SelectSort(UserRecord a[],int size)
	{
		int min;
		for (int j = 0; j <= size-2; j++)
		{
			min = j;
			for (int i = j; i <=size-1 ; i++)
			{
				if (a[i].getScore() < a[min].getScore())
				{
					min = i;
				}
			}
			UserRecord temp=a[j];
			a[j]=a[min];
			a[min]=temp;
		}
	}
	//输出本机用户得分	
	void Print(int size)
	{
		UserRecord u;
		std::ifstream printfile("Users_Records",std::ios::binary|std::ios::in);
		if (!printfile)
		{
			std::cout<<"Failed to open file to print"<<std::endl;
			exit(0);
		}
		printfile.seekg(0,std::ios::end);
		int n=printfile.tellg()/sizeof(UserRecord);
		UserRecord users[n];
		//int i=5;
		printfile.seekg(0,std::ios::beg);
		int j=0;
		while(printfile.read(reinterpret_cast<char*>(&u),sizeof(u)))
		{
			users[j].setID(u.getId());
			users[j].setScore(u.getScore());
			j++;
		}
		SelectSort(users,n);
		int k=5;
		for (int i=n-1;i>=0;i--)
		{
			COLORREF tempc=getcolor();
			setcolor(WHITE);
			RECT r1={4*size,k*size,6*size,(k+1)*size};
			drawtext(users[i].getId(),&r1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			char score[32];
			sprintf_s(score,32,"%d",users[i].getScore()*1000);
			RECT r2={6*size,k*size,8*size,(k+1)*size};
			drawtext(score,&r2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			setcolor(tempc);	
			k++;					
		}	
		printfile.close();
	}
	//弹出游戏结束窗口
	void popGameOver(char* id,int score,int size)
	{
		HWND hWnd = GetConsoleWindow(); 
	
	    int result = MessageBox(hWnd, "Game over: Play again?", "Notice", MB_OKCANCEL | MB_ICONINFORMATION);
	    
	    if (result == IDOK)
	    {
			//选择“确定”则再来一局，本次得分不存档
		}
	    else if (result == IDCANCEL) 
	    {
	    	//选择“取消”则展示本机用户得分排行榜，按任意键退出游戏窗口
	    	IMAGE img;
	    	loadimage(&img,"ranking.png",6*size,6*size);
		    putimage(2*size,4*size,&img);
		    IMAGE img1;
		    loadimage(&img1,"quit.png",6*size,size);
		    putimage(2*size,10*size,&img1);
		    Append(id,score);
		    Print(size);
			_getch();		
	        exit(0);
	    }	    
	}
};

#endif
	