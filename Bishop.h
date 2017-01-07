#ifndef BISHOP_H
#define BISHOP_H
#include "ChessPieces.h"

class Bishop : public ChessPieces{
public:
  Bishop(BlackOrWhite& _player, string _name, ChessBoard* _cb);
  virtual vector<string> leap_square(const string& source, const string& dest) const;
  virtual bool direct_attack(const string& source, const string& dest) const;
  ~Bishop();
};

#endif
