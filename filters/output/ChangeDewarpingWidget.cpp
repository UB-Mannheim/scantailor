/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C)  Joseph Artsimovich <joseph.artsimovich@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChangeDewarpingWidget.h"
#include "ChangeDewarpingWidget.moc"
#include "PageSelectionAccessor.h"
#include "QtSignalForwarder.h"
#ifndef Q_MOC_RUN
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#endif

namespace output
{

ChangeDewarpingWidget::ChangeDewarpingWidget(QWidget* parent, DewarpingMode const& mode)
:	QWidget(parent),
    m_mode(mode)
{

	ui.setupUi(this);
	switch (mode) {
		case DewarpingMode::OFF:
			ui.offRB->setChecked(true);
			break;
		case DewarpingMode::AUTO:
			ui.autoRB->setChecked(true);
			break;
		case DewarpingMode::MARGINAL:
			ui.marginalRB->setChecked(true);
			break;
		case DewarpingMode::MANUAL:
			ui.manualRB->setChecked(true);
			break;
	}

	// No, we don't leak memory here.
    using namespace boost::lambda;
	new QtSignalForwarder(ui.offRB, SIGNAL(clicked(bool)), var(m_mode) = DewarpingMode::OFF);
	new QtSignalForwarder(ui.autoRB, SIGNAL(clicked(bool)), var(m_mode) = DewarpingMode::AUTO);
	new QtSignalForwarder(ui.manualRB, SIGNAL(clicked(bool)), var(m_mode) = DewarpingMode::MANUAL);
	new QtSignalForwarder(ui.marginalRB, SIGNAL(clicked(bool)), var(m_mode) = DewarpingMode::MARGINAL);

}

ChangeDewarpingWidget::~ChangeDewarpingWidget()
{
}

DewarpingMode
ChangeDewarpingWidget::dewarpingMode() const
{
    if (ui.offRB->isChecked()) {
        return DewarpingMode::OFF;
    } else if (ui.autoRB->isChecked()) {
        return DewarpingMode::AUTO;
    } else if (ui.marginalRB->isChecked()) {
        return DewarpingMode::MARGINAL;
    } else if (ui.manualRB->isChecked()) {
        return DewarpingMode::MANUAL;
    } else assert(false);

    return DewarpingMode::OFF;
}

} // namespace output
