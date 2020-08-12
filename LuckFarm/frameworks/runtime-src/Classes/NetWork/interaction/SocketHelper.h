#ifndef _SOCKET_HELPER_H_
#define _SOCKET_HELPER_H_

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "AbstractTransaction.h"
#include "ODSocket.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::network;

#define DES_KEY "12345678"/*"H3b2e6C%"*/

class SocketHelper
{
	
public:
	
	SocketHelper();
	~SocketHelper();
	void post(AbstractTransaction* transaction);

	typedef std::function<void(AbstractTransaction*)> onPostListener;

	typedef std::function<void(string type, int errorCode, const char* errorReason)> onNetErrorListener;

	void addOnOKListener(const onPostListener &callback) {
		_onOKCallback = callback;
	}

	void addOnFailListener(const onPostListener &callback) {
		_onFailCallback = callback;
	}

	void addOnNetErrorListener(const onNetErrorListener &callback) {
		_onNetErrorCallback = callback;
	}

	void addOnFinishedListener(const onPostListener &callback) {
		_onFinishedCallback = callback;
	}

protected:
	virtual void onOK(AbstractTransaction* transaction);

	virtual void onFail(AbstractTransaction* transaction);

	virtual void onNetError(string type, int errorCode, char* errorReason);

	virtual void onFinished(AbstractTransaction* transaction);

private:
	void httpSendData(char * enData, unsigned int size);

	void onHttpRequestCompleted(char * enData, unsigned int inSize, int errorCode, char* errorReason);

	int gzipToEnBase64(char *data, unsigned long size, char** en);

	unsigned char* DeBase64ToGunzip(char *en, unsigned int size);

private:
	AbstractTransaction* _transaction;

	bool _posting; // 在此不起作为

	onPostListener _onOKCallback;
	onPostListener _onFailCallback;
	onNetErrorListener _onNetErrorCallback;
	onPostListener _onFinishedCallback;

};

#endif
