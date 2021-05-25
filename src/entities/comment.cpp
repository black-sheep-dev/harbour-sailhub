#include "comment.h"

#include <QJsonObject>

#include "src/api/keys.h"

Comment::Comment(QObject *parent) :
    Interactable(parent)
{

}

Comment::Comment(const QJsonObject &data, QObject *parent) :
    Interactable(parent)
{
    setData(data);
}

void Comment::setData(const QJsonObject &data)
{
    Interactable::setData(data);

    constexpr int max = 160;
    const QString body = data.value(ApiKey::BODY_TEXT).toString();

    if (body.length() <= max) {
        setBodyExcerpt(body);
    } else {
        const QString excerpt = body.mid(0, max);
        setBodyExcerpt(
                    excerpt.mid(0, excerpt.lastIndexOf(' '))
                    .simplified()
                    .append(QStringLiteral("...")));
    }
}

QString Comment::bodyExcerpt() const
{
    return m_bodyExcerpt;
}

void Comment::setBodyExcerpt(const QString &excerpt)
{
    if (m_bodyExcerpt == excerpt)
        return;

    m_bodyExcerpt = excerpt;
    emit bodyExcerptChanged(m_bodyExcerpt);
}


