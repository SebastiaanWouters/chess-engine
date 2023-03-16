#include "Board.hpp"
#include "Piece.hpp"

#include <ostream>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string> 
#include <sstream>
#include <algorithm>

Board::Board()
{
    
    empty_ = 0x0000000000000000;

    board_[whitePawn] = empty_;
    board_[whiteBishop] = empty_;
    board_[whiteKing] = empty_;
    board_[whiteQueen] = empty_;
    board_[whiteRook] = empty_;
    board_[whiteKnight] = empty_;
    board_[blackPawn] = empty_;
    board_[blackBishop] = empty_;
    board_[blackKing] = empty_;
    board_[blackQueen] = empty_;
    board_[blackRook] = empty_;
    board_[blackKnight] = empty_;

    plies_ = 0;
    updateEndGame();

    WHITE_JUMPS = 0xff00;
    BLACK_JUMPS = 0xff000000000000; 


    for (int index = 0; index < 64; index++) {
        U64 U64_s = Board::intToU64(index);
        KNIGHT_ATTACKS[index] = (((U64_s << 6)  | (U64_s >> 10)) & ~FILE_GH) |
                                (((U64_s << 10) | (U64_s >> 6))  & ~FILE_AB) |
                                (((U64_s << 15) | (U64_s >> 17)) & ~FILE_H)  |
                                (((U64_s << 17) | (U64_s >> 15)) & ~FILE_A);
        KING_ATTACKS[index] = (north(U64_s) | east(U64_s) | south(U64_s) | west(U64_s) |
                               north_east(U64_s) | north_west(U64_s) | south_east(U64_s) |
                               south_west(U64_s));
        WHITE_PAWN_ATTACKS[index] = (north_east(U64_s) | north_west(U64_s));
        BLACK_PAWN_ATTACKS[index] = (south_east(U64_s) | south_west(U64_s));
    }

    
    for (int direction = 0; direction < 8; direction++) {
        for (int index = 0; index < 64; index++) {
            U64 ray = 0x0;
            U64 U64_s = Board::intToU64(index);
            switch (direction) {
                case (NORTH): {
                    while(north(U64_s)) {
                        ray |= north(U64_s);
                        U64_s = north(U64_s);
                    }
                    RAYS[NORTH][index] = ray;
                    break;
                }
                case (NORTH_EAST): {
                    while(north_east(U64_s)) {
                        ray |= north_east(U64_s);
                        U64_s = north_east(U64_s);
                    }
                    RAYS[NORTH_EAST][index] = ray;
                    break;
                }
                case (EAST): {
                    while(east(U64_s)) {
                        ray |= east(U64_s);
                        U64_s = east(U64_s);
                    }
                    RAYS[EAST][index] = ray;
                    break;
                }
                case (SOUTH_EAST): {
                    while(south_east(U64_s)) {
                        ray |= south_east(U64_s);
                        U64_s = south_east(U64_s);
                    }
                    RAYS[SOUTH_EAST][index] = ray;
                    break;
                }
                case (SOUTH): {
                    while(south(U64_s)) {
                        ray |= south(U64_s);
                        U64_s = south(U64_s);
                    }
                    RAYS[SOUTH][index] = ray;
                    break;
                }
                case (SOUTH_WEST): {
                    while(south_west(U64_s)) {
                        ray |= south_west(U64_s);
                        U64_s = south_west(U64_s);
                    }
                    RAYS[SOUTH_WEST][index] = ray;
                    break;
                }
                case (WEST): {
                    while(west(U64_s)) {
                        ray |= west(U64_s);
                        U64_s = west(U64_s);
                    }
                    RAYS[WEST][index] = ray;
                    break;
                }
                case (NORTH_WEST): {
                    while(north_west(U64_s)) {
                        ray |= north_west(U64_s);
                        U64_s = north_west(U64_s);
                    }
                    RAYS[NORTH_WEST][index] = ray;
                    break;
                }
            }
        }

    }

}


U64 Board::intToU64(int index) const {
    return set_bit(0x0, index);
}

U64 Board::getBlacks() const {
    return (board_[blackBishop] | board_[blackKing] | board_[blackPawn] | board_[blackQueen] | board_[blackRook] | board_[blackKnight]);
}

U64 Board::getWhites() const {
    return (board_[whiteBishop] | board_[whiteKing] | board_[whitePawn] | board_[whiteQueen] | board_[whiteRook] | board_[whiteKnight]);
}

U64 Board::getOccupied() const {
    return (board_[blackBishop] | board_[blackKing] | board_[blackPawn] | board_[blackQueen] | board_[blackRook] | board_[blackKnight] | board_[whiteBishop] | board_[whiteKing] | board_[whitePawn] | board_[whiteQueen] | board_[whiteRook] | board_[whiteKnight]);
}

U64 Board::getEmpties() const {
    return ~(board_[blackBishop] | board_[blackKing] | board_[blackPawn] | board_[blackQueen] | board_[blackRook] | board_[blackKnight] | board_[whiteBishop] | board_[whiteKing] | board_[whitePawn] | board_[whiteQueen] | board_[whiteRook] | board_[whiteKnight]);
}

U64 Board::getFriendlies() const {
    if (turn() == PieceColor::White) {
        return (board_[whiteBishop] | board_[whiteKing] | board_[whitePawn] | board_[whiteQueen] | board_[whiteRook] | board_[whiteKnight]);
    } else {
        return (board_[blackBishop] | board_[blackKing] | board_[blackPawn] | board_[blackQueen] | board_[blackRook] | board_[blackKnight]);
    }
}

U64 Board::getEnemies() const {
    if (turn() == PieceColor::Black) {
        return (board_[whiteBishop] | board_[whiteKing] | board_[whitePawn] | board_[whiteQueen] | board_[whiteRook] | board_[blackKnight]);
    } else {
        return (board_[blackBishop] | board_[blackKing] | board_[blackPawn] | board_[blackQueen] | board_[blackRook] | board_[blackKnight]);
    }
}

U64 Board::getColored(PieceColor color) const {
    if (color == PieceColor::White) {
        return (board_[whiteBishop] | board_[whiteKing] | board_[whitePawn] | board_[whiteQueen] | board_[whiteRook] | board_[whiteKnight]);
    } else {
        return (board_[blackBishop] | board_[blackKing] | board_[blackPawn] | board_[blackQueen] | board_[blackRook] | board_[blackKnight]);
    }
}


void Board::setPiece(const Square& square, const Piece::Optional& piece) {
    U64 U64_s = Board::intToU64(square.index());
    Board::removePiece(square.index());
    int pieceValue;
    if (piece.has_value()) {
        pieceValue = Piece::toInt(piece.value());
    } else {
        return;
    }
    switch (pieceValue) {
        case (whitePawn): {
                    board_[whitePawn] |= U64_s;
                    break;
                }
        case (whiteBishop): {
                    board_[whiteBishop] |= U64_s;
                    break;
                }
        case (whiteKing): {
                    board_[whiteKing] |= U64_s;
                    break;
                }
        case (whiteQueen): {
                    board_[whiteQueen] |= U64_s;
                    break;
                }
        case (whiteRook): {
                    board_[whiteRook] |= U64_s;
                    break;
                }
        case (whiteKnight): {
                    board_[whiteKnight] |= U64_s;
                    break;
                }

        case (blackPawn): {
                    board_[blackPawn] |= U64_s;
                    break;
                }
        case (blackBishop): {
                    board_[blackBishop] |= U64_s;
                    break;
                }
        case (blackKing): {
                    board_[blackKing] |= U64_s;
                    break;
                }
        case (blackQueen): {
                    board_[blackQueen] |= U64_s;
                    break;
                }
        case (blackRook): {
                    board_[blackRook] |= U64_s;
                    break;
                }
        case (blackKnight): {
                    board_[blackKnight] |= U64_s;
                    break;
                }
            
            }
}

void Board::removePiece(const int index) {
    U64 U64_s = Board::intToU64(index);
    for (int i = whitePawn; i <= blackKing; i++) {
        if (board_[i] & U64_s) {
            board_[i] &= ~(U64_s);
        }
    }
}

Piece::Optional Board::piece(const Square& square) const {
    U64 U64_s = Board::intToU64(square.index());
    for (int i = whitePawn; i <= blackKing; i++) {
        if (board_[i] & U64_s) {
            return Piece::fromInt(i);
        }
    }
    return {};

}

char Board::piece(const int index) const {
    U64 U64_s = Board::intToU64(index);
    for (int i = whitePawn; i <= blackKing; i++) {
        if (board_[i] & U64_s) {
            return Piece::toSymbol(i);
        }
    }
    return '.';

}

void Board::setTurn(PieceColor turn) {
    turn_ = turn;    
}

void Board::toggleTurn() {
    setTurn(!turn_);
}

PieceColor Board::turn() const {
    return turn_;
}

void Board::setCastlingRights(CastlingRights cr) {
    rights_ = cr;
}

CastlingRights Board::castlingRights() const {
    return rights_;
}

bool Board::hasCastlingRights(CastlingRights cr) const {
    return ((castlingRights() & cr) != CastlingRights::None);
    
}

void Board::setEnPassantSquare(const Square::Optional& square) {
    if (square.has_value()) {
        enPassantSquare_ = square.value();
    } else {
        enPassantSquare_ = {};
    }
    
}

Square::Optional Board::enPassantSquare() const {
    return enPassantSquare_;
}

int Board::getPlies() const {
    return plies_;
}

void Board::setPlies(int plies) {
    plies_ = plies;
}

void Board::nextPly() {
    plies_ += 1;
}

bool Board::isEndGame() const {
    return endgame_;
}

void Board::updateEndGame() {
    U64 occupied = getOccupied();
    int counter = 0;
    while (occupied) {
        pop_LSB(occupied);
        counter += 1;
    }
    if (counter < 10) {
        endgame_ = true;
    } else {
        endgame_ = false;
    }
    
}

int Board::doubledPawns(PieceColor color) const {
    int counter = 0;
    if (color == PieceColor::White) {
        U64 fa_pawns = FILE_A & board_[whitePawn];
        U64 fb_pawns = FILE_B & board_[whitePawn];
        U64 fc_pawns = FILE_C & board_[whitePawn];
        U64 fd_pawns = FILE_D & board_[whitePawn];
        U64 fe_pawns = FILE_E & board_[whitePawn];
        U64 ff_pawns = FILE_F & board_[whitePawn];
        U64 fg_pawns = FILE_G & board_[whitePawn];
        U64 fh_pawns = FILE_H & board_[whitePawn];
        pop_LSB(fa_pawns);
        if (fa_pawns) {
            counter += 1;
        }
        pop_LSB(fb_pawns);
        if (fb_pawns) {
            counter += 1;
        }
        pop_LSB(fc_pawns);
        if (fc_pawns) {
            counter += 1;
        } 
        pop_LSB(fd_pawns);
        if (fd_pawns) {
            counter += 1;
        } 
        pop_LSB(fe_pawns);
        if (fe_pawns) {
            counter += 1;
        } 
        pop_LSB(ff_pawns);
        if (ff_pawns) {
            counter += 1;
        } 
        pop_LSB(fg_pawns);
        if (fg_pawns) {
            counter += 1;
        } 
        pop_LSB(fh_pawns);
        if (fh_pawns) {
            counter += 1;
        } 
    
    } else if (color == PieceColor::Black) {
            U64 fa_pawns = FILE_A & board_[blackPawn];
            U64 fb_pawns = FILE_B & board_[blackPawn];
            U64 fc_pawns = FILE_C & board_[blackPawn];
            U64 fd_pawns = FILE_D & board_[blackPawn];
            U64 fe_pawns = FILE_E & board_[blackPawn];
            U64 ff_pawns = FILE_F & board_[blackPawn];
            U64 fg_pawns = FILE_G & board_[blackPawn];
            U64 fh_pawns = FILE_H & board_[blackPawn];
            if (pop_LSB(fa_pawns)) {
                counter += 1;
            }
            if (pop_LSB(fb_pawns)) {
                counter += 1;
            }
            if (pop_LSB(fc_pawns)) {
                counter += 1;
            } 
            if (pop_LSB(fd_pawns)) {
                counter += 1;
            } 
            if (pop_LSB(fe_pawns)) {
                counter += 1;
            } 
            if (pop_LSB(ff_pawns)) {
                counter += 1;
            } 
            if (pop_LSB(fg_pawns)) {
                counter += 1;
            } 
            if (pop_LSB(fh_pawns)) {
                counter += 1;
            } 
        
    }
    return counter;
}

int Board::isolatedPawns(PieceColor color) const {
    int counter = 0;
        if (color == PieceColor::White) {
            if ((FILE_A & board_[whitePawn]) && !(FILE_B & board_[whitePawn])) {
                counter += 1;
            }
            if ((FILE_B & board_[whitePawn]) && (!(FILE_A & board_[whitePawn]) && !(FILE_C & board_[whitePawn]))) {
                counter += 1;
            }
            if ((FILE_C & board_[whitePawn]) && (!(FILE_B & board_[whitePawn]) && !(FILE_D & board_[whitePawn]))) {
                counter += 1;
            }
            if ((FILE_D & board_[whitePawn]) && (!(FILE_C & board_[whitePawn]) && !(FILE_E & board_[whitePawn]))) {
                counter += 1;
            }
            if ((FILE_E & board_[whitePawn]) && (!(FILE_D & board_[whitePawn]) && !(FILE_F & board_[whitePawn]))) {
                counter += 1;
            }
            if ((FILE_F & board_[whitePawn]) && (!(FILE_E & board_[whitePawn]) && !(FILE_G & board_[whitePawn]))) {
                counter += 1;
            }
            if ((FILE_G & board_[whitePawn]) && (!(FILE_F & board_[whitePawn]) && !(FILE_H & board_[whitePawn]))) {
                counter += 1;
            }
            if ((FILE_H & board_[whitePawn]) && !(FILE_G & board_[whitePawn])) {
                counter += 1;
            }
            
        }
        if (color == PieceColor::Black) {
            if ((FILE_A & board_[blackPawn]) && !(FILE_B & board_[blackPawn])) {
                counter += 1;
            }
            if ((FILE_B & board_[blackPawn]) && (!(FILE_A & board_[blackPawn]) & !(FILE_C & board_[blackPawn]))) {
                counter += 1;
            }
            if ((FILE_C & board_[blackPawn]) && (!(FILE_B & board_[blackPawn]) & !(FILE_D & board_[blackPawn]))) {
                counter += 1;
            }
            if ((FILE_D & board_[blackPawn]) && (!(FILE_C & board_[blackPawn]) & !(FILE_E & board_[blackPawn]))) {
                counter += 1;
            }
            if ((FILE_E & board_[blackPawn]) && (!(FILE_D & board_[blackPawn]) & !(FILE_F & board_[blackPawn]))) {
                counter += 1;
            }
            if ((FILE_F & board_[blackPawn]) && (!(FILE_E & board_[blackPawn]) & !(FILE_G & board_[blackPawn]))) {
                counter += 1;
            }
            if ((FILE_G & board_[blackPawn]) && (!(FILE_F & board_[blackPawn]) & !(FILE_H & board_[blackPawn]))) {
                counter += 1;
            }
            if ((FILE_H & board_[blackPawn]) && !(FILE_G & board_[blackPawn])) {
                counter += 1;
            }
            
        }
        return counter;
}

int Board::blockedPawns(PieceColor color) const {
    int counter = 0;
    if (color == PieceColor::White) {
        U64 whitePawns = board_[whitePawn];
        while (whitePawns) {
            int index = pop_LSB(whitePawns);
            U64 index64 = intToU64(index);
            if (north(index64) & getOccupied()) {
                counter += 1;
            }
        }
    }
    if (color == PieceColor::Black) {
        U64 blackPawns = board_[blackPawn];
        while (blackPawns) {
            int index = pop_LSB(blackPawns);
            U64 index64 = intToU64(index);
            if (south(index64) & getOccupied()) {
                counter += 1;
            }
        }
    }
    return counter;
   
}

int Board::mobility(PieceColor color) const {
    std::vector<Move> moves;
    if (turn() == color) {
        pseudoLegalMoves(moves);
    } else {
        Board copyBoard = *this;
        copyBoard.toggleTurn();
        copyBoard.pseudoLegalMoves(moves);
    }   
    
    return moves.size();

}

void Board::makeMove(const Move& move) {
    auto fromPiece = piece(move.from());
    auto toSquare = move.to();
    int fromIndex = move.from().index();
    unsigned int toIndex = move.to().index();
    U64 fromU64 = intToU64(fromIndex);
    U64 toU64 = intToU64(toIndex);
 

    for (int i = whitePawn; i <= blackKing; i ++) {
        if (board_[i] & fromU64) {
            /*check if piece lands on the enPassantSquare => remove captured pawn*/
            if (enPassantSquare().has_value()) {
                if (toIndex == enPassantSquare().value().index()) {
                    if (i == whitePawn) {
                        removePiece(toIndex - 8);
                    } else if (i == blackPawn) {
                        removePiece(toIndex + 8);
                    }
                }
            }
            /*remove en passant*/
            setEnPassantSquare({});
            if (move.promotion().has_value() && i == whitePawn) {
                /*board_[i] &= ~(fromU64);*/
                removePiece(toIndex);
                removePiece(fromIndex);
                /*board_[whiteQueen] |= toU64;*/
                auto promotionPieceType = move.promotion().value();
                setPiece(toSquare, Piece(PieceColor::White, promotionPieceType));
            } else if (move.promotion().has_value() && i == blackPawn) {
                /*board_[i] &= ~(fromU64);*/
                removePiece(toIndex);
                removePiece(fromIndex);
                /*board_[blackQueen] |= toU64;*/
                auto promotionPieceType = move.promotion().value();
                setPiece(toSquare, Piece(PieceColor::Black, promotionPieceType));
            }
            else {
                /*board_[i] &= ~(fromU64);
                board_[i] |= toU64;*/
                removePiece(fromIndex);
                setPiece(toSquare, fromPiece);
            }
            if ((i == whitePawn) && (north(north(fromU64)) == toU64) && ((getBlacks() & north(north_east(fromU64))) | (getBlacks() & north(north_west(fromU64))))) {
                auto square = Square::fromIndex(fromIndex + 8);
                setEnPassantSquare(square);
            } else if ((i == blackPawn) && (south(south(fromU64)) & toU64) && ((getWhites() & south(south_east(fromU64))) | (getWhites() & south(south_west(fromU64))))) {
                auto square = Square::fromIndex(fromIndex - 8);
                setEnPassantSquare(square);
            }


            toggleTurn();      
            updateEndGame(); 
            

            /*check for castling and set rights accordingly*/
            if (fromIndex == 4 && i == whiteKing) {
                setCastlingRights(castlingRights() & ~CastlingRights::White);
                if (toIndex == 2) {
                    board_[whiteRook] &= ~(0x1);
                    board_[whiteRook] |= 0x8;
                } else if (toIndex == 6) {
                    board_[whiteRook] &= ~(0x80);
                    board_[whiteRook] |= 0x20;
                }
            } else if (fromIndex == 0) {
                setCastlingRights(castlingRights() & ~CastlingRights::WhiteQueenside);
            } else if (fromIndex == 7) {
                setCastlingRights(castlingRights() & ~CastlingRights::WhiteKingside);
            } else if (fromIndex == 60 && i == blackKing) {
                setCastlingRights(castlingRights() & ~CastlingRights::Black);
                if (toIndex == 58) {
                    board_[blackRook] &= ~(0x100000000000000);
                    board_[blackRook] |= 0x800000000000000;
                } else if (toIndex == 62) {
                    board_[blackRook] &= ~(0x8000000000000000);
                    board_[blackRook] |= 0x2000000000000000;
                }
            } else if (fromIndex == 56) {
                setCastlingRights(castlingRights() & ~CastlingRights::BlackQueenside);
            } else if (fromIndex == 63) {
                setCastlingRights(castlingRights() & ~CastlingRights::BlackKingside);
            }

            if (toIndex == 0) {
                setCastlingRights(castlingRights() & ~CastlingRights::WhiteQueenside);
            } else if (toIndex == 7) {
                setCastlingRights(castlingRights() & ~CastlingRights::WhiteKingside);
            } else if (toIndex == 4) {
                setCastlingRights(castlingRights() & ~CastlingRights::White);
            } else if (toIndex == 56) {
                setCastlingRights(castlingRights() & ~CastlingRights::BlackQueenside);
            } else if (toIndex == 60) {
                setCastlingRights(castlingRights() & ~CastlingRights::Black);
            } else if (toIndex == 63) {
                setCastlingRights(castlingRights() & ~CastlingRights::BlackKingside);
            }

        }
    }
}

bool Board::isSquareAttackedBy(int toIndex, PieceColor color) const {
    U64 attackedSquares = 0x0;
    for (int fromIndex = 0; fromIndex < 64; fromIndex++) {
        U64 fromU64 = intToU64(fromIndex);
        if (getColored(color) & fromU64) {
            if (Square::fromIndex(fromIndex).has_value()) {
                    attackedSquares |= getAllAttackedSquares(Square::fromIndex(fromIndex).value());
            }
                
        }
    }

    while(attackedSquares) {
        int attackedIndex = pop_LSB(attackedSquares);
            if (toIndex == attackedIndex) {
                return true;
            }
    }
    return false;
}
bool Board::isMate() const {
    if (kingChecked(turn(), {})) {
        std::vector<Move> moves_;
        pseudoLegalMoves(moves_);
        if (moves_.size() == 0) {
                return true;
        }
    }
    return false;
}

bool Board::kingChecked(PieceColor color, std::optional<Move> move) const {
    Board copyBoard = *this;
    if (move.has_value()) {
        copyBoard.makeMove(move.value());
    }
    int king;
    PieceColor otherColor;
    if (color == PieceColor::White) {
        king = whiteKing;
        otherColor = PieceColor::Black;
    } else {
        king = blackKing;
        otherColor = PieceColor::White;
    }

    int kingIndex = get_LSB(copyBoard.board_[king]);

    return copyBoard.isSquareAttackedBy(kingIndex, otherColor);
}

int Board::evaluate() const {
    /*for (Move move : moves) {
        copyBoard.makeMove(move);
    }*/
    int bonus = 0;
    int perspective = 0;
    if (turn() == PieceColor::White) {
        perspective = 1;
    } else {
        perspective = -1;
    }
    if (isMate()) {
        bonus -= 200000;
    }
    if (kingChecked(turn(), {})) {
        bonus -= 700;
    }

    int whiteMobility = mobility(PieceColor::White);
    int whiteDoubledPawns = doubledPawns(PieceColor::White);
    int whiteIsolatedPawns = isolatedPawns(PieceColor::White);
    int whiteBlockedPawns = blockedPawns(PieceColor::White);
    int blackMobility = mobility(PieceColor::Black);
    int blackDoubledPawns = doubledPawns(PieceColor::Black);
    int blackIsolatedPawns = isolatedPawns(PieceColor::Black);
    int blackBlockedPawns = blockedPawns(PieceColor::Black);

    int mobilityScore = 10 * (whiteMobility - blackMobility);
    int doubledPawnScore = 50 * (blackDoubledPawns - whiteDoubledPawns);
    int isolatedPawnScore = 50 * (blackIsolatedPawns - whiteIsolatedPawns);
    int blockedPawnScore = 50 * (blackBlockedPawns - whiteBlockedPawns);

    int whiteEval = countMaterial(PieceColor::White);
    int blackEval = countMaterial(PieceColor::Black);

    int eval = (whiteEval - blackEval) + mobilityScore + doubledPawnScore + isolatedPawnScore + blockedPawnScore;
    
    return (eval * perspective) + bonus;
}

int Board::countMaterial(PieceColor color) const {
    int counter = 0;
    for (int index = 0; index < 64; index++) {
            auto square = Square::fromIndex(index);
            int fromIndex = index;
            if (square.has_value()) {
                std::optional<Piece> piece_ = piece(square.value());
                if (piece_.has_value() && piece_.value().color() == color) {
                    int pieceValue = Piece::toInt(piece_.value());
                    counter += PIECE_SCORES_MATERIAL[pieceValue];
                    if (color == PieceColor::White) {
                        fromIndex = (int)(((int)(fromIndex + 56)) - (int)((int)(fromIndex / 8) * 16));
			        }
                    if (isEndGame() && (pieceValue == blackKing || pieceValue == whiteKing)) {
                        counter += SCORES_POSITIONAL[pieceValue % 6 + 1][fromIndex];
                    } else {
                        counter += SCORES_POSITIONAL[pieceValue % 6][fromIndex];
                    }
                }
            }
            
    }
    return counter;
}
 
void Board::pseudoLegalMoves(MoveVec& moves) const {
    for (int index = 0; index < 64; index++) {
        auto square = Square::fromIndex(index);
        if (square.has_value() ) {
            auto piece = this->piece(square.value());
            if (piece.has_value()) {
                if (piece.value().color() == turn()) {
                    pseudoLegalMovesFrom(square.value(), moves);
                }
            }
        }
    }
}

void Board::pseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves) const {
    int score = 0;
    U64 attacks = 0x0;
    
    int pieceValue;
    int fromIndex = from.index();
    U64 fromU64 = intToU64(fromIndex);
    std::optional<Piece> optionalPiece = piece(from);

    if (optionalPiece.has_value()) {
        pieceValue = Piece::toInt(optionalPiece.value());
    } else {
        std::cout << "error" << std::endl;
        return;
    }
    
    switch (pieceValue) {
        case (whitePawn): {
                    attacks = ((north(fromU64) & getEmpties()) | (WHITE_PAWN_ATTACKS[fromIndex] & getBlacks()));
                    if (!((getOccupied() & north(fromU64)) | (getOccupied() & north(north(fromU64))))) {
                        attacks |= (north(north(fromU64)) & north(north(WHITE_JUMPS)));
                    }
                    if (enPassantSquare().has_value()) {
                        U64 enPassant64 = Board::intToU64(enPassantSquare().value().index());
                        if ((north_west(fromU64) & enPassant64)) {
                            attacks |= north_west(fromU64);
                        } else if ((north_east(fromU64) & enPassant64)) {
                            attacks |= north_east(fromU64);
                        }
                    }
                    break;
                }
        case (whiteBishop): {
                    attacks = getBishopMovesClassical(fromIndex, getOccupied());

                    break;
                }
        case (whiteKing): {
                    attacks = (KING_ATTACKS[fromIndex] & (~(getWhites())));
                    if (hasCastlingRights(CastlingRights::WhiteQueenside) && fromIndex == 4) {
                        if (!(getOccupied() & intToU64(1)) && !(getOccupied() & intToU64(2)) && !(getOccupied() & intToU64(3)) && !isSquareAttackedBy(fromIndex, PieceColor::Black) && !isSquareAttackedBy(fromIndex - 1, PieceColor::Black) && !isSquareAttackedBy(fromIndex - 2, PieceColor::Black)) {
                            attacks |= west(west(fromU64));
                        }
                    } 
                    if (hasCastlingRights(CastlingRights::WhiteKingside) && fromIndex == 4) {
                        if (!(getOccupied() & intToU64(5)) && !(getOccupied() & intToU64(6)) && !isSquareAttackedBy(fromIndex, PieceColor::Black) && !isSquareAttackedBy(fromIndex + 1, PieceColor::Black) && !isSquareAttackedBy(fromIndex + 2, PieceColor::Black)){
                            attacks |= east(east(fromU64));
                        }
                    }
                    break;
                }
        case (whiteQueen): {
                    attacks = getRookMovesClassical(fromIndex, getOccupied()) | getBishopMovesClassical(fromIndex, getOccupied());
                    break;
                }
        case (whiteRook): {
                    attacks = getRookMovesClassical(fromIndex, getOccupied());
                    break;
                }
        case (whiteKnight): {
                    attacks = (KNIGHT_ATTACKS[fromIndex] & (~(getWhites())) );
                    break;
                }

        case (blackPawn): {
                    attacks = ((south(fromU64) & getEmpties()) | (BLACK_PAWN_ATTACKS[fromIndex] & getWhites()));
                    if (!((getOccupied() & south(fromU64)) | (getOccupied() & south(south(fromU64))))) {
                        attacks |= (south(south(fromU64)) & south(south(BLACK_JUMPS)));
                    }
                    if (enPassantSquare().has_value()) {
                        U64 enPassant64 = Board::intToU64(enPassantSquare().value().index());
                        if ((south_west(fromU64) & enPassant64)) {
                            attacks |= south_west(fromU64);
                        } else if ((south_east(fromU64) & enPassant64)) {
                            attacks |= south_east(fromU64);
                        }
                    }
                    break;
                }
        case (blackBishop): {

                    attacks = getBishopMovesClassical(fromIndex, getOccupied());

                    break;
                }
        case (blackKing): {
                    attacks = (KING_ATTACKS[fromIndex] & (~(getBlacks())) );
                    if (hasCastlingRights(CastlingRights::BlackQueenside) && fromIndex == 60) {
                        if (!(getOccupied() & intToU64(57)) && !(getOccupied() & intToU64(58)) && !(getOccupied() & intToU64(59)) && !isSquareAttackedBy(fromIndex, PieceColor::White) && !isSquareAttackedBy(fromIndex - 1, PieceColor::White) && !isSquareAttackedBy(fromIndex - 2, PieceColor::White)) {
                            attacks |= west(west(fromU64));
                        }
                    } else if (hasCastlingRights(CastlingRights::BlackKingside) && fromIndex == 60) {
                        if (!(getOccupied() & intToU64(61)) && !(getOccupied() & intToU64(62)) && !isSquareAttackedBy(fromIndex, PieceColor::White) && !isSquareAttackedBy(fromIndex + 1, PieceColor::White) && !isSquareAttackedBy(fromIndex + 2, PieceColor::White)){
                            attacks |= east(east(fromU64));
                        }
                    }
                    break;
                }
        case (blackQueen): {

                    attacks = getRookMovesClassical(fromIndex, getOccupied()) | getBishopMovesClassical(fromIndex, getOccupied());
                    break;
                }
        case (blackRook): {
                    attacks = getRookMovesClassical(fromIndex, getOccupied());
                    break;
                }
        case (blackKnight): {
                    attacks = (KNIGHT_ATTACKS[fromIndex] & (~(getBlacks())) );
                    break;
                }
    }
    while(attacks) {
        int toIndex = pop_LSB(attacks);

        /*check for capture*/
        auto attackedSquare = Square::fromIndex(toIndex);
        if (attackedSquare.has_value()) {
            auto attackedPiece = piece(attackedSquare.value());
            if (attackedPiece.has_value()) {
                int attackedPieceValue = Piece::toInt(attackedPiece.value());
                score += 10000 + PIECE_SCORES_MATERIAL[attackedPieceValue];
                if (PIECE_SCORES_MATERIAL[pieceValue] < PIECE_SCORES_MATERIAL[attackedPieceValue]) {
                    score += PIECE_SCORES_MATERIAL[attackedPieceValue] - PIECE_SCORES_MATERIAL[pieceValue];
                }
            } 
        }
        
        
        
        U64 toIndex64 = intToU64(toIndex);
        if ((pieceValue == whitePawn) && (toIndex64 & RANK_8)) {
            Move move(Square::fromIndex(fromIndex).value(), Square::fromIndex(toIndex).value(), PieceType::Queen, score+9000);
            if (!kingChecked(turn(), move)) {
                moves.push_back(move);
            } 
        }
        else if ((pieceValue == blackPawn) && (toIndex64 & RANK_1)) {
            Move move(Square::fromIndex(fromIndex).value(), Square::fromIndex(toIndex).value(), PieceType::Queen, score+9000);
            if (!kingChecked(turn(), move)) {
                moves.push_back(move);
            }
            
        } else {
            Move move(Square::fromIndex(fromIndex).value(), Square::fromIndex(toIndex).value(),{}, score);
            if (!kingChecked(turn(), move)) {
                moves.push_back(move);
            }
        }
    }
    

}

U64 Board::getAllAttackedSquares(const Square& from) const {
    U64 attacks = 0x0;
    U64 finalAttacks = 0x0;
    
    int pieceValue;
    int fromIndex = from.index();
    U64 fromU64 = intToU64(fromIndex);
    std::optional<Piece> optionalPiece = piece(from);

    if (optionalPiece.has_value()) {
        pieceValue = Piece::toInt(optionalPiece.value());
    } else {
        return 0x0;
    }

    switch (pieceValue) {
        case (whitePawn): {
                    attacks = ((WHITE_PAWN_ATTACKS[fromIndex] & getBlacks()));
                    if (!((getOccupied() & north(fromU64)) | (getOccupied() & north(north(fromU64))))) {
                        attacks |= (north(north(fromU64)) & north(north(WHITE_JUMPS)));
                    }
                    if (enPassantSquare().has_value()) {
                        U64 enPassant64 = Board::intToU64(enPassantSquare().value().index());
                        if ((north_west(fromU64) & enPassant64)) {
                            attacks |= north_west(fromU64);
                        } else if ((north_east(fromU64) & enPassant64)) {
                            attacks |= north_east(fromU64);
                        }
                    }
                    break;
                }
        case (whiteBishop): {
                    attacks = getBishopMovesClassical(fromIndex, getOccupied());

                    break;
                }
        case (whiteKing): {
                    attacks = (KING_ATTACKS[fromIndex] & (~(getWhites())));
                    break;
                }
        case (whiteQueen): {
                    attacks = getRookMovesClassical(fromIndex, getOccupied()) | getBishopMovesClassical(fromIndex, getOccupied());
                    break;
                }
        case (whiteRook): {
                    attacks = getRookMovesClassical(fromIndex, getOccupied());
                    break;
                }
        case (whiteKnight): {
                    attacks = (KNIGHT_ATTACKS[fromIndex] & (~(getWhites())) );
                    break;
                }

        case (blackPawn): {
                    attacks = ((BLACK_PAWN_ATTACKS[fromIndex] & getWhites()));
                    if (!((getOccupied() & south(fromU64)) | (getOccupied() & south(south(fromU64))))) {
                        attacks |= (south(south(fromU64)) & south(south(BLACK_JUMPS)));
                    }
                    if (enPassantSquare().has_value()) {
                        U64 enPassant64 = Board::intToU64(enPassantSquare().value().index());
                        if ((south_west(fromU64) & enPassant64)) {
                            attacks |= south_west(fromU64);
                        } else if ((south_east(fromU64) & enPassant64)) {
                            attacks |= south_east(fromU64);
                        }
                    }
                    break;
                }
        case (blackBishop): {

                    attacks = getBishopMovesClassical(fromIndex, getOccupied());

                    break;
                }
        case (blackKing): {
                    attacks = (KING_ATTACKS[fromIndex] & (~(getBlacks())) );
                    break;
                }
        case (blackQueen): {

                    attacks = getRookMovesClassical(fromIndex, getOccupied()) | getBishopMovesClassical(fromIndex, getOccupied());
                    break;
                }
        case (blackRook): {
                    attacks = getRookMovesClassical(fromIndex, getOccupied());
                    break;
                }
        case (blackKnight): {
                    attacks = (KNIGHT_ATTACKS[fromIndex] & (~(getBlacks())) );
                    break;
                }
    }

    while(attacks) {
        int toIndex = pop_LSB(attacks);
        U64 toIndex64 = intToU64(toIndex);
        Move move(Square::fromIndex(fromIndex).value(), Square::fromIndex(toIndex).value(), PieceType::Queen);
        finalAttacks |= toIndex64;
    }
    
    return finalAttacks;
}
    

U64 Board::getBishopMovesClassical(int square, U64 blockers) const {
  U64 attacks = 0x0;

  auto fromSquare = Square::fromIndex(square);
  auto color = PieceColor::White;

  if (fromSquare.has_value()) {
    auto fromColor = piece(fromSquare.value());
    if (fromColor.has_value()) {
        color = fromColor.value().color();
    }
  }

  // North West
  attacks |= RAYS[NORTH_WEST][square];
  if (RAYS[NORTH_WEST][square] & blockers) {
    int blockerIndex = bitScanForward(RAYS[NORTH_WEST][square] & blockers);
    attacks &= ~(RAYS[NORTH_WEST][blockerIndex] | getColored(color));
  }

  // North East
  attacks |= RAYS[NORTH_EAST][square];
  if (RAYS[NORTH_EAST][square] & blockers) {
    int blockerIndex = bitScanForward(RAYS[NORTH_EAST][square] & blockers);
    attacks &= ~(RAYS[NORTH_EAST][blockerIndex] | getColored(color));
  }

  // South East
  attacks |= RAYS[SOUTH_EAST][square];
  if (RAYS[SOUTH_EAST][square] & blockers) {
    int blockerIndex = bitScanReverse(RAYS[SOUTH_EAST][square] & blockers);
    attacks &= ~(RAYS[SOUTH_EAST][blockerIndex] | getColored(color));
  }

  // South West
  attacks |= RAYS[SOUTH_WEST][square];
  if (RAYS[SOUTH_WEST][square] & blockers) {
    int blockerIndex = bitScanReverse(RAYS[SOUTH_WEST][square] & blockers);
    attacks &= ~(RAYS[SOUTH_WEST][blockerIndex] | getColored(color));
  }

  return attacks;
}

U64 Board::getRookMovesClassical(int square, U64 blockers) const {
  U64 attacks = 0x0;
  auto fromSquare = Square::fromIndex(square);
  auto color = PieceColor::White;

  if (fromSquare.has_value()) {
    auto fromColor = piece(fromSquare.value());
    if (fromColor.has_value()) {
        color = fromColor.value().color();
    }
  }
   
  
  // North West
  attacks |= RAYS[NORTH][square];
  if (RAYS[NORTH][square] & blockers) {
    int blockerIndex = bitScanForward(RAYS[NORTH][square] & blockers);
    attacks &= ~(RAYS[NORTH][blockerIndex] | getColored(color));
  }

  // North East
  attacks |= RAYS[EAST][square];
  if (RAYS[EAST][square] & blockers) {
    int blockerIndex = bitScanForward(RAYS[EAST][square] & blockers);
    attacks &= ~(RAYS[EAST][blockerIndex] | getColored(color));
  }

  // South East
  attacks |= RAYS[WEST][square];
  if (RAYS[WEST][square] & blockers) {
    int blockerIndex = bitScanReverse(RAYS[WEST][square] & blockers);
    attacks &= ~(RAYS[WEST][blockerIndex] | getColored(color));
  }

  // South West
  attacks |= RAYS[SOUTH][square];
  if (RAYS[SOUTH][square] & blockers) {
    int blockerIndex = bitScanReverse(RAYS[SOUTH][square] & blockers);
    attacks &= ~(RAYS[SOUTH][blockerIndex] | getColored(color));
  }

  return attacks;
}


std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << " abcdefgh\n8";
    const int rankStart = 8;
    const int fileStart = 1;
    int boardIndex;
    for (int rank = rankStart; rank > 0; rank--) {
        for (int file = fileStart; file <= 8; file++) {
            boardIndex = (8*(rank - 1)) + (file - 1);
            os << board.piece(boardIndex);
        }
        os << "\n";
        auto s = std::to_string(((boardIndex + 1) / 8)-1);
        if (s != "0") {
             os << s;
        } else {
            os << "\n";
        }
       
    }
    return os;
}
