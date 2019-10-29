#include <QSettings>

#include "cookiejar.h"

CookieJar::CookieJar(QObject* parent) : QNetworkCookieJar(parent)
{
    QSettings settings;
    QByteArray data = settings.value("cookies").toByteArray();

    const QList<QNetworkCookie> savedCookies = QNetworkCookie::parseCookies(data);
    for (const QNetworkCookie &cookie : savedCookies) {
        this->insertCookie(cookie);
    }
}

CookieJar::~CookieJar()
{
    this->save();
}

bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url) {
    auto cookiesSet = QNetworkCookieJar::setCookiesFromUrl(cookieList, url);

    if (cookiesSet) {
        this->save();
    }

    return cookiesSet;
}

void CookieJar::save()
{
    QByteArray data;

    const QList<QNetworkCookie> cookies = this->allCookies();
    for (const QNetworkCookie &cookie : cookies) {
        if (!cookie.isSessionCookie()) {
            data.append(cookie.toRawForm());
            data.append("\n");
        }
    }

    QSettings settings;
    settings.setValue("cookies", data);
}
