INCLUDES = #-I "C:/Users/mthib/Documents/M2IF/Programmation par composants/Seance2/Crypto/micro-ecc-master/"

all: key_object.cpp uECC.c
	g++ -Wall ${INCLUDES} -o keyobject key_object.cpp uECC.c
clean:
	$(RM) keyobject