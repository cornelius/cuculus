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

#include "statusparser.h"

#include <QXmlStreamReader>

using namespace Cuculus;

StatusParser::StatusParser()
{
}

Status::List StatusParser::parseList( const QString &xmlString )
{
  Status::List statusList;
  
  QXmlStreamReader xml( xmlString );
  
  while ( !xml.atEnd() ) {
    xml.readNext();
    
    if ( xml.isStartElement() && xml.name() == "status" ) {
      Status status;

      while ( !xml.atEnd() ) {
        xml.readNext();

        if ( xml.isStartElement() ) {
          if ( xml.name() == "text" ) {
            status.setText( xml.readElementText() );
          } else if ( xml.name() == "created_at" ) {
            QString timestampString = xml.readElementText();
            QDateTime timestamp = QDateTime::fromString( timestampString );
            status.setCreatedAt( timestamp );
          } else if ( xml.name() == "source" ) {
            status.setSource( xml.readElementText() );
          }
        }

        if ( xml.isEndElement() && xml.name() == "status" ) break;
      }
      
      statusList.append( status );
    }
  }
  
  return statusList;
}
