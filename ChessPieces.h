#ifndef CHESSPIECES_H
#define CHESSPIECES_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

enum  BlackOrWhite {White, Black};
class ChessBoard;

class ChessPieces{
protected:
  // The number of moves that the piece has already been made
  ChessBoard* cb;
  string name; //Name of the piece
  BlackOrWhite player;// Player (Black or White) of the piece

  //Functions to seperate the input postion (string) into file and rank (both in integer)
  int position_file_to_int(const string& position_str) const;
  int position_rank_to_int(const string& position_str) const;
  //Return the leap over postions between the souece and the destination positions
  virtual vector<string> leap_square(const string& source, const string& dest) const;
  //Check whether a move leap over any pieces
  bool check_leapover(const string& source, const string& dest) const;
  //Check whether the destination is occupied by your own piece
  bool check_dest_player(const string& dest) const;

public:
  ChessPieces(BlackOrWhite& _player, string _name, ChessBoard* _cb);
  //Return player
  BlackOrWhite get_player() const;
  //Return name
  string get_name() const;
  //Check whether the move is legal or not
  bool is_legal_move(const string& source, const string& dest) const;
  //Pure virtual fucntion: to check if a piece can directly move from source to destination (without checking whether the move leads to your own king in danger)
  virtual bool direct_attack(const string& source, const string& dest) const=0;
  //Increase No_move
  void increase_no_move();
  //Set No_move to 0
  void restset_move();
  //Virtual destructor
  virtual ~ChessPieces();
  int No_move;
};

#endif
