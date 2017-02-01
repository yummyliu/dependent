#coding:utf-8
import os, time, sched
import subprocess as sub
import signal
import warnings
import ConfigParser
import threading

cf = ConfigParser.ConfigParser()
schedule = sched.scheduler(time.time,time.sleep)

def getkillcmd(cmdname):
    print "kill ",cmdname
    return "kill -9 `ps -aux | grep "+cmdname+" | grep -v 'grep' | awk '{print $2}' `"

def killittask(name):
    cmd = getkillcmd(name)
    os.system(cmd)
    print time.ctime(),name,'killed'

import errno

def timeout( p ):
    if p.poll() is None:
        try:
            p.kill()
            print "kill it"
        except OSError as e:
            if e.errno != errno.ESRCH:
                raise
    else:
        print "already stop"

class RunCmd(threading.Thread):
    def __init__(self, cmd, timeout):
        threading.Thread.__init__(self)
        self.cmd = cmd
        self.timeout = timeout

    def run(self):
        self.p = sub.Popen(self.cmd,shell=True)
        self.p.wait()

    def Run(self):
        self.start()
        self.join(self.timeout)

        if self.is_alive():
            self.p.terminate()
            self.join()

if __name__ == '__main__':
    cf.read("data/auto.conf")
    datasets = cf.sections()

    for dataname in datasets:
        #读取当前dataset的配置
        it = cf.items(dataname)
        insnum = it[0][1]
        css = it[1][1]
        cse = it[2][1]
        ds  = it[3][1]
        df =  it[4][1]
        #构造执行命令
        #./test algotype cs_start cs_end ds datafile initpart looppart
        tasklist = []
        tasklist.append("test")
        tasklist.append(str(0)) # algotype先初始化为0
        tasklist.append(css)
        tasklist.append(cse)
        tasklist.append(ds)
        tasklist.append(df)
        tasklist.append(str(0)) # 站位
        tasklist.append(str(0)) # 占位

        # 分组执行 经典算法
        groupnum = [2,6,10]
        for gn in groupnum:
            insn = int(insnum)
            initpart = insn/gn+insn%gn
            looppart = insn/gn
            tasklist[6] = str(initpart)
            tasklist[7] = str(looppart)
            task = " ".join(tasklist)
            outfile = "out/"+dataname+".out_"+str(tasklist[1])+str(gn)
            task = "./"+task+" >> "+outfile
            f = open(outfile,"w")
            print >>f, task
            f.close()
            RunCmd(task,259200).Run()


        # 分组执行 增量算法
        tasklist[1] = str(1)
        groupnum = [2,6,10]
        for gn in groupnum:
            insn = int(insnum)
            initpart = insn/gn+insn%gn
            looppart = insn/gn
            tasklist[6] = str(initpart)
            tasklist[7] = str(looppart)
            task = " ".join(tasklist)
            outfile = "out/"+dataname+".out_"+str(tasklist[1])+str(gn)
            task = "./"+task+" >> "+outfile
            f = open(outfile,"w")
            print >>f, task
            f.close()
            RunCmd(task,259200).Run()
