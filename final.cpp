// 不围棋（NoGo）
// MCTS策略
// 作者：AAA
// 游戏信息：http://www.botzone.org/games#NoGo
// v3.4 继承自v3 重构代码
// Final
#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,no-stack-protector")

#include "jsoncpp/json.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

#define TIME_OUT_SET 0.98
#define EXPLORE 0.1

int board[9][9] = {0};
int node_count = 0;

bool dfs_air_visit[9][9] = {0};
const int cx[] = {-1, 0, 1, 0};
const int cy[] = {0, -1, 0, 1};

inline bool inBorder(int x, int y) { return x >= 0 && y >= 0 && x < 9 && y < 9; }


struct Action
{
    int x = -1;
    int y = -1;
};

class Node
{
    //Node的棋盘状态记录：包括评估值current_value,盘面current_board
    //实现有判断是否达terminal；simulation阶段的单步default policy
public:
    Node();
    signed char current_board[9][9] = {0};
    int col = 0;
    Node *parent = NULL;
    Node *children[81];
    int visit_times = 0;
    int countChildrenNum = 0;
    int maxChildrenNum = 0;
    double quality_value = 0.0;
    int available_choices[81];
    void getAviliableAction();           //得到可行的行动
    bool dfsAir(int fx, int fy);         //判断是否有气
    bool judgeAvailable(int fx, int fy); //判断是否可下
    double quickEvaluate();              //快速估值
    Node *bestChild(double C);
    Node *expand();
    Node *treePolicy();
    double defaultPolicy();
    void backup(double reward);
};

Node::Node()
{
    memset(current_board, 0, sizeof(current_board));
    memset(available_choices, 0, sizeof(available_choices));
}

double Node::quickEvaluate()
{
    int n1 = 0, n2 = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            bool f1 = judgeAvailable(i, j);
            col = -col;
            bool f2 = judgeAvailable(i, j);
            col = -col;
            if (f1 && !f2)
                n1 ++;
            else if (!f1 && f2)
                n2 ++;
        }
    return n2 - n1;
}

bool Node::dfsAir(int fx, int fy)
{
    dfs_air_visit[fx][fy] = true;
    bool flag = false;
    for (int dir = 0; dir < 4; dir++) //某一位置有气的条件为周围有空格或者有一个邻近的同色有气(反证法进一步证明邻近的有一个有气即都有气)
    {
        int dx = fx + cx[dir], dy = fy + cy[dir];
        if (inBorder(dx, dy))
        {
            if (current_board[dx][dy] == 0)
                flag = true;
            if (current_board[dx][dy] == current_board[fx][fy] && !dfs_air_visit[dx][dy])
                if (dfsAir(dx, dy))
                {
                    flag = true;
                    
                }
        }
    }
    return flag;
}

bool Node::judgeAvailable(int fx, int fy)
{
    if (current_board[fx][fy])
        return false;
    current_board[fx][fy] = col;
    memset(dfs_air_visit, 0, sizeof(dfs_air_visit));
    if (!dfsAir(fx, fy)) //判定自杀
    {
        current_board[fx][fy] = 0;
        return false;
    }
    for (int dir = 0; dir < 4; dir++) //不围对方
    {
        int dx = fx + cx[dir], dy = fy + cy[dir];
        if (inBorder(dx, dy))
        {
            if (current_board[dx][dy] && !dfs_air_visit[dx][dy])
            {
                if (!dfsAir(dx, dy))
                {
                    current_board[fx][fy] = 0;
                    return false;
                }
            }
        }
    }
    current_board[fx][fy] = 0;
    return true;
}

void Node::getAviliableAction()
{
    memset(available_choices, 0, sizeof(available_choices));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (judgeAvailable(i, j))
            {
                int act = i * 9 + j;
                available_choices[maxChildrenNum++] = act;
            }
}

//使用UCB算法，权衡exploration和exploitation后选择得分最高的子节点，注意如果是预测阶段直接选择当前Q值得分最高的。
Node *Node::bestChild(double C)
{
    double max_score = -2e50; //参数开始设成了2e-50，难怪会返回NULL
    Node *best_child = NULL;
    for (int i = 0; i < countChildrenNum; i++)
    {
        Node *p = children[i];
        double score = p->quality_value / (p->visit_times) + 2 * C * sqrt(log(2 * visit_times) / (p->visit_times));
        if (score > max_score)
        {
            max_score = score;
            best_child = p;
        }
    }
    return best_child;
}

Node *Node::expand()
{

    int a = available_choices[countChildrenNum];
    int x = a / 9;
    int y = a % 9;
    Node *new_node = new Node;
    children[countChildrenNum++] = new_node;
    new_node->parent = this;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            new_node->current_board[i][j] = current_board[i][j];
    new_node->col = -col;
    new_node->current_board[x][y] = col;
    new_node->getAviliableAction();
    return new_node;
}

Node *Node::treePolicy()
{
    //Selection与Expansion阶段。传入当前需要开始搜索的节点，根据UCB1值返回最好的需要expend的节点，注意如果节点是叶子结点直接返回。
    //基本策略是先找当前未选择过的子节点，如果有多个则随机选。如果都选择过就找权衡过exploration/exploitation的UCB值最大的，如果UCB值相等则随机选。
    if (maxChildrenNum == 0) //当treePolicy到达叶节点时(node->state.available_choices.empty() && node->children.empty())
    {
        //cout << "leaf";
        return this;
    }
    if (countChildrenNum >= maxChildrenNum)
    {
        Node *p = bestChild(EXPLORE);
        return p->treePolicy();
    }
    else
        return expand();
}

//Simulation阶段，从当前节点快速落子模拟运算至终局，返回reward
double Node::defaultPolicy()
{
    return quickEvaluate();
}

//蒙特卡洛树搜索的Backpropagation阶段，输入前面获取需要expend的节点和新执行Action的reward，反馈给expend节点和上游所有节点并更新对应数据。
void Node::backup(double reward)
{
    Node *p = this;
    while (p)
    {
        p->visit_times++;
        p->quality_value += reward;
        reward = -reward;
        p = p->parent;
    }
}

//MCTS的主体部分
/*实现蒙特卡洛树搜索算法，传入一个根节点，在有限的时间内根据之前已经探索过的树结构expand新节点和更新数据，然后返回只要exploitation最高的子节点。
  蒙特卡洛树搜索包含四个步骤，Selection、Expansion、Simulation、Backpropagation。
  前两步使用tree policy找到值得探索的节点。
  第三步使用default policy也就是在选中的节点上随机算法选一个子节点并计算reward。
  最后一步使用backup也就是把reward更新到所有经过的选中节点的节点上。
  进行预测时，只需要根据Q值选择exploitation最大的节点即可，找到下一个最优的节点。*/

int main()
{
    srand((unsigned)time(0));
    string str;
    int x, y;
    // 读入JSON
    getline(cin, str);
    //getline(cin, str);

    //计时开始并计算时限
    int start = clock();
    int timeout = (int)(TIME_OUT_SET * (double)CLOCKS_PER_SEC);

    Json::Reader reader;
    Json::Value input;
    reader.parse(str, input);

    //初始化节点
    int first = 0;
    Node *node = new Node;
    if (input["requests"][first]["x"].asInt() == -1) //确定颜色
        node->col = 1;                               //黑棋
    else
        node->col = -1;

    int color = node->col;
    // 分析自己收到的输入和自己过往的输出，并恢复状态
    int turnID = input["responses"].size();
    for (int i = 0; i < turnID; i++)
    {
        x = input["requests"][i]["x"].asInt(), y = input["requests"][i]["y"].asInt();
        if (x != -1)
        {
            board[x][y] = -color;
        }
        x = input["responses"][i]["x"].asInt(), y = input["responses"][i]["y"].asInt();
        if (x != -1)
        {
            board[x][y] = color;
        }
    }
    x = input["requests"][turnID]["x"].asInt(), y = input["requests"][turnID]["y"].asInt();
    if (x != -1) //对方为黑子
    {
        board[x][y] = -color;
        node_count++;
    }

    for (int i = 0; i < 9; i++) //载入棋盘
        for (int j = 0; j < 9; j++)
            node->current_board[i][j] = board[i][j];
    node->getAviliableAction();

    //开始蒙特卡洛树搜索
    while (clock() - start < timeout)
    {
        node_count++;
        Node *expand_node = node->treePolicy();
        double reward = expand_node->defaultPolicy();
        expand_node->backup(reward);
    }

    //输出结果
    Json::Value ret;
    Json::Value action;

    Node *best_child = node->bestChild(0);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j] != best_child->current_board[i][j])
            {
                action["x"] = i;
                action["y"] = j;
                break;
            }
    ret["response"] = action;
    Json::FastWriter writer;
    char buffer[4096];
    sprintf(buffer, "???:%d", node_count);
    ret["debug"] = buffer;
    cout << writer.write(ret) << endl;
    //system("pause");
    return 0;
}


