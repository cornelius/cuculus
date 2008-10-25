/*
 * cuculusview.cpp
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */

#include "cuculusview.h"

#include "settings.h"

#include "twitterapi.h"

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
  connect( m_tweetEdit, SIGNAL( textChanged() ), SLOT( checkUpdateButton() ) );

  m_updateButton = new QPushButton( "Update" );
  topLayout->addWidget( m_updateButton );
  connect( m_updateButton, SIGNAL( clicked() ), SLOT( sendTweet() ) );


  QBoxLayout *updateLayout = new QHBoxLayout;
  topLayout->addLayout( updateLayout );
  
  updateLayout->addStretch( 1 );

  QPushButton *button = new QPushButton( "Get latest tweets" );
  updateLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( updateTimeline() ) );

  
  for( int i = 0; i < 5; ++i ) {
    TweetView *view = new TweetView;
    topLayout->addWidget( view );
    m_tweetViews.append( view );
  }

  
  updateEditCount();
  checkUpdateButton();
  
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

void CuculusView::checkUpdateButton()
{
  m_updateButton->setEnabled( !m_tweetEdit->toPlainText().isEmpty() );
}

void CuculusView::updateTimeline()
{
  Cuculus::StatusListJob *job = Cuculus::TwitterApi::requestFriendsTimeline();
  connect( job, SIGNAL( result( KJob * ) ), SLOT( slotResult( KJob * ) ) );
}

void CuculusView::slotResult( KJob *j )
{
  if ( j->error() ) {
    qDebug() << "Error" << j->errorText();
  } else {
    Cuculus::StatusListJob *job = static_cast<Cuculus::StatusListJob *>( j );
    int i = 0;
    foreach( Cuculus::Status status, job->statusList() ) {
      qDebug() << "STATUS" << status.text();
      m_tweetViews[ i ]->setStatus( status );
      ++i;
      if ( i >= m_tweetViews.size() ) break;
    }
  }
}

void CuculusView::sendTweet()
{
  QString text = m_tweetEdit->toPlainText();

  qDebug() << "SEND" << text;

  Cuculus::PostJob *job = Cuculus::TwitterApi::postUpdate( text );
  connect( job, SIGNAL( result( KJob * ) ),
    SLOT( slotSendTweetResult( KJob * ) ) );
}

void CuculusView::slotSendTweetResult( KJob *j )
{
  Cuculus::PostJob *job = static_cast<Cuculus::PostJob *>( j );
  
  if ( job->error() ) {
    qDebug() << "ERROR" << job->errorText();
  } else {
    qDebug() << "SUCCESS SENDING TWEET";
    updateTimeline();
  }
}

#include "cuculusview.moc"
