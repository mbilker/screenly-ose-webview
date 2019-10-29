#pragma once

#include <QNetworkCookie>
#include <QNetworkCookieJar>

class CookieJar : public QNetworkCookieJar
{
public:
    explicit CookieJar(QObject* parent);

    ~CookieJar();

private:
    virtual bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url) override;

    void save();
};
