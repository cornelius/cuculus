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

#include "userparser.h"

#include <QXmlStreamReader>

using namespace Cuculus;

UserParser::UserParser()
{
}

User::List UserParser::parseList( const QString &xmlString )
{
  User::List userList;
  
  QXmlStreamReader xml( xmlString );
  
  while ( !xml.atEnd() ) {
    xml.readNext();
    
    if ( xml.isStartElement() && xml.name() == "user" ) {
      User user = parse( xml );
      userList.append( user );
    }
  }
  
  return userList;
}

User UserParser::parse( QXmlStreamReader &xml )
{
  User user;
  
  while ( !xml.atEnd() ) {
    xml.readNext();
    
    if ( xml.isStartElement() ) {
      if ( xml.name() == "id" ) {
        user.setId( xml.readElementText() );
      } else if ( xml.name() == "name" ) {
        user.setName( xml.readElementText() );
      } else if ( xml.name() == "screen_name" ) {
        user.setScreenName( xml.readElementText() );
      } else if ( xml.name() == "profile_image_url" ) {
        user.setImageUrl( KUrl( xml.readElementText() ) );
      }
    } else if ( xml.isEndElement() && xml.name() == "user" ) {
      return user;
    }
  }
  
  return user;
}
