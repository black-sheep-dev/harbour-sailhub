#ifndef RELEASE_H
#define RELEASE_H

#include "node.h"

#include <QDateTime>

#include "owner.h"

struct ReleaseListItem : public NodeListItem {
    ReleaseListItem() = default;
    ReleaseListItem(const QJsonObject &data);

    QDateTime createdAt;
    QString createdAtTimeSpan;
    bool isDraft{false};
    bool isLatest{false};
    bool isPrerelease{false};
};

class Release : public Node
{
    Q_OBJECT

    Q_PROPERTY(quint32 assetCount READ assetCount WRITE setAssetCount NOTIFY assetCountChanged)
    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool isDraft READ isDraft WRITE setIsDraft NOTIFY isDraftChanged)
    Q_PROPERTY(bool isLatest READ isLatest WRITE setIsLatest NOTIFY isLatestChanged)
    Q_PROPERTY(bool isPrerelease READ isPrerelease WRITE setIsPrerelease NOTIFY isPrereleaseChanged)
    Q_PROPERTY(QDateTime publishedAt READ publishedAt WRITE setPublishedAt NOTIFY publishedAtChanged)
    Q_PROPERTY(QString repository READ repository WRITE setRepository NOTIFY repositoryChanged)
    Q_PROPERTY(QString tagCommit READ tagCommit WRITE setTagCommit NOTIFY tagCommitChanged)
    Q_PROPERTY(QString tagName READ tagName WRITE setTagName NOTIFY tagNameChanged)

public:
    explicit Release(QObject *parent = nullptr);
    Release(const QJsonObject &data, QObject *parent = nullptr);

    void setData(const QJsonObject &data);

    // properties
    quint32 assetCount() const;
    Owner *author() const;
    QDateTime createdAt() const;
    QString description() const;
    bool isDraft() const;
    bool isLatest() const;
    bool isPrerelease() const;
    QDateTime publishedAt() const;
    QString repository() const;
    QString tagCommit() const;
    QString tagName() const;

signals:
    // properties
    void assetCountChanged(quint32 count);
    void authorChanged(Owner *author);
    void createdAtChanged(const QDateTime &createdAt);
    void descriptionChanged(const QString &description);
    void isDraftChanged(bool isDraft);
    void isLatestChanged(bool isLatest);
    void isPrereleaseChanged(bool isPrerelease);
    void publishedAtChanged(const QDateTime &publishedAt);
    void repositoryChanged(const QString &repository);
    void tagCommitChanged(const QString &tagCommit);
    void tagNameChanged(const QString &tagName);

public slots:
    // properties
    void setAssetCount(quint32 count);
    void setAuthor(Owner *author);
    void setCreatedAt(const QDateTime &createdAt);
    void setDescription(const QString &description);
    void setIsDraft(bool isDraft);
    void setIsLatest(bool isLatest);
    void setIsPrerelease(bool isPrerelease);
    void setPublishedAt(const QDateTime &publishedAt);
    void setRepository(const QString &repository);
    void setTagCommit(const QString &tagCommit);
    void setTagName(const QString &tagName);

private:
    // properties
    quint32 m_assetCount{0};
    Owner *m_author{nullptr};
    QDateTime m_createdAt;
    QString m_description;
    bool m_isDraft{false};
    bool m_isLatest{false};
    bool m_isPrerelease{false};
    QDateTime m_publishedAt;
    QString m_repository;
    QString m_tagCommit;
    QString m_tagName;  
};

#endif // RELEASE_H
