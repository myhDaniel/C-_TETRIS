#ifndef GAMEBG_H
#define GAMEBG_H

#include <graphics.h>
#include "GameData.h"

class GameBG
{
public:
	//根据用户偏好，载入指定的游戏背景图片
	void addImage(int windowSide_x,int windowSide_y,int u)
	{
		IMAGE img;
		if (u==1)
		{
			loadimage(&img,"MildNight.png",windowSide_x,windowSide_y);
			putimage(0,0,&img);		
		}
		else if (u==2)
		{
			loadimage(&img,"DesertCastle.jpg",windowSide_x,windowSide_y);
			putimage(0,0,&img);				
		}
		else if (u==3)
		{
			loadimage(&img,"SunnyForest.jpg",windowSide_x,windowSide_y);
			putimage(0,0,&img);	
		}
	}
};

#endif