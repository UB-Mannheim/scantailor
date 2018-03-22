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

#ifndef HOTKEYSMANAGER_H
#define HOTKEYSMANAGER_H

#include <Qt>
#include <QString>
#include <QMouseEvent>
#include "settings/ini_keys.h"
#include <QObject>

enum KeyType {
    DefaultValueKT = 0,
    KeysAllowed = 1,
    ModifierAllowed = 2,
    KeysAndModifiers = KeysAllowed|ModifierAllowed
};

enum HotKeyType {
    DefaultValueHK = 0,
    HotKey,
    MouseClick,
    MouseHold,
    MouseWheel,
    MouseDoubleCLick
};

enum HotKeysId {
    DefaultValueId = 0,
    ProjectNew = 10,
    ProjectOpen,
    ProjectSave,
    ProjectSaveAs,
    ProjectClose,
    AppQuit = 100,
    StageFixOrientation = 200,
    StageSplitPages,
    StageDeskew,
    StageSelectContent,
    StageMargins,
    StageOutput,
    PageFirst = 300,
    PageLast,
    PagePrev,
    PageNext,
    PageJumpForward,
    PageJumpBackward,
    PageFirstSelected,
    PageLastSelected,
    PagePrevSelected,
    PageNextSelected,
    ThumbSizeChange,
    DeskewChange = 400,
    DeskewChangePrec,
    ContentMove = 500,
    ContentMoveAxes,
    ContentStretch,
    ContentInsert,
    ContentDelete,
    ContentMoveUp,
    ContentMoveDown,
    ContentMoveLeft,
    ContentMoveRight,
    PageViewZoomIn = 600,
    PageViewZoomOut,
    PageViewDisplayOriginal,
    PageViewMoveNoRestrictions,
    ZoneRectangle = 700,
    ZoneMove,
    ZoneMoveVertically,
    ZoneMoveHorizontally,
    ZonePaste,
    ZoneClone,
    ZoneDelete,
    ZoneCancel,
    DewarpingMoveVertically = 800,
    DewarpingMoveHorizontally,
    DewarpingDeletePoint,
    DespeckleMode0 = 900,
    DespeckleMode1,
    DespeckleMode2,
    DespeckleMode3
};

struct HotKeySequence {
    HotKeySequence(){}
    HotKeySequence(Qt::KeyboardModifiers modifier, QVector<Qt::Key> keys):
        m_modifierSequence(modifier), m_keySequence(keys) {}
    HotKeySequence(Qt::KeyboardModifiers modifier, Qt::Key key):
        m_modifierSequence(modifier), m_keySequence(QVector<Qt::Key>(1, key)) {}

    Qt::KeyboardModifiers m_modifierSequence;
    QVector<Qt::Key> m_keySequence;
};

class HotKeyInfo {
public:
    HotKeyInfo() {}
    HotKeyInfo(const HotKeysId id, const QString& title, const KeyType editorType, const HotKeyType displayType,
               const HotKeySequence sequence):
        HotKeyInfo(id, title, editorType, displayType, QVector<HotKeySequence>(1,sequence)) {}

    HotKeyInfo(const HotKeysId id, const QString& title, const KeyType editorType, const HotKeyType displayType,
               const QVector<HotKeySequence>& sequences):
        m_id(id), m_title(title), m_editorType(editorType), m_displayType(displayType),
        m_sequences(sequences) {}

    const HotKeysId id() const { return m_id; }
    const QString& title() const { return m_title; }
    const HotKeyType displayType() const { return m_displayType; }
    const KeyType editorType() const { return m_editorType; }
    const QVector<HotKeySequence>& sequences() const { return m_sequences; }
    QVector<HotKeySequence>& sequences() { return m_sequences; }
    static const QString hotKeyTypeToString(const HotKeyType& val);
private:
    HotKeysId m_id;
    QString m_title;
    KeyType m_editorType;
    HotKeyType m_displayType;
    QVector<HotKeySequence> m_sequences;
};

class HotKeyGroup {
public:
    HotKeyGroup() {}
    HotKeyGroup(const QString& groupName, const QString& groupTitle):
        m_groupName(groupName), m_groupTitle(groupTitle) {}
    bool load(const QSettings& settings);
    void save(QSettings& settings) const;
    void setHotKeys(const QVector<HotKeyInfo>& data) {m_hotKeys = data; }
    const QVector<HotKeyInfo>& hotKeys() const { return m_hotKeys; }
    QVector<HotKeyInfo>& hotKeys() { return m_hotKeys; }
    const QString& id() const { return m_groupName; }
    const QString& title() const { return m_groupTitle; }
private:
    QString m_groupName;
    QString m_groupTitle;
    QVector<HotKeyInfo> m_hotKeys;
};

class QHotKeys {
public:
    QHotKeys();
    void resetToDefaults();
    bool load(QSettings *_settings = nullptr);
    void save(QSettings* settings= nullptr) const;
    const QString toDisplayableText() const;
    const HotKeyInfo *get( const HotKeysId& id) const;
    bool replace(const HotKeysId &id, const HotKeyInfo& new_val);
    static const QString modifiersToString(const Qt::KeyboardModifiers modifiers);
    static const QString keysToString(const QVector<Qt::Key>& keys);
    static const QString hotkeysToString(const Qt::KeyboardModifiers modifiers, const QVector<Qt::Key>& keys);
private:
    void mergeHotkeys(const QVector<HotKeyGroup>& new_data);
private:
    QVector<HotKeyGroup> m_data;
};

#endif // HOTKEYSMANAGER_H
