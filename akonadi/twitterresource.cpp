#include "twitterresource.h"

#include "settings.h"
#include "settingsadaptor.h"

#include "userlistjob.h"
#include "user.h"
#include "twitterapi.h"

#include <kabc/addressee.h>
#include <kmessagebox.h>
#include <klocale.h>

#include <QtDBus/QDBusConnection>

using namespace Akonadi;

TwitterResource::TwitterResource( const QString &id )
  : ResourceBase( id )
{
  new SettingsAdaptor( Settings::self() );
  QDBusConnection::sessionBus().registerObject( QLatin1String( "/Settings" ),
                            Settings::self(), QDBusConnection::ExportAdaptors );

  // TODO: you can put any resource specific initialization code here.
}

TwitterResource::~TwitterResource()
{
}

void TwitterResource::retrieveCollections()
{
  // TODO: this method is called when Akonadi wants to have all the
  // collections your resource provides.
  // Be sure to set the remote ID and the content MIME types

  Collection c;
  c.setParent( Collection::root() );
  c.setRemoteId( "twitter.com/friends" );
  c.setName( name() );
  
  QStringList mimeTypes;
  mimeTypes << "text/directory";
  c.setContentMimeTypes( mimeTypes );
  
  Collection::List list;
  list << c;
  collectionsRetrieved( list );
}

void TwitterResource::retrieveItems( const Akonadi::Collection &collection )
{
  KMessageBox::information( 0, "GET ITEMS" );

  Q_UNUSED( collection );

  // TODO: this method is called when Akonadi wants to know about all the
  // items in the given collection. You can but don't have to provide all the
  // data for each item, remote ID and MIME type are enough at this stage.
  // Depending on how your resource accesses the data, there are several
  // different ways to tell Akonadi when you are done.

  Cuculus::UserListJob *job =
    Cuculus::TwitterApi::requestFriends();
  connect( job, SIGNAL( result( KJob * ) ),
    SLOT( slotUserListResult( KJob * ) ) );
}

void TwitterResource::slotUserListResult( KJob *j )
{
  Cuculus::UserListJob *job = static_cast<Cuculus::UserListJob *>( j );

  Item::List items;

  foreach( Cuculus::User user, job->userList() ) {    
    Item item( "text/directory" );
    item.setRemoteId( user.id() );
    
    KABC::Addressee addressee;
    addressee.setNameFromString( user.name() );
    addressee.setNickName( user.screenName() );
    addressee.insertCustom( "twitterresource", "imageurl",
      user.imageUrl().url() );

    item.setPayload<KABC::Addressee>( addressee );

    items << item;
  }
    
  itemsRetrieved( items );
}

bool TwitterResource::retrieveItem( const Akonadi::Item &item, const QSet<QByteArray> &parts )
{
  Q_UNUSED( parts );

  KMessageBox::information( 0, "GET ITEM" );

  // TODO: this method is called when Akonadi wants more data for a given item.
  // You can only provide the parts that have been requested but you are allowed
  // to provide all in one go

  QString avatarUrl = item.payload<KABC::Addressee>().custom( "twitterresource",
    "imageurl" );

  KJob *job = KIO::get( avatarUrl, KIO::NoReload,
    KIO::HideProgressInfo );
  connect( job, SIGNAL( result( KJob * ) ),
    SLOT( slotAvatarJobResult( KJob * ) ) );
  connect( job, SIGNAL( data( KIO::Job *, const QByteArray & ) ),
    SLOT( slotAvatarJobData( KIO::Job *, const QByteArray & ) ) );    

  m_jobs.insert( job, item );

/*
  Twitter::PersonJob *job = Twitter::OcsApi::requestPerson( item.remoteId() );

  if ( !job->exec() ) {
    qDebug() << "ERROR";
  } else {
    Twitter::Person p = job->person();
  
    KABC::Addressee addressee;
    addressee.setGivenName( p.firstName() );
    addressee.setFamilyName( p.lastName() );
    addressee.setUrl( KUrl( p.homepage() ) );
    addressee.setPhoto( KABC::Picture( p.avatar().toImage() ) );

    Item newItem( item );
    newItem.setRemoteId( p.id() );
    newItem.setPayload<KABC::Addressee>( addressee );

    itemRetrieved( newItem );
  }

*/
  return true;
}

void TwitterResource::slotAvatarJobResult( KJob *job )
{
  Akonadi::Item item = m_jobs.take( job );

  KABC::Addressee addressee = item.payload<KABC::Addressee>();
  
  if ( job->error() ) {
    qWarning() << "Error retrieving Avatar:" << job->errorText();
  } else {
    QPixmap pic;
    if ( !pic.loadFromData( m_avatarData ) ) {
      qWarning() << "Error parsing avatar image";
    } else {
      addressee.setPhoto( KABC::Picture( pic.toImage() ) );
    }
  }

  Item newItem( item );
  newItem.setPayload<KABC::Addressee>( addressee );

  itemRetrieved( newItem );
}

void TwitterResource::slotAvatarJobData( KIO::Job *, const QByteArray &data )
{
  m_avatarData.append( data );
}

void TwitterResource::aboutToQuit()
{
  // TODO: any cleanup you need to do while there is still an active
  // event loop. The resource will terminate after this method returns
}

void TwitterResource::configure( WId windowId )
{
  Q_UNUSED( windowId );

  // TODO: this method is usually called when a new resource is being
  // added to the Akonadi setup. You can do any kind of user interaction here,
  // e.g. showing dialogs.
  // The given window ID is usually useful to get the correct
  // "on top of parent" behavior if the running window manager applies any kind
  // of focus stealing prevention technique

  KMessageBox::informationWId( windowId,
    i18n("Twitter Akonadi resource ready to go") );
    
  synchronize();
}

void TwitterResource::itemAdded( const Akonadi::Item &item, const Akonadi::Collection &collection )
{
  Q_UNUSED( item );
  Q_UNUSED( collection );

  // TODO: this method is called when somebody else, e.g. a client application,
  // has created an item in a collection managed by your resource.

  // NOTE: There is an equivalent method for collections, but it isn't part
  // of this template code to keep it simple
}

void TwitterResource::itemChanged( const Akonadi::Item &item, const QSet<QByteArray> &parts )
{
  Q_UNUSED( item );
  Q_UNUSED( parts );

  // TODO: this method is called when somebody else, e.g. a client application,
  // has changed an item managed by your resource.

  // NOTE: There is an equivalent method for collections, but it isn't part
  // of this template code to keep it simple
}

void TwitterResource::itemRemoved( const Akonadi::Item &item )
{
  Q_UNUSED( item );

  // TODO: this method is called when somebody else, e.g. a client application,
  // has deleted an item managed by your resource.

  // NOTE: There is an equivalent method for collections, but it isn't part
  // of this template code to keep it simple
}

AKONADI_RESOURCE_MAIN( TwitterResource )

#include "twitterresource.moc"
