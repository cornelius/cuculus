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

#include "imageloader.h"

#include <QDebug>

ImageLoader::ImageLoader()
{
}

ImageLoader *ImageLoader::load( const KUrl &url )
{
  // TODO: Retrieve cached pixmap if available

  ImageLoader *loader = new ImageLoader;
  loader->setUrl( url );

  KJob *job = KIO::get( url, KIO::NoReload, KIO::HideProgressInfo );
  QObject::connect( job, SIGNAL( result( KJob * ) ), loader,
    SLOT( slotResult( KJob * ) ) );
  QObject::connect( job, SIGNAL( data( KIO::Job *, const QByteArray & ) ),
    loader, SLOT( slotData( KIO::Job *, const QByteArray & ) ) );

  return loader;
}

void ImageLoader::setUrl( const KUrl &url )
{
  m_url = url;
}

KUrl ImageLoader::url() const
{
  return m_url;
}

void ImageLoader::slotResult( KJob *job )
{
  if ( job->error() ) {
    qWarning() << "Error retrieving image:" << url() << job->errorText();
    emit error( job->errorText() );
  } else {
    QPixmap pic;
    if ( !pic.loadFromData( m_data ) ) {
      qWarning() << "Unable to parse image data" << url();
    } else {
      // TODO: Cache pixmap
      emit loaded( pic );
    }
  }
  
  deleteLater();
}

void ImageLoader::slotData( KIO::Job *, const QByteArray &data )
{
  m_data.append( data );
}
