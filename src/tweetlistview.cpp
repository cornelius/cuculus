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

#include "tweetlistview.h"

TweetListView::TweetListView()
{
  QGridLayout *tweetLayout = new QGridLayout( this );
  tweetLayout->setColumnStretch( 1, 1 );
  
  for( int i = 0; i < pageSize() ; ++i ) {
    TweetView *view = new TweetView;
    tweetLayout->addWidget( view->personWidget(), i, 0, Qt::AlignHCenter );
    tweetLayout->addWidget( view->tweetWidget(), i, 1 );
    m_tweetViews.append( view );
  }
}

int TweetListView::pageSize() const
{
  return 5;
}

void TweetListView::setStatus( int index, Status status )
{
  m_tweetViews[ index ]->setStatus( status );
}
