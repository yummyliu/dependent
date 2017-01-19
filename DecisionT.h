#ifndef DECISIONT_H
#define DECISIONT_H
/*
 *  决策表的相关定义
 */ 
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <string>
using namespace std;


class DecisionT
{
    public:
        DecisionT();
        DecisionT(ifstream& in,vector<int>& Cs, int Ds);
        DecisionT(
                const vector<vector<double> >& records,
                size_t len,
                vector<int>& Cs,
                int Ds);
        DecisionT(
                vector<int>& Cs,
                int Ds);
        DecisionT(DecisionT& d);

        DecisionT& getcopy() const;
        set<int>& getCs();
        vector<vector<double> >& getrecords();
        int getDs();
        void addrecords(vector<vector<double> >::const_iterator it,int);

    private:
        vector<vector<double> > records;
        set<int> Cs; // 条件属性
        int Ds; // 决策属性

};

string getkey(const vector<double> &x, int i);
double Dependent(DecisionT& dt, set<int>& B,int holdpos,...); 
double Dependentplus(
        vector<vector<double> >::const_iterator iold,
        size_t presize,
        vector<vector<double> >::const_iterator inew,
        size_t gsize,
        set<int>& B,
        int ds,
        double predep,
        vector<double>& prepos
        );
double pos_x(
       vector<vector<double> >& records,
       size_t x,
       set<int> & B,
       int ds,
       bool chuzao);
#endif
