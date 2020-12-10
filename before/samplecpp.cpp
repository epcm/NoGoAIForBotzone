// 不围棋（NoGo）样例程序
// 随机策略
// 作者：fffasttime
// 游戏信息：http://www.botzone.org/games#NoGo
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include "jsoncpp/json.h"
using namespace std;

int board[9][9];


bool dfs_air_visit[9][9];
const int cx[]={-1,0,1,0};
const int cy[]={0,-1,0,1};

bool inBorder(int x, int y){return x>=0 && y>=0 && x<9 && y<9;}

//true: has air，这规则算法写得比我的策略还漂亮
bool dfsAir(int fx, int fy)
{
	dfs_air_visit[fx][fy] = true;
	bool flag=false;
	for (int dir = 0; dir < 4; dir++) //某一位置有气的条件为周围有空格或者有一个邻近的同色有气(反证法进一步证明邻近的有一个有气即都有气)
	{
		int dx=fx+cx[dir], dy=fy+cy[dir];
		if (inBorder(dx, dy))
		{
			if (board[dx][dy] == 0)
				flag=true;
			if (board[dx][dy] == board[fx][fy] && !dfs_air_visit[dx][dy])
				if (dfsAir(dx, dy))
					flag=true;
		}
	}
	return flag;
}

//true: available
bool judgeAvailable(int fx, int fy, int col)
{
	if (board[fx][fy]) return false;
	board[fx][fy] = col;
	memset(dfs_air_visit, 0, sizeof(dfs_air_visit));
	if (!dfsAir(fx, fy))
	{
		board[fx][fy]  = 0;
		return false; 
	}
	for (int dir = 0; dir < 4; dir++)
	{
		int dx=fx+cx[dir], dy=fy+cy[dir];
		if (inBorder(dx, dy))
		{
			if (board[dx][dy] && !dfs_air_visit[dx][dy])
				if (!dfsAir(dx, dy))
				{
					board[fx][fy]  = 0;
					return false;
				}
		}
	}
	board[fx][fy]  = 0;
	return true;
}

int main()
{
	srand((unsigned)time(0));
	string str;
	int x,y;
	// 读入JSON
	getline(cin,str);
	//getline(cin, str);
	Json::Reader reader;
	Json::Value input;
	reader.parse(str, input); 
	// 分析自己收到的输入和自己过往的输出，并恢复状态
	int turnID = input["responses"].size();
	for (int i = 0; i < turnID; i++) 
	{
		x=input["requests"][i]["x"].asInt(), y=input["requests"][i]["y"].asInt();
		if (x!=-1) board[x][y]=1;
		x=input["responses"][i]["x"].asInt(), y=input["responses"][i]["y"].asInt();
		if (x!=-1) board[x][y]=-1;
	}
	x=input["requests"][turnID]["x"].asInt(), y=input["requests"][turnID]["y"].asInt();
	if (x!=-1) board[x][y]=1;
	// 输出决策JSON
	Json::Value ret;
	Json::Value action;
	
	//以下为随机策略 
	vector<int> available_list; //合法位置表 
	
	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
			if (judgeAvailable(i,j,x==-1?1:-1))
				available_list.push_back(i*9+j);
	int result=available_list[rand()%available_list.size()];

	
	action["x"]=result/9; action["y"]=result%9;
	ret["response"] = action;
	Json::FastWriter writer;
	
	cout << writer.write(ret) << endl;
	return 0;
}