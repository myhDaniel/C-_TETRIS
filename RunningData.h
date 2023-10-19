#ifndef RUNNINGDATA_H
#define RUNNINGDATA_H
class RunningData
{
public:
	int now_x;
	int now_y;
	int map[10][15];
	RunningData()
	{
		now_x=0;
		now_y=0;
		for (int j=0;j<=14;j++)
		{
			for (int i=0;i<=9;i++)
			{
				map[i][j]=0;
			}
		}
	}
	
};

#endif