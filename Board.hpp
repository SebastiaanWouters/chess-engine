#ifndef CHESS_ENGINE_BOARD_HPP
#define CHESS_ENGINE_BOARD_HPP

#include "Piece.hpp"
#include "Square.hpp"
#include "Move.hpp"
#include "CastlingRights.hpp"

#include <optional>
#include <iosfwd>
#include <vector>

#define whitePawn 0
#define whiteKnight 1
#define whiteBishop 2
#define whiteRook 3
#define whiteQueen 4
#define whiteKing 5
#define blackPawn 6
#define blackKnight 7
#define blackBishop 8
#define blackRook 9
#define blackQueen 10
#define blackKing 11
#define NORTH 0
#define NORTH_EAST 1
#define EAST 2
#define SOUTH_EAST 3
#define SOUTH 4
#define SOUTH_WEST 5
#define WEST 6
#define NORTH_WEST 7


typedef uint64_t U64;

const U64 FILE_A = 0x101010101010101;
const U64 FILE_H = 0x8080808080808080;
const U64 RANK_8 = 0xff00000000000000;
const U64 RANK_1 = 0xff;
const U64 FILE_GH = 0xc0c0c0c0c0c0c0c0;
const U64 FILE_AB = 0x303030303030303;
const U64 FR_A8 = 0xff01010101010101;
const U64 FR_H8 = 0xff80808080808080;
const U64 FR_A1 = 0x1010101010101ff;
const U64 FR_H1 = 0x80808080808080ff;
const U64 FILE_B = 0x202020202020202;
const U64 FILE_C = 0x404040404040404;
const U64 FILE_D = 0x808080808080808;
const U64 FILE_E = 0x1010101010101010;
const U64 FILE_F = 0x2020202020202020;
const U64 FILE_G = 0x4040404040404040;
const U64 RANK_2 = 0xff00;
const U64 RANK_3 = 0xff0000;
const U64 RANK_4 = 0xff000000;
const U64 RANK_5 = 0xff00000000;
const U64 RANK_6 = 0xff0000000000;
const U64 RANK_7 = 0xff000000000000;


const int PIECE_SCORES_MATERIAL[12] = {
    // pawn, knight, bishop, rook, queen, king
    100, 300, 300, 500, 900, 12000, 100, 300, 300, 500, 900, 12000
};

const int SCORES_POSITIONAL[7][64] = {{
            0, 0, 0, 0, 0, 0, 0, 0,
            50, 50, 50, 50, 50, 50, 50, 50,
            10, 10, 20, 30, 30, 20, 10, 10,
            5, 5, 10, 27, 27, 10, 5, 5,
            0, 0, 0, 25, 25, 0, 0, 0,
            5, -5,-10, 0, 0,-10, -5, 5,
            5, 10, 10,-25,-25, 10, 10, 5,
            0, 0, 0, 0, 0, 0, 0, 0
            },  {
            -50,-40,-30,-30,-30,-30,-40,-50,
            -40,-20, 0, 0, 0, 0,-20,-40,
            -30, 0, 10, 15, 15, 10, 0,-30,
            -30, 5, 15, 20, 20, 15, 5,-30,
            -30, 0, 15, 20, 20, 15, 0,-30,
            -30, 5, 10, 15, 15, 10, 5,-30,
            -40,-20, 0, 5, 5, 0,-20,-40,
            -50,-40,-20,-30,-30,-20,-40,-50,
            }, {
            -20,-10,-10,-10,-10,-10,-10,-20,
            -10, 0, 0, 0, 0, 0, 0,-10,
            -10, 0, 5, 10, 10, 5, 0,-10,
            -10, 5, 5, 10, 10, 5, 5,-10,
            -10, 0, 10, 10, 10, 10, 0,-10,
            -10, 10, 10, 10, 10, 10, 10,-10,
            -10, 5, 0, 0, 0, 0, 5,-10,
            49
            -20,-10,-40,-10,-10,-40,-10,-20,
            }, {
			0,  0,  0,  0,  0,  0,  0,  0,
			5, 10, 10, 10, 10, 10, 10,  5,
			-5,  0,  0,  0,  0,  0,  0, -5,
			-5,  0,  0,  0,  0,  0,  0, -5,
			-5,  0,  0,  0,  0,  0,  0, -5,
			-5,  0,  0,  0,  0,  0,  0, -5,
			-5,  0,  0,  0,  0,  0,  0, -5,
			0,  0,  0,  5,  5,  0,  0,  0
		}, {
			-20,-10,-10, -5, -5,-10,-10,-20,
			-10,  0,  0,  0,  0,  0,  0,-10,
			-10,  0,  5,  5,  5,  5,  0,-10,
			-5,  0,  5,  5,  5,  5,  0, -5,
			0,  0,  5,  5,  5,  5,  0, -5,
			-10,  5,  5,  5,  5,  5,  0,-10,
			-10,  0,  5,  0,  0,  0,  0,-10,
			-20,-10,-10, -5, -5,-10,-10,-20
		}, {
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -20, -30, -30, -40, -40, -30, -30, -20,
            -10, -20, -20, -20, -20, -20, -20, -10,
            20, 20, 0, 0, 0, 0, 20, 20,
            20, 30, 10, 0, 0, 10, 30, 20
            },
            {
            -50,-40,-30,-20,-20,-30,-40,-50,
            -30,-20,-10, 0, 0,-10,-20,-30,
            -30,-10, 20, 30, 30, 20,-10,-30,
            -30,-10, 30, 40, 40, 30,-10,-30,
            -30,-10, 30, 40, 40, 30,-10,-30,
            -30,-10, 20, 30, 30, 20,-10,-30,
            -30,-30, 0, 0, 0, 0,-30,-30,
            -50,-30,-30,-30,-30,-30,-30,-50
            }
        };

constexpr U64 west(U64 b) { return (b & ~FILE_A) >> 1; }
constexpr U64 east(U64 b) { return (b & ~FILE_H) << 1; }
constexpr U64 north(U64 b) { return (b & ~RANK_8) << 8; }
constexpr U64 south(U64 b) { return (b & ~RANK_1) >> 8; }
constexpr U64 north_east(U64 b) { return (b & ~FILE_H & ~RANK_8) << 9; }
constexpr U64 north_west(U64 b) { return (b & ~FILE_A & ~RANK_8) << 7; }
constexpr U64 south_west(U64 b) { return (b & ~FILE_A & ~RANK_1) >> 9; }
constexpr U64 south_east(U64 b) { return (b & ~FILE_H & ~RANK_1) >> 7; }

constexpr U64 set_bit(U64 b, int i) { return ((b) | (1ULL << i)); }
#define get_bit(b, i) ((b) & (0xF << i))  
#define clear_bit(b, i) ((b) &= ~(0xF << i)) 

#define get_LSB(b) (__builtin_ctzll(b))
#define get_MSB(b) (__builtin_clzll(b))

constexpr int bitScanReverse(U64 n) {
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    int seq[] = {
        0,  47, 1,  56, 48, 27, 2,  60, 57, 49, 41, 37, 28, 16, 3,  61,
        54, 58, 35, 52, 50, 42, 21, 44, 38, 32, 29, 23, 17, 11, 4,  62,
        46, 55, 26, 59, 40, 36, 15, 53, 34, 51, 20, 43, 31, 22, 10, 45,
        25, 39, 14, 33, 19, 30, 9,  24, 13, 18, 8,  12, 7,  6,  5,  63};
    return seq[(n * 0x03f79d71b4cb0a89ULL) >> 58];
}

constexpr int bitScanForward(U64 n){
    int seq[] = {
        0,  47, 1,  56, 48, 27, 2,  60, 57, 49, 41, 37, 28, 16, 3,  61,
        54, 58, 35, 52, 50, 42, 21, 44, 38, 32, 29, 23, 17, 11, 4,  62,
        46, 55, 26, 59, 40, 36, 15, 53, 34, 51, 20, 43, 31, 22, 10, 45,
        25, 39, 14, 33, 19, 30, 9,  24, 13, 18, 8,  12, 7,  6,  5,  63};
    return seq[((n ^ (n - 1)) * 0x03f79d71b4cb0a89ULL) >> 58];
}
inline int pop_LSB(U64 &b) {
    int i = get_LSB(b);
    b &= b - 1;
    return i;
}
inline int pop_MSB(U64 &b) {
    int i = get_MSB(b);
    b &= b - 1;
    return i;
}

class Board {
public:

    using Optional = std::optional<Board>;
    using OptionalSquare = std::optional<Square>;
    using MoveVec = std::vector<Move>;

    Board();

    void setPiece(const Square& square, const Piece::Optional& piece);
    void removePiece(const int index);
    Piece::Optional piece(const Square& square) const;
    char piece(const int index) const;
    void setTurn(PieceColor turn);
    PieceColor turn() const;
    void toggleTurn();
    void setCastlingRights(CastlingRights cr);
    bool hasCastlingRights(CastlingRights cr) const;
    CastlingRights castlingRights() const;
    void setEnPassantSquare(const Square::Optional& square);
    Square::Optional enPassantSquare() const;

    void makeMove(const Move& move);

    void pseudoLegalMoves(MoveVec& moves) const;
    void pseudoLegalMovesFrom(const Square& from, MoveVec& moves) const;
    U64 getAllAttackedSquares(const Square& from) const;

    bool isSquareAttackedBy(int index, PieceColor color) const;
    bool kingChecked(PieceColor color, std::optional<Move> move) const;
    bool isMate() const;
    int evaluate() const;
    int countMaterial(PieceColor color) const;
    int getPlies() const;
    void setPlies(int plies);
    void nextPly();
    bool isEndGame() const;
    void updateEndGame();

    int doubledPawns(PieceColor color) const;
    int isolatedPawns(PieceColor color) const;
    int blockedPawns(PieceColor color) const;
    int mobility(PieceColor color) const;

    U64 getBishopMovesClassical(int square, U64 blockers) const;
    U64 getRookMovesClassical(int square, U64 blockers) const;

    U64 intToU64(int index) const;

    U64 getBlacks() const;
    U64 getWhites() const;
    U64 getOccupied() const;
    U64 getEmpties() const;
    U64 getFriendlies() const;
    U64 getEnemies() const;
    U64 getColored(PieceColor color) const;

    U64 KNIGHT_ATTACKS[64];
    U64 KING_ATTACKS[64];
    U64 WHITE_PAWN_ATTACKS[64];
    U64 BLACK_PAWN_ATTACKS[64];
    U64 QUEEN_ATTACKS[64];
    U64 BISHOP_ATTACKS[64];
    U64 ROOK_ATTACKS[64];

    U64 WHITE_JUMPS;
    U64 BLACK_JUMPS;

    U64 RAYS[8][64];

    U64 a1;
    U64 b1;
    U64 c1;
    U64 d1;
    U64 e1;
    U64 f1;
    U64 g1;

    U64 a8;
    U64 b8;
    U64 c8;
    U64 d8;
    U64 e8;
    U64 f8;
    U64 g8;
    

private:
    PieceColor turn_;
    CastlingRights rights_;
    OptionalSquare enPassantSquare_;

    U64 empty_;
    U64 whitePawn_;
    U64 whiteBishop_;
    U64 whiteKing_;
    U64 whiteQueen_;
    U64 whiteRook_;
    U64 whiteKnight_;
    U64 blackPawn_;
    U64 blackBishop_;
    U64 blackKing_;
    U64 blackQueen_;
    U64 blackRook_;
    U64 blackKnight_;
    U64 board_[12];

    int plies_;
    bool endgame_;
    

};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif
