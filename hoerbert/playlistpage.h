/***************************************************************************
 * hörbert Software
 * Copyright (C) 2019 WINZKI GmbH & Co. KG
 *
 * Authors of the original version: Igor Yalovenko, Rainer Brang
 * Dec. 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#ifndef PLAYLISTPAGE_H
#define PLAYLISTPAGE_H

#include <QWidget>

#include "define.h"
#include "mainwindow.h"

class QComboBox;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QFileInfo;
class QMenu;
class QCheckBox;
class QRadioButton;

class PieButton;
class PlaylistView;
class MainWindow;

/**
 * @brief The PlaylistPage class represents a page to work on a playlist
 */
class PlaylistPage : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief PlaylistPage constructor
     * @param parent
     */
    explicit PlaylistPage(QWidget *parent = Q_NULLPTR);

    /**
     * @brief set the absolute path to selected directory and directory number, list all files in it
     */
    void setListData(const QString &, quint8 , const AudioList &, MainWindow*);

    /**
     * @brief return the directory number
     * @return
     */
    quint8 directory();

    /**
     * @brief return path to current directory
     * @return
     */
    QString directoryPath();

    /**
     * @brief set background color of container frame
     * @param color
     */
    void setBackgroundColor(const QColor &color);

    /**
     * @brief move selected entries from current directory to desired directory
     * @param to_dir
     * @param add2beginning
     */
    void moveSelectedEntriesTo(quint8 to_dir, bool add2beginning);

    /**
     * @brief getPlaylistView return a pointer to the playlistView
     * @return
     */
    const PlaylistView *getPlaylistView();

    /**
     * @brief getPlaylistIndex
     * @return the index of this playlist page
     */
    int getPlaylistIndex();

signals:

    /**
     * @brief cancelClicked
     */
    void cancelClicked();

    /**
     * @brief commitChanges
     * @param list
     */
    void commitChanges(const QMap<ENTRY_LIST_TYPE, AudioList>&, const quint8);

    /**
     * @brief emitted when an entry is added or removed
     * @param seconds seconds added or removed
     */
    void durationChanged(int playlistIndex, int seconds, bool isEstimation);

    /**
     * @brief emitted when error occurs
     * @param errorString
     */
    void errorOccurred(const QString &errorString);

    void setBluetoothRecordingPlaylist(qint8 dirNum, bool onOff);
    void setWifiRecordingPermission(qint8 dirNum, bool onOff );
    void setMicrophoneRecordingPermission(qint8 dirNum, bool onOff);

public slots:
    /**
     * @brief add silence to the position
     */
    void addSilence();

    /**
     * @brief add an url to the position
     */
    void addUrl();

    /**
     * @brief add files through file dialog
     */
    void add();

    /**
     * @brief remove selected files from playlist
     */
    void remove();

    /**
     * @brief discard any changes and close playlist
     */
    void discard();

    /**
     * @brief setDriveSpaceInfo
     * @param used
     * @param total
     */
    void setDriveSpaceDetails(quint64 used, quint64 total);
protected:
    void contextMenuEvent(QContextMenuEvent *e);

private slots:

    /**
     * @brief this signal is emitted when the page is about to close(commit/cancel)
     * @param doCommitChanges indicates whether the closing is due to commit or cancel
     */
    void onClosePage(bool doCommitChanges);

    void show();

private:
    /**
     * @brief getSelectedSilenceDurationInSeconds get duration of silence from combobox in seconds
     * @return duration in seconds
     */
    int getSelectedSilenceDurationInSeconds();

    /**
     * @brief updateColumnVisibleSettings update settings of column visibility
     * @param columnName name of column to be set
     * @param visible visibility flag
     */
    void updateColumnVisibleSettings(const QString &columnName, bool visible);

    /**
     * @brief columnVisibleFromSettings retrieve visibility of column from settings
     * @param columnName name of column to be considered
     * @return visibility of the column
     */
    bool columnVisibleFromSettings(const QString &columnName);


    quint8 m_dirNum;
    QString m_dir;

    MainWindow* m_mainWindow;

    AudioList m_clipBoard;

    QMap<int, AudioList> m_originalList;
    QMap<int, AudioList> m_implicitlyMovedList;

    QLabel *m_silenceLabel;
    QLabel *m_urlLabel;
    QLabel *m_fileLabel;
    QLabel *m_colorBlindHintLabel;
    QComboBox *m_silenceDuration;
    PieButton *m_addSilenceButton;
    PieButton *m_addUrlButton;
    PieButton *m_addButton;
    PieButton *m_removeButton;
    PieButton *m_commitButton;
    PieButton *m_cancelButton;
    PlaylistView *m_playlistView;

    QPushButton *m_bluetoothRecordingsRadioButton;
    QPushButton *m_microphoneRecordingsCheckbox;
    QPushButton *m_wifiRecordingsCheckbox;

    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_toolLayout;
    QHBoxLayout *m_authorizationsLayout;
    QHBoxLayout *m_leftToolLayout;
    QHBoxLayout *m_centerToolLayout;
    QHBoxLayout *m_rightToolLayout;

    QPalette m_pal;
};

#endif // PLAYLISTPAGE_H
