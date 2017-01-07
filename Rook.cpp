#include "Rook.h"
#include "ChessBoard.h"
Rook::Rook(BlackOrWhite& _player, string _name, ChessBoard* _cb) : ChessPieces(_player, _name, _cb){
}


vector<string> Rook::leap_square(const string& source, const string& dest) const{
  vector<string> temp;
  char start;
  char end;
  if(source[0]==dest[0]){
  //The case that rook move along the same file
    if(source[1]<dest[1]){
      start = source[1];
      end = dest[1];
    }else{
      start = dest[1];
      end = source[1];
    }
    for(char i= start+1; i<end; i++){
      string temp_str;
      temp_str += source[0];
      temp.push_back(temp_str+=i);
    }
  }else{
    //The case that rook move along the same rank
    if(source[0]<dest[0]){
      start = source[0];
      end = dest[0];
    }else{
      start = dest[0];
      end = source[0];
    }
    for(char i= start+1; i<end; i++){
      string temp_str;
      temp_str += i;
      temp.push_back(temp_str+=source[1]);
    }
  }
  return temp;
}


bool Rook::direct_attack(const string& source, const string& dest) const{
  if(check_dest_player(dest)==false){
    return false;
  }
  int source_file = position_file_to_int(source);
  int source_rank = position_rank_to_int(source);
  int dest_file = position_file_to_int(dest);
  int dest_rank = position_rank_to_int(dest);
  //Move rules
  if(source_file == dest_file || source_rank == dest_rank){
    if(check_leapover(source, dest)==true){
      return true;
    }
  }
  return false;
}


Rook::~Rook(){}
