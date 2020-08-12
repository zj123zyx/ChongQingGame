#ifndef _BASICSCENE_H_
#define _BASICSCENE_H_

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "AbstractTransaction.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::network;

#define DES_KEY "12345678"/*"H3b2e6C%"*/

class BaseScene : public Scene
{
	
public:
	CREATE_FUNC(BaseScene);

	BaseScene();

	void post(AbstractTransaction* transaction);

protected:
	virtual void onOK(AbstractTransaction* transaction);

	virtual void onFail(AbstractTransaction* transaction);

	virtual void onNetError(AbstractTransaction* transaction, HttpResponse *response);

private:
	void httpSendData(char * enData, unsigned int size);

	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);

	int gzipToEnBase64(char *data, unsigned long size, char** en);

	unsigned char* DeBase64ToGunzip(char *en, unsigned int size);

private:
	AbstractTransaction* _transaction;

	bool _posting;

};

#endif
