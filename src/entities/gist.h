#ifndef GIST_H
#define GIST_H

#include "node.h"

#include <QDateTime>

#include "owner.h"

struct GistListItem {
    quint32 commentCount{0};
    QDateTime createdAt;
    QString description;
    quint32 fileCount{0};
    quint32 forkCount{0};
    bool isPublic{false};
    QString nodeId;
    QString ownerLogin;
    QString ownerAvatar;
    QDateTime pushedAt;
    quint32 stargazerCount{0};
    QDateTime updatedAt;
};

class Gist : public Node
{
    Q_OBJECT

    Q_PROPERTY(quint32 commetCount READ commetCount WRITE setCommetCount NOTIFY commetCountChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(quint32 fileCount READ fileCount WRITE setFileCount NOTIFY fileCountChanged)
    Q_PROPERTY(quint32 forkCount READ forkCount WRITE setForkCount NOTIFY forkCountChanged)
    Q_PROPERTY(bool isFork READ isFork WRITE setIsFork NOTIFY isForkChanged)
    Q_PROPERTY(bool isPublic READ isPublic WRITE setIsPublic NOTIFY isPublicChanged)
    Q_PROPERTY(Owner* owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(QDateTime pushedAt READ pushedAt WRITE setPushedAt NOTIFY pushedAtChanged)
    Q_PROPERTY(quint32 stargazerCount READ stargazerCount WRITE setStargazerCount NOTIFY stargazerCountChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(bool viewerHasStarred READ viewerHasStarred WRITE setViewerHasStarred NOTIFY viewerHasStarredChanged)

public:
    explicit Gist(QObject *parent = nullptr);

    quint32 commetCount() const;
    QDateTime createdAt() const;
    QString description() const;
    quint32 fileCount() const;
    quint32 forkCount() const;
    bool isFork() const;
    bool isPublic() const;
    Owner *owner() const;
    QDateTime pushedAt() const;
    quint32 stargazerCount() const;
    QDateTime updatedAt() const;
    bool viewerHasStarred() const;

signals:
    void commetCountChanged(quint32 count);
    void createdAtChanged(const QDateTime &createdAt);
    void descriptionChanged(const QString &description);
    void fileCountChanged(quint32 count);
    void forkCountChanged(quint32 count);
    void isForkChanged(bool isFork);
    void isPublicChanged(bool isPublic);
    void ownerChanged(Owner* owner);
    void pushedAtChanged(const QDateTime &pushedAt);
    void stargazerCountChanged(quint32 count);
    void updatedAtChanged(const QDateTime &updatedAt);
    void viewerHasStarredChanged(bool starred);

public slots:
    void setCommetCount(quint32 count);
    void setCreatedAt(const QDateTime &createdAt);
    void setDescription(const QString &description);
    void setFileCount(quint32 count);
    void setForkCount(quint32 count);
    void setIsFork(bool isFork);
    void setIsPublic(bool isPublic);
    void setOwner(Owner *owner);
    void setPushedAt(const QDateTime &pushedAt);
    void setStargazerCount(quint32 count);
    void setUpdatedAt(const QDateTime &updatedAt);
    void setViewerHasStarred(bool starred);

private:
    quint32 m_commetCount{0};
    QDateTime m_createdAt;
    QString m_description;
    quint32 m_fileCount{0};
    quint32 m_forkCount{0};
    bool m_isFork{false};
    bool m_isPublic{false};
    Owner* m_owner{nullptr};
    QDateTime m_pushedAt;
    quint32 m_stargazerCount{0};
    QDateTime m_updatedAt;
    bool m_viewerHasStarred{false};
};

#endif // GIST_H
