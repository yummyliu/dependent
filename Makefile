all: DecisionT.o algorithm.o cancer.o letter.o shuttle.o tic.o wine.o wave.o iris.o arcene.o gene14.o gene12.o gene9.o arem.o credit.o dota2.o poker.o gas.o
	g++ -g -std=c++11 -o cancer DecisionT.o algorithm.o cancer.o
	g++ -g -std=c++11 -o letter DecisionT.o algorithm.o letter.o
	g++ -g -std=c++11 -o shuttle DecisionT.o algorithm.o shuttle.o
	g++ -g -std=c++11 -o tic DecisionT.o algorithm.o tic.o
	g++ -g -std=c++11 -o wine DecisionT.o algorithm.o wine.o
	g++ -g -std=c++11 -o wave DecisionT.o algorithm.o wave.o
	g++ -g -std=c++11 -o iris DecisionT.o algorithm.o iris.o
	g++ -g -std=c++11 -o arcene DecisionT.o algorithm.o arcene.o
	g++ -g -std=c++11 -o gene14 DecisionT.o algorithm.o gene14.o
	g++ -g -std=c++11 -o gene12 DecisionT.o algorithm.o gene12.o
	g++ -g -std=c++11 -o gene9 DecisionT.o algorithm.o gene9.o
	g++ -g -std=c++11 -o arem DecisionT.o algorithm.o arem.o
	g++ -g -std=c++11 -o credit DecisionT.o algorithm.o credit.o
	g++ -g -std=c++11 -o dota DecisionT.o algorithm.o dota2.o
	g++ -g -std=c++11 -o gas DecisionT.o algorithm.o gas.o
	g++ -g -std=c++11 -o pok DecisionT.o algorithm.o poker.o

DecisionT.o : DecisionT.cpp DecisionT.h
	g++ -g -std=c++11 -c DecisionT.cpp

algorithm.o : algorithm.cpp algorithm.h
	g++ -g -std=c++11 -c algorithm.cpp

cancer.o : cancer.cpp
	g++ -g -std=c++11 -c cancer.cpp

letter.o : letter.cpp
	g++ -g -std=c++11 -c letter.cpp

shuttle.o : shuttle.cpp
	g++ -g -std=c++11 -c shuttle.cpp

tic.o : tic.cpp
	g++ -g -std=c++11 -c tic.cpp

wine.o : wine.cpp
	g++ -g -std=c++11 -c wine.cpp

iris.o : iris.cpp
	g++ -g -std=c++11 -c iris.cpp

gene14.o : gene14.cpp
	g++ -g -std=c++11 -c gene14.cpp

gene12.o : gene12.cpp
	g++ -g -std=c++11 -c gene12.cpp

gene9.o : gene9.cpp
	g++ -g -std=c++11 -c gene9.cpp

arcene.o : arcene.cpp
	g++ -g -std=c++11 -c arcene.cpp

wave.o : wave.cpp
	g++ -g -std=c++11 -c wave.cpp

arem.o : arem.cpp
	g++ -g -std=c++11 -c arem.cpp

credit.o : credit.cpp
	g++ -g -std=c++11 -c credit.cpp

dota2.o : dota2.cpp
	g++ -g -std=c++11 -c dota2.cpp

gas.o : gas.cpp
	g++ -g -std=c++11 -c gas.cpp

poker.o : poker.cpp
	g++ -g -std=c++11 -c poker.cpp

test.o: test.cpp
	g++ -g -std=c++11 -c test.cpp

cancer: cancer.o DecisionT.o algorithm.o 
	g++ -g -std=c++11 -o cancer DecisionT.o algorithm.o cancer.o

clean:
	rm arem gas credit dota pok gene9 gene12 gene14 arcene iris wine wave tic shuttle letter cancer *.o test

test: DecisionT.o algorithm.o test.o
	g++ -g -std=c++11 -o test DecisionT.o algorithm.o test.o
