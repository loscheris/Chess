#ifndef ROOK_H
#define ROOK_H
#include "ChessPieces.h"

class Rook : public ChessPieces{
public:
  Rook(BlackOrWhite& _player, string _name, ChessBoard* _cb);
  virtual vector<string> leap_square(const string& source, const string& dest) const;
  virtual bool direct_attack(const string& source, const string& dest) const;
  ~Rook();
};

#endif
