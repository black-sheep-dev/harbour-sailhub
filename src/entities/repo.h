#ifndef REPO_H
#define REPO_H

#include "node.h"

#include "user.h"

class Repo : public Node
{
    Q_OBJECT

    Q_PROPERTY(bool archived READ archived WRITE setArchived NOTIFY archivedChanged)
    Q_PROPERTY(QString defaultBranch READ defaultBranch WRITE setDefaultBranch NOTIFY defaultBranchChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool disabled READ disabled WRITE setDisabled NOTIFY disabledChanged)
    Q_PROPERTY(bool fork READ fork WRITE setFork NOTIFY forkChanged)
    Q_PROPERTY(quint32 forks READ forks WRITE setForks NOTIFY forksChanged)
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(bool hasDownloads READ hasDownloads WRITE setHasDownloads NOTIFY hasDownloadsChanged)
    Q_PROPERTY(bool hasIssues READ hasIssues WRITE setHasIssues NOTIFY hasIssuesChanged)
    Q_PROPERTY(bool hasPages READ hasPages WRITE setHasPages NOTIFY hasPagesChanged)
    Q_PROPERTY(bool hasProjects READ hasProjects WRITE setHasProjects NOTIFY hasProjectsChanged)
    Q_PROPERTY(bool hasWiki READ hasWiki WRITE setHasWiki NOTIFY hasWikiChanged)
    Q_PROPERTY(QString homepage READ homepage WRITE setHomepage NOTIFY homepageChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString licenseKey READ licenseKey WRITE setLicenseKey NOTIFY licenseKeyChanged)
    Q_PROPERTY(QString licenseName READ licenseName WRITE setLicenseName NOTIFY licenseNameChanged)
    Q_PROPERTY(QString licenseUrl READ licenseUrl WRITE setLicenseUrl NOTIFY licenseUrlChanged)
    Q_PROPERTY(QString mirrorUrl READ mirrorUrl WRITE setMirrorUrl NOTIFY mirrorUrlChanged)
    Q_PROPERTY(quint32 openIssues READ openIssues WRITE setOpenIssues NOTIFY openIssuesChanged)
    Q_PROPERTY(User* owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(bool privateRepo READ privateRepo WRITE setPrivateRepo NOTIFY privateRepoChanged)
    Q_PROPERTY(QDateTime pushedAt READ pushedAt WRITE setPushedAt NOTIFY pushedAtChanged)
    Q_PROPERTY(qreal score READ score WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(quint64 size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(quint32 stargazers READ stargazers WRITE setStargazers NOTIFY stargazersChanged)
    Q_PROPERTY(quint32 subscribers READ subscribers WRITE setSubscribers NOTIFY subscribersChanged)
    Q_PROPERTY(quint32 watchers READ watchers WRITE setWatchers NOTIFY watchersChanged)

public:
    explicit Repo(QObject *parent = nullptr);

    bool archived() const;
    QString defaultBranch() const;
    QString description() const;
    bool disabled() const;
    bool fork() const;
    quint32 forks() const;
    QString fullName() const;
    bool hasDownloads() const;
    bool hasIssues() const;
    bool hasPages() const;
    bool hasProjects() const;
    bool hasWiki() const;
    QString homepage() const;
    QString language() const;
    QString licenseKey() const;
    QString licenseName() const;
    QString licenseUrl() const;
    QString mirrorUrl() const;
    quint32 openIssues() const;
    User *owner() const;
    bool privateRepo() const;
    QDateTime pushedAt() const;
    qreal score() const;
    quint64 size() const;
    quint32 stargazers() const;
    quint32 subscribers() const;
    quint32 watchers() const;

signals:
    void archivedChanged(bool archived);
    void defaultBranchChanged(const QString &branch);
    void descriptionChanged(const QString &description);
    void disabledChanged(bool disabled);
    void forkChanged(bool fork);
    void forksChanged(quint32 forks);
    void fullNameChanged(const QString &name);
    void hasDownloadsChanged(bool hasDownloads);
    void hasIssuesChanged(bool hasIssues);
    void hasPagesChanged(bool hasPages);
    void hasProjectsChanged(bool hasProjects);
    void hasWikiChanged(bool hasWiki);
    void homepageChanged(const QString &homepage);
    void languageChanged(const QString &language);
    void licenseKeyChanged(const QString &key);
    void licenseNameChanged(const QString &name);
    void licenseUrlChanged(const QString &url);
    void mirrorUrlChanged(const QString &mirrorUrl);
    void openIssuesChanged(quint32 issues);
    void ownerChanged(User *owner);
    void privateRepoChanged(bool privateRepo);
    void pushedAtChanged(const QDateTime &timestamp);
    void scoreChanged(qreal score);
    void sizeChanged(quint64 size);
    void stargazersChanged(quint32 stargazers);
    void subscribersChanged(quint32 subscribers);
    void watchersChanged(quint32 watchers);

public slots:
    void setArchived(bool archived);
    void setDefaultBranch(const QString &branch);
    void setDescription(const QString &description);
    void setDisabled(bool disabled);
    void setFork(bool fork);
    void setForks(quint32 forks);
    void setFullName(const QString &name);
    void setHasDownloads(bool hasDownloads);
    void setHasIssues(bool hasIssues);
    void setHasPages(bool hasPages);
    void setHasProjects(bool hasProjects);
    void setHasWiki(bool hasWiki);
    void setHomepage(const QString &homepage);
    void setLanguage(const QString &language);
    void setLicenseKey(const QString &key);
    void setLicenseName(const QString &name);
    void setLicenseUrl(const QString &url);
    void setMirrorUrl(const QString &url);
    void setOpenIssues(quint32 issues);
    void setOwner(User *owner);
    void setPrivateRepo(bool privateRepo);
    void setPushedAt(const QDateTime &timestamp);
    void setScore(qreal score);
    void setSize(quint64 size);
    void setStargazers(quint32 stargazers);
    void setSubscribers(quint32 subscribers);
    void setWatchers(quint32 watchers);

private:
    bool m_archived{false};
    QString m_defaultBranch;
    QString m_description;
    bool m_disabled{false};
    bool m_fork{false};
    quint32 m_forks{0};
    QString m_fullName;
    bool m_hasDownloads{false};
    bool m_hasIssues{false};
    bool m_hasPages{false};
    bool m_hasProjects{false};
    bool m_hasWiki{false};
    QString m_homepage;
    QString m_language;
    QString m_licenseKey;
    QString m_licenseName;
    QString m_licenseUrl;
    QString m_mirrorUrl;
    quint32 m_openIssues{0};
    User* m_owner{nullptr};
    bool m_privateRepo{false};
    QDateTime m_pushedAt;
    qreal m_score{0.0};
    quint64 m_size{0};
    quint32 m_stargazers{0};
    quint32 m_subscribers{0};
    quint32 m_watchers{0};

};

#endif // REPO_H
