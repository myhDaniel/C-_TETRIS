#ifndef USER_H
#define USER_H

#include <graphics.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <string>
#include <iostream>
//InitUser类用于记录用户偏好
class InitUser
{
public:
	char ID[11];     //用户ID
	int gameSize;    //窗口大小选择
	int bgPictureNum;//游戏背景图片选择
	int bgMusicNum;  //游戏背景音乐选择
	//载入游戏首页
	void initStart(int windowSize_x,int windowSize_y)
	{
		initgraph(windowSize_x,windowSize_y);
		IMAGE img;
		loadimage(&img,"frontpage.png",windowSize_x,windowSize_y);
		putimage(0,0,&img);
		std::cout<<"*************************************************************"<<std::endl;
		std::cout<<"                     Welcome to TETRIS!"<<std::endl;
		std::cout<<"                     ^"<<" for rotation"<<std::endl;
		std::cout<<"                     v"<<" for moving down"<<std::endl;
		std::cout<<"                     <"<<" for moving left"<<std::endl;
		std::cout<<"                     >"<<" for moving right"<<std::endl;
		std::cout<<"                     space   for pause"<<std::endl;
		std::cout<<"                Press any to start the game!"<<std::endl;
		std::cout<<"*************************************************************"<<std::endl;		
		_getch();
		closegraph();		
	}
	//设置用户偏好
	void setInit()
	{
		char _ID[11];
		int _gameSize;
		int _bgp;
		int _bgm;
		std::cout<<"Please enter your name:[No longer than 10]"<<std::endl;
		std::cin>>_ID;
		strncpy(ID,_ID,sizeof(ID));
		
		std::cout<<"Which size do you prefer?[Enter the number]"<<std::endl;
		std::cout<<"1.Small size"<<std::endl;
		std::cout<<"2.Big size"<<std::endl;
		std::cin>>_gameSize;
		while(!(_gameSize==1||_gameSize==2))
		{
			std::cout<<"Error!Please choose again:"<<std::endl;
			std::cin>>_gameSize;
		}
		gameSize=_gameSize;
		
		std::cout<<"Which style of background picture do you prefer?[Enter the number]"<<std::endl;
		std::cout<<"1.Mild Night"<<std::endl;
		std::cout<<"2.Desert Castle"<<std::endl;
		std::cout<<"3.Sunny Forest"<<std::endl;
		std::cin>>_bgp;
		while(!(_bgp==1||_bgp==2||_bgp==3))
		{
			std::cout<<"Error!Please choose again:"<<std::endl;
			std::cin>>_bgp;
		}
		bgPictureNum=_bgp;	
		
		std::cout<<"What kind of background music do you like?[Enter the number]"<<std::endl;
		std::cout<<"1.Excited Moment"<<std::endl;
		std::cout<<"2.Sweet Time"<<std::endl;
		std::cout<<"3.Soft Night"<<std::endl;
		std::cin>>_bgm;
		while(!(_bgm==1||_bgm==2||_bgm==3))
		{
			std::cout<<"Error!Please choose again:"<<std::endl;
			std::cin>>_bgm;
		}
		bgMusicNum=_bgm;		
			
	}
	//播放背景音乐
	void playMusic()
	{
		if (bgMusicNum==1)
		{
			mciSendString("open Mistletoe.mp3", 0, 0, 0);
			mciSendString("play Mistletoe.mp3 repeat",0,0,0);
		}
		else if(bgMusicNum==2)
		{
			mciSendString("open Listen_to_your_Mom.mp3", 0, 0, 0);
			mciSendString("play Listen_to_your_Mom.mp3 repeat",0,0,0);			
		}
		else if (bgMusicNum==3)
		{
			mciSendString("open Shinest_star.mp3", 0, 0, 0);
			mciSendString("play Shinest_star.mp3 repeat",0,0,0);			
		}
	}
};

//UserRecord类用于记录有效用户得分
class UserRecord
{
private:
	char id[11];//用户ID
	int score;  //用户得分 
public:
	UserRecord(char* _id="",int _score=0)
	{
		strncpy(id,_id,sizeof(id));
		score=_score;
	}	
	char* getId()
	{
		return this->id;
	}
	int getScore()
	{
		return score;
	}
	void setID(char* _id)
	{
		strncpy(id,_id,sizeof(id));
	}
	void setScore(int _score)
	{
		score=_score;
	}
};

#endif