/*
 * matrixresidue.hpp
 *
 *  Created on: May 26, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_MODEL_MATRIXRESIDUE_HPP_
#define NSCSEARCH_INCLUDE_MODEL_MATRIXRESIDUE_HPP_

namespace nscsearch {

	enum class MatrixResidue { A=0, R, N, D, C, Q, E, G, H, I, L, K, M, F, P, S, T, W, Y, V, B, J, Z, X, STAR};

	MatrixResidue residue_to_matrix_index(char iresidue);
	char residue_to_char(MatrixResidue iresidue);

	MatrixResidue operator++( MatrixResidue &c );

	// Special behavior for Colors++
	MatrixResidue operator++( MatrixResidue &c, int );
}



#endif /* NSCSEARCH_INCLUDE_MODEL_MATRIXRESIDUE_HPP_ */
