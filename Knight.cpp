#include "Knight.h"
#include "ChessBoard.h"

Knight::Knight(BlackOrWhite& _player, string _name, ChessBoard* _cb) : ChessPieces(_player, _name, _cb){
}

bool Knight::direct_attack(const string& source, const string& dest) const{
  if(check_dest_player(dest)==false){
    return false;
  }
  int source_file = position_file_to_int(source);
  int source_rank = position_rank_to_int(source);
  int dest_file = position_file_to_int(dest);
  int dest_rank = position_rank_to_int(dest);
  int diff_file = abs(source_file - dest_file);
  int diff_rank = abs(source_rank - dest_rank);
  //Move rules
  if(diff_rank==2 && diff_file ==1){
    return true;
  }else if(diff_rank==1 && diff_file ==2){
    return true;
  }
  return false;
}

Knight::~Knight(){}
