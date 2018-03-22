/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) Joseph Artsimovich <joseph_a@mail.ru>

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

#include "globalstaticsettings.h"

bool GlobalStaticSettings::m_drawDeskewDeviants = false;
bool GlobalStaticSettings::m_drawContentDeviants = false;
bool GlobalStaticSettings::m_drawMarginDeviants = false;
bool GlobalStaticSettings::m_drawDeviants = false;
int  GlobalStaticSettings::m_currentStage = 0;
int  GlobalStaticSettings::m_binrization_threshold_control_default = 0;
bool GlobalStaticSettings::m_use_horizontal_predictor = false;
bool GlobalStaticSettings::m_disable_bw_smoothing = false;
qreal GlobalStaticSettings::m_zone_editor_min_angle = 3.0;
float GlobalStaticSettings::m_picture_detection_sensitivity = 100.;
QHotKeys GlobalStaticSettings::m_hotKeyManager = QHotKeys();
std::unique_ptr<int> GlobalStaticSettings::m_ForegroundLayerAdjustment = nullptr;
int  GlobalStaticSettings::m_highlightColorAdjustment = 140;

bool GlobalStaticSettings::m_thumbsListOrderAllowed = true;
int GlobalStaticSettings::m_thumbsMinSpacing = 3;
int GlobalStaticSettings::m_thumbsBoundaryAdjTop = 5;
int GlobalStaticSettings::m_thumbsBoundaryAdjBottom = 5;
int GlobalStaticSettings::m_thumbsBoundaryAdjLeft = 5;
int GlobalStaticSettings::m_thumbsBoundaryAdjRight = 3;
bool GlobalStaticSettings::m_fixedMaxLogicalThumbSize = false;
