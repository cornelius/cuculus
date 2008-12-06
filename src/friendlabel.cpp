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

#include "friendlabel.h"

#include "imageloader.h"

FriendLabel::FriendLabel()
{
  QBoxLayout *topLayout = new QHBoxLayout( this );
  
  m_pictureLabel = new QLabel;
  topLayout->addWidget( m_pictureLabel );
  
  m_textLabel = new QLabel;
  topLayout->addWidget( m_textLabel );
}

void FriendLabel::setFriend( const Cuculus::User &user )
{
  m_textLabel->setText( user.name() );

  ImageLoader* imageLoader = ImageLoader::load( user.miniImageUrl() );
  imageLoader->setScaledSize( QSize( 24, 24 ) );
  connect( imageLoader, SIGNAL( loaded( const QPixmap & ) ),
    m_pictureLabel, SLOT( setPixmap( const QPixmap & ) ) );
}
