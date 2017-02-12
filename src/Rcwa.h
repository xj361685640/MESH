/* Copyright (C) 2016-2018, Stanford University
 * This file is part of MESH
 * Written by Kaifeng Chen (kfchen@stanford.edu)
 *
 * MESH is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MESH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef _RCWA_H
#define _RCWA_H
#define ARMA_DONT_USE_WRAPPER
#include <armadillo>
#include <vector>
#include "Common.h"

namespace RCWA{

  using namespace arma;
  typedef cx_mat RCWAMatrix;
  typedef std::vector< RCWAMatrix > RCWAMatrices;
  typedef fvec RCWAVector;
  typedef std::vector< SOURCE > SourceList;


  /*============================================================
  * Function initializing S matrix
  @arg:
   n: size of S matrix
   S: the S matrix, initialized to be an identity matrix with size nxn
  ==============================================================*/
  void initSMatrix(const int n, RCWAMatrix* S);

  /*============================================================
  * Function similar to meshgrid in matlab
  @arg:
   vL, vR: the input two vectors (here everything is a matrix)
   qL, qR: the input two vectors
    [qL, qR] = meshgrid(vl, vR)
  ==============================================================*/
  void populateQ(
    const RCWAMatrix* vL,
    const RCWAMatrix* vR,
    RCWAMatrix* qL,
    RCWAMatrix* qR
  );
  /*============================================================
  * Function computing S matrix for each layers
  @arg:
   startLayer: the starting layer for the propogation
   N: number of G total G
   numOfLayer: the number of layers
   MMatrices: matrix corresponding to the propogation in each layer
   FMatrices: matrix corresponding to the phase in each layer
   SMatrices: the S matrix for each layer
  ==============================================================*/
  void getSMatrices(
    const int startLayer,
    const int N,
    const int numOfLayer,
    RCWAMatrices* MMatrices,
    RCWAMatrices* FMatrices,
    RCWAMatrices* SMatrices
  );

  /*============================================================
  * Function computing numbef of G for the system
  @arg:
   nGx: positive G along x direction
   nGy: positive G along y direction
  ==============================================================*/
 int getN(
   const int nGx,
   const int nGy
 );
  /*============================================================
  * Function computing G matrix for the system
  @arg:
   startLayer: the starting layer for the propogation
   nGx: positive G along x direction
   nGy: positive G along y direction
   period: periodicity along two directions
   Gx_mat: the Gx matrix
   Gy_mat: the Gy matrix
   d: the dimension of the structure
  ==============================================================*/
  void getGMatrices(
    const int nGx,
    const int nGy,
    const double period[2],
    RCWAMatrix* Gx_mat,
    RCWAMatrix* Gy_mat,
    DIMENSION d
  );

  /*============================================================
  * Function computing imaginary dielectric matrix for the system
  @arg:
  grandImaginaryMatrices: the matrices containing the imaginary part matrix
  dielectricImMatrix: the imaginary part matrices
  numOfLayer: the number of layer in the system
  ==============================================================*/
  void getGrandImaginaryMatrices(
    RCWAMatrices* grandImaginaryMatrices,
    RCWAMatrices* dielectricImMatrix,
    int numOfLayer
  );

  /*============================================================
  * Function computing E matrices for the system
  @arg:
  EMatrices: the Ematrices
  dielectricMatrix: the dielectric matrices
  numOfLayer: the number of layer in the system
  N: the number of G
  ==============================================================*/
  void getEMatrices(
    RCWAMatrices* EMatrices,
    RCWAMatrices* dielectricMatrix,
    int numOfLayer,
    int N
  );

  /*============================================================
  * Function computing the poynting vector at given (kx, ky)
  @arg:
   omega: the angular frequency (normalized to c)
   thicknessList: the thickness for each layer
   kx: the k vector at x direction (absolute value)
   ky: the y vector at x direction (absolute value)
   EMatrices:  the E matrices for all layers
   grandImaginaryMatrices: collection of all imaginary matrices in all layers
   dielectricMatrixInverse: the inverse of dielectric matrix
   Gx_mat: the Gx matrix
   Gy_mat: the Gy matrix
   sourceList: list of 0 or 1 with the same size of thicknessList
   targetLayer: the targetLayer for the flux measurement
   N: total number of G
  ==============================================================*/
  double poyntingFlux(
    const double omega,
    const RCWAVector* thicknessList,
    double kx,
    double ky,
    const RCWAMatrices* EMatrices,
    const RCWAMatrices* grandImaginaryMatrices,
    const RCWAMatrices* dielectricMatrixInverse,
    const RCWAMatrix* Gx_mat,
    const RCWAMatrix* Gy_mat,
    const SourceList* sourceList,
    const int targetLayer,
    const int N
  );
}
#endif
