#-*- coding: utf-8 -*-
from numpy import *
import operator
import sys
import csv

'''构造数据'''
def createDataSet():
    characters=array([[1.0,1.1],[1.0,1.0],[0,0],[0,0.1]])
    labels=['A','A','B','B']
    return characters,labels

'''从文件中读取数据，将文本记录转换为矩阵，提取其中特征和类标'''
def file2matrix(filename,cslist=[],ds=-1):
    fr=open(filename)
    arrayOLines=fr.readlines()
    numberOfLines=len(arrayOLines)        #得到文件行数
    returnMat=zeros((numberOfLines,len(cslist)))     #创建以零填充的numberOfLines*len(cslist)的NumPy矩阵
    classLabelVector=[]
    index=0
    for line in arrayOLines:              #解析文件数据到列表
        line=line.strip()
        line=line.split(',')

        # 得到条件属性下的值和label
        listFromLine= []
        for ci in cslist:
            listFromLine.append(line[int(ci)])
        listFromLine.append(line[int(ds)])

        returnMat[index, : ] = listFromLine[0:len(cslist)]
        classLabelVector.append(listFromLine[-1])
        index+=1

    return returnMat,classLabelVector     #返回特征矩阵和类标集合

'''归一化数字特征值到0-1范围'''
'''输入为特征值矩阵'''
def autoNorm(dataSet):
    minVals=dataSet.min(0)
    maxVals=dataSet.max(0)
    ranges=maxVals-minVals
    normDataSet=zeros(shape(dataSet))
    m=dataSet.shape[0]
    normDataSet=dataSet-tile(minVals,(m,1))
    normDataSet=normDataSet/tile(ranges,(m,1))
    return normDataSet, ranges, minVals

def classify(sample,dataSet,labels,k):
    dataSetSize=dataSet.shape[0]     #数据集行数即数据集记录数
    '''距离计算'''
    diffMat=tile(sample,(dataSetSize,1))-dataSet         #样本与原先所有样本的差值矩阵
    sqDiffMat=diffMat**2      #差值矩阵平方
    sqDistances=sqDiffMat.sum(axis=1)       #计算每一行上元素的和
    distances=sqDistances**0.5   #开方
    sortedDistIndicies=distances.argsort()      #按distances中元素进行升序排序后得到的对应下标的列表
    '''选择距离最小的k个点'''
    classCount={}
    for i in range(k):
        voteIlabel=labels[sortedDistIndicies[i]]
        classCount[voteIlabel]=classCount.get(voteIlabel,0)+1
    '''从大到小排序'''
    sortedClassCount=sorted(classCount.items(),key=operator.itemgetter(1),reverse=True)
    return sortedClassCount[0][0]

def classTest(trainfile,testfilelist,cslist,ds,k):


    count = 0
    numTestVecs = 0

    # 输入训练数据集
    dataMat,dataLabel = file2matrix(trainfile,cslist,ds)
    # 遍历测试数据集，进行测试
    testfile = open(testfilelist[0],"r")
    testlines = testfile.readlines()
    numTestVecs += len(testlines)
    for li in range(len(testlines)):
        testline = testlines[li]
        sample=[]
        tmpline = testline.split(',')
        for i in range(len(tmpline)):
            try:
                tmpline[i] = float(tmpline[i])
            except:
                print len(tmpline),tmpline[i]
                exit()
        for ci in cslist:
            sample.append(tmpline[int(ci)])
        classifierResult = classify(sample,dataMat,dataLabel,k)
        if classifierResult != dataLabel[li] :
            count += 1

    testfile = open(testfilelist[1],"r")
    testlines = testfile.readlines()
    numTestVecs += len(testlines)
    for li in range(len(testlines)):
        testline = testlines[li]
        sample=[]
        tmpline = testline.split(',')
        for i in range(len(tmpline)):
            tmpline[i] = float(tmpline[i])
        for ci in cslist:
            sample.append(tmpline[int(ci)])
        classifierResult = classify(sample,dataMat,dataLabel,k)
        if classifierResult != dataLabel[li] :
            count += 1


    testfile = open(testfilelist[2],"r")
    testlines = testfile.readlines()
    numTestVecs += len(testlines)
    for li in range(len(testlines)):
        testline = testlines[li]
        sample=[]
        tmpline = testline.split(',')
        for i in range(len(tmpline)):
            tmpline[i] = float(tmpline[i])
        for ci in cslist:
            sample.append(tmpline[int(ci)])
        classifierResult = classify(sample,dataMat,dataLabel,k)
        if classifierResult != dataLabel[li] :
            count += 1



    testfile = open(testfilelist[3],"r")
    testlines = testfile.readlines()
    numTestVecs += len(testlines)
    for li in range(len(testlines)):
        testline = testlines[li]
        sample=[]
        tmpline = testline.split(',')
        for i in range(len(tmpline)):
            tmpline[i] = float(tmpline[i])
        for ci in cslist:
            sample.append(tmpline[int(ci)])
        classifierResult = classify(sample,dataMat,dataLabel,k)
        if classifierResult != dataLabel[li] :
            count += 1



    testfile = open(testfilelist[4],"r")
    testlines = testfile.readlines()
    numTestVecs += len(testlines)
    for li in range(len(testlines)):
        testline = testlines[li]
        sample=[]
        tmpline = testline.split(',')
        for i in range(len(tmpline)):
            tmpline[i] = float(tmpline[i])
        for ci in cslist:
            sample.append(tmpline[int(ci)])
        classifierResult = classify(sample,dataMat,dataLabel,k)
        if classifierResult != dataLabel[li] :
            count += 1


    print count/float(numTestVecs);

def main():
    sample=[0,0]
    k=3
    group,labels=createDataSet()
    label=classify(sample,group,labels,k)
    print("Classified Label:"+label)

if __name__=='__main__':
    #main()
    args = sys.argv
    testfilelist = ["xaa","xab","xac","xad","xae"]
    for i in range(len(testfilelist)):
        testfilelist[i]=(args[2]+testfilelist[i])

    cf = open(args[4],"r")
    lines = cf.readlines()

    # 全部属性
    line = lines[0].strip()
    cslist=line.split(',')
    classTest(args[1],testfilelist,cslist,args[3],4)

    # car
    line = lines[1].strip()
    cslist=line.split(',')
    classTest(args[1],testfilelist,cslist,args[3],4)

    # icar 2
    line = lines[2].strip()
    cslist=line.split(',')
    classTest(args[1],testfilelist,cslist,args[3],4)

    # icar 多
    line = lines[3].strip()
    cslist=line.split(',')
    classTest(args[1],testfilelist,cslist,args[3],4)
