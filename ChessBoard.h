#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "Knight.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"
using namespace std;

class ChessBoard{
private:
  bool game_over; //whether the game is over
  bool new_game; // new_game = true only when the board is created
  int No_move; // number of move
  map<string, ChessPieces*> chessboard_mapping; // Mapping
  ChessPieces* whiteking;
  ChessPieces* whitequeen;
  ChessPieces** whiterook;
  ChessPieces** whiteknight;
  ChessPieces** whitebishop;
  ChessPieces** whitepawn;
  ChessPieces* blackking;
  ChessPieces* blackqueen;
  ChessPieces** blackrook;
  ChessPieces** blackknight;
  ChessPieces** blackbishop;
  ChessPieces** blackpawn;

  //Function to initialise (create) all the pieces dynamically
  void create_pieces();
  //Initial the board, mapping all the pieces to the specific board positions
  void init_mapping();
  //Function to check whether the board position string is valid
  bool check_string(const string& square) const;
  //Function to check whether it is the correct player to move in this turn
  bool check_turn(const ChessPieces* source_piece) const;
  //Function to determine whether the move leads to in check
  bool is_in_check();
  //Function to determine whteter the move leads to checkmate
  bool is_checkmate(const BlackOrWhite& current, const BlackOrWhite& opponent);
  //Move a piece from one position to another
  void move(ChessPieces* source_piece, const string& source, const string& dest,const map<string, ChessPieces*>::iterator& dest_piece);

public:
  ChessBoard();
  //Function to submit a move
  void submitMove(const string& source, const string& dest);
  //Function to reset board and begin a new game
  void resetBoard();
  //Function to return the chess board map.
  map<string, ChessPieces*> get_chessboard() const;
  //Function to check whether a certain position is empty or not
  bool is_empty_position(const string& dest)const;
  //Function to check whether a move leads to the current player (not the opponent) to be in check.
  bool is_attacking_own_king(const string& source, const string& dest);
  ~ChessBoard();
};

#endif
