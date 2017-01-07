#ifndef KNIGHT_H
#define KNIGHT_H
#include "ChessPieces.h"

class Knight : public ChessPieces{
public:
  Knight(BlackOrWhite& _player, string _name, ChessBoard* _cb);
  virtual bool direct_attack(const string& source, const string& dest) const;
  ~Knight();
};

#endif
