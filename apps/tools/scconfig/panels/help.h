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


#ifndef SEISCOMP_CONFIGURATION_GUI_PANEL_HELP_H__
#define SEISCOMP_CONFIGURATION_GUI_PANEL_HELP_H__

#include "../gui.h"

#include <QWidget>


class HelpPanel : public ConfiguratorPanel {
	Q_OBJECT

	public:
		HelpPanel(QWidget *parent = 0);


	private slots:
		void refresh();
		void openIndex(const QModelIndex & index);


	private:
		QListView          *_folderView;
		QStandardItemModel *_model;
};


#endif
