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

PostJob *TwitterApi::postUpdate( const QString &message )
{
  // FIXME: Properly escape message

  PostJob *job = new PostJob();

  KUrl url = createUrl( "statuses/update.xml" );
  job->setUrl( url );
  job->setData( "status", message );
  
  job->start();
  return job;
}

UserListJob *TwitterApi::requestFriends()
{
  // Broken, because API return 404 instead of 401. Reported issue 79.

  KUrl url = createUrl( "statuses/friends.xml" );
  return doRequestUserList( url );
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

UserListJob *TwitterApi::doRequestUserList( const KUrl &url )
{
  UserListJob *job = new UserListJob();

  job->setUrl( url );

  job->start();
  return job;
}
