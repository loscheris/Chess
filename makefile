EXE=chess
OBJ=ChessMain.o Bishop.o ChessBoard.o ChessPieces.o King.o  Knight.o Pawn.o Queen.o Rook.o
CXX=g++
CXXFLAGS=-Wall -g -MMD

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(EXE) $(OBJ) $(OBJ:.o=.d)

.PHONY: clean
