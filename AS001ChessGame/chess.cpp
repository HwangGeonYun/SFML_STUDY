//
// Created by ghkdw on 2023-04-06.
//
#include "chess.h"
#include <iostream>
#include <algorithm>
#include <memory>

void print_board(ChessBoard const board) {
    std::cout << "  ";

    /*auto unique_board = std::make_unique<std::unique_ptr<ChessPiece[]>[]>(BOARD_SIZE);

    for(int i = 0;i<BOARD_SIZE;i++) unique_board[i] = std::make_unique<ChessPiece[]>(BOARD_SIZE);

    for(int i =0;i<BOARD_SIZE;i++) std::copy(board[i], board[i]+BOARD_SIZE, unique_board[i].get());*/

    //std::copy(std::begin(board*), std::end(board*), )
    for (int i = 0; i < BOARD_SIZE; i++)
        std::cout << i << "  ";

    std::cout << "\n";

    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
                std::cout << static_cast<char>(board[i][j].piece) << static_cast<char>(board[i][j].color) << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::pair<int, int>> find_pawn_moves(ChessBoard board,int x, int y, Color color){
    std::vector<std::pair<int , int>> legalMoves;
    ChessPiece piece;
    if(color == WHITE) {
        //그냥 이동
        if(board[x+1][y].color == BLANK)
            legalMoves.push_back({x+1, y});
        if(x == 1 && board[x+2][y].color == BLANK)
            legalMoves.push_back({x+2, y});

        //잡아 먹을 때 이동
        if(board[x+1][y-1].color == BLACK)
            legalMoves.push_back({x+1, y-1});
        if(board[x+1][y+1].color == BLACK)
            legalMoves.push_back({x+1, y+1});

        //앙파쌍
        if(x == 4) {
            if (board[x][y - 1].color == BLACK)
                legalMoves.push_back({x + 1, y - 1});

            if (board[x][y + 1].color == BLACK)
                legalMoves.push_back({x + 1, y + 1});
        }
    }
    else if(color == BLACK){
        //그냥 이동
        if(board[x-1][y].color == BLANK)
            legalMoves.push_back({x-1, y});
        if(x == 6 && board[x-2][y].color == BLANK)
            legalMoves.push_back({x-2, y});

        //잡아 먹을 때 이동
        if(board[x-1][y-1].color == WHITE)
            legalMoves.push_back({x-1, y-1});
        if(board[x-1][y+1].color == WHITE)
            legalMoves.push_back({x-1, y+1});

        //앙파쌍
        if(x == 3) {
            if (board[x][y - 1].color == WHITE)
                legalMoves.push_back({x - 1, y - 1});

            if (board[x][y + 1].color == WHITE)
                legalMoves.push_back({x - 1, y + 1});
        }
    }

    return legalMoves;
    //return vec;

}

std::vector<std::pair<int, int>> find_knight_moves(ChessBoard board,int x, int y, Color color) {
    std::vector<std::pair<int , int>> legalMoves ={
            {x+2, y+1}, {x+2, y-1}, {x-2, y+1}, {x-2, y-1},
            {x+1, y+2}, {x+1, y-2}, {x-1, y+2}, {x-1, y-2}
            };


    legalMoves.erase(std::remove_if(legalMoves.begin(), legalMoves.end(), [](std::pair<int , int> move){
        return move.first<0 || move.first >7 || move.second<0 || move.second>7;
    })
    , legalMoves.end());

    legalMoves.erase(std::remove_if(legalMoves.begin(), legalMoves.end(), [&board, &color](std::pair<int, int> move){
        return board[move.first][move.second].color == color;
    }), legalMoves.end());

    return legalMoves;
}

std::vector<std::pair<int, int>> find_bishop_moves(ChessBoard board, int x, int y, Color color){

    std::vector<std::pair<int, int>> legalMoves;

    std::vector<std::pair<int, int>> move_diagonal = find_move_vertical_diagonal("DIAGONAL", board, x, y, color);
    std::vector<std::pair<int, int>> move_antidiagonal = find_move_horizon_anti_diagonal("ANTI_DIAGONAL", board, x, y, color);
    //std:://vector<std::pair<int, int>> move_horizon = find_move_horizon_anti_diagonal(board, x, y, color);
    legalMoves.insert(legalMoves.end(), move_diagonal.begin(), move_diagonal.end());
    legalMoves.insert(legalMoves.end(), move_antidiagonal.begin(), move_antidiagonal.end());

    return legalMoves;
}

std::vector<std::pair<int, int>> find_rook_moves(ChessBoard board,int x, int y, Color color){
    /*std::vector<std::pair<int , int>> legalMoves(64);
    int n = 0;

    std::generate(legalMoves.begin(), legalMoves.end(), [&n](){
        return std::make_pair(n/8, (n++)%8);});

    legalMoves.erase(std::remove_if(legalMoves.begin(), legalMoves.end(), [&x, &y](std::pair<int, int> move){
        return move.first != x && move.second != y;
    }), legalMoves.end());

    std::vector<std::pair<int, int>> height;


    std::copy_if(legalMoves.begin(), legalMoves.end(), std::back_inserter(height), [&x, &y](std::pair<int, int> move){
        return (move.second == y);
    });

    std::vector<std::pair<int, int>> malls;

    std::copy_if(height.begin(), height.end(), std::back_inserter(malls), [&board](std::pair<int , int> move){
        return board[move.first][move.second].piece != EMPTY;
    });



    int bokunoposition = std::count_if(malls.begin(), malls.end(), [&x, &y](std::pair<int, int> move){return move.first = x && move.second == y;});

    std::pair<int , int> before = height[bokunoposition-1];
    std::pair<int, int> after = height[bokunoposition+1];

    std::vector<std::pair<int , int>> goal;

    std::copy_if(height.begin(), height.end(), std::back_inserter(goal), [&before, &after](std::pair<int, int> move){
        return before.first <move.first && move.first <after.first;});

    /*std::sort(height.begin(), height.end(), [](std::pair<int , int> moveA, std::pair<int , int> moveB){
        return moveA.first < moveB.first;
    });

    auto before = height.begin();
    std::advance(before, x+1);

    std::find_if(height.begin(), before, [](){return });
*/
    /*std::vector<std::pair<int, int>> width;

    std::copy_if(legalMoves.begin(), legalMoves.end(), std::back_inserter(width), [&x, &y](std::pair<int, int> move){
        return move.first == x && move.second != y;
    });*/

    //legalMoves.erase(std::remove_if(legalMoves.begin(), ))

    /*std::vector<std::pair<int, int>> rightTopMoves = find_move_by_location("RIGHT", x, y, color, board);
    std::vector<std::pair<int, int>> leftTopMoves = find_move_by_location("TOP", x, y, color, board);
    std::vector<std::pair<int, int>> leftBottomMoves =find_move_by_location("LEFT", x, y, color, board);
    std::vector<std::pair<int, int>> rightBottomMoves =find_move_by_location("BOTTOM", x, y, color, board);

    legalMoves.insert(legalMoves.end(), rightTopMoves.begin(), rightTopMoves.end());
    legalMoves.insert(legalMoves.end(), leftTopMoves.begin(), leftTopMoves.end());
    legalMoves.insert(legalMoves.end(), leftBottomMoves.begin(), leftBottomMoves.end());
    legalMoves.insert(legalMoves.end(), rightBottomMoves.begin(), rightBottomMoves.end());
*/
    //castling은 킹의 행마이기에 룩에서 구현해선 안된다ㅜㅜ
    //if(check_castling(x, y, board) == true) legalMoves.push_back(std::make_pair(10, y)); //10은 캐슬링을 지칭하는 특별 번호, y는 캐슬링할 룩의 위치

    //else if(color == BLACK);

    /*if(color == WHITE)
        if(x == 0 && y == 0)
            if(board[x][y].moved == false && board[0][4].moved == false)
                for(int i = y; i<4;i++){
                    if(board[x][i].piece == BLANK)

                }
      */

    std::vector<std::pair<int, int>> legalMoves;

    std::vector<std::pair<int, int>> move_vertical = find_move_vertical_diagonal("VERTICAL", board, x, y, color);
    std::vector<std::pair<int, int>> move_horizon = find_move_horizon_anti_diagonal("HORIZON", board, x, y, color);
    legalMoves.insert(legalMoves.end(), move_vertical.begin(), move_vertical.end());
    legalMoves.insert(legalMoves.end(), move_horizon.begin(), move_horizon.end());

    //legalMoves = find_move_horizon_anti_diagonal(board, x, y, color);

    return legalMoves;
}

/*std::vector<std::pair<int, int>> find_move_by_location(std::string move_location, int x, int y, Color color, ChessBoard board){
    std::vector<std::pair<int , int>> legalMoves;

    int moveRight, moveTop;

    if(move_location == "RIGHT_TOP")
        moveTop = -1, moveRight = 1;
    else if(move_location == "LEFT_TOP")
        moveTop = -1, moveRight = -1;
    else if(move_location == "LEFT_BOTTOM")
        moveTop = 1, moveRight = -1;
    else if(move_location == "RIGHT_BOTTOM")
        moveTop = 1, moveRight = 1;
    else if(move_location == "RIGHT")
        moveTop = 0, moveRight = 1;
    else if(move_location == "TOP")
        moveTop = -1, moveRight = 0;
    else if(move_location == "LEFT")
        moveTop = 0, moveRight = -1;
    else if(move_location == "BOTTOM")
        moveTop = 1, moveRight = 0;



    //std::transform(board[x][y], end(), );

    /*int i = 0;
    while(board[x+(++i)*moveTop][y+i*moveRight].color == BLANK) {
        if(x + i*moveTop<0 || x + i*moveTop >7 || y + i*moveRight <0 || y + i*moveRight>7) break;
            legalMoves.push_back({x + i*moveTop, y + i*moveRight});
    }


    if(color == WHITE) {if(board[x+i*moveTop][y+i*moveRight].color == BLACK && !(x + i*moveTop<0 || x + i*moveTop >7 || y + i*moveRight <0 || y + i*moveRight>7)) legalMoves.push_back({x+i*moveTop, y+i*moveRight});}

    else if(color == BLACK) {if(board[x+i*moveTop][y+i*moveRight].color == WHITE && !(x + i*moveTop<0 || x + i*moveTop >7 || y + i*moveRight <0 || y + i*moveRight>7)) legalMoves.push_back({x+i*moveTop, y+i*moveRight});}

    return legalMoves;
}*/

/*bool check_castling(int x, int y, ChessBoard board){
    //현재 위치의 룩이 움직였나?
    if(board[x][y].moved != false)
        return false;
    //현재 우리 킹이 움직였나?
    if(board[x][4].piece != KING || board[x][4].moved != false)
        return false;

    int max = std::max(4, y);
    int min = std::min(4, y);

    //킹과 룩 사이에 기물이 존재하는가?
    for(int i = min+1;i<max;i++){
        if(board[x][i].piece !=BLANK)
            return false;
    }

    return true;
}*/

std::vector<std::pair<int, int>> find_move_vertical_diagonal(std::string location, ChessBoard board, int x, int y, Color color){

    int forDiagonal;

    if(location == "VERTICAL")
        forDiagonal = 0;
    else if(location == "DIAGONAL")
        forDiagonal = 1;
    int n = 0;

    std::vector<std::pair<int, int>> legalMoves(8);

    std::generate(legalMoves.begin(), legalMoves.end(), [&x, &y, &forDiagonal, i = 0]()mutable{
        int distance = x - i++;
        return std::make_pair(x -distance, y + distance*forDiagonal);
    });

    legalMoves.erase(std::remove_if(legalMoves.begin(), legalMoves.end(), [](std::pair<int, int> move){
        return move.first<0 || 7<move.first || move.second<0 || 7<move.second;
    }), legalMoves.end());

    std::sort(legalMoves.begin(), legalMoves.end(), [](std::pair<int, int> moveA, std::pair<int, int> moveB){return moveA.first < moveB.first;});

    std::vector<std::pair<int, int>> malls;

    std::copy_if(legalMoves.begin(), legalMoves.end(), std::back_inserter(malls), [&board](std::pair<int , int> move){
        return board[move.first][move.second].piece != EMPTY;
    });

    std::sort(malls.begin(), malls.end(), [](std::pair<int, int> moveA, std::pair<int, int> moveB){return moveA.first < moveB.first;});

    int bokunoposition = std::find_if(malls.begin(), malls.end(), [&x, &y](std::pair<int, int> move){return (move.first == x && move.second == y);}) - malls.begin();

    std::pair<int , int> before;
    std::pair<int, int> after;
    if(bokunoposition==0)
        before = {legalMoves[0].first-1 ,legalMoves[0].second +1};
    else if(board[malls[bokunoposition-1].first][malls[bokunoposition-1].second].color != color)
         before = {malls[bokunoposition-1].first-1, malls[bokunoposition-1].second-forDiagonal};
    else
        before = malls[bokunoposition-1];
    if(bokunoposition==malls.size()-1)
        after = {legalMoves[legalMoves.size()-1].first+1, legalMoves[legalMoves.size()-1].second-1};
    else if(board[malls[bokunoposition+1].first][malls[bokunoposition+1].second].color != color)
        after = {malls[bokunoposition+1].first+1, malls[bokunoposition+1].second +forDiagonal};
    else
        after = malls[bokunoposition+1];

    std::vector<std::pair<int , int>> goal;

    std::copy_if(legalMoves.begin(), legalMoves.end(), std::back_inserter(goal), [&before, &after, &x, &y](std::pair<int, int> move){
        return before.first <move.first && move.first <after.first && !(move.first == x && move.second == y);});


    return goal;
}

std::vector<std::pair<int, int>> find_move_horizon_anti_diagonal(std::string location, ChessBoard board, int x, int y, Color color){
    int forDiagonal;

    if(location == "HORIZON")
        forDiagonal = 0;
    else if(location == "ANTI_DIAGONAL")
        forDiagonal = 1;

    std::vector<std::pair<int, int>> legalMoves(8);

    std::generate(legalMoves.begin(), legalMoves.end(), [&x, &y,&forDiagonal, i=0]() mutable {
        int distance = y-i++; // 0~7과 y 사이의 거리
        return std::make_pair(x - distance*forDiagonal, y - distance );
    });

    legalMoves.erase(std::remove_if(legalMoves.begin(), legalMoves.end(), [](std::pair<int, int> move){
        return move.first<0 || 7<move.first || move.second<0 || 7<move.second;
    }), legalMoves.end());

    std::sort(legalMoves.begin(), legalMoves.end(), [](std::pair<int, int> moveA, std::pair<int, int> moveB){return moveA.second < moveB.second;});

    std::vector<std::pair<int, int>> malls;



    std::copy_if(legalMoves.begin(), legalMoves.end(), std::back_inserter(malls), [&board](std::pair<int , int> move){
        return board[move.first][move.second].piece != EMPTY;
    });

    std::sort(malls.begin(), malls.end(), [](std::pair<int, int> moveA, std::pair<int, int> moveB){return moveA.second < moveB.second;});


    int bokunoposition = std::find_if(malls.begin(), malls.end(), [&x, &y](std::pair<int, int> move){return (move.first == x && move.second == y);}) - malls.begin();
    std::pair<int , int> before;
    std::pair<int, int> after;
    if(bokunoposition==0)
        //before = {x, -1};
        before = {legalMoves[0].first -1, legalMoves[0].second -1};
    else if(board[malls[bokunoposition-1].first][malls[bokunoposition-1].second].color != color)
        before = {malls[bokunoposition-1].first - forDiagonal, malls[bokunoposition-1].second-1};
    else
        before = malls[bokunoposition-1];
    if(bokunoposition==malls.size()-1)
        after = {legalMoves[legalMoves.size()-1].first +1, legalMoves[legalMoves.size()-1].second +1};
    else if(board[malls[bokunoposition+1].first][malls[bokunoposition+1].second].color != color)
        after = {malls[bokunoposition+1].first + forDiagonal, malls[bokunoposition+1].second+1};
    else
        after = malls[bokunoposition+1];

    std::vector<std::pair<int , int>> goal;

    std::copy_if(legalMoves.begin(), legalMoves.end(), std::back_inserter(goal), [&before, &after, &x, &y](std::pair<int, int> move){
        return before.second <move.second && move.second <after.second && !(move.first == x && move.second == y);});


    return goal;
}