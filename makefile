#Logic Simplifier
#by Parsa Mohebbi

CC = g++
FLAGS =
SrcDir = src
BinDir = bin

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(BinDir)" mkdir $(BinDir)
    RM = if exist "$(BinDir)" del /Q "$(BinDir)/*.o" & if exist "KarnaughCat.exe" del KarnaughCat.exe
else
    MKDIR = mkdir -p $(BinDir)
    RM = rm -f $(BinDir)/*.o KarnaughCat
endif



KarnaughCat: $(SrcDir)/KarnaughCat.cpp $(BinDir)/SubString.o $(BinDir)/Analyser.o $(BinDir)/LogicTable.o
	$(CC) $(SrcDir)/KarnaughCat.cpp $(BinDir)/SubString.o $(BinDir)/Analyser.o $(BinDir)/LogicTable.o -o KarnaughCat $(FLAGS)


$(BinDir)/SubString.o: $(SrcDir)/SubString.cpp $(SrcDir)/SubString.h | $(BinDir)
	$(CC) -c $(SrcDir)/SubString.cpp -o $(BinDir)/SubString.o $(FLAGS)

$(BinDir)/Analyser.o: $(SrcDir)/Analyser.cpp $(SrcDir)/Analyser.h $(SrcDir)/SubString.h $(SrcDir)/LogicTable.h | $(BinDir)
	$(CC) -c $(SrcDir)/Analyser.cpp -o $(BinDir)/Analyser.o $(FLAGS)

$(BinDir)/LogicTable.o: $(SrcDir)/LogicTable.cpp $(SrcDir)/LogicTable.h | $(BinDir)
	$(CC) -c $(SrcDir)/LogicTable.cpp -o $(BinDir)/LogicTable.o $(FLAGS)

$(BinDir):
	$(MKDIR)

clean:
	$(RM)
