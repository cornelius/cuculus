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

  QBoxLayout *countLayout = new QHBoxLayout;
  topLayout->addLayout( countLayout );

  QLabel *label = new QLabel( i18n("What are you doing?") );
  countLayout->addWidget( label );

  countLayout->addStretch( 1 );

  m_countLabel = new QLabel;
  countLayout->addWidget( m_countLabel );

  m_tweetEdit = new QTextEdit;
  topLayout->addWidget( m_tweetEdit );
  connect( m_tweetEdit, SIGNAL( textChanged() ), SLOT( updateEditCount() ) );
  
  for( int i = 0; i < 5; ++i ) {
    TweetView *view = new TweetView;
    topLayout->addWidget( view );
    m_tweetViews.append( view );
  }
  
  updateEditCount();
  
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

void CuculusView::updateEditCount()
{
  m_countLabel->setText(
    QString::number( 140 - m_tweetEdit->toPlainText().length() ) );
}

#include "cuculusview.moc"
