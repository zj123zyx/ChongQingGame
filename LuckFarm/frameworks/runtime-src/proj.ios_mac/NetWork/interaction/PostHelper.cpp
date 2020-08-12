#include "PostHelper.h"
#include "../util/GzipUtil.h"
#include "../util/Des.h"
#include "../helper/DataHelper.h"

PostHelper::PostHelper():_posting(false), _transaction(nullptr),
	_onOKCallback(nullptr),
	_onFailCallback(nullptr),
	_onNetErrorCallback(nullptr),
	_onFinishedCallback(nullptr)
{

}
PostHelper::~PostHelper()
{
	log("~PostHelper()");
}

void PostHelper::post(AbstractTransaction* transaction)
{
	if (_posting == true)
		return;
	_posting = true;
	_transaction = transaction;
	string sendXml = transaction->getSendContent();
	log("PostHelper::send1=%s", sendXml.c_str());
	

	unsigned char *ciphertext;
	int outSize = Des::encrypt((unsigned char*)sendXml.c_str(), &ciphertext, sendXml.size(), (unsigned char*)DES_KEY);
	//char *output = (char * ) malloc(outSize*2 + 1);
	/*char* dst = new char[outSize*2 + 1];
	for (int i = 0; i < outSize; i++) {		
		sprintf(&dst[i*2], "%02X", ciphertext[i]);
	}*/
	char* dst = DataHelper::bytesToString(ciphertext, outSize); 
	free(ciphertext);
	//log("PostHelper::send2=%s", dst);

	char* enXml;
	int enSize = gzipToEnBase64(dst, outSize*2, &enXml); // dst size = 2 * outSize
	delete []dst;
	
	httpSendData(enXml, enSize);
	free(enXml);	
}

void PostHelper::httpSendData(char * postData, unsigned int size)
{
	bool isImmediate = true;

    HttpRequest* request = new HttpRequest();	//(std::nothrow) 当ip错时不会运行到onHttpRequestCompleted
	request->setUrl("http://61.145.116.221:8000/LotteryAgentServer/ServiceServlet");
	//request->setUrl("http://192.168.1.41:8088/LotteryAgentServer/ServiceServlet");
    request->setRequestType(HttpRequest::Type::POST);
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/x-www-form-urlencoded; charset=utf-8");
    request->setHeaders(headers);
    request->setResponseCallback(CC_CALLBACK_2(PostHelper::onHttpRequestCompleted, this));
  
	request->setRequestData(postData, size);

	HttpClient * httpClient = HttpClient::getInstance();
	httpClient->setTimeoutForConnect(30);
	httpClient->setTimeoutForRead(20);
	request->setTag(_transaction->getType().c_str());
    if (isImmediate)
    {    
        httpClient->sendImmediate(request);		
    }
	else
    {
        httpClient->send(request);
    }
    request->release();
    
    log("PostHelper::loading...");
}

void PostHelper::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	_posting = false;
    /*if (!response)
    {
		log("!response");
		this->onNetError(_transaction, response);
		delete _transaction;
		_transaction = nullptr;
        return;
    }*/
    
    // You can get original request type from: response->request->reqType
    /*if (0 != strlen(response->getHttpRequest()->getTag())) 
    {
        log("%s completed", response->getHttpRequest()->getTag());
    }*/
    
    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("PostHelper::status=%s", statusString);

    if (!response->isSucceed()) 
    {
        log("PostHelper::response failed");        
		this->onNetError(_transaction, response);
		this->onFinished(_transaction);
        return;
    }
     
    std::vector<char> *buffer = response->getResponseData();
    // log("Http Test, dump data: ");
 
	char result[65535] ;
	for (unsigned int i = 0; i < buffer->size(); i++)
    {	
		sprintf(&result[i], "%c", (*buffer)[i]);
    }
	//log("PostHelper::result1=%s", result);
	char* bytes;
	int bytesSize = DataHelper::stringToBytes(result, &bytes);

	unsigned char *outbuf;
	int outSize = Des::decrypt((unsigned char*)bytes, &outbuf, bytesSize, (unsigned char*)DES_KEY);
	//log("PostHelper::result2=%s", outbuf);
	delete []bytes;
	unsigned char *resp = DeBase64ToGunzip((char*)outbuf, outSize);
	free(outbuf);
	
	//log("PostHelper::result3=%s", (char*)resp);

    if (response->getHttpRequest()->getReferenceCount() != 2)
    {
        log("PostHelper::request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
    }

	string revXml((char*)resp);
	_transaction->handleXml(const_cast<char*>(revXml.c_str())); // 必须要string,不可char*

	if (_transaction->getResponseCode() == "000000")
	{			
		this->onOK(_transaction);
	}
	else {
		this->onFail(_transaction);		
	}
	this->onFinished(_transaction);

	
}

int PostHelper::gzipToEnBase64(char *data, unsigned long size, char** en)
{	
	#define BUF_SIZE 65535
	
	uLong ndata = size;	
	Bytef zdata[BUF_SIZE];
	uLong nzdata = BUF_SIZE;
	
	memset(zdata, 0, BUF_SIZE); // 将数组里的元素全部初始化为0, 内容置为0，也就是清空
	//char* en;	
	int enSize = 0;
	char* temp;
	if(GzipUtil::gzipCompress((Bytef *)data, ndata, zdata, &nzdata) == 0)
	{
		//log("PostHelper::enCompress=%s", zdata);//fprintf(stdout, "nzdata:%d %s/n", nzdata, zdata);
		//log("encompress.size = %d", nzdata);	
		enSize = base64Encode(zdata, nzdata, &temp);
		//free(zdata); 释放Invalid address specified to RtlValidateHeap
		
		//log("EnBase64=%s", temp);
		*en = new char[enSize];
		memcpy(*en, temp, enSize);
		free(temp);
	}
	
	return enSize;
}


unsigned char* PostHelper::DeBase64ToGunzip(char *en, unsigned int size)
{
	#define BUF_SIZE 65535
	Bytef  odata[BUF_SIZE];
	uLong nodata = BUF_SIZE;

	unsigned char* de;
	int deSize = base64Decode((unsigned char*)en, size, &de);
	log("DeBase64=%s", de);
	
	memset(odata, 0, BUF_SIZE);		
	if(GzipUtil::gzipDecompress(de, deSize, odata, &nodata) == 0)
	{
		log("PostHelper::deCompress=%s", odata);		
	}
	free(de);
	
	return odata;
}

void PostHelper::onOK(AbstractTransaction* transaction)
{
	log("PostHelper::onOK...");
	if(_onOKCallback)
		_onOKCallback(transaction);
}

void PostHelper::onFail(AbstractTransaction* transaction)
{
	log("PostHelper::onFail...");
	if (transaction->getResponseCode() == "100105") //用户验证失败
	{

	}
	else if (transaction->getResponseCode() == "100102") //用户余额不足
	{

	}
	else if (transaction->getResponseCode() == "300111") //奖期未开售或已过截止时间
	{

	}
	else if (transaction->getResponseCode() == "300121" || transaction->getResponseCode() == "300110") //无未完成的票
	{

	}	
	else if (transaction->getResponseCode() == "100302") //游戏客户端版本与服务器不匹配
	{

	}
	if(_onFailCallback)
		_onFailCallback(transaction);
}

void PostHelper::onNetError(AbstractTransaction* transaction, HttpResponse *response)
{	
	log("PostHelper::onNetError: %s", response->getErrorBuffer());
	if(_onNetErrorCallback)
		_onNetErrorCallback(transaction, response->getErrorBuffer());
}

void PostHelper::onFinished(AbstractTransaction* transaction)
{
	log("PostHelper::onFinished...");
	if(_onFinishedCallback)
		_onFinishedCallback(transaction);

	delete _transaction;
	_transaction = nullptr;
	
	delete this;
}
