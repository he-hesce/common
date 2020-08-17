/***************************************************************************
 * Copyright (C) gempa GmbH                                                *
 * All rights reserved.                                                    *
 * Contact: gempa GmbH (seiscomp-dev@gempa.de)                             *
 *                                                                         *
 * GNU Affero General Public License Usage                                 *
 * This file may be used under the terms of the GNU Affero                 *
 * Public License version 3.0 as published by the Free Software Foundation *
 * and appearing in the file LICENSE included in the packaging of this     *
 * file. Please review the following information to ensure the GNU Affero  *
 * Public License version 3.0 requirements will be met:                    *
 * https://www.gnu.org/licenses/agpl-3.0.html.                             *
 *                                                                         *
 * Other Usage                                                             *
 * Alternatively, this file may be used in accordance with the terms and   *
 * conditions contained in a signed written agreement between you and      *
 * gempa GmbH.                                                             *
 ***************************************************************************/


#ifndef SEISCOMP_MATH_FILTER_BIQUAD_H
#define SEISCOMP_MATH_FILTER_BIQUAD_H


#include <vector>
#include <string>
#include <ostream>

#include<seiscomp/math/filter.h>


namespace Seiscomp {
namespace Math {
namespace Filtering {
namespace IIR {


struct BiquadCoefficients {
	BiquadCoefficients(double a0 = 0, double a1 = 0, double a2 = 0,
	                   double b0 = 1, double b1 = 0, double b2 = 0);
	BiquadCoefficients(BiquadCoefficients const &bq);

	void set(double a0, double a1, double a2,
	         double b0, double b1, double b2);

	// filter coefficients
	double a0, a1, a2;
	double b0, b1, b2;
};


typedef std::vector<BiquadCoefficients> Biquads;


std::ostream &operator<<(std::ostream &os, const BiquadCoefficients &biq);


/**
 * Template class to implement the filter interface for a single set of
 * biquad coefficients.
 */
template<typename TYPE>
class Biquad : public InPlaceFilter<TYPE> {
	// ------------------------------------------------------------------
	//  X'truction
	// ------------------------------------------------------------------
	public:
		Biquad(double a0 = 0, double a1 = 0, double a2 = 0,
		             double b0 = 1, double b1 = 0, double b2 = 0);
		Biquad(const BiquadCoefficients &bq);
		Biquad(const Biquad &bq);


	// ------------------------------------------------------------------
	//  Public methods
	// ------------------------------------------------------------------
	public:
		// reset the filter by erasing memory of past samples
		void reset();


	// ------------------------------------------------------------------
	//  InplaceFilter interface
	// ------------------------------------------------------------------
	public:
		// apply filter to data vector **in*place**
		virtual void apply(int n, TYPE *inout) override;

		// Implement InPlaceFilter interface with default values
		virtual void setSamplingFrequency(double fsamp) override;
		virtual int setParameters(int n, const double *params) override;

		virtual InPlaceFilter<TYPE> *clone() const override;


	// ------------------------------------------------------------------
	//  Public members
	// ------------------------------------------------------------------
	public:
		// filter coefficients
		BiquadCoefficients coefficients;
		// filter memory
		double v1, v2;

};


template<typename TYPE>
class BiquadCascade : public InPlaceFilter<TYPE> {
	// ------------------------------------------------------------------
	//  X'truction
	// ------------------------------------------------------------------
	public:
		BiquadCascade();
		BiquadCascade(const BiquadCascade &other);


	// ------------------------------------------------------------------
	//  Public methods
	// ------------------------------------------------------------------
	public:
		// number of biquads comprising the cascade
		int size() const;

		// resets the filter, i.e. erases the filter memory
		void reset();

		// append a single biquad to this cascade
		void append(const Biquad<TYPE> &biq);

		void set(const Biquads &biquads);


	// ------------------------------------------------------------------
	//  InplaceFilter interface
	// ------------------------------------------------------------------
	public:
		// apply filter to data vector **in*place**
		virtual void apply(int n, TYPE *inout) override;
		virtual InPlaceFilter<TYPE> *clone() const override;

		virtual void setSamplingFrequency(double /*fsamp*/) override {}
		virtual int setParameters(int n, const double *params) override ;


	// ------------------------------------------------------------------
	//  Protected members
	// ------------------------------------------------------------------
	protected:
		std::vector< Biquad<TYPE> > _biq;

	template <typename T>
	friend std::ostream &operator<<(std::ostream &os, const BiquadCascade<T> &b);
};


template <typename T>
std::ostream &operator<<(std::ostream &os, const BiquadCascade<T> &b);


} // namespace Seiscomp::Math::Filtering::IIR
} // namespace Seiscomp::Math::Filtering
} // namespace Seiscomp::Math
} // namespace Seiscomp


#endif
