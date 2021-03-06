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



template<typename TYPE, template <class T> class OPERATION>
Op2Filter<TYPE, OPERATION>::Op2Filter(InPlaceFilter<TYPE> *op1, InPlaceFilter<TYPE> *op2, double fsamp) {
	_op1 = op1;
	_op2 = op2;

	if ( fsamp )
		setSamplingFrequency(fsamp);
}


template<typename TYPE, template <class T> class OPERATION>
Op2Filter<TYPE, OPERATION>::~Op2Filter() {
	if ( _op1 ) delete _op1;
	if ( _op2 ) delete _op2;
}


template<typename TYPE, template <class T> class OPERATION>
void Op2Filter<TYPE, OPERATION>::apply(int n, TYPE *inout) {
	OPERATION<TYPE> op;
	for ( int i = 0; i < n; ++i ) {
		TYPE v1 = *inout, v2 = *inout;
		_op1->apply(1, &v1);
		_op2->apply(1, &v2);

		*inout = op(v1, v2);

		++inout;
	}
}


template<typename TYPE, template <class T> class OPERATION>
InPlaceFilter<TYPE>* Op2Filter<TYPE, OPERATION>::clone() const {
	return new Op2Filter<TYPE, OPERATION>(_op1->clone(), _op2->clone());
}


template<typename TYPE, template <class T> class OPERATION>
void Op2Filter<TYPE, OPERATION>::setStartTime(const Core::Time &time) {
	if ( _op1 ) _op1->setStartTime(time);
	if ( _op2 ) _op2->setStartTime(time);
}


template<typename TYPE, template <class T> class OPERATION>
void Op2Filter<TYPE, OPERATION>::setStreamID(const std::string &net,
                                             const std::string &sta,
                                             const std::string &loc,
                                             const std::string &cha) {
	if ( _op1 ) _op1->setStreamID(net, sta, loc, cha);
	if ( _op2 ) _op2->setStreamID(net, sta, loc, cha);
}


template<typename TYPE, template <class T> class OPERATION>
void Op2Filter<TYPE, OPERATION>::setSamplingFrequency(double fsamp) {
	if ( _op1 ) _op1->setSamplingFrequency(fsamp);
	if ( _op2 ) _op2->setSamplingFrequency(fsamp);
}


template<typename TYPE, template <class T> class OPERATION>
int Op2Filter<TYPE, OPERATION>::setParameters(int n, double const *params) {
	return 0;
}

