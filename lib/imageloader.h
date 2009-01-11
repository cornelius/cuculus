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
#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <kurl.h>
#include <kjob.h>
#include <kio/job.h>

#include <QObject>
#include <QMap>

namespace Cuculus {

class ImageLoader : public QObject
{
    Q_OBJECT
  public:
    class Cache {
      public:
        static Cache *self();
        
        bool hasPixmap( const KUrl & );
        QPixmap pixmap( const KUrl & );
        void setPixmap( const KUrl &, const QPixmap & );
        
      private:
        Cache();
        
        static Cache *m_self;

        QMap<KUrl,QPixmap> m_pixmaps;
    };
  
    ImageLoader();

    static ImageLoader *load( const KUrl & );
    
    void setUrl( const KUrl & );
    KUrl url() const;

    void setScaledSize( const QSize & );
    
  signals:
    void loaded( const QPixmap & );
    void error( const QString &text );

  protected slots:
    void slotResult( KJob *job );
    void slotData( KIO::Job *job, const QByteArray &data );

    void emitCached();

  private:
    KUrl m_url;
    QByteArray m_data;
    QSize m_scaledSize;
};

}

#endif
