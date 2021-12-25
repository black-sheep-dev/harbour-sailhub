#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QAbstractListModel>

#include <QVariantList>

#include "src/api/graphqlquery.h"

class BaseModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)
    Q_PROPERTY(quint8 modelType READ modelType WRITE setModelType NOTIFY modelTypeChanged)
    Q_PROPERTY(QByteArray uuid READ uuid WRITE setUuid NOTIFY uuidChanged)

public:
    explicit BaseModel(QObject *parent = nullptr);

    const QString &identifier() const;
    bool loading() const;
    quint8 modelType() const;
    const QByteArray &uuid() const;

signals:
    void identifierChanged(const QString &identifier);
    void loadingChanged(bool loading);
    void modelTypeChanged(quint8 modelType);
    void uuidChanged(const QByteArray &uuid);
    void variablesChanged(const QVariantList &variables);

public slots:
    void setIdentifier(const QString &identifier);
    void setLoading(bool loading);
    void setModelType(quint8 modelType);
    void setUuid(const QByteArray &uuid);

private:
    QString m_identifier;
    bool m_loading{false};
    quint8 m_modelType{0};
    QByteArray m_uuid;

    // virtual
public:
    virtual void clear() = 0;
    virtual void parseQueryResult(const QJsonObject &data);
    virtual GraphQLQuery query() const;
};

#endif // BASEMODEL_H
