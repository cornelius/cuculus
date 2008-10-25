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

#include "user.h"

using namespace Cuculus;

User::User()
{
}

void User::setId( const QString &u )
{
  m_id = u;
}

QString User::id() const
{
  return m_id;
}

void User::setName( const QString &u )
{
  m_name = u;
}

QString User::name() const
{
  return m_name;
}

void User::setScreenName( const QString &u )
{
  m_screenName = u;
}

QString User::screenName() const
{
  return m_screenName;
}

void User::setImageUrl( const KUrl &d )
{
  m_imageUrl = d;
}

KUrl User::imageUrl() const
{
  return m_imageUrl;
}
