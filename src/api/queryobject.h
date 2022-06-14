#ifndef QUERYOBJECT_H
#define QUERYOBJECT_H

#include <QObject>

#include <QJsonObject>

class QueryObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint8 error READ error WRITE setError NOTIFY errorChanged)
    Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged)
    Q_PROPERTY(bool ready READ ready WRITE setReady NOTIFY readyChanged)
    Q_PROPERTY(QJsonObject result READ result WRITE setResult NOTIFY resultChanged)
    Q_PROPERTY(QJsonObject variables READ variables WRITE setVariables NOTIFY variablesChanged)

public:
    enum Error {
        ErrorNone,
        ErrorInvalidData,
        ErrorNotFound,
        ErrorTimeout,
        ErrorUnauthorized,
        ErrorUndefined
    };
    Q_ENUM(Error)

    explicit QueryObject(QObject *parent = nullptr);

    // properties
    quint8 error() const;
    void setError(quint8 error);

    const QString &query() const;
    void setQuery(const QString &query);

    bool ready() const;
    void setReady(bool ready = true);

    const QJsonObject &result() const;
    void setResult(const QJsonObject &result);

    const QJsonObject &variables() const;
    void setVariables(const QJsonObject &variables);

signals:
    // properties
    void errorChanged();
    void queryChanged();
    void readyChanged();
    void resultChanged();
    void variablesChanged();

public slots:
    void onResultAvailable();

private:
    // properties
    quint8 m_error{ErrorNone};
    QString m_query;
    bool m_ready{false};
    QJsonObject m_result;
    QJsonObject m_variables;
};

#endif // QUERYOBJECT_H
