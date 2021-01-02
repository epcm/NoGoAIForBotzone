//如果你要看真正的源码的话，请访问github
//https://github.com/lwh9346/NoGoBot
#pragma GCC optimize(3)
#include "./jsoncpp/json.h"
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;
class gameRule
{
public:
    struct ValidPositionResult
    {
        int numS;
        int numR;
        char resS[81];
        char resR[81];
    };

private:
    struct Group
    {
        bool self;
        int posCount;
        int groupID;
        int gasNum;
        char gasPos[81];
        char pos[81];
    };

private:
    struct Gas
    {
        int ownerID[4];
        int ownerGasCount[4];
        int ownerCount;
        bool onlyGasS;
        bool onlyGasR;
        bool notOnlyGasS;
        bool notOnlyGasR;
    };

public:
    static void GetValidPosition(signed char board[81], ValidPositionResult *res)
    {
        signed char groupMark[81];
        Group groups[81];
        Gas gas[81];
        int groupNum = 0;
        res->numR = 0;
        res->numS = 0;
        for (int i = 0; i < 81; i++)
        {
            groupMark[i] = -1;
            gas[i].ownerCount = 0;
            gas[i].notOnlyGasR = false;
            gas[i].notOnlyGasS = false;
            gas[i].onlyGasR = false;
            gas[i].onlyGasS = false;
            groups[i].groupID = i;
            groups[i].posCount = 0;
            groups[i].gasNum = 0;
            for (int j = 0; j < 81; j++)
            {
                groups[i].gasPos[j] = 0;
            }
        }
        for (int i = 0; i < 81; i++)
        {
            if (groupMark[i] != -1 || board[i] == 0)
            {
                continue;
            }
            grouping(i, groupNum, board, groupMark);
            groupNum++;
        }
        for (int i = 0; i < 81; i++)
        {
            if (groupMark[i] == -1)
            {
                continue;
            }
            groups[groupMark[i]].pos[groups[groupMark[i]].posCount] = i;
            groups[groupMark[i]].posCount++;
        }
        for (int i = 0; i < groupNum; i++)
        {
            groups[i].self = board[groups[i].pos[0]] == 1;
            for (int j = 0; j < groups[i].posCount; j++)
            {
                int pos = groups[i].pos[j];
                int x = pos / 9, y = pos % 9;
                int up = pos - 9;
                int down = pos + 9;
                int left = pos - 1;
                int right = pos + 1;
                if (x != 0 && board[up] == 0)
                {
                    groups[i].gasPos[up] = 1;
                }
                if (x != 8 && board[down] == 0)
                {
                    groups[i].gasPos[down] = 1;
                }
                if (y != 0 && board[left] == 0)
                {
                    groups[i].gasPos[left] = 1;
                }
                if (y != 8 && board[right] == 0)
                {
                    groups[i].gasPos[right] = 1;
                }
            }
            int gasPos[81];
            int gasCount = 0;
            for (int j = 0; j < 81; j++)
            {
                if (groups[i].gasPos[j] == 1)
                {
                    gasPos[gasCount] = j;
                    gasCount++;
                }
            }
            for (int j = 0; j < gasCount; j++)
            {
                gas[gasPos[j]].ownerGasCount[gas[gasPos[j]].ownerCount] = gasCount;
                gas[gasPos[j]].ownerID[gas[gasPos[j]].ownerCount] = i;
                gas[gasPos[j]].ownerCount++;
            }
        }
        for (int i = 0; i < 81; i++)
        {
            for (int j = 0; j < gas[i].ownerCount; j++)
            {
                if (groups[gas[i].ownerID[j]].self)
                {
                    if (gas[i].ownerGasCount[j] == 1)
                    {
                        gas[i].onlyGasS = true;
                        continue;
                    }
                    gas[i].notOnlyGasS = true;
                }
                else
                {
                    if (gas[i].ownerGasCount[j] == 1)
                    {
                        gas[i].onlyGasR = true;
                        continue;
                    }
                    gas[i].notOnlyGasR = true;
                }
            }
        }
        for (int pos = 0; pos < 81; pos++)
        {
            int x = pos / 9, y = pos % 9;
            int up = pos - 9;
            int down = pos + 9;
            int left = pos - 1;
            int right = pos + 1;
            bool atTop = x == 0;
            bool atBut = x == 8;
            bool atLef = y == 0;
            bool atRig = y == 8;
            if (board[pos] != 0 || gas[pos].onlyGasR)
            {
                res->resS[pos] = 0;
                goto r;
            }
            if (gas[pos].notOnlyGasS)
            {
                res->resS[pos] = 1;
                res->numS++;
                goto r;
            }
            if (gas[pos].onlyGasS)
            {
                if ((!atTop && board[up] == 0) || (!atBut && board[down] == 0) || (!atLef && board[left] == 0) || (!atRig && board[right] == 0))
                {
                    res->resS[pos] = 1;
                    res->numS++;
                    goto r;
                }
                res->resS[pos] = 0;
                goto r;
            }
            if ((atTop || board[up] == -1) && (atBut || board[down] == -1) && (atLef || board[left] == -1) && (atRig || board[right] == -1))
            {
                res->resS[pos] = 0;
                goto r;
            }
            res->resS[pos] = 1;
            res->numS++;
        r:
            if (board[pos] != 0 || gas[pos].onlyGasS)
            {
                res->resR[pos] = 0;
                continue;
            }
            if (gas[pos].notOnlyGasR)
            {
                res->resR[pos] = 1;
                res->numR++;
                continue;
            }
            if (gas[pos].onlyGasR)
            {
                if ((!atTop && board[up] == 0) || (!atBut && board[down] == 0) || (!atLef && board[left] == 0) || (!atRig && board[right] == 0))
                {
                    res->resR[pos] = 1;
                    res->numR++;
                    continue;
                }
                res->resR[pos] = 0;
                continue;
            }
            if ((atTop || board[up] == 1) && (atBut || board[down] == 1) && (atLef || board[left] == 1) && (atRig || board[right] == 1))
            {
                res->resR[pos] = 0;
                continue;
            }
            res->resR[pos] = 1;
            res->numR++;
        }
    }

private:
    static void grouping(int pos, int groupID, signed char board[81], signed char groupMark[81])
    {
        groupMark[pos] = groupID;
        int x = pos / 9, y = pos % 9;
        int t = board[pos];
        int up = pos - 9;
        int down = pos + 9;
        int left = pos - 1;
        int right = pos + 1;
        if (x != 0 && groupMark[up] == -1 && t == board[up])
        {
            grouping(up, groupID, board, groupMark);
        }
        if (x != 8 && groupMark[down] == -1 && t == board[down])
        {
            grouping(down, groupID, board, groupMark);
        }
        if (y != 0 && groupMark[left] == -1 && t == board[left])
        {
            grouping(left, groupID, board, groupMark);
        }
        if (y != 8 && groupMark[right] == -1 && t == board[right])
        {
            grouping(right, groupID, board, groupMark);
        }
    }
};
class mcts
{
private:
    struct TreeNode
    {
        TreeNode *parent;
        TreeNode *children[81];
        signed char board[81];
        int childrenAction[81];
        int childrenCount;
        int childrenCountMax;
        double q;
        int n;
        int *totalN;
        gameRule::ValidPositionResult res;
    };
    static TreeNode *createNewTreeNode(TreeNode *parent, int action)
    {
        TreeNode *t = new TreeNode;
        t->q = 0.0;
        t->n = 0;
        t->parent = parent;
        t->childrenCount = 0;
        t->totalN = parent->totalN;
        for (int i = 0; i < 81; i++)
        {
            t->board[i] = -parent->board[i];
        }
        t->board[action] = -1;
        gameRule::GetValidPosition(t->board, &t->res);
        t->childrenCountMax = 0;
        for (int i = 0; i < 81; i++)
        {
            if (t->res.resS[i] == 1)
            {
                t->childrenAction[t->childrenCountMax] = i;
                t->childrenCountMax++;
            }
        }
        return t;
    }
    static TreeNode *createRootTreeNode(signed char board[81], int *totalN)
    {
        TreeNode *t = new TreeNode;
        t->q = 0.0;
        t->n = 0;
        t->parent = nullptr;
        t->childrenCount = 0;
        t->totalN = totalN;
        for (int i = 0; i < 81; i++)
        {
            t->board[i] = board[i];
        }
        gameRule::GetValidPosition(t->board, &t->res);
        t->childrenCountMax = 0;
        for (int i = 0; i < 81; i++)
        {
            if (t->res.resS[i] == 1)
            {
                t->childrenAction[t->childrenCountMax] = i;
                t->childrenCountMax++;
            }
        }
        return t;
    }
    static TreeNode *treePolicy(TreeNode *t)
    {
        if (t->childrenCountMax == 0)
        {
            return t;
        }
        if (t->childrenCount < t->childrenCountMax)
        {
            TreeNode *c = createNewTreeNode(t, t->childrenAction[t->childrenCount]);
            t->children[t->childrenCount] = c;
            t->childrenCount++;
            return c;
        }
        double maxScore = -1.0;
        int maxI = 0;
        for (int i = 0; i < t->childrenCount; i++)
        {
            double s = t->children[i]->q / double(t->children[i]->n) + 0.2 * sqrt(log(double(*t->totalN)) / double(t->children[i]->n));
            if (s > maxScore)
            {
                maxScore = s;
                maxI = i;
            }
        }
        return treePolicy(t->children[maxI]);
    }
    static double defaultPolicy(TreeNode *t)
    {
        if (t->res.numR + t->res.numS == 0)
        {
            return 0.0;
        }
        if (t->res.numR == 0)
        {
            return 1.0;
        }
        if (t->res.numS == 0)
        {
            return -1.0;
        }
        return tanh(double(t->res.numS - t->res.numR) / double(t->res.numR + t->res.numS));
    }
    static void backup(double delta, TreeNode *t)
    {
        int i = 0;
        while (t != nullptr)
        {
            t->q += i % 2 == 1 ? delta : -delta;
            t->n++;
            t = t->parent;
            i++;
        }
    }
    static void deleteTree(TreeNode *t)
    {
        for (int i = 0; i < t->childrenCount; i++)
        {
            if (t->children[i]->childrenCount == 0)
            {
                delete (t->children[i]);
            }
            else
            {
                deleteTree(t->children[i]);
            }
        }
        delete (t);
    }

public:
    struct DebugData
    {
        double winningRate;
        int nodeCount;
    };
    static int GetBestAction(signed char board[81], double timeOut, DebugData *debug)
    {
        int totalN = 0;
        int end = (int)(timeOut * double(CLOCKS_PER_SEC)) + clock();
        TreeNode *root = createRootTreeNode(board, &totalN);
        while (clock() < end)
        {
            for (int i = 0; i < 16; i++)
            {
                totalN++;
                TreeNode *t = treePolicy(root);
                double delta = defaultPolicy(t);
                backup(delta, t);
            }
        }
        int maxN = root->children[0]->n;
        int maxI = 0;
        for (int i = 1; i < root->childrenCount; i++)
        {
            if (root->children[i]->n > maxN)
            {
                maxI = i;
                maxN = root->children[i]->n;
            }
        }
        int bestAction = root->childrenAction[maxI];
        if (debug != nullptr)
        {
            debug->nodeCount = totalN;
            debug->winningRate = (root->children[maxI]->q / double(root->children[maxI]->n) + 1) * 0.5;
        }
        deleteTree(root);
        return bestAction;
    }
};
int main()
{
    signed char board[81] = {0};
    string str;
    getline(cin, str);
    Json::Reader reader;
    Json::Value input;
    reader.parse(str, input);
    int turnID = input["responses"].size();
    int x, y;
    for (int i = 0; i < turnID; i++)
    {
        x = input["requests"][i]["y"].asInt(), y = input["requests"][i]["x"].asInt();
        if (x != -1)
            board[x * 9 + y] = -1;
        x = input["responses"][i]["y"].asInt(), y = input["responses"][i]["x"].asInt();
        if (x != -1)
            board[x * 9 + y] = 1;
    }
    x = input["requests"][turnID]["y"].asInt(), y = input["requests"][turnID]["x"].asInt();
    if (x != -1)
    {
        board[x * 9 + y] = -1;
    }
    mcts::DebugData debug;
    int bestAction = mcts::GetBestAction(board, 0.95, &debug);
    Json::Value ret;
    Json::Value action;
    action["x"] = bestAction % 9;
    action["y"] = bestAction / 9;
    ret["response"] = action;
    char buffer[4096];
    sprintf(buffer, "MCTS节点数:%d,当前预估胜率:%.3f", debug.nodeCount, debug.winningRate);
    ret["debug"] = buffer;
    Json::FastWriter writer;
    cout << writer.write(ret) << endl;
}