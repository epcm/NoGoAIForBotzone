//如果你要看真正的源码的话，请访问github
//https://github.com/lwh9346/NoGoBot
#pragma GCC optimize(2)
#include "./jsoncpp/json.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#define minInt -2147483648
#define branchNum 81
using namespace std;
void gasFinding(int x, int y, int i, int j, int groupIndex, int board[9][9], char group[9][9], char groupGasState[81], char groupGasPosition[81][2], char positionState[9][9], char unicGasGroup[9][9])
{
    if (board[i][j] == 0)
    {
        switch (groupGasState[groupIndex])
        {
        case 0:
            groupGasPosition[groupIndex][0] = i;
            groupGasPosition[groupIndex][1] = j;
            groupGasState[groupIndex] = 1;
            if (board[x][y] == 1)
            {
                positionState[i][j] |= 2;
            }
            else
            {
                positionState[i][j] |= 1;
                if (unicGasGroup[i][j] == -1 && board[x][y] == -1)
                {
                    unicGasGroup[i][j] = groupIndex;
                }
            }
            break;
        case 1:
            if (groupGasPosition[groupIndex][0] == i && groupGasPosition[groupIndex][1] == j)
            {
                break;
            }
            groupGasState[groupIndex] = 2;
            if (board[x][y] == 1)
            {
                positionState[(int)groupGasPosition[groupIndex][0]][(int)groupGasPosition[groupIndex][1]] |= 4;
                positionState[i][j] |= 4;
            }
            else if (unicGasGroup[(int)groupGasPosition[groupIndex][0]][(int)groupGasPosition[groupIndex][1]] == groupIndex)
            {
                positionState[(int)groupGasPosition[groupIndex][0]][(int)groupGasPosition[groupIndex][1]] = positionState[(int)groupGasPosition[groupIndex][0]][(int)groupGasPosition[groupIndex][1]] / 2 * 2;
                unicGasGroup[(int)groupGasPosition[groupIndex][0]][(int)groupGasPosition[groupIndex][1]] = -1;
            }
            break;
        case 2:
            if (board[x][y] == 1)
            {
                positionState[i][j] |= 4;
            }
            break;
        }
    }
}
void grouping(int x, int y, int groupIndex, int board[9][9], char group[9][9], char groupGasState[81], char groupGasPosition[81][2], char positionState[9][9], char unicGasGroup[9][9])
{
    group[x][y] = groupIndex;
    if (x != 0)
    {
        gasFinding(x, y, x - 1, y, groupIndex, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
    }
    if (y != 0)
    {
        gasFinding(x, y, x, y - 1, groupIndex, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
    }
    if (x != 8)
    {
        gasFinding(x, y, x + 1, y, groupIndex, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
    }
    if (y != 8)
    {
        gasFinding(x, y, x, y + 1, groupIndex, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
    }
    if (x != 0 && group[x - 1][y] == -1 && board[x][y] == board[x - 1][y])
    {
        grouping(x - 1, y, groupIndex, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
    }
    if (y != 0 && group[x][y - 1] == -1 && board[x][y] == board[x][y - 1])
    {
        grouping(x, y - 1, groupIndex, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
    }
    if (x != 8 && group[x + 1][y] == -1 && board[x][y] == board[x + 1][y])
    {
        grouping(x + 1, y, groupIndex, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
    }
    if (y != 8 && group[x][y + 1] == -1 && board[x][y] == board[x][y + 1])
    {
        grouping(x, y + 1, groupIndex, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
    }
}
int getValidPositions(int board[9][9], int result[9][9])
{
    int r = 0;
    int groupCount = 0;
    char group[9][9];
    char unicGasGroup[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            unicGasGroup[i][j] = -1;
            group[i][j] = -1;
        }
    }
    char groupGasState[81] = {0};
    char groupGasPosition[81][2] = {0};
    char positionState[9][9] = {0};
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (group[i][j] != -1 || board[i][j] == 0)
            {
                continue;
            }
            grouping(i, j, groupCount, board, group, groupGasState, groupGasPosition, positionState, unicGasGroup);
            groupCount++;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != 0)
            {
                result[i][j] = 0;
                continue;
            }
            if (positionState[i][j] % 2 == 1)
            {
                result[i][j] = 0;
                continue;
            }
            if (positionState[i][j] / 4 == 1)
            {
                result[i][j] = 1;
                r++;
                continue;
            }
            if (positionState[i][j] / 2 % 2 == 1)
            {
                if ((i != 0 && board[i - 1][j] == 0) || (j != 0 && board[i][j - 1] == 0) || (i != 8 && board[i + 1][j] == 0) || (j != 8 && board[i][j + 1] == 0))
                {
                    result[i][j] = 1;
                    r++;
                }
                else
                {
                    result[i][j] = 0;
                }
                continue;
            }
            if ((i == 0 || board[i - 1][j] == -1) && (j == 0 || board[i][j - 1] == -1) && (i == 8 || board[i + 1][j] == -1) && (j == 8 || board[i][j + 1] == -1))
            {
                result[i][j] = 0;
                continue;
            }
            result[i][j] = 1;
            r++;
        }
    }
    return r;
}
class treeNode
{
public:
    treeNode *parent;
    treeNode *children[branchNum];
    int board[9][9];
    int childrenAction[branchNum][2];
    int childrenCount;
    int childrenCountMax;
    double q;
    int n;
    double score;
    int *countPtr;
    treeNode(int parentBoard[9][9], int action[2], treeNode *p, int *countp)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                board[i][j] = -parentBoard[i][j];
            }
        }
        board[action[0]][action[1]] = -1;
        parent = p;
        q = 0;
        n = 0;
        childrenCount = 0;
        countPtr = countp;
        evaluate();
    }
    treeNode *treePolicy()
    {
        if (childrenCountMax == 0)
        {
            return this;
        }
        if (childrenCountMax > childrenCount)
        {
            treeNode *c = new treeNode(board, childrenAction[childrenCount], this, countPtr);
            children[childrenCount] = c;
            childrenCount++;
            return c;
        }
        for (int i = 0; i < childrenCount; i++)
        {
            children[i]->score = children[i]->q / double(children[i]->n) + 0.2 * sqrt(log(double(*countPtr)) / double(children[i]->n));
        }
        int bestChild = 0;
        double maxScore = 0;
        for (int i = 0; i < childrenCount; i++)
        {
            if (maxScore < children[i]->score)
            {
                bestChild = i;
                maxScore = children[i]->score;
            }
        }
        return children[bestChild]->treePolicy();
    }
    double simulation()
    {
        int boardR[9][9];
        int res[9][9];
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                boardR[i][j] = -board[i][j];
            }
        }
        int x = getValidPositions(board, res);
        int y = getValidPositions(boardR, res);
        if (x + y == 0)
        {
            return 0.0;
        }
        if (y == 0)
        {
            return 1.0;
        }
        if (x == 0)
        {
            return -1.0;
        }
        double rate = tanh(double(x - y) / double(x + y));
        return rate;
    }
    void backup(double delta)
    {
        treeNode *node = this;
        int d = 0;
        while (node != nullptr)
        {
            if (1 == d % 2)
            {
                node->q += delta;
            }
            else
            {
                node->q -= delta;
            }
            node->n++;
            node = node->parent;
            d++;
        }
    }

private:
    void evaluate()
    {
        int result[9][9];
        int validPositionCount = getValidPositions(board, result);
        int validPositions[81];
        int n = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (result[i][j])
                {
                    validPositions[n] = 9 * i + j;
                    n++;
                }
            }
        }
        childrenCountMax = validPositionCount;
        for (int i = 0; i < validPositionCount; i++)
        {
            childrenAction[i][0] = validPositions[i] / 9;
            childrenAction[i][1] = validPositions[i] % 9;
        }
    }
};
int main()
{
    int count = 0;
    int board[9][9] = {0};
    srand(clock());
    string str;
    getline(cin, str);
    int start = clock();
    int timeout = (int)(0.95 * (double)CLOCKS_PER_SEC);
    Json::Reader reader;
    Json::Value input;
    reader.parse(str, input);
    int turnID = input["responses"].size();
    int x, y;
    for (int i = 0; i < turnID; i++)
    {
        x = input["requests"][i]["y"].asInt(), y = input["requests"][i]["x"].asInt();
        if (x != -1)
            board[x][y] = 1;
        x = input["responses"][i]["y"].asInt(), y = input["responses"][i]["x"].asInt();
        if (x != -1)
            board[x][y] = -1;
    }
    x = input["requests"][turnID]["y"].asInt(), y = input["requests"][turnID]["x"].asInt();
    int actionR[2] = {x, y};
    treeNode root(board, actionR, nullptr, &count);
    while (clock() - start < timeout)
    {
        count++;
        treeNode *node = root.treePolicy();
        double result = node->simulation();
        node->backup(result);
    }
    int max = 0;
    int maxI = 0;
    int *bestAction = root.childrenAction[0];
    for (int i = 0; i < root.childrenCount; i++)
    {
        if (max < root.children[i]->n)
        {
            maxI = i;
            max = root.children[i]->n;
            bestAction = root.childrenAction[i];
        }
    }
    Json::Value ret;
    Json::Value action;
    action["x"] = bestAction[1];
    action["y"] = bestAction[0];
    ret["response"] = action;
    char buffer[4096];
    sprintf(buffer, "MCTS节点数:%d,当前预估胜率:%.3f", count, (((double)(root.children[maxI]->q)) / ((double)root.children[maxI]->n) + 1.0) * 0.5);
    ret["debug"] = buffer;
    Json::FastWriter writer;
    cout << writer.write(ret) << endl;
}