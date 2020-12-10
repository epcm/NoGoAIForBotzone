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