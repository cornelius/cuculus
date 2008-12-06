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

#include "friendsview.h"

#include "twitterapi.h"
#include "friendlabel.h"

#include <klocale.h>

FriendsView::FriendsView()
{
  QBoxLayout *topLayout = new QVBoxLayout( this );
  
  QPushButton *button = new QPushButton( i18n("Get Friends") );
  topLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( loadFriends() ) );

  m_friendsList = new QWidget;
  topLayout->addWidget( m_friendsList, 1 );  
}

void FriendsView::loadFriends()
{
  Cuculus::UserListJob *job = Cuculus::TwitterApi::requestFriends();
  connect( job, SIGNAL( result( KJob * ) ), SLOT( slotResult( KJob * ) ) );
}

void FriendsView::slotResult( KJob *j )
{
  if ( j->error() ) {
    qDebug() << "Error" << j->errorText();
  } else {
    Cuculus::UserListJob *job = static_cast<Cuculus::UserListJob *>( j );

    QBoxLayout *userLayout = new QVBoxLayout( m_friendsList );

    foreach( Cuculus::User user, job->userList() ) {
      FriendLabel *label = new FriendLabel();
      userLayout->addWidget( label );
      label->setFriend( user );
    }
  }
}
