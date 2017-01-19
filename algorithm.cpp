#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <float.h>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include "DecisionT.h"
#include "algorithm.h"
#define eps 1e-3
#define eps2 1e-1

void print2d(vector<vector<int> >& r)
{

    for(int i=0; i<r.size(); i++)
    {
        for(int j=0;j<r[0].size();j++)
        {
            cout << r[i][j]<<" : ";
        }
        cout << endl;
    }
}


void getrecords(
        map<string,queue<vector<double> > > &records,
        size_t sum,
        size_t len,
        vector<vector<double> >&rec)
{
     for(map<string,queue<vector<double> > >::iterator ri = records.begin();
             ri != records.end();
             ++ri)
     {
        double p = (((double)ri->second.size())/((double)sum));
        size_t L = p*((double)len);

        for(int i=0; i<L; i++)
        {
            rec.push_back(ri->second.front());
            ri->second.pop();
        }
     }
}

int getrandomgroup(
        map<string,queue<vector<double> > > &records,
        size_t sum,
        size_t len,
        vector<vector<double> >&rec)
{
    //
    srand(time(NULL));

    for(map<string,queue<vector<double> > >::iterator ri = records.begin();;)
    {
        double p = (((double)ri->second.size())/((double)sum));
        int tmp = (int)(p*10000);
        int r = rand()%10000;
        if(r<=tmp && ri->second.size()>0){
            rec.push_back(ri->second.front());
            ri->second.pop();
            if (rec.size() == len || rec.size() == sum)
                break;
        }
        ++ri;
        if(ri==records.end())
            ri = records.begin();
    }
    return 0;
}

int gcd(int m, int n)
{
	if (m < n)
	{
		int tmp = m;
		m = n;
		n = tmp;
	}
	if (n == 0)
		return m;
	else
		return gcd(n, m % n);
}
int get_com_div(vector<int> &a)
{
	int n  = a.size();
	if (n <= 0)
		return 0;

	int number = a[0];
	for (int i = 1; i < n; ++i)
	{
		number = gcd(number, a[i]);
	}
	return number;
}

bool dequal(double a,double b)
{
    return fabs(a-b) < eps;
}
bool dequal2(double a,double b)
{
    return fabs(a-b) < eps;
}
void delci(int k, vector<int>& Cs, vector<int>& redu)
{
    for(int i=0;i<Cs.size();i++)
    {
        if(Cs[i]!=k)
            redu.push_back(Cs[i]);
    }
}

void printv(set<int>& r)
{
    for(set<int>::iterator it = r.begin();
            it != r.end();
            ++it)
    {
        cout << *it << " : ";
    }
}

static bool checkdel(DecisionT &d,const set<int> &redu, const set<int>::iterator &it,double initdep)
{
    set<int> tmpredu = redu;
    tmpredu.erase(*it);

    vector<double> a;
    double tmpdep = Dependent(d,tmpredu,0);

    if(tmpdep>=initdep){
        cout << "del" << endl;
        return true;
    }
    else
        return false;
}
double pos_x(
       vector<vector<double> >& records,
       size_t x,
       set<int> & B,
       int ds,
       bool chuzao);

bool notredundancy(int Bi, set<int>& redu, DecisionT& d, vector<double>& prepos)
{
    for(size_t x = 0; x<prepos.size(); x++)
    {
        double newpos = pos_x(
                d.getrecords(),
                x,
                redu,
                d.getDs(),
                true
                );
        if(newpos < prepos[x])
            return true;
    }
    return false;
}
void clearRedundancy2(
        DecisionT &d,
        set<int>& redu,
        vector<double>& prepos
        )
{
    set<int> B = redu;
    redu.clear();
    set<int>::iterator it = redu.begin();
    for(;it != redu.end();)
    {
        if(!notredundancy(*it,redu,d,prepos))
            redu.insert(*it);
        ++it;
    }
}
void clearRedundancy(
        DecisionT &d,
        set<int>& redu,
        double initdep
        )
{
    while(true)
    {
        int idel;
        bool delflag = false;
        set<int>::iterator it = redu.begin();
        for(;it != redu.end();)
        {
            delflag = checkdel(d,redu,it,initdep);
            if(!delflag)
            {
                ++it;
            }
            else
            {
                idel = *it;
                delflag = true;
                break;
            }
        }
        if(delflag){
            cout << "del" <<endl;
            redu.erase(idel);
        }else
            break;
    }
}

double car_dep(
        DecisionT &d,
        set<int>& redu
        )
{
    double initdep = Dependent(d,d.getCs(),0);

    double maxdep= DBL_MIN; // 只是为了让开始的时候，这两个不相同
    set<int> lef;
    set<int> &Cs =d.getCs();
    set_difference(Cs.begin(),Cs.end(),redu.begin(),redu.end(),std::inserter(lef, lef.begin()));
    /* 不断添加属性，直到redu计算的dep等于initdep
     */
    while(maxdep<initdep)
    {
        // DEBUG
        // cout << maxdep<< ":" << initdep<<endl;
        int k;
        for(set<int>::iterator it = lef.begin();
                it != lef.end();
                ++it)
        {
            redu.insert(*it);
            double tmp = Dependent(d,redu,0);
            if (maxdep== DBL_MIN|| tmp >maxdep)
            {
                /* 从lef 中，找到最大的dep
                 */
                k = *it;
                maxdep= tmp;
            }
            redu.erase(*it);
        }
        redu.insert(k);
//        printv(redu);
//        cout<<maxdep<<endl;
        lef.erase(k);
    }

    clearRedundancy(d,redu,initdep);

    return initdep;
}

double findbest(
        DecisionT d,
        double curdep,
        set<int>& redu,
        int ds,
        set<int>& lef,
        vector<double> &prepos,
        vector<double> &allpos,
        int &a
        ){
    vector<int> conins;
    // 得到有待更新的样本点
    for(size_t i =0; i< prepos.size(); i++)
    {
        if (prepos[i] >= allpos[i])
            continue;
        conins.push_back(i);
    }

    // 找到使得这些待更新样本点的依赖度提高最多的，遍历lef集合，
    // 计算redu+ai的新的下近似，累加增加的差值，就是正域要增加部分，找到最大的就是结果，
    // 相应就能计算依赖度
    double maxdelta = 0.0;
    for (set<int>::iterator i=lef.begin(); 
            i!= lef.end(); ++i)
    {
        int tmpa = *i;
        redu.insert(tmpa);
        double tmpdelta = 0.0;
        for(int j=0; j<conins.size(); j++)
        {
            double posj = pos_x(
                    d.getrecords(),
                    conins[j],
                    redu,
                    ds,
                    true
                    );
            if (posj>prepos[conins[j]])
                tmpdelta+=posj-prepos[conins[j]];
        }
        if (tmpdelta > maxdelta){
            maxdelta = tmpdelta;
            a = tmpa;
        }
        redu.erase(tmpa);
    }
    curdep += (maxdelta/(prepos.size()));
    return curdep;
}
double car_dep_plus(
        DecisionT &d,
        vector<vector<double> >::const_iterator ib,
        size_t gsize,
        set<int>& redu,
        double predep,
        vector<double>& prepos,
        double alldep,
        vector<double>& allpos
        )
{
    // 得到剩的属性 lef
    set<int> lef;
    set<int> &Cs = d.getCs();
    set_difference(
            Cs.begin(),
            Cs.end(),
            redu.begin(),
            redu.end(),
            std::inserter(lef, lef.begin())
            );

    clock_t start,finish;
    double totaltime;

    // 计算加了Ux之后的全集dep
    auto& records = d.getrecords();
    double initdep = Dependentplus(
                        records.begin(),
                        records.size(),
                        ib,
                        gsize,
                        d.getCs(),
                        d.getDs(),
                        alldep,
                        allpos);
    // 计算加了Ux之后的约简dep， 这里可以用增量公式
    double curdep = Dependentplus(
                        records.begin(),
                        records.size(),
                        ib,
                        gsize,
                        redu,
                        d.getDs(),
                        predep,
                        prepos);

    d.addrecords(ib,gsize);
    // add ,get a attribute from lef
    start = clock();
    while(lef.size()!=0)
    {
        // DEBUG
        // cout << initdep << ":" << curdep <<endl;
        // find the i, which dependent is max
        int i=-1;
        curdep = findbest(d,curdep,redu,d.getDs(),lef,prepos,allpos,i);
        redu.insert(i);
        lef.erase(i);
        if (curdep < initdep)
            continue;
        else
            break;
    }
    finish = clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    // cout << "time 3: "<<totaltime << " , ";

    //printv(redu);

    return initdep;
}

double icar_dep(
        DecisionT& T,
        vector<vector<double> > & records,
        size_t initsize,
        size_t gsize,
        set<int>& redu,
        double finaldep
        )
{

    clock_t start,finish;
    double totaltime;

    // 先用经典算法，计算初始样本集的dependent 和 redu
    start = clock();
    vector<vector<double> >::const_iterator curit = records.begin();
    T.addrecords(curit,initsize);
    car_dep(T, redu);
    vector<double> curpos;
    double curdep = Dependent(T,redu,1,&curpos);

    finish = clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;

    printv(redu);
    cout << "init : "<< curdep <<" : "<< finaldep <<" : "<< totaltime<< endl;;
    // 计算属性全集的dependent 和 pos
    vector<double> allpos;
    double alldep = Dependent(T,T.getCs(),1,&allpos);

    curit = curit + initsize;
    // 采用增量算法,进行逐次迭代，直到满足最后的条件
    int index=1;
    while( curit != records.end() )
    {
        // 取一组数据，进行一次增量计算
        start = clock();

        curdep = car_dep_plus(
                        T,\
                        curit,
                        (curit + gsize < records.end() ? gsize : records.end()-curit),
                        redu,
                        curdep,
                        curpos,
                        alldep,
                        allpos);

        finish = clock();
        totaltime=(double)(finish-start)/CLOCKS_PER_SEC;

        curit = curit + gsize < records.end() ? curit+gsize : records.end();

        printv(redu);
        cout << "loop "<<index << " ：" << curdep <<" : "<< finaldep <<" : "<< totaltime<< endl;;
        index++;
    }

    //clearRedundancy2(T,redu,curpos);
    clearRedundancy(T,redu,curdep);
    if (curit == records.end())
        cout << " end" <<endl;

    return curdep;
}
double _icar_dep(
        DecisionT& T,
        vector<vector<double> > & records,
        size_t initsize,
        size_t gsize,
        set<int>& redu,
        double finaldep
        )
{

    clock_t start,finish;
    double totaltime;

    // 先用经典算法，计算初始样本集的dependent 和 redu
    start = clock();
    vector<vector<double> >::const_iterator curit = records.begin();
    T.addrecords(curit,initsize);
    car_dep(T, redu);
    vector<double> curpos;
    double curdep = Dependent(T,redu,1,&curpos);

    finish = clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;

    printv(redu);
    cout << "init : "<< curdep <<" : "<< finaldep <<" : "<< totaltime<< endl;;
    // 计算属性全集的dependent 和 pos
    vector<double> allpos;
    double alldep = Dependent(T,T.getCs(),1,&allpos);

    curit = curit + initsize;
    // 采用增量算法,进行逐次迭代，直到满足最后的条件
    int index=1;
    while( curit != records.end() )
    {
        // 取一组数据，进行一次增量计算
        start = clock();
        gsize = (curit + gsize < records.end() ? gsize : records.end()-curit);
        T.addrecords(curit,gsize);
        curdep = car_dep(T,redu);
        finish = clock();
        totaltime=(double)(finish-start)/CLOCKS_PER_SEC;

        curit = curit + gsize < records.end() ? curit+gsize : records.end();

        printv(redu);
        cout << "loop "<<index << " ：" << curdep <<" : "<< finaldep <<" : "<< totaltime<< endl;;
        index++;
    }

    //clearRedundancy2(T,redu,curpos);
    clearRedundancy(T,redu,curdep);
    if (curit == records.end())
        cout << " end" <<endl;

    return curdep;
}
void test1 (
        string datafile,
        int* cons,
        size_t N,
        int ds,
        size_t initsize,
        size_t gsize
        )
{
    clock_t start,finish;
    double totaltime;

    // 读取数据
    ifstream in;
    in.open(datafile.c_str());
    if(!in.is_open())
    {
        cout << "文件打开失败" <<endl;
        return ;
    }
    vector<vector<double> > records;
    string line;
    while(getline(in,line))
    {
        istringstream stream(line);

        vector<double> *record = new vector<double>();
        string field;
        while(getline(stream,field,','))
        {
            record->push_back(atof(field.c_str()));
        }
        records.push_back(*record);
    }
    in.close();

    // 增量算法
    set<int> redu;
    vector<int> cs(cons,cons+N);
    DecisionT T(records,records.size(),cs,ds);
    DecisionT _T(cs,ds);
    double finaldep = Dependent(T,T.getCs(),0);

    start = clock();
    double dep = icar_dep(_T,records,initsize,gsize,redu,finaldep);
    finish = clock();

    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout << "--> " << totaltime <<" <--"<<endl;
    printv(redu);
    cout << "<--" <<endl;
}
void test0(
        string datafile,
        int* cons,
        size_t N,
        int ds,
        size_t initsize,
        size_t gsize
        )
{
    clock_t start,finish;
    double totaltime;

    // 读取数据
    ifstream in;
    in.open(datafile.c_str());
    if(!in.is_open())
    {
        cout << "文件打开失败" <<endl;
        return ;
    }
    vector<vector<double> > records;
    string line;
    while(getline(in,line))
    {
        istringstream stream(line);

        vector<double> *record = new vector<double>();
        string field;
        while(getline(stream,field,','))
        {
            record->push_back(atof(field.c_str()));
        }
        records.push_back(*record);
    }
    in.close();

    // 增量算法
    set<int> redu;
    vector<int> cs(cons,cons+N);
    DecisionT T(records,records.size(),cs,ds);
    DecisionT _T(cs,ds);
    double finaldep = Dependent(T,T.getCs(),0);

    start = clock();
    double dep = _icar_dep(_T,records,initsize,gsize,redu,finaldep);
    finish = clock();

    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout << "--> " << totaltime <<" <--"<<endl;
    printv(redu);
    cout << "<--" <<endl;
}
