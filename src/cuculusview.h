/*
 * cuculusview.h
 *
 * Copyright (C) 2007 Cornelius Schumacher <schumacher@kde.org>
 */
#ifndef CUCULUSVIEW_H
#define CUCULUSVIEW_H

#include "tweetview.h"
#include "cuculusmodel.h"

#include <kjob.h>

#include <QtGui>

class KUrl;

/**
 * This is the main view class for cuculus.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author Cornelius Schumacher <schumacher@kde.org>
 * @version 0.1
 */

class CuculusView : public QWidget
{
    Q_OBJECT
  public:
    /**
     * Default constructor
     */
    CuculusView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~CuculusView();

  signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

  protected:
    void showPage();

  protected slots:
    void updateEditCount();
    void checkUpdateButton();
    void updateTimeLabel();
    void updatePageButtons();

    void pageUp();
    void pageDown();

    void updateTimeline();
    void sendTweet();

    void slotResult( KJob *j );
    void slotSendTweetResult( KJob *j );

  private slots:
    void switchColors();
    void settingsChanged();

  private:
    CuculusModel *m_model;
  
    QLabel *m_timeLabel;
    QLabel *m_countLabel;
    QPushButton *m_updateButton;
    QTextEdit *m_tweetEdit;
    QPushButton *m_upButton;
    QPushButton *m_downButton;
    QList<TweetView *> m_tweetViews;

    int m_pageSize;
    int m_currentTweetIndex;

    QTimer m_timeLabelTimer;
};

#endif
