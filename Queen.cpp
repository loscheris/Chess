#include "Queen.h"
#include "ChessBoard.h"
Queen::Queen(BlackOrWhite& _player, string _name, ChessBoard* _cb) : ChessPieces(_player, _name, _cb){
}


vector<string> Queen::leap_square(const string& source, const string& dest) const{
  vector<string> temp;
  //The case that the queen moves as rook and return the leap over positions
  char start;
  char end;
  if(source[0]==dest[0]){
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
  }else if(source[1]==dest[1]){
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

  //The case that the queen moves as bishop and return the leap over positions
  char file_start;
  char rank_start;
  char rank_end;
  if(source[0]<dest[0]&&source[1]<dest[1]){
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


bool Queen::direct_attack(const string& source, const string& dest) const{
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
  }else if(source_file == dest_file || source_rank == dest_rank){
    if(check_leapover(source, dest)==true){
      return true;
    }
  }

  return false;
}


Queen::~Queen(){}
