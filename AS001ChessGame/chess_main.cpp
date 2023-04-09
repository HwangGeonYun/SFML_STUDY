//
// Created by ghkdw on 2023-04-06.
//
// chess_main.cpp


#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include "chess.h"

/*void special_move_castling(int from_x, int from_y, ChessBoard board){
    if(from_y == 0){
        board[from_x][3]
    }

    else if(from_y = 8){

    }
}*/

bool make_move(ChessBoard board, int from_x, int from_y) {
    ChessPiece piece = board[from_x][from_y];
    if(piece.color == ' ')
        return false;

    std::vector<std::pair<int , int>> legal_moves;
    switch (piece.piece) {
        case PAWN: {
            legal_moves = find_pawn_moves(board, from_x, from_y, piece.color);
            break;
        }
        case KNIGHT:{
            legal_moves = find_knight_moves(board, from_x, from_y, piece.color);
            break;
        }
        case BISHOP:{
            legal_moves = find_bishop_moves(board, from_x, from_y, piece.color);
            break;
        }
        case ROOK:{
            legal_moves = find_rook_moves(board, from_x, from_y, piece.color);
            break;
        }
    }
    //이동할 곳이 존재하지 않을 때
    if(legal_moves.empty())
        return false;

    std::cout << "Legal moves: ";
    std::sort(legal_moves.begin(), legal_moves.end(), [](std::pair<int , int> moveA, std::pair<int , int> moveB){return moveA.first < moveB.first ||
            (moveA.first == moveB.first && moveA.second < moveB.second);} );

    std::for_each(legal_moves.begin(), legal_moves.end(), [](std::pair<int, int> move){std::cout << "("<< move.first <<", " << move.second << ") ";});


    std::cout << "\nSelect a move (0-" << legal_moves.size()-1 << "): \n";

    int selectingMove;

    std::cin >> selectingMove;
    //잘못된 곳을 선택했을때
    if(selectingMove < 0 || selectingMove > legal_moves.size()-1)
        return false;

    if(legal_moves[selectingMove].first == 9){ //앙파쌍

    }

    /*else if(legal_moves[selectingMove].first == 10){ //캐슬링은 킹의 행마지 룩의 행마가 아니다ㅜㅜ
        special_move_castling(from_x, from_y, board);
    }*/
     //일반 움직임
        //board[legal_moves[selectingMove].first][legal_moves[selectingMove].second].moved = true;
        //board[from_x][from_y].moved = true;
        board[legal_moves[selectingMove].first][legal_moves[selectingMove].second] = board[from_x][from_y];
        board[from_x][from_y] = {EMPTY, BLANK};

    std::cout << std::endl;
    return true;
}

int main() {
    /*ChessBoard board = {
            {{ROOK,   WHITE}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE},{KING,  WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK,   WHITE}},
            {{PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,  WHITE}, {PAWN,  WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,  BLACK}, {PAWN,  BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}},
            {{ROOK,   BLACK}, {KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK}, {KING,  BLACK}, {BISHOP, BLACK}, {KNIGHT, BLACK}, {ROOK,   BLACK}}
    };*/

   /* ChessBoard board = {
            {{EMPTY,  BLANK}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE},{KING,  WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK,   WHITE}},
            {{EMPTY,  BLANK}, {PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,  WHITE}, {PAWN,  WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,  BLACK}, {PAWN,  BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}},
            {{EMPTY,  BLANK}, {KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK}, {KING,  BLACK}, {BISHOP, BLACK}, {KNIGHT, BLACK}, {ROOK,   BLACK}}
    };*/

    ChessBoard board = {
                                {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
                                {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
                                {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {PAWN,  BLACK}, {PAWN,  WHITE}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
                                {{EMPTY,  BLANK}, {PAWN,  BLACK}, {PAWN,  BLACK}, {ROOK,  WHITE}, {PAWN,  BLACK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
                                {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {PAWN,  WHITE}, {PAWN,  BLACK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
                                {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
                                {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
                                {{EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK},
                                  {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}}
                                };

    /*auto board = std::make_unique<ChessBoard>();
    auto board = std::make_unique<std::unique_ptr<ChessPiece[]>[]>(BOARD_SIZE);

    board[0] = std::make_unique<ChessPiece[]>(std::initializer_list<ChessPiece>{{ROOK,   WHITE}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE},{KING,  WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK,   WHITE}});
    print_board(board);
/*/
    print_board(board);
    while (true) {
        int from_x, from_y;
        std::cout << "Select your piece (x y): ";
        std::cin >> from_x >> from_y;
        std::cin.ignore();
        if (from_x == -1 && from_y == -1) break;

        if (!make_move(board, from_x, from_y)) {
            std::cout << "Illegal move!\n";
            continue;
        }

        print_board(board);
    }

    return 0;
}

