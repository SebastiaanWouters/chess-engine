#include "Square.hpp"

#include <ostream>
#include <cmath>

Square::Square(Index index) 
{
    this->index_ = index;
    this->file_ = (Coordinate) (index % 8);
    this->rank_ = (Coordinate) floor(index / 8);
}

Square::Optional Square::returnSquare(Index index) {
    if (index == 0) {return A1;}
    else if (index == 1) {return B1;}
    else if (index == 2) {return C1;}
    else if (index == 3) {return D1;}
    else if (index == 4) {return E1;}
    else if (index == 5) {return F1;}
    else if (index == 6) {return G1;}
    else if (index == 7) {return H1;}
    else if (index == 8) {return A2;}
    else if (index == 9) {return B2;}
    else if (index == 10) {return C2;}
    else if (index == 11) {return D2;}
    else if (index == 12) {return E2;}
    else if (index == 13) {return F2;}
    else if (index == 14) {return G2;}
    else if (index == 15) {return H2;}
    else if (index == 16) {return A3;}
    else if (index == 17) {return B3;}
    else if (index == 18) {return C3;}
    else if (index == 19) {return D3;}
    else if (index == 20) {return E3;}
    else if (index == 21) {return F3;}
    else if (index == 22) {return G3;}
    else if (index == 23) {return H3;}
    else if (index == 24) {return A4;}
    else if (index == 25) {return B4;}
    else if (index == 26) {return C4;}
    else if (index == 27) {return D4;}
    else if (index == 28) {return E4;}
    else if (index == 29) {return F4;}
    else if (index == 30) {return G4;}
    else if (index == 31) {return H4;}
    else if (index == 32) {return A5;}
    else if (index == 33) {return B5;}
    else if (index == 34) {return C5;}
    else if (index == 35) {return D5;}
    else if (index == 36) {return E5;}
    else if (index == 37) {return F5;}
    else if (index == 38) {return G5;}
    else if (index == 39) {return H5;}
    else if (index == 40) {return A6;}
    else if (index == 41) {return B6;}
    else if (index == 42) {return C6;}
    else if (index == 43) {return D6;}
    else if (index == 44) {return E6;}
    else if (index == 45) {return F6;}
    else if (index == 46) {return G6;}
    else if (index == 47) {return H6;}
    else if (index == 48) {return A7;}
    else if (index == 49) {return B7;}
    else if (index == 50) {return C7;}
    else if (index == 51) {return D7;}
    else if (index == 52) {return E7;}
    else if (index == 53) {return F7;}
    else if (index == 54) {return G7;}
    else if (index == 55) {return H7;}
    else if (index == 56) {return A8;}
    else if (index == 57) {return B8;}
    else if (index == 58) {return C8;}
    else if (index == 59) {return D8;}
    else if (index == 60) {return E8;}
    else if (index == 61) {return F8;}
    else if (index == 62) {return G8;}
    else if (index == 63) {return H8;}
    else {return {};}

}

Square::Optional Square::fromCoordinates(Coordinate file, Coordinate rank) {
    if (rank < 8 && file < 8) {
        return returnSquare(rank * 8 + file);
    }
    return {};
}

Square::Optional Square::fromIndex(Index index) {
    return returnSquare(index);
}

Square::Optional Square::fromName(const std::string& name) {
    if (name.length() > 2) {
        return std::nullopt;
    }
    int index0 = 0;
    int index1 = 8;
    switch (name[0]) {
        case 'a':
            index0 += 0;
            break;
        case 'b':
            index0 += 1;
            break;
        case 'c':
            index0 += 2;
            break;
        case 'd':
            index0 += 3;
            break;
        case 'e':
            index0 += 4;
            break;
        case 'f':
            index0 += 5;
            break;
        case 'g':
            index0 += 6;
            break;
        case 'h':
            index0 += 7;
            break;
        default:
            return {};
    }
    switch (name[1]) {
        case '1':
            index1 *= 0;
            break;
        case '2':
            index1 *= 1;
            break;
        case '3':
            index1 *= 2;
            break;
        case '4':
            index1 *= 3;
            break;
        case '5':
            index1 *= 4;
            break;
        case '6':
            index1 *= 5;
            break;
        case '7':
            index1 *= 6;
            break;
        case '8':
            index1 *= 7;
            break;
        default:
            return {};
    }
    int index = index1 + index0;
    return returnSquare(index);
}

Square::Coordinate Square::file() const {
    return this->file_;
}

Square::Coordinate Square::rank() const {
    return this->rank_;
}

Square::Index Square::index() const {
    return this->index_;
}


const Square Square::A1 = Square( 0 + 0);
const Square Square::B1 = Square( 0 + 1);
const Square Square::C1 = Square( 0 + 2);
const Square Square::D1 = Square( 0 + 3);
const Square Square::E1 = Square( 0 + 4);
const Square Square::F1 = Square( 0 + 5);
const Square Square::G1 = Square( 0 + 6);
const Square Square::H1 = Square( 0 + 7);

const Square Square::A2 = Square( 8 + 0);
const Square Square::B2 = Square( 8 + 1);
const Square Square::C2 = Square( 8 + 2);
const Square Square::D2 = Square( 8 + 3);
const Square Square::E2 = Square( 8 + 4);
const Square Square::F2 = Square( 8 + 5);
const Square Square::G2 = Square( 8 + 6);
const Square Square::H2 = Square( 8 + 7);

const Square Square::A3 = Square(16 + 0);
const Square Square::B3 = Square(16 + 1);
const Square Square::C3 = Square(16 + 2);
const Square Square::D3 = Square(16 + 3);
const Square Square::E3 = Square(16 + 4);
const Square Square::F3 = Square(16 + 5);
const Square Square::G3 = Square(16 + 6);
const Square Square::H3 = Square(16 + 7);

const Square Square::A4 = Square(24 + 0);
const Square Square::B4 = Square(24 + 1);
const Square Square::C4 = Square(24 + 2);
const Square Square::D4 = Square(24 + 3);
const Square Square::E4 = Square(24 + 4);
const Square Square::F4 = Square(24 + 5);
const Square Square::G4 = Square(24 + 6);
const Square Square::H4 = Square(24 + 7);

const Square Square::A5 = Square(32 + 0);
const Square Square::B5 = Square(32 + 1);
const Square Square::C5 = Square(32 + 2);
const Square Square::D5 = Square(32 + 3);
const Square Square::E5 = Square(32 + 4);
const Square Square::F5 = Square(32 + 5);
const Square Square::G5 = Square(32 + 6);
const Square Square::H5 = Square(32 + 7);

const Square Square::A6 = Square(40 + 0);
const Square Square::B6 = Square(40 + 1);
const Square Square::C6 = Square(40 + 2);
const Square Square::D6 = Square(40 + 3);
const Square Square::E6 = Square(40 + 4);
const Square Square::F6 = Square(40 + 5);
const Square Square::G6 = Square(40 + 6);
const Square Square::H6 = Square(40 + 7);

const Square Square::A7 = Square(48 + 0);
const Square Square::B7 = Square(48 + 1);
const Square Square::C7 = Square(48 + 2);
const Square Square::D7 = Square(48 + 3);
const Square Square::E7 = Square(48 + 4);
const Square Square::F7 = Square(48 + 5);
const Square Square::G7 = Square(48 + 6);
const Square Square::H7 = Square(48 + 7);

const Square Square::A8 = Square(56 + 0);
const Square Square::B8 = Square(56 + 1);
const Square Square::C8 = Square(56 + 2);
const Square Square::D8 = Square(56 + 3);
const Square Square::E8 = Square(56 + 4);
const Square Square::F8 = Square(56 + 5);
const Square Square::G8 = Square(56 + 6);
const Square Square::H8 = Square(56 + 7);

std::ostream& operator<<(std::ostream& os, const Square& square) {
    switch (square.file()) {
        case 0:
            os << 'a';
            break;
        case 1:
            os << 'b';
            break;
        case 2:
            os << 'c';
            break;
        case 3:
            os << 'd';
            break;
        case 4:
            os << 'e';
            break;
        case 5:
            os << 'f';
            break;
        case 6:
            os << 'g';
            break;
        case 7:
            os << 'h';
            break;
    }
    const std::string &second = std::to_string(square.rank() + 1);
    os << second;
    return os;
}

bool operator<(const Square& lhs, const Square& rhs) {
    return lhs.index() < rhs.index();
}

bool operator==(const Square& lhs, const Square& rhs) {
    return (lhs.index() == rhs.index());
}
