#ifndef PAWN_H
#define PAWN_H
#include "ChessPieces.h"

class Pawn : public ChessPieces{
public:
  Pawn(BlackOrWhite& _player, string _name, ChessBoard* _cb);
  //Function to return the position (string) directly in front of the pawn
  string position_in_front(const string& source) const;
  virtual bool direct_attack(const string& source, const string& dest) const;
  ~Pawn();
};

#endif
