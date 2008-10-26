/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include "tweetview.h"

#include "imageloader.h"

#include "kstandarddirs.h"
#include "klocale.h"

TweetView::TweetView()
{
  setObjectName( "tweetView" );


  m_personWidget = new QWidget;

  QBoxLayout *picLayout = new QVBoxLayout( m_personWidget );
  
  m_imageLabel = new QLabel;
  m_imageLabel->setAlignment( Qt::AlignHCenter );
  picLayout->addWidget( m_imageLabel );
  QString picPath = KStandardDirs::locate( "appdata", "attica_person.png" );
  m_imageLabel->setPixmap( QPixmap( picPath ) );

  m_nameLabel = new QLabel;
  m_nameLabel->setAlignment( Qt::AlignHCenter );
  picLayout->addWidget( m_nameLabel );


  m_label = new QLabel( "This will be a tweet." );
  m_tweetWidget = m_label;
}

void TweetView::setStatus( const Cuculus::Status &status )
{
  m_status = status;

  QString txt = "<qt>";
  
  txt += status.text();
  txt += "<br/>";
  txt += "<em>";
  txt += timeAgoInWords( status.createdAt() );
  txt += " from " + status.source();
  txt += "</em>";

  txt += "</qt>";

  m_label->setText( txt );

  m_nameLabel->setText( status.user().name() );

  ImageLoader *loader = ImageLoader::load( status.user().imageUrl() );
  connect( loader, SIGNAL( loaded( const QPixmap & ) ),
    SLOT( setUserImage( const QPixmap & ) ) );
}

Status TweetView::status() const
{
  return m_status;
}

void TweetView::setUserImage( const QPixmap &pixmap )
{
  m_imageLabel->setPixmap( pixmap );
}

QString TweetView::timeAgoInWords( const QDateTime &dt )
{
  QString txt;

  QDateTime now = QDateTime::currentDateTime().toUTC();

  int daysAgo = dt.daysTo( now );
  if ( daysAgo == 0 ) {
    int minutesAgo = dt.secsTo( now ) / 60;
    if ( minutesAgo == 0 ) {
      txt = i18n("Now");
    } else if ( minutesAgo < 60 ) {
      txt = i18n("%1 minutes ago").arg( minutesAgo );
    } else {
      txt = i18n("Today %1").arg( dt.toLocalTime().time().toString( "h:mm" ) );
    }
  } else if ( daysAgo == 1 ) {
    txt = i18n("Yesterday %1").arg(
      dt.toLocalTime().time().toString( "h:mm" ) );
  } else {
    txt = i18n("%1 days ago").arg( daysAgo );
  }

  return txt;
}

QWidget *TweetView::tweetWidget() const
{
  return m_tweetWidget;
}

QWidget *TweetView::personWidget() const
{
  return m_personWidget;
}
