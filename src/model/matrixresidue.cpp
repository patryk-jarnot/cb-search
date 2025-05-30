/*
 * matrixresidue.cpp
 *
 *  Created on: May 27, 2023
 *      Author: pjarnot
 */

#include "model/matrixresidue.hpp"

#include "debug.hpp"

#include <stdexcept>


namespace nscsearch {

	MatrixResidue operator++( MatrixResidue &c ) {
		using IntType = typename std::underlying_type<MatrixResidue>::type;
		if ( c == MatrixResidue::STAR ) {
			c = static_cast<MatrixResidue>(0);
		}
		else {
			c = static_cast<MatrixResidue>( static_cast<IntType>(c) + 1 );
		}
		return c;
	}

	// Special behavior for Colors++
	MatrixResidue operator++( MatrixResidue &c, int ) {
		MatrixResidue result = c;
		++c;
		return result;
	}


	MatrixResidue residue_to_matrix_index(char iresidue) {
		switch (iresidue) {
		case 'A':
			return MatrixResidue::A;
		case 'R':
			return MatrixResidue::R;
		case 'N':
			return MatrixResidue::N;
		case 'D':
			return MatrixResidue::D;
		case 'C':
			return MatrixResidue::C;
		case 'Q':
			return MatrixResidue::Q;
		case 'E':
			return MatrixResidue::E;
		case 'G':
			return MatrixResidue::G;
		case 'H':
			return MatrixResidue::H;
		case 'I':
			return MatrixResidue::I;
		case 'L':
			return MatrixResidue::L;
		case 'K':
			return MatrixResidue::K;
		case 'M':
			return MatrixResidue::M;
		case 'F':
			return MatrixResidue::F;
		case 'P':
			return MatrixResidue::P;
		case 'S':
			return MatrixResidue::S;
		case 'T':
			return MatrixResidue::T;
		case 'W':
			return MatrixResidue::W;
		case 'Y':
			return MatrixResidue::Y;
		case 'V':
			return MatrixResidue::V;
		case 'B':
			return MatrixResidue::B;
		case 'J':
			return MatrixResidue::J;
		case 'Z':
			return MatrixResidue::Z;
		case 'X':
			return MatrixResidue::X;
		case '*':
			return MatrixResidue::STAR;
		case 'U':
		case 'O':
			return MatrixResidue::STAR;
		default:
			DEBUG((int)iresidue);
			throw std::invalid_argument("Residue letter not found");
		}
	}


	char residue_to_char(MatrixResidue iresidue) {
		switch (iresidue) {
		case MatrixResidue::A:
			return 'A';
		case MatrixResidue::R:
			return 'R';
		case MatrixResidue::N:
			return 'N';
		case MatrixResidue::D:
			return 'D';
		case MatrixResidue::C:
			return 'C';
		case MatrixResidue::Q:
			return 'Q';
		case MatrixResidue::E:
			return 'E';
		case MatrixResidue::G:
			return 'G';
		case MatrixResidue::H:
			return 'H';
		case MatrixResidue::I:
			return 'I';
		case MatrixResidue::L:
			return 'L';
		case MatrixResidue::K:
			return 'K';
		case MatrixResidue::M:
			return 'M';
		case MatrixResidue::F:
			return 'F';
		case MatrixResidue::P:
			return 'P';
		case MatrixResidue::S:
			return 'S';
		case MatrixResidue::T:
			return 'T';
		case MatrixResidue::W:
			return 'W';
		case MatrixResidue::Y:
			return 'Y';
		case MatrixResidue::V:
			return 'V';
		case MatrixResidue::B:
			return 'B';
		case MatrixResidue::J:
			return 'J';
		case MatrixResidue::Z:
			return 'Z';
		case MatrixResidue::X:
			return 'X';
		case MatrixResidue::STAR:
			return '*';
		default:
			throw std::invalid_argument("Residue letter not found");
		}
	}

}

