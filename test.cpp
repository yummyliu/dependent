#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <time.h>
#include <stdlib.h>
#include "DecisionT.h"
#include "algorithm.h"

int main(int argc,char *argv[])
{
    int algotype = atoi(argv[1]);
    int cs_start = atoi(argv[2]);
    int cs_end = atoi(argv[3]);
    int ds = atoi(argv[4]);
    string datafile = argv[5];
    int cons[cs_end-cs_start+1];
    for(int i=cs_start; i<=cs_end;i++)
        cons[i-1]=i;
    int cslen = cs_end-cs_start+1;

    int initpart = atoi(argv[6]);
    int looppart = atoi(argv[7]);

    if (algotype==0){
        // 经典算法
        test0(datafile,
            cons,
            cslen,
            ds,
            initpart,
            looppart);
    }else if(algotype==1){
        // 增量算法
        test1(datafile,
            cons,
            cslen,
            ds,
            initpart,
            looppart);
    }
    return 0;
}
