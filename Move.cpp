#include "Move.hpp"
#include "Piece.hpp"
#include "Square.hpp"

#include <ostream>

Move::Move(const Square& from, const Square& to,
           const std::optional<PieceType>& promotion, const int score)
{
    this->from_ = from;
    this->to_ = to;
    promotion_ = promotion;
    score_ = score;
}

Move::Optional Move::fromUci(const std::string& uci) {
    if (uci.length() < 4) {
        return {};
    }
    std::optional<Square> fromSquare = Square::fromName(uci.substr(0,2));
    std::optional<Square> toSquare = Square::fromName(uci.substr(2,2));
    if (!fromSquare.has_value() || !toSquare.has_value()) {
        return {};
    }
    if (uci.length() > 4) {
        std::optional<Piece> promotion = Piece::fromSymbol(uci[4]);
        if (promotion.has_value() && promotion.value().type() != PieceType::King && promotion.value().type() != PieceType::Pawn)  {
            return Move(fromSquare.value(), toSquare.value(), promotion.value().type());
        } else {
            return {};
        }
    }

    return Move(fromSquare.value(), toSquare.value());
}

Square Move::from() const {
    return from_;
}

Square Move::to() const {
    return to_;
}

std::optional<PieceType> Move::promotion() const {
    return promotion_;
}

int Move::score() const {
    return score_;
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.from() << move.to();
    if (move.promotion().has_value()) {
        PieceType promotion = move.promotion().value();
        switch (promotion) {
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
    return os;
}


bool operator<(const Move& lhs, const Move& rhs) {
    return lhs.from().index() + lhs.to().index() < rhs.from().index() + rhs.to().index();
}

bool operator==(const Move& lhs, const Move& rhs) {
    return lhs.from() == rhs.from() && rhs.to() == lhs.to() && lhs.promotion() == rhs.promotion();
}
