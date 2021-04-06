#include "file.h"

File::File(QObject *parent) :
    QObject(parent)
{

}

QString File::content() const
{
    return m_content;
}

QString File::name() const
{
    return m_name;
}

quint64 File::size() const
{
    return m_size;
}

bool File::truncated() const
{
    return m_truncated;
}

File::Type File::type() const
{
    return m_type;
}

void File::setContent(const QString &content)
{
    if (m_content == content)
        return;

    m_content = content;
    emit contentChanged(m_content);
}

void File::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void File::setSize(quint64 size)
{
    if (m_size == size)
        return;

    m_size = size;
    emit sizeChanged(m_size);
}

void File::setTruncated(bool truncated)
{
    if (m_truncated == truncated)
        return;

    m_truncated = truncated;
    emit truncatedChanged(m_truncated);
}

void File::setType(File::Type type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}
