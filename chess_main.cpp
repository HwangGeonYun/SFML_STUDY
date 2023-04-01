////
//// Created by ghkdw on 2023-04-01.
////
//#include <iostream>
//#include <algorithm>
//#include "chess.h"
//
//using namespace std;
//bool make_move(ChessBoard board, int from_x, int from_y) {
//    ChessPiece piece = board[from_x][from_y];
//    while(piece.piece == EMPTY){
//        cout << "don't touch Blank" <<std::endl;
//    }
//
//    std::vector<std::pair<int, int>> legal_moves;
//    switch (piece.piece) {
//        case PAWN: {
//            // implement your code
//            //....
//            legal_moves = find_pawn_moves(board, from_x, from_y, piece.color);
//            break;
//        }
//
//    }
//
//    std::for_each(legal_moves.begin(), legal_moves.end(), [](pair<int, int> move){ cout<< "(" << move.first<< ", " << move.second<< ")";});
//    cout << "\nSelect a move (0-" << legal_moves.size()-1 << "): ";
//    int selectMove;
//    cin >> selectMove;
//
//    if(0<=selectMove && selectMove <= legal_moves.size()-1) {
//       // swap();
//        return true;
//    }
//    else
//        return false;
//}
//int main() {
//
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    ChessBoard board = {
//            {{ROOK,   WHITE}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE},{KING,  WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK,   WHITE}},
//            {{PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,  WHITE}, {PAWN,  WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}},
//            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
//            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
//            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
//            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
//            {{PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,  BLACK}, {PAWN,  BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}},
//            {{ROOK,   BLACK}, {KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK}, {KING,  BLACK}, {BISHOP, BLACK}, {KNIGHT, BLACK}, {ROOK,   BLACK}}
//    };
//
//    print_board(board);
//
//    while (true) {
//        int from_x, from_y;
//        std::cout << "Select your piece (x y): ";
//        std::cin >> from_x >> from_y;
//        std::cin.ignore();
//        if (from_x == -1 && from_y == -1) break;
//
//        if (!make_move(board, from_x, from_y)) {
//            std::cout << "Illegal move!\n";
//            continue;
//        }
//
//        print_board(board);
//    }
//
//    return 0;
//}