/*
    This file is part of KDE.

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

#include "twitterapi.h"

using namespace Cuculus;

TwitterApi::TwitterApi()
{
}

StatusListJob *TwitterApi::requestFriendsTimeline()
{
  KUrl url = createUrl( "statuses/friends_timeline.xml" );
  return doRequestStatusList( url );
}

KUrl TwitterApi::createUrl( const QString &path )
{
  KUrl url( "http://twitter.com/" );
  url.addPath( path );
  return url;
}

StatusListJob *TwitterApi::doRequestStatusList( const KUrl &url )
{
  StatusListJob *job = new StatusListJob();

  job->setUrl( url );

  job->start();
  return job;
}
