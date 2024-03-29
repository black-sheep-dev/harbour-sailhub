#ifndef FILE_H
#define FILE_H

#include <QObject>

class File : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(quint64 size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(bool truncated READ truncated WRITE setTruncated NOTIFY truncatedChanged)
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)

public:
    enum Type {
        Unsupported,
        Binary,
        Image,
        Markdown,
        Text
    };
    Q_ENUM(Type)

    explicit File(QObject *parent = nullptr);

    const QString &content() const;
    const QString &name() const;
    quint64 size() const;
    bool truncated() const;
    Type type() const;

signals:
    void contentChanged();
    void nameChanged();
    void sizeChanged();
    void truncatedChanged();
    void typeChanged();

public slots:
    void setContent(const QString &content);
    void setName(const QString &name);
    void setSize(quint64 size);
    void setTruncated(bool truncated);
    void setType(File::Type type);

private:
    QString m_content;
    QString m_name;
    quint64 m_size{0};
    bool m_truncated{false};
    Type m_type{Unsupported};
};

#endif // FILE_H
