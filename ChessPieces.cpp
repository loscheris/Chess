#include "ChessPieces.h"
#include "ChessBoard.h"

ChessPieces::ChessPieces(BlackOrWhite& _player, string _name, ChessBoard* _cb){
  player = _player;
  name = _name;
  cb = _cb;
  No_move = 0;
}

int ChessPieces::position_file_to_int(const string& position_str) const{
  int temp;
  char temp_char;
  temp_char = position_str[0];
  temp = (int) temp_char-64;
  return temp;
}

int ChessPieces::position_rank_to_int(const string& position_str) const{
  int temp;
  char temp_char;
  temp_char = position_str[1];
  temp = (int) temp_char-64;
  return temp;
}

vector<string> ChessPieces::leap_square(const string& source, const string& dest) const{
  vector<string> temp;
  return temp;
}


bool ChessPieces::check_leapover(const string& source, const string& dest) const{
  vector<string> leap_over = leap_square(source,dest);
  map<string, ChessPieces*> cb_mapping = cb->get_chessboard();
  map<string, ChessPieces*> :: iterator find_leap_over;
  for(int i=0; i<(int)leap_over.size(); i++){
    find_leap_over = cb_mapping.find(leap_over[i]);
    if(find_leap_over != cb_mapping.end()){
      return false;
    }
  }
  return true;
}


bool ChessPieces::check_dest_player(const string& dest) const{
  map<string, ChessPieces*> copy_cb = cb->get_chessboard();
  map<string, ChessPieces*> :: iterator it;
  it = copy_cb.find(dest);
  if(it!= copy_cb.end()){
    if(it->second->get_player()== this->player){
      return false;
    }
  }
  return true;
}


BlackOrWhite ChessPieces::get_player() const{
  return player;
}


string ChessPieces::get_name() const{
  return name;
}


bool ChessPieces::is_legal_move(const string& source, const string& dest) const{
  if(direct_attack(source,dest)==true&&cb->is_attacking_own_king(source,dest)==false){
    return true;
  }
  return false;
}


void ChessPieces::increase_no_move(){
  No_move++;
  return;
}


void ChessPieces::restset_move(){
  No_move=0;
  return;
}

ChessPieces::~ChessPieces(){}
