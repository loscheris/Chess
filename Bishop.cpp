#include "Bishop.h"
#include "ChessBoard.h"

Bishop::Bishop(BlackOrWhite& _player, string _name, ChessBoard* _cb) : ChessPieces(_player, _name, _cb){
}


vector<string> Bishop::leap_square(const string& source, const string& dest) const{
  vector<string> temp;
  char file_start;
  char rank_start;
  char rank_end;
  if(source[0]<dest[0]&&source[1]<dest[1]){
    //The case that Bishop moves in the direction of from bottom left to top right
    rank_start = source[0];
    rank_end = dest[0];
    file_start = source[1];
    for(char i=rank_start+1; i<rank_end; i++){
      string temp_str;
      temp_str += i;
      temp_str += ++file_start;
      temp.push_back(temp_str);
    }
  }else if(source[0]>dest[0]&&source[1]>dest[1]){
    //The case that Bishop moves in the direction of from top right to bottom left
    rank_start = dest[0];
    rank_end = source[0];
    file_start = dest[1];
    for(char i=rank_start+1; i<rank_end; i++){
      string temp_str;
      temp_str += i;
      temp_str += ++file_start;
      temp.push_back(temp_str);
    }
  }else if(source[0]<dest[0]&&source[1]>dest[1]){
    //The case that Bishop moves in the direction of from top left to bottom right
    rank_start = source[0];
    rank_end = dest[0];
    file_start = source[1];
    for(char i=rank_start+1; i<rank_end; i++){
      string temp_str;
      temp_str += i;
      temp_str += --file_start;
      temp.push_back(temp_str);
    }
  }else if(source[0]>dest[0]&&source[1]<dest[1]){
    //The case that Bishop moves in the direction of from bottom right to top left
    rank_start = dest[0];
    rank_end = source[0];
    file_start = dest[1];
    for(char i=rank_start+1; i<rank_end; i++){
      string temp_str;
      temp_str += i;
      temp_str += --file_start;
      temp.push_back(temp_str);
    }
  }
  return temp;
}


bool Bishop::direct_attack(const string& source, const string& dest) const{
  if(check_dest_player(dest)==false){
    return false;
  }
  int source_file = position_file_to_int(source);
  int source_rank = position_rank_to_int(source);
  int dest_file = position_file_to_int(dest);
  int dest_rank = position_rank_to_int(dest);
  int diff_file = abs(source_file - dest_file);
  int diff_rank = abs(source_rank - dest_rank);
  //move rules
  if(diff_file == diff_rank){
    if(check_leapover(source, dest)==true){
      return true;
    }
  }
  return false;
}


Bishop::~Bishop(){}
