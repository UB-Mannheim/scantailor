/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2007-2009  Joseph Artsimovich <joseph_a@mail.ru>

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

#include "BlackWhiteOptions.h"
#include <QDomDocument>
#include <QDomElement>
#include <QString>

namespace output
{

BlackWhiteOptions::BlackWhiteOptions(QDomElement const& el)
:	m_thresholdAdjustment(el.attribute("thresholdAdj").toInt()),
	m_despeckle(el.attribute("despeckle") != "0")
{
	// Note that we default to true if the attribute is not found.
}

QDomElement
BlackWhiteOptions::toXml(QDomDocument& doc, QString const& name) const
{
	QDomElement el(doc.createElement(name));
	el.setAttribute("thresholdAdj", m_thresholdAdjustment);
	el.setAttribute("despeckle", m_despeckle ? "1" : "0");
	return el;
}

bool
BlackWhiteOptions::operator==(BlackWhiteOptions const& other) const
{
	if (m_thresholdAdjustment != other.m_thresholdAdjustment) {
		return false;
	}
	
	if (m_despeckle != other.m_despeckle) {
		return false;
	}
	
	return true;
}

bool
BlackWhiteOptions::operator!=(BlackWhiteOptions const& other) const
{
	return !(*this == other);
}

} // namespace output