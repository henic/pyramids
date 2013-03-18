// --------------------------------------------------------------------
// httpget.cpp
// --------------------------------------------------------------------

#include <QObject>
#include <QDebug>
#include <QTextDocument>

#include "httpget.h"

#if HTTPGET_MODULE==1

HttpGet::HttpGet (const QString& url_str, QObject* parent)
    : QObject (parent)
{
    str.clear();
    startRequest (QUrl (url_str));
}

void HttpGet::startRequest(QUrl url)
{
    qDebug() << "HttpGet::startRequest:";
    if (url.isEmpty()) {
        qCritical() << "HttpGet: empty url passed";
        return;
    }
    if (!url.isValid()) {
        qCritical() << "HttpGet: invalud url '" << url.toString() << "' passed";
        return;
    }
    reply = nam.get(QNetworkRequest(url));
    connect(reply, SIGNAL (finished   ()),
                     this,  SLOT   (httpFinished ()));
    connect(reply, SIGNAL (readyRead  ()),
                     this,  SLOT   (httpReadyRead()));
}

static
QString HtmlToText (QString Str)
{
    const QString pattern_to_skip = "Get Insulted Online!";

    QTextDocument doc;
    doc.setHtml(Str);
    QString result = doc.toPlainText();

    int i = result.indexOf(pattern_to_skip);
    if (i>0) result = result.mid(i+pattern_to_skip.size());
    result = result.trimmed ();
    for (int i=0; i<result.size(); i++)
        if ((int)result.at(i).toAscii()==0) {
            result = result.left (i);
            break;
        }
    return result;
}

void HttpGet::httpFinished (void)
{
    QVariant redirectionTarget =
               reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) { // message about download fail
        return;
    }
    else
    if (!redirectionTarget.isNull()) {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());
        url = newUrl;
        reply->deleteLater();
        startRequest(url);
        return;
    } else {
        QString result = HtmlToText (str);
        qDebug() << result;
    }

    reply->deleteLater();
    reply = 0;
}

void HttpGet::httpReadyRead (void)
{
    str += reply->readAll();
}

QString& HttpGet::get_string (void) {return str;}

#endif //HTTPGET_MODULE
