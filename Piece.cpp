#include "Piece.hpp"

#include <ostream>

Piece::Piece(PieceColor color, PieceType type) : color_(color), type_(type)
{

}

Piece::Optional Piece::fromSymbol(char symbol) {
    switch (symbol) {
        case 'P':
            return Piece(PieceColor::White, PieceType::Pawn);
        case 'N':
            return Piece(PieceColor::White, PieceType::Knight);
        case 'Q':
            return Piece(PieceColor::White, PieceType::Queen);
        case 'K':
            return Piece(PieceColor::White, PieceType::King);
        case 'B':
            return Piece(PieceColor::White, PieceType::Bishop);
        case 'R':
            return Piece(PieceColor::White, PieceType::Rook);
        case 'p':
            return Piece(PieceColor::Black, PieceType::Pawn);
        case 'n':
            return Piece(PieceColor::Black, PieceType::Knight);
        case 'q':
            return Piece(PieceColor::Black, PieceType::Queen);
        case 'k':
            return Piece(PieceColor::Black, PieceType::King);
        case 'b':
            return Piece(PieceColor::Black, PieceType::Bishop);
        case 'r':
            return Piece(PieceColor::Black, PieceType::Rook);
        default : {
            return {};
        }
    }
}

PieceColor Piece::color() const {
    return this->color_;
}

PieceType Piece::type() const {
    return this->type_;
}

bool operator==(const Piece& lhs, const Piece& rhs) {
    if (lhs.color() == rhs.color() && lhs.type() == rhs.type()) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    switch (piece.color()) {
        case PieceColor::White: {
            switch (piece.type()) {
                case PieceType::Pawn:
                    os << 'P';
                    break;
                case PieceType::Knight:
                    os << 'N';
                    break;
                case PieceType::Bishop:
                    os << 'B';
                    break;
                case PieceType::Rook:
                    os << 'R';
                    break;
                case PieceType::Queen:
                    os << 'Q';
                    break;
                case PieceType::King:
                    os << 'K';
                    break;
            }
            break;
        }

        case PieceColor::Black: {
            switch (piece.type()) {
                case PieceType::Pawn:
                    os << 'p';
                    break;
                case PieceType::Knight:
                    os << 'n';
                    break;
                case PieceType::Bishop:
                    os << 'b';
                    break;
                case PieceType::Rook:
                    os << 'r';
                    break;
                case PieceType::Queen:
                    os << 'q';
                    break;
                case PieceType::King:
                    os << 'k';
                    break;
            }
        }
    }
    return os;
}

PieceColor operator!(PieceColor color) {
    if (color == PieceColor::Black) {
        return PieceColor::White;
    }
    return PieceColor::Black;
}

int Piece::toInt(Piece piece) {
    switch (piece.color()) {
        case PieceColor::White: {
            switch (piece.type()) {
                case PieceType::Pawn:
                    return 0;
                case PieceType::Knight:
                    return 1;
                case PieceType::Bishop:
                    return 2;
                case PieceType::Rook:
                    return 3;
                case PieceType::Queen:
                    return 4;
                case PieceType::King:
                    return 5;
            }
            break;
        }
        case PieceColor::Black: {
            switch (piece.type()) {
                case PieceType::Pawn:
                    return 6;
                case PieceType::Knight:
                    return 7;
                case PieceType::Bishop:
                    return 8;
                case PieceType::Rook:
                    return 9;
                case PieceType::Queen:
                    return 10;
                case PieceType::King:
                    return 11;
            }
        }
    }
    return 12;
}

Piece::Optional Piece::fromInt(int index) {
    switch (index) {
        case (0): {
            return Piece(PieceColor::White, PieceType::Pawn);
        }
        case (1): {
            return Piece(PieceColor::White, PieceType::Knight);
        }
        case (2): {
            return Piece(PieceColor::White, PieceType::Bishop);
        }
        case (3): {
            return Piece(PieceColor::White, PieceType::Rook);
        }
        case (4): {
            return Piece(PieceColor::White, PieceType::Queen);
        }
        case (5): {
            return Piece(PieceColor::White, PieceType::King);
        }

        case (6): {
            return Piece(PieceColor::Black, PieceType::Pawn);
        }
        case (7): {
            return Piece(PieceColor::Black, PieceType::Knight);
        }
        case (8): {
            return Piece(PieceColor::Black, PieceType::Bishop);
        }
        case (9): {
            return Piece(PieceColor::Black, PieceType::Rook);
        }
        case (10): {
            return Piece(PieceColor::Black, PieceType::Queen);
        }
        case (11): {
            return Piece(PieceColor::Black, PieceType::King);
        }

    }
    return {};
}

char Piece::toSymbol(int index) {
    switch (index) {
        case (0): {
            return 'P';
        }
        case (1): {
            return 'K';
        }
        case (2): {
            return 'B';
        }
        case (3): {
            return 'R';
        }
        case (4): {
            return 'Q';
        }
        case (5): {
            return 'K';
        }

        case (6): {
            return 'p';
        }
        case (7): {
            return 'k';
        }
        case (8): {
            return 'b';
        }
        case (9): {
            return 'r';
        }
        case (10): {
            return 'q';
        }
        case (11): {
            return 'k';
        }

    }
    return '.';
}
