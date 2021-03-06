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


#include <seiscomp/qc/qcprocessor_availability.h>


namespace Seiscomp {
namespace Processing {


IMPLEMENT_SC_CLASS_DERIVED(QcProcessorAvailability, QcProcessor, "QcProcessorAvailability");

QcProcessorAvailability::QcProcessorAvailability() 
: QcProcessor() {}

double QcProcessorAvailability::getAvailability() {
	try {
		return boost::any_cast<double>(_qcp->parameter);
	}
	catch ( const boost::bad_any_cast & ) {
		throw Core::ValueException("no data");
	}
}

bool QcProcessorAvailability::setState(const Record *record, const DoubleArray &data) {
	try {
		_qcp->parameter = 0;

		return true;
	}
	catch ( Core::ValueException & ) {}

	return false;
}


}
}
