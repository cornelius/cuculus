/*
 * cuculusview.h
 *
 * Copyright (C) 2007 Cornelius Schumacher <schumacher@kde.org>
 */
#ifndef CUCULUSVIEW_H
#define CUCULUSVIEW_H

#include "tweetview.h"

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

  protected slots:
    void updateEditCount();
    void updateTimeline();

    void slotResult( KJob *j );

  private slots:
    void switchColors();
    void settingsChanged();

  private:
    QLabel *m_countLabel;
    QTextEdit *m_tweetEdit;
    QList<TweetView *> m_tweetViews;
};

#endif
