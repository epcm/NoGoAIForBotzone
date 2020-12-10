//你接下来看到的代码是经过了混淆的整活代码
//如果你要看真正的源码的话，请访问github
//https://github.com/lwh9346/NoGoBot
#include <string>
#include <math.h>
#include <ctime>
#include <random>
#include <iostream>
#include <cstring>
#include "./jsoncpp/json.h"
#define minInt -2147483648
#define branchNum 64
using namespace std;
void I111I(int Il1lI, int lll1l, int II11I, int II1I, int IllI, int IIlIl[9][9], char I1II[9][9], char Il11l[81], char llI[81][2], char Illll[9][9], char ll[9][9])
{
if (IIlIl[II11I][II1I] == 0)
{
switch (Il11l[IllI])
{
case 0:
llI[IllI][0] = II11I;
llI[IllI][1] = II1I;
Il11l[IllI] = 1;
if (IIlIl[Il1lI][lll1l] == 1)
{
Illll[II11I][II1I] |= 2;
}
else
{
Illll[II11I][II1I] |= 1;
if (ll[II11I][II1I] == -1 && IIlIl[Il1lI][lll1l] == -1) 
{
ll[II11I][II1I] = IllI;
}
}
break;
case 1: 
if (llI[IllI][0] == II11I && llI[IllI][1] == II1I) 
{
break;
}
Il11l[IllI] = 2;
if (IIlIl[Il1lI][lll1l] == 1)
{
Illll[(int)llI[IllI][0]][(int)llI[IllI][1]] |= 4;
Illll[II11I][II1I] |= 4;
}
else if (ll[(int)llI[IllI][0]][(int)llI[IllI][1]] == IllI) 
{
Illll[(int)llI[IllI][0]][(int)llI[IllI][1]] = Illll[(int)llI[IllI][0]][(int)llI[IllI][1]] / 2 * 2;
ll[(int)llI[IllI][0]][(int)llI[IllI][1]] = -1;
}
break;
case 2:
if (IIlIl[Il1lI][lll1l] == 1)
{
Illll[II11I][II1I] |= 4;
}
break;
}
}
}
void I11ll(int Il1lI, int lll1l, int IllI, int IIlIl[9][9], char I1II[9][9], char Il11l[81], char llI[81][2], char Illll[9][9], char ll[9][9])
{
I1II[Il1lI][lll1l] = IllI;
if (Il1lI != 0)
{
I111I(Il1lI, lll1l, Il1lI - 1, lll1l, IllI, IIlIl, I1II, Il11l, llI, Illll, ll);
}
if (lll1l != 0)
{
I111I(Il1lI, lll1l, Il1lI, lll1l - 1, IllI, IIlIl, I1II, Il11l, llI, Illll, ll);
}
if (Il1lI != 8)
{
I111I(Il1lI, lll1l, Il1lI + 1, lll1l, IllI, IIlIl, I1II, Il11l, llI, Illll, ll);
}
if (lll1l != 8)
{
I111I(Il1lI, lll1l, Il1lI, lll1l + 1, IllI, IIlIl, I1II, Il11l, llI, Illll, ll);
}
if (Il1lI != 0 && I1II[Il1lI - 1][lll1l] == -1 && IIlIl[Il1lI][lll1l] == IIlIl[Il1lI - 1][lll1l])
{
I11ll(Il1lI - 1, lll1l, IllI, IIlIl, I1II, Il11l, llI, Illll, ll);
}
if (lll1l != 0 && I1II[Il1lI][lll1l - 1] == -1 && IIlIl[Il1lI][lll1l] == IIlIl[Il1lI][lll1l - 1])
{
I11ll(Il1lI, lll1l - 1, IllI, IIlIl, I1II, Il11l, llI, Illll, ll);
}
if (Il1lI != 8 && I1II[Il1lI + 1][lll1l] == -1 && IIlIl[Il1lI][lll1l] == IIlIl[Il1lI + 1][lll1l])
{
I11ll(Il1lI + 1, lll1l, IllI, IIlIl, I1II, Il11l, llI, Illll, ll);
}
if (lll1l != 8 && I1II[Il1lI][lll1l + 1] == -1 && IIlIl[Il1lI][lll1l] == IIlIl[Il1lI][lll1l + 1])
{
I11ll(Il1lI, lll1l + 1, IllI, IIlIl, I1II, Il11l, llI, Illll, ll);
}
}
int ll1ll(int IIlIl[9][9], int I1ll[9][9])
{
int lII1l = 0;
int Il1l = 0;
char I1II[9][9]; 
char ll[9][9]; 
for (int II11I = 0; II11I < 9; II11I++)
{
for (int II1I = 0; II1I < 9; II1I++)
{
ll[II11I][II1I] = -1;
I1II[II11I][II1I] = -1;
}
}
char Il11l[81] = {0}; 
char llI[81][2] = {0}; 
char Illll[9][9] = {0}; 
for (int II11I = 0; II11I < 9; II11I++)
{
for (int II1I = 0; II1I < 9; II1I++)
{
if (I1II[II11I][II1I] != -1 || IIlIl[II11I][II1I] == 0) 
{
continue;
}
I11ll(II11I, II1I, Il1l, IIlIl, I1II, Il11l, llI, Illll, ll);
Il1l++;
}
}
for (int II11I = 0; II11I < 9; II11I++)
{
for (int II1I = 0; II1I < 9; II1I++)
{
if (IIlIl[II11I][II1I] != 0) 
{
I1ll[II11I][II1I] = 0;
continue;
}
if (Illll[II11I][II1I] % 2 == 1) 
{
I1ll[II11I][II1I] = 0;
continue;
}
if (Illll[II11I][II1I] / 4 == 1) 
{
I1ll[II11I][II1I] = 1;
lII1l++;
continue;
}
if (Illll[II11I][II1I] / 2 % 2 == 1) 
{
if ((II11I != 0 && IIlIl[II11I - 1][II1I] == 0) || (II1I != 0 && IIlIl[II11I][II1I - 1] == 0) || (II11I != 8 && IIlIl[II11I + 1][II1I] == 0) || (II1I != 8 && IIlIl[II11I][II1I + 1] == 0))
{
I1ll[II11I][II1I] = 1;
lII1l++;
}
else
{
I1ll[II11I][II1I] = 0;
}
continue;
}
if ((II11I == 0 || IIlIl[II11I - 1][II1I] == -1) && (II1I == 0 || IIlIl[II11I][II1I - 1] == -1) && (II11I == 8 || IIlIl[II11I + 1][II1I] == -1) && (II1I == 8 || IIlIl[II11I][II1I + 1] == -1))
{
I1ll[II11I][II1I] = 0;
continue; 
}
I1ll[II11I][II1I] = 1;
lII1l++;
}
}
return lII1l;
}
class lIlI
{
public:
lIlI *I1lIl;
lIlI *lIIIl[branchNum];
int IIlIl[9][9];
int I1I[branchNum][2]; 
int l11l; 
int I1llI; 
int l1l1I; 
int l1l; 
double l1I1l; 
int *II; 
lIlI(int IIll[9][9], int lllIl[2], lIlI *l11Il, int *llII)
{
for (int II11I = 0; II11I < 9; II11I++)
{
for (int II1I = 0; II1I < 9; II1I++)
{
IIlIl[II11I][II1I] = -IIll[II11I][II1I]; 
}
}
IIlIl[lllIl[0]][lllIl[1]] = -1; 
I1lIl = l11Il;
l1l1I = 0;
l1l = 0;
l11l = 0;
II = llII;
Ill(); 
}
lIlI *I1l1l()
{
if (I1llI == 0) 
{
return this;
}
if (I1llI > l11l) 
{
lIlI *l11lI = new lIlI(IIlIl, I1I[l11l], this, II);
lIIIl[l11l] = l11lI;
l11l++;
return l11lI;
}
int l1lI = 0;
double II1ll = 0;
for (int II11I = 0; II11I < l11l; II11I++)
{
if (II1ll < lIIIl[II11I]->l1I1l)
{
l1lI = II11I;
II1ll = lIIIl[II11I]->l1I1l;
}
}
return lIIIl[l1lI]->I1l1l();
}
int IlIIl()
{
int llI1I[9][9]; 
int I1ll[9][9];
for (int II11I = 0; II11I < 9; II11I++)
{
for (int II1I = 0; II1I < 9; II1I++)
{
llI1I[II11I][II1I] = -IIlIl[II11I][II1I];
}
}
double lI1lI = (double)ll1ll(IIlIl, I1ll);
double lIl = (double)ll1ll(llI1I, I1ll);
double IlIl;
if (lI1lI == lIl)
{
IlIl = 0.5;
}
else
{
IlIl = lI1lI > lIl ? 1.0 - 0.5 / (lI1lI - lIl + 1.0) : 0.5 / (lIl - lI1lI + 1.0);
}
if (IlIl * (double)RAND_MAX > (double)rand())
{
return 1;
}
else
{
return -1;
}
}
void IlI1l(int I)
{
lIlI *I1I1I = this;
int lIIl = 0;
while (I1I1I != nullptr)
{
if (I == lIIl % 2) 
{
I1I1I->l1l1I++;
}
I1I1I->l1l++;
I1I1I->l1I1l = double(I1I1I->l1l1I) / double(I1I1I->l1l) + 1.414 * sqrt(log(double(*II)) / double(I1I1I->l1l)); 
I1I1I = I1I1I->I1lIl;
lIIl++;
}
}
private:
void Ill()
{
int I1ll[9][9];
int llIll[9][9];
int llI1I[9][9]; 
for (int II11I = 0; II11I < 9; II11I++)
{
for (int II1I = 0; II1I < 9; II1I++)
{
llI1I[II11I][II1I] = -IIlIl[II11I][II1I];
}
}
int lI1Il = ll1ll(IIlIl, I1ll);
int Il1Il[81];
int l1l = 0;
for (int II11I = 0; II11I < 9; II11I++)
{
for (int II1I = 0; II1I < 9; II1I++)
{
if (I1ll[II11I][II1I])
{
Il1Il[l1l] = 9 * II11I + II1I;
l1l++;
}
}
}
if (lI1Il <= branchNum)
{
I1llI = lI1Il;
for (int II11I = 0; II11I < lI1Il; II11I++)
{
I1I[II11I][0] = Il1Il[II11I] / 9;
I1I[II11I][1] = Il1Il[II11I] % 9;
}
}
else
{
I1llI = branchNum;
int Ill1I[81]; 
for (int II11I = 0; II11I < lI1Il; II11I++)
{
int Il1lI, lll1l;
Il1lI = Il1Il[II11I] / 9;
lll1l = Il1Il[II11I] % 9;
int lIl1I = 0; 
if (Il1lI != 0 && lll1l != 0 && IIlIl[Il1lI - 1][lll1l - 1] != 0)
{
lIl1I += 1;
}
if (Il1lI != 0 && lll1l != 8 && IIlIl[Il1lI - 1][lll1l + 1] != 0)
{
lIl1I += 1;
}
if (Il1lI != 8 && lll1l != 0 && IIlIl[Il1lI + 1][lll1l - 1] != 0)
{
lIl1I += 1;
}
if (Il1lI != 8 && lll1l != 8 && IIlIl[Il1lI + 1][lll1l + 1] != 0)
{
lIl1I += 1;
}
if (Il1lI != 0 && IIlIl[Il1lI - 1][lll1l] == 1)
{
lIl1I -= 1;
}
if (Il1lI != 8 && IIlIl[Il1lI + 1][lll1l] == 1)
{
lIl1I -= 1;
}
if (lll1l != 0 && IIlIl[Il1lI][lll1l - 1] == 1)
{
lIl1I -= 1;
}
if (lll1l != 8 && IIlIl[Il1lI][lll1l + 1] == 1)
{
lIl1I -= 1;
}
IIlIl[Il1lI][lll1l] = 1;
llI1I[Il1lI][lll1l] = -1;
lIl1I += ll1ll(IIlIl, llIll) * 4;
lIl1I -= ll1ll(llI1I, llIll) * 4;
IIlIl[Il1lI][lll1l] = 0;
llI1I[Il1lI][lll1l] = 0;
Ill1I[II11I] = lIl1I;
}
for (int II11I = 0; II11I < branchNum; II11I++)
{
int lIl1I = Ill1I[II11I];
int ll11I = II11I;
for (int II1I = II11I; II1I < lI1Il; II1I++)
{
if (lIl1I < Ill1I[II1I])
{
lIl1I = Ill1I[II1I];
ll11I = II1I;
}
}
swap(Ill1I[II11I], Ill1I[ll11I]);
swap(Il1Il[II11I], Il1Il[ll11I]);
}
for (int II11I = 0; II11I < branchNum; II11I++)
{
I1I[II11I][0] = Il1Il[II11I] / 9;
I1I[II11I][1] = Il1Il[II11I] % 9;
}
}
}
int I1ll(int IIlIl[9][9], int llI1I[9][9])
{
int I1ll[9][9];
int lI1lI, lIl;
lI1lI = ll1ll(IIlIl, I1ll);
lIl = ll1ll(llI1I, I1ll);
if (lI1lI != 0 && lIl != 0)
{
return 0;
}
if (lI1lI == 0)
{
return -1;
}
return 1;
}
int lI1l(int IIlIl[9][9])
{
int I1ll[9][9];
int lI1Il = ll1ll(IIlIl, I1ll);
int Il1Il[81];
int l1l = 0;
for (int II11I = 0; II11I < 9; II11I++)
{
for (int II1I = 0; II1I < 9; II1I++)
{
if (I1ll[II11I][II1I])
{
Il1Il[l1l] = 9 * II11I + II1I;
l1l++;
}
}
}
int III1I = minInt; 
int l111l = 0; 
for (int II11I = 0; II11I < lI1Il; II11I++)
{
int lIl1I = rand();
if (lIl1I > III1I)
{
III1I = lIl1I;
l111l = II11I;
}
}
return Il1Il[l111l];
}
};
int main()
{
int IIl1l = 0;
int IIlIl[9][9] = {0};
srand(233);
string l1Il;
getline(cin, l1Il);
int ll1I = clock();
int lI11l = (int)(0.95 * (double)CLOCKS_PER_SEC);
Json::Reader lIlll;
Json::Value l1IIl;
lIlll.parse(l1Il, l1IIl);
int IIIll = l1IIl["responses"].size();
int Il1lI, lll1l;
for (int II11I = 0; II11I < IIIll; II11I++)
{
Il1lI = l1IIl["requests"][II11I]["y"].asInt(), lll1l = l1IIl["requests"][II11I]["x"].asInt();
if (Il1lI != -1)
IIlIl[Il1lI][lll1l] = 1;
Il1lI = l1IIl["responses"][II11I]["y"].asInt(), lll1l = l1IIl["responses"][II11I]["x"].asInt();
if (Il1lI != -1)
IIlIl[Il1lI][lll1l] = -1;
}
Il1lI = l1IIl["requests"][IIIll]["y"].asInt(), lll1l = l1IIl["requests"][IIIll]["x"].asInt();
int I11I[2] = {Il1lI, lll1l};
lIlI III(IIlIl, I11I, nullptr, &IIl1l);
while (clock() - ll1I < lI11l)
{
IIl1l++;
lIlI *I1I1I = III.I1l1l();
int I1ll = I1I1I->IlIIl();
I1I1I->IlI1l(I1ll == 1 ? 1 : 0);
}
int III1I = 0;
int l111l = 0;
int *IIII = III.I1I[0];
for (int II11I = 0; II11I < III.l11l; II11I++)
{
if (III1I < III.lIIIl[II11I]->l1l)
{
l111l = II11I;
III1I = III.lIIIl[II11I]->l1l;
IIII = III.I1I[II11I];
}
}
Json::Value I1Ill;
Json::Value lllIl;
lllIl["x"] = IIII[1];
lllIl["y"] = IIII[0];
I1Ill["response"] = lllIl;
char llll[4096];
sprintf(llll, "MCTS节点数:%d,当前预估胜率:%.3f", IIl1l, ((double)(III.lIIIl[l111l]->l1l1I)) / ((double)III.lIIIl[l111l]->l1l));
I1Ill["debug"] = llll;
Json::FastWriter l1lll;
cout << l1lll.write(I1Ill) << endl;
}