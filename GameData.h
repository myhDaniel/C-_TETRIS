#ifndef GAMEDATA_H
#define GAMEDATA_H

class GameData
{
protected:
	int windowSize_x;//窗口的长
	int windowSize_y;//窗口的宽
	int gameSize_x;  //游戏区域的长
	int previewSize; //预览框的大小
	int preview_x;   //预览框左上角横坐标
	int preview_y;   //预览框左上角纵坐标
	int scoreSize;   //得分区域的大小
	int score_x;     //得分区域左上角横坐标
	int score_y;     //得分区域左上角纵坐标
	int levelSize;   //难度等级区域的大小
	int level_x;     //难度等级区域的横坐标
	int level_y;     //难度等级区域的纵坐标
	int blockSize;   //方块边长大小

public:
	GameData(int u)
	{
		if (u==1)
		{
			windowSize_x=600;
			windowSize_y=540;
		    gameSize_x=360;
			previewSize=144;
			preview_x=360+48;
			preview_y=36+36;
			scoreSize=144;
			score_x=360+48;
			score_y=200+36+36;
			levelSize=144;
			level_x=360+48;
			level_y=300+36+36;
			blockSize=36;
		}
		else if (u==2)
		{
			windowSize_x=600*1.5;
			windowSize_y=540*1.5;
		    gameSize_x=360*1.5;
			previewSize=144*1.5;
			preview_x=(360+48)*1.5;
			preview_y=(36+36)*1.5;
			scoreSize=144*1.5;
			score_x=(360+48)*1.5;
			score_y=(200+36+36)*1.5;
			levelSize=144*1.5;
			level_x=(360+48)*1.5;
			level_y=(300+36+36)*1.5;
			blockSize=36*1.5;
		}
	}
	int getWin_x()
	{
		return windowSize_x;
	}
	int getWin_y()
	{
		return windowSize_y;
	}
	int getGameSize_x()
	{
		return gameSize_x;
	}
	int getPreSize()
	{
		return previewSize;
	}
	int getPre_x()
	{
		return preview_x;
	}
	int getPre_y()
	{
		return preview_y;
	}
	int getScoreSize()
	{
		return scoreSize;
	}
	int getScore_x()
	{
		return score_x;
	}
	int getScore_y()
	{
		return score_y;
	}
	int getLevelSize()
	{
		return levelSize;
	}
	int getLevel_x()
	{
		return level_x;
	}
	int getLevel_y()
	{
		return level_y;
	}
	int getBlockSize()
	{
		return blockSize;
	}

};

#endif