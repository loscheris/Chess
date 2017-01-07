#ifndef KING_H
#define KING_H
#include "ChessPieces.h"

class King : public ChessPieces{
public:
  King(BlackOrWhite& _player, string _name, ChessBoard* _cb);
  virtual bool direct_attack(const string& source, const string& dest) const;
  ~King();
};

#endif
