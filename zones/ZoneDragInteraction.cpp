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

#include "ZoneDragInteraction.h"
#include "ZoneInteractionContext.h"
#include "EditableZoneSet.h"
#include "ImageViewBase.h"
#include "settings/globalstaticsettings.h"
#include <QTransform>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QLinearGradient>
#include <Qt>
#include <QLineF>

ZoneDragInteraction::ZoneDragInteraction(
    ZoneInteractionContext& context, InteractionState& interaction,
    EditableSpline::Ptr const& spline, SplineVertex::Ptr const& vertex)
:	m_rContext(context),
    m_ptrSpline(spline),
    m_savedSpline(*spline.get()),
    m_ptrVertex(vertex)
{
	QPointF const screen_mouse_pos(
		m_rContext.imageView().mapFromGlobal(QCursor::pos()) + QPointF(0.5, 0.5)
	);
	QTransform const to_screen(m_rContext.imageView().imageToWidget());
	m_dragOffset = to_screen.map(vertex->point()) - screen_mouse_pos;

    m_interaction.setInteractionCursor(QCursor(Qt::DragMoveCursor));
    m_interaction.setInteractionStatusTip(tr("Press %1 to cancel")
                                          .arg(GlobalStaticSettings::getShortcutText(ZoneCancel)));
	interaction.capture(m_interaction);
	checkProximity(interaction);
}

void
ZoneDragInteraction::onPaint(QPainter& painter, InteractionState const& interaction)
{
	painter.setWorldMatrixEnabled(false);
	painter.setRenderHint(QPainter::Antialiasing);

	QTransform const to_screen(m_rContext.imageView().imageToWidget());

    for (EditableZoneSet::Zone const& zone: m_rContext.zones()) {
		EditableSpline::Ptr const& spline = zone.spline();

		if (spline != m_ptrSpline) {
			// Draw the whole spline in solid color.
			m_visualizer.drawSpline(painter, to_screen, spline);
			continue;
		}
	}
}

void
ZoneDragInteraction::onMouseReleaseEvent(
	QMouseEvent* event, InteractionState& interaction)
{
	if (event->button() == Qt::LeftButton) {		
        m_ptrSpline->simplify(GlobalStaticSettings::m_zone_editor_min_angle);
		m_rContext.zones().commit();
		makePeerPreceeder(*m_rContext.createDefaultInteraction());
		delete this;        
    }
}

void
ZoneDragInteraction::onMouseMoveEvent(QMouseEvent* event, InteractionState& interaction)
{
	QTransform const from_screen(m_rContext.imageView().widgetToImage());	
    const Qt::KeyboardModifiers mask = event->modifiers();

    const bool move = GlobalStaticSettings::checkModifiersMatch(ZoneMove, mask);
    const bool nove_hor = GlobalStaticSettings::checkModifiersMatch(ZoneMoveHorizontally, mask);
    const bool nove_vert = GlobalStaticSettings::checkModifiersMatch(ZoneMoveVertically, mask);

    if (move||nove_hor||nove_vert) {
        QPointF current = event->pos() + QPointF(0.5, 0.5) + m_dragOffset;

        if (!m_moveStart.isNull()) {
            QPointF diff = from_screen.map(current) - from_screen.map(m_moveStart);

            if (nove_hor) {
                diff.setX(0);
            } else if (nove_vert) {
                diff.setY(0);
            }

            SplineVertex::Ptr i = m_ptrSpline->firstVertex();
            do {
                // m_ptrVertex is changed in this loop too
                QPointF current = i->point();
                current += diff;
                i->setPoint(current);
                i = i->next(SplineVertex::NO_LOOP);
            } while (i.get());
        }
        m_moveStart = current;
    } else {
        // No modifiers
        m_moveStart = QPointF();
        m_ptrVertex->setPoint(from_screen.map(event->pos() + QPointF(0.5, 0.5) + m_dragOffset));
    }

	checkProximity(interaction);
	m_rContext.imageView().update();
}

void
ZoneDragInteraction::checkProximity(InteractionState const& /*interaction*/)
{
}

void
ZoneDragInteraction::onKeyPressEvent(QKeyEvent* event, InteractionState& /*interaction*/)
{
    if (GlobalStaticSettings::checkKeysMatch(ZoneCancel, event->modifiers(), (Qt::Key) event->key())) {
        m_ptrSpline->copyFromSerializableSpline(m_savedSpline);
        m_rContext.zones().commit();
        makePeerPreceeder(*m_rContext.createDefaultInteraction());
        delete this;
    }
}
