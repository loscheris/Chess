#ifndef QUEEN_H
#define QUEEN_H
#include "ChessPieces.h"

class Queen : public ChessPieces{
public:
  Queen(BlackOrWhite& _player, string _name, ChessBoard* _cb);
  virtual vector<string> leap_square(const string& source, const string& dest) const;
  virtual bool direct_attack(const string& source, const string& dest) const;
  ~Queen();
};

#endif
