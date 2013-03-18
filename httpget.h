
#ifndef HTTPGET_H
#define HTTPGET_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>

#include "const_int.h"

#if (! defined (HTTPGET_MODULE))
#error "HTTPGET_MODULE should be defined"
#endif

#if HTTPGET_MODULE==1

class HttpGet : public QObject
{
    Q_OBJECT

public:
    HttpGet (const QString& url, QObject* parent = 0);
    void startRequest(QUrl url);
    QString& get_string (void);

private slots:
    void httpFinished (void);
    void httpReadyRead(void);

private:
    QUrl url;
    QNetworkAccessManager nam;
    QNetworkReply *reply;
    QString str;
};

#endif //HTTPGET_MODULE

#endif
