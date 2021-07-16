#ifndef LABELSMODEL_H
#define LABELSMODEL_H

#include "paginationmodel.h"

#include "src/entities/label.h"

class LabelsModel : public PaginationModel
{
    Q_OBJECT
public:
    enum LabelRoles {
        ColorRole           = Qt::UserRole + 1,
        CreatedAtRole,
        NameRole
    };
    Q_ENUM(LabelRoles)

    explicit LabelsModel(QObject *parent = nullptr);
    ~LabelsModel() override;

    void addLabels(const QList<LabelListItem> &labels);
    void setLabels(const QList<LabelListItem> &labels);

private:
    QList<LabelListItem> m_labels;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // PaginationModel interface
public:
    void clear() override;
    void parseQueryResult(const QJsonObject &data) override;
    GraphQLQuery query() const override;

    // PaginationModel interface
public:
    QString sortField() const override;
};

#endif // LABELSMODEL_H
