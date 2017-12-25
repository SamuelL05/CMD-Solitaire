#makefile

Solitaire : Main.o DrawPileMethods.o HandPileMethods.o TargetPileMethods.o

	g++ -std=c++11 -o Solitaire Main.o DrawPileMethods.o HandPileMethods.o TargetPileMethods.o

Main.o : Main.cpp 

	g++ -std=c++11 -c Main.cpp

DrawPileMethods.o : DrawPileMethods.cpp HandPileHeader.h Card.h

	g++ -std=c++11 -c DrawPileMethods.cpp

HandPileMethods.o : HandPileMethods.cpp HandPileHeader.h Card.h

	g++ -std=c++11 -c HandPileMethods.cpp

TargetPileMethods.o : TargetPileMethods.cpp TargetPileHeader.h Card.h

	g++ -std=c++11 -c TargetPileMethods.cpp

