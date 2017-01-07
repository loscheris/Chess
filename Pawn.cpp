#include "ChessBoard.h"
#include "Pawn.h"

Pawn::Pawn(BlackOrWhite& _player, string _name, ChessBoard* _cb) : ChessPieces(_player, _name, _cb){
}


string Pawn::position_in_front(const string& source) const{
  string temp;
  temp += source[0];
  temp += source[1]+1;
  return temp;
}


bool Pawn::direct_attack(const string& source, const string& dest)const{
  if(check_dest_player(dest)==false){
    return false;
  }
  int source_file = position_file_to_int(source);
  int source_rank = position_rank_to_int(source);
  int dest_file = position_file_to_int(dest);
  int dest_rank = position_rank_to_int(dest);
  int abs_diff_file = abs(source_file - dest_file);
  int diff_file = dest_file - source_file;
  int diff_rank = dest_rank - source_rank;

  //Move rules for white pawn
  if(this->player == White ){
    string in_front = position_in_front(source);
    if(diff_rank==2 && diff_file==0 && No_move==0 && cb->is_empty_position(dest)==true && cb->is_empty_position(in_front)==true){
      return true;
    }else if(diff_rank==1 && diff_file==0 && cb->is_empty_position(dest)==true){
      return true;
    }else if(diff_rank==1 && abs_diff_file==1 && cb->is_empty_position(dest)==false){
      return true;
    }
  }
  //Move rules for black pawn
  if(this->player == Black ){
    string in_front = position_in_front(dest);
    if(diff_rank==-2 && diff_file==0 && No_move==0 &&cb->is_empty_position(dest)==true && cb->is_empty_position(in_front)==true){
      return true;
    }else if(diff_rank==-1 && diff_file==0 && cb->is_empty_position(dest)==true){
      return true;
    }else if(diff_rank==-1 && abs_diff_file==1 && cb->is_empty_position(dest)==false){
      return true;
    }
  }
  return false;
}


Pawn::~Pawn(){}
