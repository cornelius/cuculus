/*
 * cuculusview.cpp
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */

#include "cuculusview.h"

#include "settings.h"
#include "friendsview.h"

#include "twitterapi.h"

#include <klocale.h>
#include <kglobal.h>
#include <kstandarddirs.h>

CuculusView::CuculusView(QWidget *)
  : m_currentTweetIndex( 0 )
{
  setObjectName( "view" );

  m_model = new CuculusModel;

  QBoxLayout *mainLayout = new QHBoxLayout( this );
  
  QBoxLayout *topLayout = new QVBoxLayout;
  mainLayout->addLayout( topLayout );

  m_timeLabel = new QLabel;
  topLayout->addWidget( m_timeLabel );
  m_timeLabel->setAlignment( Qt::AlignCenter );

  connect( &m_timeLabelTimer, SIGNAL( timeout() ), SLOT( updateTimeLabel() ) );
  m_timeLabelTimer.start( 60 * 1000 );

  QBoxLayout *countLayout = new QHBoxLayout;
  topLayout->addLayout( countLayout );

  QLabel *label = new QLabel( i18n("What are you doing?") );
  countLayout->addWidget( label );

  countLayout->addStretch( 1 );

  m_countLabel = new QLabel;
  countLayout->addWidget( m_countLabel );


  m_tweetEdit = new QTextEdit;
  m_tweetEdit->setFixedHeight( 60 );
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


  m_upButton = new QPushButton;
  connect( m_upButton, SIGNAL( clicked() ), SLOT( pageUp() ) );
  QString picPath = KStandardDirs::locate( "appdata", "1uparrow.png" );
  m_upButton->setIcon( QPixmap( picPath ) );
  topLayout->addWidget( m_upButton );

  m_tweetsView = new TweetListView;
  topLayout->addWidget( m_tweetsView, 1 );
  m_tweetsView->setStyleSheet("background-color: white");

  m_downButton = new QPushButton;
  connect( m_downButton, SIGNAL( clicked() ), SLOT( pageDown() ) );
  picPath = KStandardDirs::locate( "appdata", "1downarrow.png" );
  m_downButton->setIcon( QPixmap( picPath ) );
  topLayout->addWidget( m_downButton );


  FriendsView *friendsView = new FriendsView;
  mainLayout->addWidget( friendsView );

  
  updateEditCount();
  checkUpdateButton();
  updateTimeLabel();
  updatePageButtons();
  
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

void CuculusView::updateTimeLabel()
{
  m_timeLabel->setText( KGlobal::locale()->formatDateTime(
    QDateTime::currentDateTime(), KLocale::LongDate ) );
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

void CuculusView::updatePageButtons()
{
  m_upButton->setEnabled( m_currentTweetIndex > 0 );
  m_downButton->setEnabled(
    m_currentTweetIndex + m_tweetsView->pageSize() < m_model->count() );
}

void CuculusView::slotResult( KJob *j )
{
  if ( j->error() ) {
    qDebug() << "Error" << j->errorText();
  } else {
    Cuculus::StatusListJob *job = static_cast<Cuculus::StatusListJob *>( j );

    m_model->addStatuses( job->statusList() );
    updatePageButtons();

    showPage();
  }
}

void CuculusView::sendTweet()
{
  QString text = m_tweetEdit->toPlainText();

  qDebug() << "SEND" << text;

  Cuculus::PostJob *job = Cuculus::TwitterApi::postUpdate( text );
  connect( job, SIGNAL( result( KJob * ) ),
    SLOT( slotSendTweetResult( KJob * ) ) );

  m_tweetEdit->clear();
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

void CuculusView::showPage()
{
  int tweetViewCount = 0;
  for( int i = m_currentTweetIndex;
       i < m_currentTweetIndex + m_tweetsView->pageSize(); ++i ) {
    Cuculus::Status status = m_model->status( i );
    m_tweetsView->setStatus( tweetViewCount, status );
    
    tweetViewCount++;
  }
}

void CuculusView::pageUp()
{
  m_currentTweetIndex -= m_tweetsView->pageSize();
  if ( m_currentTweetIndex < 0 ) m_currentTweetIndex = 0;
  
  showPage();
  
  updatePageButtons();
}

void CuculusView::pageDown()
{
  m_currentTweetIndex += m_tweetsView->pageSize();
  
  showPage();
  
  updatePageButtons();
}

#include "cuculusview.moc"
