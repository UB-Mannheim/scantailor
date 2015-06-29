/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2015  Joseph Artsimovich <joseph.artsimovich@gmail.com>

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

#include "ImageView.h"
#include "ImagePresentation.h"
#include "AffineImageTransform.h"
#include "AffineTransformedImage.h"
#include <QRect>
#include <QRectF>
#include <QPolygonF>

namespace fix_orientation
{

ImageView::ImageView(AffineTransformedImage const& full_size_image,
	ImagePixmapUnion const& downscaled_image)
:	ImageViewBase(
		full_size_image.origImage(), downscaled_image,
		ImagePresentation(
			full_size_image.xform().transform(),
			full_size_image.xform().transformedCropArea()
		)
	),
	m_dragHandler(*this),
	m_zoomHandler(*this),
	m_origImageSize(full_size_image.origImage().size())
{
	rootInteractionHandler().makeLastFollower(m_dragHandler);
	rootInteractionHandler().makeLastFollower(m_zoomHandler);
}

ImageView::~ImageView()
{
}

void
ImageView::setPreRotation(OrthogonalRotation const rotation)
{
	QRectF const rect(QPointF(0, 0), rotation.rotate(m_origImageSize));

	// This should call update() by itself.
	updateTransform(ImagePresentation(rotation.transform(m_origImageSize), rect));
}

} // namespace fix_orientation
