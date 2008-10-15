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
#ifndef CUCULUS_STATUS_H
#define CUCULUS_STATUS_H

#include "cuculusclient_export.h"

#include <kurl.h>

#include <QtCore>
#include <QPixmap>

namespace Cuculus {

class StatusListJob;

class CUCULUS_EXPORT Status
{
  public:
    typedef QList<Status> List;
  
    Status();

    void setText( const QString & );
    QString text() const;

    void setCreatedAt( const QDateTime & );
    QDateTime createdAt() const;

    void setSource( const QString & );
    QString source() const;

  private:
    QString m_text;
    QDateTime m_createdAt;
    QString m_source;
};

}

#endif
