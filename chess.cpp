////
//// Created by ghkdw on 2023-04-01.
////
//#include "chess.h"
//#include <algorithm>
//#include <memory>
//#include <iterator>
//
//void print_board(ChessBoard const board){
//    std::cout << "  0  1  2  3  4  5  6  7 \n";
//
//    for(int i = 0;i<8;i++){
//        std::cout << i<<" ";
//        for(int j = 0;j<8;j++){
//            std::cout << static_cast<char>(board[i][j].piece) << static_cast<char>(board[i][j].color) << ' ';
//        }
//        std::cout << "\n";
//    }
//    std::cout << "\n";
//}
//
//std::vector<std::pair<int, int>> find_pawn_moves(ChessBoard board,int x, int y, Color color){
//
//    std::vector<std::pair<int, int>> legal_moves;
//    int relativePosition;
//    int firstStartPosition;
//
//    switch(color){
//        case 'b':
//            relativePosition = 1;
//            firstStartPosition = 6;
//            //if(x == 6) legal_moves.push_back(std::make_pair(x, y+2*relativePosition));
//            break;
//        case 'w':
//            relativePosition = -1;
//            firstStartPosition = 2;
//            //if(x == 2) legal_moves.push_back(std::make_pair(x, y+2*relativePosition));
//            break;
//    }
//
//    legal_moves.push_back(std::make_pair(x, y+relativePosition));
//        if(x == firstStartPosition) legal_moves.push_back(std::make_pair(x, y+2*relativePosition));
//
//
//
//    //firstStartOfPawnCase
//
//
//    //std::swap(board[0][0], board[1][1]);
//
//    return legal_moves;
//};
