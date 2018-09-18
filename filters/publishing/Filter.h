/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2018 Alexander Trufanov <trufanovan@gmail.com>

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

#ifndef PUBLISHING_FILTER_H_
#define PUBLISHING_FILTER_H_

#include "NonCopyable.h"
#include "AbstractFilter.h"
#include "PageView.h"
#include "IntrusivePtr.h"
#include "FilterResult.h"
#include "SafeDeletingQObjectPtr.h"
#include "ProjectPages.h"
#include "DjVuPageGenerator.h"
#include "djview4/qdjvu.h"
#include "djview4/qdjvuwidget.h"

#include <QCoreApplication>
#include <QImage>
#include <memory>

class PageId;
class PageSelectionAccessor;
class ThumbnailPixmapCache;
class OutputFileNameGenerator;
class QString;


namespace publishing
{

class OptionsWidget;
class Task;
class CacheDrivenTask;
class Settings;
class QMLLoader;

/**
 * \note All methods of this class except the destructor
 *       must be called from the GUI thread only.
 */
class Filter : public AbstractFilter
{
	DECLARE_NON_COPYABLE(Filter)
    Q_DECLARE_TR_FUNCTIONS(publishing::Filter)
public:
    Filter(IntrusivePtr<ProjectPages> const& pages, PageSelectionAccessor const& page_selection_accessor);
	
	virtual ~Filter();
	
	virtual QString getName() const;
	
	virtual PageView getView() const;
	
	virtual void performRelinking(AbstractRelinker const& relinker);

	virtual void preUpdateUI(FilterUiInterface* ui, PageId const&);
	
	virtual QDomElement saveSettings(
		ProjectWriter const& writer, QDomDocument& doc) const;
	
	virtual void loadSettings(
		ProjectReader const& reader, QDomElement const& filters_el);

    virtual void invalidateSetting(PageId const& page);
	
	IntrusivePtr<Task> createTask(
		PageId const& page_id,		
		bool batch_processing);
	
    IntrusivePtr<CacheDrivenTask> createCacheDrivenTask();
	
    OptionsWidget* optionsWidget() { return m_ptrOptionsWidget.get(); }

    Settings* getSettings() { return m_ptrSettings.get(); }

    QDjVuWidget* getDjVuWidget() const { return m_ptrDjVuWidget.get(); }

    DjVuPageGenerator& getPageGenerator() { return m_PageGenerator; }

    QMLLoader* getQMLLoader() const { return m_QMLLoader; }
private:
    void writePageSettings(
		QDomDocument& doc, QDomElement& filter_el,
        PageId const& page_id, int numeric_id) const;
	
    IntrusivePtr<ProjectPages> m_ptrPages;
	IntrusivePtr<Settings> m_ptrSettings;
    DjVuPageGenerator m_PageGenerator;
	SafeDeletingQObjectPtr<OptionsWidget> m_ptrOptionsWidget;
    SafeDeletingQObjectPtr<QDjVuContext> m_ptrDjVuContext;
    SafeDeletingQObjectPtr<QDjVuWidget> m_ptrDjVuWidget;
    QMLLoader* m_QMLLoader;
    bool m_isGUI;
};

} // publishing

#endif
