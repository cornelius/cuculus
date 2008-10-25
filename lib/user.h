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
#ifndef CUCULUS_USER_H
#define CUCULUS_USER_H

#include "cuculusclient_export.h"

#include <kurl.h>

#include <QtCore>
#include <QPixmap>

namespace Cuculus {

class CUCULUS_EXPORT User
{
  public:
    typedef QList<User> List;
  
    User();

    void setId( const QString & );
    QString id() const;

    void setName( const QString & );
    QString name() const;

    void setScreenName( const QString & );
    QString screenName() const;

    void setImageUrl( const KUrl & );
    KUrl imageUrl() const;

  private:
    QString m_id;
    QString m_name;
    QString m_screenName;
    KUrl m_imageUrl;
};

}

#endif
