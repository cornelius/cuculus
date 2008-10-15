/*
 * cuculusview.cpp
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */

#include "cuculusview.h"

#include "settings.h"

#include <klocale.h>

CuculusView::CuculusView(QWidget *)
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  m_tweetEdit = new QTextEdit;
  topLayout->addWidget( m_tweetEdit );
  
  for( int i = 0; i < 5; ++i ) {
    TweetView *view = new TweetView;
    topLayout->addWidget( view );
    m_tweetViews.append( view );
  }
  
  settingsChanged();
  setAutoFillBackground(true);
}

CuculusView::~CuculusView()
{
}

void CuculusView::switchColors()
{
  // switch the foreground/background colors of the label
  QColor color = Settings::col_background();
  Settings::setCol_background( Settings::col_foreground() );
  Settings::setCol_foreground( color );

  settingsChanged();
}

void CuculusView::settingsChanged()
{
}

#include "cuculusview.moc"
