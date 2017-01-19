/*
 *  决策表的相关计算
 *
 *  创建一个决策表类，会初始化 全集U，
 *  执行setCs和setDs 初始化Cs和Ds，并生成等价类 UCs/UDs
 *  执行count_UDs ，根据全集生成UDs等价类集合的补集
 */ 
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstdarg>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "DecisionT.h"
#include <float.h>
using namespace std;

// DEBUG
template class std::vector<vector<int> >;
vector<vector<double> >& DecisionT::getrecords()
{
    return this->records;
}
static void trans_set(set<int>& a, vector<int> & b)
{
    for(vector<int>::iterator it = b.begin();
            it != b.end();
            ++it)
    {
        a.insert(*it);
    }
}


DecisionT::DecisionT(ifstream& in,vector<int>& Cs, int Ds)
{
    this->Ds = Ds;
    trans_set(this->Cs, Cs);

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
        this->records.push_back(*record);
        int val = (*record)[0];
    }
}
DecisionT::DecisionT(
        const vector<vector<double> >& records,
        size_t len,
        vector<int>& Cs, 
        int Ds)
{
    this->Ds = Ds;
    trans_set(this->Cs, Cs);

    for(vector<vector<double> >::const_iterator record = records.begin();
            record != records.begin()+len;
            ++record)
    {
        this->records.push_back(*record);
        int val = (*record)[0];
    }
}

DecisionT::DecisionT(
        vector<int>& Cs,
        int Ds)
{
    this->Ds = Ds;
    trans_set(this->Cs, Cs);
}

DecisionT::DecisionT(DecisionT& d){
    this->records = d.records;
    this->Cs = d.getCs();
    this->Ds = d.getDs();
}

DecisionT::DecisionT()
{
}
set<int>& DecisionT::getCs()
{
    return this->Cs;
}
int DecisionT::getDs()
{
    return this->Ds;
}

void DecisionT::addrecords(vector<vector<double> >::const_iterator iBegin,int size)
{
    for(vector<vector<double> >::const_iterator record = iBegin;
            record !=iBegin+size;
            ++record)
    {
        this->records.push_back(*record);
    }

}


static double getdistance(
        const vector<double>& Xi,
        const vector<double>& Xj,
        set<int>& B)
{
    double dis= DBL_MIN;
    for(set<int>::iterator it = B.begin();
            it != B.end();
            ++it)
    {
        double tmpd = fabs(Xi[*it]-Xj[*it]);
        if(dis<tmpd){
            dis = tmpd;
        }
    }
    return dis;
}

/*
 * 找到全集U内的x的异类中,基于属性集B,离x最近的u的距离
 */
double pos_x(
       vector<vector<double> >& records,
       size_t x,
       set<int> & B,
       int ds,
       bool chuzao)
{
    double mindes = DBL_MAX;
    //static double alpha=0.1;
    static double alpha=0.2;
    for(vector<vector<double> >::const_iterator icur = records.begin();
            icur != records.end();
            ++icur)
    {
        if(records[x][ds] != (*icur)[ds]){
            double tmpdes  = getdistance(records[x],*icur,B);
            if (tmpdes < mindes){
                mindes = tmpdes;
            }
        }
    }

    if (chuzao)
        return mindes*(1+alpha);
    else
        return mindes;
}

double Dependent(
        DecisionT& dt,
        set<int>& B,
        int holdpos,
        ...
        ){
    double sum_pos = 0.0;
    vector<vector<double> >& records = dt.getrecords();
    bool chuzao = !(dt.getCs().size()==B.size());

    if (holdpos){
        va_list  vlist;
        va_start(vlist,holdpos);
        void* ppos = va_arg(vlist,void*);
        vector<double>& pos = *(vector<double>*)ppos;

        for(size_t it = 0;
                it < records.size();
                ++it)
        {
            double posx = pos_x(records,it,B,dt.getDs(),chuzao);
            // 更新pos，而不是追加pos
            if(pos.size()>records.size())
                pos[it] = posx;
            else
                pos.push_back(posx);
            sum_pos += posx;
        }
    }else{
        int k;
        for(size_t it = 0;
                it < records.size();
                ++it)
        {
            double posx = pos_x(records,it,B,dt.getDs(),chuzao);
            sum_pos += posx;
        }
    }
    double dep = sum_pos/records.size();
    return dep;
}

double Dependentplus(
        vector<vector<double> >::const_iterator iold,
        size_t presize,
        vector<vector<double> >::const_iterator inew,
        size_t gsize,
        set<int>& B,
        int ds,
        double predep,
        vector<double>& prepos
        ){
    double retdep = 0.0;

    // update old pos
    for(size_t i = 0;i<prepos.size(); i++){
        double mindes = prepos[i];
        for(vector<vector<double> >::const_iterator icur = inew;
                icur != inew+gsize;
                ++icur)
        {
            if((*(iold+i))[ds]!=(*icur)[ds]){   // 异类
                double tmpdes  = getdistance(iold[i],*icur,B);
                if (tmpdes < mindes)
                    mindes = tmpdes;
            }
        }
        prepos[i] = mindes;
        retdep += mindes;
    }

    // calculate new pos
    for(vector<vector<double> >::const_iterator icur = inew;
            icur != inew+gsize;
            ++icur)
    {
        double mindes = DBL_MAX;
        for(auto _iold = iold;_iold != iold+presize; ++_iold)
        {
            if((*_iold)[ds] != (*icur)[ds])
            {
                double tmpdes = getdistance((*_iold),(*icur),B);
                if (tmpdes < mindes)
                    mindes = tmpdes;
            }
        }
        for(auto _inew = inew; _inew != inew+gsize; ++_inew)
        {
            if((*_inew)[ds] != (*icur)[ds])
            {
                double tmpdes = getdistance((*_inew),(*icur),B);
                if (tmpdes < mindes)
                    mindes = tmpdes;
            }
        }
        prepos.push_back(mindes);
        retdep += mindes;
    }

    retdep = (retdep/(presize+gsize));
    return retdep;
}
