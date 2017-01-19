#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>
#include "DecisionT.h"
using namespace std;

void print2d(vector<vector<int> >& r);
void getrecords(
        map<string,queue<vector<double> > > &records,
        size_t sum,
        size_t len,
        vector<vector<double> >&rec);
int getrandomgroup(
        map<string,queue<vector<double> > > &records,
        size_t sum,
        size_t len,
        vector<vector<double> >&rec);
void printv(set<int>& r);
int get_com_div(vector<int> &a);
bool dequal(double a,double b);
void getlef(vector<int>& C, vector<int> &B, vector<int> &lef);
double car_dep(
        DecisionT &d,
        set<int>& redu
        );
double icar_dep(
        DecisionT& T,
        vector<vector<double> > & records,
        size_t initsize,
        size_t gsize,
        set<int>& redu,
        double finaldep
        );
void test1 (
        string datafile,
        int* cons,
        size_t N,
        int ds,
        size_t initsize,
        size_t gsize
        );
void test0(
        string datafile,
        int* cons,
        size_t N,
        int ds,
        size_t initsize,
        size_t gsize
        );

#endif
