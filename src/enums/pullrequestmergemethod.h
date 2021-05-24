#ifndef PULLREQUESTMERGEMETHOD_H
#define PULLREQUESTMERGEMETHOD_H

#include <QObject>

class PullRequestMergeMethod {
    Q_GADGET
public:
    enum Method {
        Unknown,
        Merge,
        Rebase,
        Squash
    };
    Q_ENUM(Method)

    static quint8 fromString(const QString &str) {
        if (str == QLatin1String("MERGE")) {
            return PullRequestMergeMethod::Merge;
        } else if (str == QLatin1String("REBASE")) {
            return PullRequestMergeMethod::Rebase;
        } else if (str == QLatin1String("SQUASH")) {
            return PullRequestMergeMethod::Squash;
        }

        return PullRequestMergeMethod::Unknown;
    }

    static QString toString(quint8 reason){
        switch (reason) {
        case PullRequestMergeMethod::Merge:
            return QStringLiteral("MERGE");

        case PullRequestMergeMethod::Rebase:
            return QStringLiteral("REBASE");

        case PullRequestMergeMethod::Squash:
            return QStringLiteral("SQUASH");

        default:
            return QString();
        }
    }
};

#endif // PULLREQUESTMERGEMETHOD_H
