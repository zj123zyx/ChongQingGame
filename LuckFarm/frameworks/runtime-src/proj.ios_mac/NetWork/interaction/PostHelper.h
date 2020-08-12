#ifndef _POST_HELPER_H_
#define _POST_HELPER_H_

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "../trans/AbstractTransaction.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::network;

#define DES_KEY "12345678"/*"H3b2e6C%"*/

class PostHelper
{
	
public:
	
	PostHelper();
	~PostHelper();
	void post(AbstractTransaction* transaction);

	typedef std::function<void(AbstractTransaction*)> onPostListener;

	typedef std::function<void(AbstractTransaction*, const char*)> onNetErrorListener;

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

	virtual void onNetError(AbstractTransaction* transaction, HttpResponse *response);

	virtual void onFinished(AbstractTransaction* transaction);

private:
	void httpSendData(char * enData, unsigned int size);

	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);

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
