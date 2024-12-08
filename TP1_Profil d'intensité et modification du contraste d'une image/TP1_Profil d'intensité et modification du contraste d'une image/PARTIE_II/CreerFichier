
OB += \
fonction.o \
amelioration_contraste.o
	

%.o:
	g++  -O0 -g3 -Wall -c  fonction.cpp  amelioration_contraste.cpp `pkg-config --cflags --libs opencv`

all:$(OB)
	@echo 'Building target: $@'
	g++  -o "amelioration_contraste" $(OB)  `pkg-config --cflags --libs opencv`
	@echo 'Finished building target: $@'

clear:
	rm -rf *.o

mproper: clean
	rm -rf $(OB) fonction
