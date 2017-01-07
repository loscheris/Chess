#include "ChessBoard.h"
//Overload << operator
ostream& operator<<(ostream& out,const BlackOrWhite input){
  if(input==White){
    out<<"White";
  }else{
    out<<"Black";
  }
  return out;
}


ChessBoard::ChessBoard(){
  game_over = false;
  No_move = 0;
  new_game = true;
  create_pieces();
  init_mapping();
}

void ChessBoard::create_pieces(){
  BlackOrWhite white = White;
  BlackOrWhite black = Black;
  string k = "King";
  string q = "Queen";
  string r = "Rook";
  string b = "Bishop";
  string kn = "Knight";
  string p = "Pawn";
  //White pieces
  whiteking = new King(white, k, this);
  whitequeen = new Queen(white, q, this);
  whiterook = new ChessPieces*[2];
  whiteknight = new ChessPieces*[2];
  whitebishop = new ChessPieces*[2];
  whitepawn = new ChessPieces*[8];
  //Black pieces
  blackking = new King(black, k, this);
  blackqueen = new Queen(black, q, this);
  blackrook = new ChessPieces*[2];
  blackknight = new ChessPieces*[2];
  blackbishop = new ChessPieces*[2];
  blackpawn = new ChessPieces*[8];
  // Rook/Knight/Bishop x2
  for(int i=0; i<2; i++){
    whiterook[i] = new Rook(white,r, this);
    whiteknight[i] = new Knight(white,kn, this);
    whitebishop[i] = new Bishop(white,b, this);
    blackrook[i] = new Rook(black,r, this);
    blackknight[i] = new Knight(black,kn, this);
    blackbishop[i] = new Bishop(black,b, this);
  }
  //Pawn x8
  for(int i=0; i<8; i++){
    whitepawn[i] = new Pawn(white,p, this);
    blackpawn[i] = new Pawn(black,p, this);
  }
}


void ChessBoard::init_mapping(){
  //Mapping for ant other pieces except pawn
  chessboard_mapping["A1"] = whiterook[0];
  chessboard_mapping["B1"] = whiteknight[0];
  chessboard_mapping["C1"] = whitebishop[0];
  chessboard_mapping["D1"] = whitequeen;
  chessboard_mapping["E1"] = whiteking;
  chessboard_mapping["F1"] = whitebishop[1];
  chessboard_mapping["G1"] = whiteknight[1];
  chessboard_mapping["H1"] = whiterook[1];
  chessboard_mapping["A8"] = blackrook[0];
  chessboard_mapping["B8"] = blackknight[0];
  chessboard_mapping["C8"] = blackbishop[0];
  chessboard_mapping["D8"] = blackqueen;
  chessboard_mapping["E8"] = blackking;
  chessboard_mapping["F8"] = blackbishop[1];
  chessboard_mapping["G8"] = blackknight[1];
  chessboard_mapping["H8"] = blackrook[1];
  //Mapping for pawns
  for(char i='A'; i<'I'; i++){
    stringstream ss;
    string temp_str_black;
    string temp_str_white;
    ss<<i;
    ss>>temp_str_white;
    temp_str_black = temp_str_white;
    temp_str_white.append("2");
    temp_str_black.append("7");
    chessboard_mapping[temp_str_white] = whitepawn[(int)i - 65];
    chessboard_mapping[temp_str_black] = blackpawn[(int)i - 65];
  }
}


bool ChessBoard::check_string(const string& square) const{
  if(square.length()!=2){
    cout<<square<<" is not a valid position."<<endl;
    return false;
  }else if(square[0]<'A'||square[0]>'H'){
    cout<<square<<" is not a valid postion."<<endl;
    return false;
  }else if(square[1]<'1'||square[1]>'8'){
    cout<<square<<" is not a valid postion."<<endl;
    return false;
  }
  return true;
}


bool ChessBoard::check_turn(const ChessPieces* source_piece) const{
  BlackOrWhite player = source_piece->get_player();
  if(player == White && No_move%2!=0){
    return false;
  }else if(player == Black && No_move%2!=1){
    return false;
  }
  return true;
}


bool ChessBoard::is_in_check(){
  BlackOrWhite current;
  BlackOrWhite opponent;
  if(No_move%2==0){
    current = White;
    opponent = Black;
  }else{
    current = Black;
    opponent = White;
  }
  string opponent_king;
  //Find opponent king position
  map<string, ChessPieces*> :: iterator it;
  for(it=chessboard_mapping.begin();it!=chessboard_mapping.end();it++){
    if(it->second->get_name()=="King"&&it->second->get_player()==opponent){
      opponent_king = it->first;
      break;
    }
  }
  //Check whether the opponent is in check
  for(it=chessboard_mapping.begin();it!=chessboard_mapping.end();it++){
    if(it->second->get_player()==current){
      if(it->second->direct_attack(it->first,opponent_king)){
        return true;
      }
    }
  }
  return false;
}


bool ChessBoard::is_checkmate(const BlackOrWhite& current, const BlackOrWhite& opponent){
  //Whole board
  vector<string> whole_board;
  for(char i = 'A'; i<='H'; i++){
    for(char j = '1'; j<= '8'; j++){
      string temp;
      temp +=i;
      temp +=j;
      whole_board.push_back(temp);
    }
  }
  //Iterrate the map, move any opponent pieces to see whether the current player is still in check
  map<string, ChessPieces*> :: iterator it;
  for(it=chessboard_mapping.begin();it!=chessboard_mapping.end();it++){
    string original_pos = it->first;
    ChessPieces* it_second = it->second;
    if(it->second->get_player()==opponent){
      for(int i=0; i<(int)whole_board.size(); i++){
        if(it_second->is_legal_move(original_pos, whole_board[i])==true){
          //attemp move
          ChessPieces* temp_piece;
          bool dest_empty=true;
          if(chessboard_mapping.find(whole_board[i])!=chessboard_mapping.end()){
            dest_empty=false;
            temp_piece = chessboard_mapping[whole_board[i]];
          }
          chessboard_mapping[whole_board[i]]=chessboard_mapping[original_pos];
          chessboard_mapping.erase(original_pos);
          //The case of one of opponent move leads to the removal of current in check state
          if(is_in_check()==false){
            //recover board
            chessboard_mapping[original_pos]=chessboard_mapping[whole_board[i]];
            chessboard_mapping.erase(whole_board[i]);
            if(dest_empty==false){
              chessboard_mapping[whole_board[i]] = temp_piece;
              dest_empty = true;
            }
            return false;
          }
          //recover board
          chessboard_mapping[original_pos]=chessboard_mapping[whole_board[i]];
          chessboard_mapping.erase(whole_board[i]);
          if(dest_empty==false){
            chessboard_mapping[whole_board[i]] = temp_piece;
            dest_empty = true;
          }
        }
      }
    }
    it=chessboard_mapping.find(original_pos);
  }
  return true;
}


bool ChessBoard::is_attacking_own_king(const string& source, const string& dest){
  string original_pos = source;
  string destination = dest;
  ChessPieces* temp_piece;
  bool dest_empty=true;
  string own_king_pos;
  BlackOrWhite current = chessboard_mapping[source]->get_player();
  //attemp move
  if(chessboard_mapping.find(destination)!=chessboard_mapping.end()){
    temp_piece = chessboard_mapping[destination];
    dest_empty=false;
  }
  chessboard_mapping[destination]=chessboard_mapping[source];
  chessboard_mapping.erase(original_pos);
  //Find the current player's King
  map<string,ChessPieces*> :: iterator it;
  for(it=chessboard_mapping.begin(); it!=chessboard_mapping.end(); it++){
    if(it->second->get_player()==current && it->second->get_name()=="King"){
      own_king_pos = it->first;
      break;
    }
  }
  //Check any opponent pieces can attack the own King dircetly
  for(it=chessboard_mapping.begin(); it!=chessboard_mapping.end();it++){
    if(it->second->get_player()!= current){
      if(it->second->direct_attack(it->first, own_king_pos)==true){
        //recover board and return true
        chessboard_mapping[original_pos]=chessboard_mapping[destination];
        chessboard_mapping.erase(destination);
        if(dest_empty==false){
          chessboard_mapping[destination] = temp_piece;
          dest_empty = true;
        }
        return true;
      }
    }
  }
  //recover board
  chessboard_mapping[original_pos]=chessboard_mapping[destination];
  chessboard_mapping.erase(destination);
  if(dest_empty==false){
    chessboard_mapping[destination] = temp_piece;
    dest_empty = true;
  }
  return false;
}


void ChessBoard::submitMove(const string& source,const string& dest){
  //Check game state
  if(new_game==true){
    cout<<"A new chess game is started!"<<endl<<endl;
    new_game = false;
  }else if(game_over==true){
    cout<<"The game is over, please reset board!"<<endl;
    return;
  }
  //Check input string
  if(check_string(source)==false||check_string(dest)==false){
    return;
  }else if(source == dest){
    cout<<"The destination square is the same as the source."<<endl;
    return;
  }

  map<string, ChessPieces*> :: iterator source_piece_it;
  source_piece_it=chessboard_mapping.find(source);
  map<string, ChessPieces*> :: iterator dest_piece_it;
  dest_piece_it=chessboard_mapping.find(dest);
  // Check if the source position is empty or not
  if(source_piece_it == chessboard_mapping.end()){
    cout<<"There is no piece at postion "<<source<<"!"<<endl;
    return;
  }
  ChessPieces* source_piece = chessboard_mapping[source];
  //Check whether the move is valid or not
  if(check_turn(source_piece)==false){
    cout<<"It is not "<<source_piece->get_player()<<"'s turn to move!"<<endl;
    return;
  }else if(source_piece->is_legal_move(source, dest)==false){
    cout<<source_piece->get_player()<<"'s "<<source_piece->get_name()<<" cannot move to "<<dest<<endl;
    return;
  }
  //Make move/Change the Board
  move(source_piece, source, dest, dest_piece_it);
  //Check for in check/checkmate/stalemate
  BlackOrWhite current;
  BlackOrWhite opponent;
  if(No_move%2==0){
    current = White;
    opponent = Black;
  }else{
    current = Black;
    opponent = White;
  }
  if(is_in_check()==true){
    if(is_checkmate(current,opponent)==true){
      game_over = true;
      cout<<opponent<<" is in checkmate"<<endl;
      return;
    }else{
      cout<<opponent<<" is in check"<<endl;
    }
  }else if(is_checkmate(current,opponent)==true){
    game_over = true;
    cout<<opponent<<" is in stalemate"<<endl;
    return;
  }
  No_move++;
  return;
}


map<string, ChessPieces*> ChessBoard::get_chessboard()const{
  return chessboard_mapping;
}


bool ChessBoard::is_empty_position(const string& dest)const{
  map<string, ChessPieces*> :: const_iterator it;
  it = chessboard_mapping.find(dest);
  if(it == chessboard_mapping.end()){
    return true;
  }
  return false;
}


void ChessBoard::move(ChessPieces* source_piece, const string& source, const string& dest, const map<string, ChessPieces*>::iterator& dest_piece){
  cout<< source_piece->get_player()<<"'s "<<source_piece->get_name()<<" moves from "<<source<<" to "<<dest;

  if(dest_piece==chessboard_mapping.end()){
    cout<<endl;
  }else{
    cout<<" taking ";
    if(source_piece->get_player()==White){
      cout<<"Black's ";
    }else{
      cout<<"White's ";
    }
    cout<<dest_piece->second->get_name()<<endl;
  }
  //Change the board
  source_piece->increase_no_move();
  chessboard_mapping.erase(dest);
  chessboard_mapping[dest] = source_piece;
  chessboard_mapping.erase(source);
  return;
}


void ChessBoard::resetBoard(){
  game_over =false;
  No_move = 0;
  chessboard_mapping.clear();
  init_mapping();
  map<string,ChessPieces*>::iterator it;
  for(it = chessboard_mapping.begin(); it!=chessboard_mapping.end();it++){
    it->second->restset_move();
  }
  cout<<"A new chess game is started!"<<endl;
}

ChessBoard::~ChessBoard(){
  chessboard_mapping.clear();
  //delete all dynamic allocated objects
  delete whiteking;
  delete whitequeen;
  delete blackking;
  delete blackqueen;
  for(int i=0; i<2; i++){
    delete whiterook[i];
    delete blackrook[i];
    delete whiteknight[i];
    delete blackknight[i];
    delete whitebishop[i];
    delete blackbishop[i];
  }
  for(int i=0; i<8; i++){
    delete whitepawn[i];
    delete blackpawn[i];
  }
  delete[] whiterook;
  delete[] blackrook;
  delete[] whiteknight;
  delete[] blackknight;
  delete[] whitebishop;
  delete[] blackbishop;
  delete[] whitepawn;
  delete[] blackpawn;
}
