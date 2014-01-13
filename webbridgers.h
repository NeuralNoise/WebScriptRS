#ifndef WEBBRIDGERS_H
#define WEBBRIDGERS_H

#include <QObject>
#include <QStringList>
#include<QVariantMap>
#include <QPixmap>
#include <retroshare/rsfiles.h>
#include <util/TokenQueue.h>

#ifdef EMBPYTHON
#include "embpyqt/embeddedpyqt.h"
#endif
#if defined(WIN32) || defined(MINGW) || defined(__CYGWIN__)
#include "qjsonrpcservice.h"
#else
#include "qjsonrpc/qjsonrpcservice.h"
#endif

class p3JsonRS;

/*this class is passed to JS as "bridge"*/
class WebBridgeRS : public QJsonRpcService, public TokenResponse
{

    Q_OBJECT
    Q_CLASSINFO("serviceName", "bridge")
public:
    explicit WebBridgeRS(QObject *parent = 0);
    void pushMsgToJs(QVariantMap message);
    p3JsonRS *p3service;
    QMap<QString,QPixmap> avatars;
#ifdef EMBPYTHON
    EmbeddedPyQt *embpyqt;
#endif
#ifdef BRIDGEGXS
	TokenQueue *mPostedQueue;
#endif

//the public slots are exposed to JS
public slots:

#ifdef EMBPYTHON
    void runPython(QString text);
    void runPythonFile(QString fileName);
#endif
    QVariantList getChannelList();
    QVariantList getForumThreadList(QString flid);
    QVariantList getForumThreadMsgList(QString flid, QString msgid);
    QVariantList getForums();
    QVariantMap getForumMessage(QString flid, QString msgid);
    QString getOwnId();
    QString getDownloadDirectory();
    QVariantMap searchKeywords(const QString& keywords, QVariantMap searchOptions);
    //QString processLink(QString url);
    void processLinks(QStringList urls);

    void broadcastMessage(QString msg);
    void sendMessage(QString peer, QString msg);
    QVariantMap getPeers();
    QVariantMap downloadFile(QString qname, QString qhash, int qsize);
    void downloadURL(QString url);
    void broadcastToRS(QString msg);
    //QVariantList getPublicChatQueue();

    QVariantMap fileDetails(QString qhash);
    void newTabAt(QString url);
#ifdef BRIDGEGXS
    QVariantList getPostedList();
#endif
	QStringList getFriendList();
	QStringList getGPGAllList();
	QString getGPGId(QString inId);
    QStringList getOnlineList();
    QVariantMap getPeerDetails(QString ssl_id);
    QString getPeerName(QString ssl_id);
    QPixmap getAvatarDetails(QString ssl_id);
	QStringList getDiscGPGFriends(QString gpg_id);
	void writeString(QString fname, QString data);
private slots:
    void onUrlDownloaded();
    void onDownloadComplete(QString hash);
    void gotTurtleSearchResult(qulonglong search_id,FileDetail file);
private:

	void loadRequest(const TokenQueue *queue, const TokenRequest &req);
signals:
    void msgPush(QVariantMap message);
    void urlDownloaded(QString path, QString url);
    void rsDownloaded(QVariantMap);
    void rsTurtleResult(QVariantMap);
    void newTabUrl(QString url);

};

extern WebBridgeRS *eBridge;

#endif // WEBBRIDGERS_H
