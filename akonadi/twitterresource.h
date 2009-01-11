#ifndef TWITTERRESOURCE_H
#define TWITTERRESOURCE_H

#include <akonadi/resourcebase.h>

#include <kio/job.h>

class TwitterResource : public Akonadi::ResourceBase,
                           public Akonadi::AgentBase::Observer
{
  Q_OBJECT

  public:
    TwitterResource( const QString &id );
    ~TwitterResource();

  public Q_SLOTS:
    virtual void configure( WId windowId );

  protected Q_SLOTS:
    void retrieveCollections();
    void retrieveItems( const Akonadi::Collection &col );
    bool retrieveItem( const Akonadi::Item &item, const QSet<QByteArray> &parts );

    void slotUserListResult( KJob *j );

    void slotAvatarJobResult( KJob *job );
    void slotAvatarJobData( KIO::Job *job, const QByteArray &data );

  protected:
    virtual void aboutToQuit();

    virtual void itemAdded( const Akonadi::Item &item, const Akonadi::Collection &collection );
    virtual void itemChanged( const Akonadi::Item &item, const QSet<QByteArray> &parts );
    virtual void itemRemoved( const Akonadi::Item &item );

  private:
    QByteArray m_avatarData;
    QMap<KJob *,Akonadi::Item> m_jobs;
};

#endif
