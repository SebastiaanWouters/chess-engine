#include "catch2/catch.hpp"

#include "TestUtils.hpp"

#include "Board.hpp"
#include "Move.hpp"
#include "Square.hpp"
#include "Fen.hpp"
#include "EngineFactory.hpp"

#include <iostream>
#include <sstream>

#include <vector>
#include <set>
#include <algorithm>
#include <map>

using MoveVec = std::vector<Move>;

TEST_CASE("Create a Board, place a piece and make a move", "[Custom][Fundamental]") {
    /*auto square1 = Square::D3;
    auto square2 = Square::C7;
    auto squareRook = Square::A1;
    auto squareKing = Square::E1;
    std::cout << "\n";
    auto color1 = PieceColor::White;
    auto type = PieceType::Pawn;
    auto rook = PieceType::Rook;
    auto king = PieceType::King;
    auto color2 = PieceColor::Black;
    auto whitePawn_ = Piece(color1, type);
    auto blackPawn_ = Piece(color2, type);
    auto whiteRook_ = Piece(color1, rook);
    auto whiteKing_ = Piece(color2, king);
    auto board = Board();
    board.setPiece(square1, whitePawn_);
    board.setPiece(square2, blackPawn_);
    board.setPiece(squareRook, whiteRook_);
    board.setPiece(squareKing, whiteKing_);
    std::cout << board;
    std::cout << std::endl;
    std::cout << board.isSquareAttackedBy(2, PieceColor::White) << std::endl;
    auto move = Move(squareKing, Square::C1);
    board.makeMove(move);
    std::cout << board;
    std::cout << std::endl;
    std::cout << "Is Square 2 Attacked By White?: " << board.isSquareAttackedBy(2, PieceColor::White) << std::endl;
    std::cout << board.hasCastlingRights(CastlingRights::WhiteQueenside) << std::endl;
    std::cout << board.piece(Square::C1) << std::endl;
    auto moves = MoveVec();
    board.pseudoLegalMovesFrom(Square::D1, moves);
    for (Move move : moves) {
        std::cout << move.from().index() << std::endl;
        std::cout << move.to().index() << std::endl;
        std::cout << std::endl;

    }*/

    const char* fen = "5rk1/ppp5/2n4p/3b2p1/6R1/P1B1P2P/1Pq5/R4QK1 w - - 2 29";

    auto optBoard = Fen::createBoard(fen);
    
    if (optBoard.has_value()) {
        std::cout << optBoard.value() << std::endl;
    }

    auto board = optBoard.value();
    int fromIndex = 10;
    std::cout << "blockedPawns: " << SCORES_POSITIONAL[0][fromIndex] << std::endl;
    std::cout << "blockedPawns: " << board.blockedPawns(board.turn()) << std::endl;
    std::cout << "isolatedPawns: " << board.isolatedPawns(board.turn()) << std::endl;
    std::cout << "doubledPawns: " << board.doubledPawns(board.turn()) << std::endl;



    /*REQUIRE(move.from() == from);
    REQUIRE(move.to() == to);
    REQUIRE_FALSE(move.promotion().has_value());
    auto generatedMovesVec = Board::MoveVec();*/
    /*std::ostringstream ss;
    ss << std::hex << x;
    std::string result = ss.str();
    std::cout << result << std::endl;
    std::cout << generatedMovesVec.length;*/
    
}
