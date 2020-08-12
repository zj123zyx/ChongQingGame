#include "BaseScene.h"
#include "GzipUtil.h"
#include "Des.h"
#include "DataHelper.h"

BaseScene::BaseScene():_posting(false), _transaction(nullptr)
{

}

void BaseScene::post(AbstractTransaction* transaction)
{
	if (_posting == true)
		return;
	_posting = true;
	_transaction = transaction;
	string sendXml = transaction->getSendContent();
	//string sendXml = "BD0F42ED9ACBCE3436125199285BB9C853C999D23693AD74494C7E8A42AC51008284AC8540771618E493586B3C57CB3FA57926B32E43BA77B15EDF7BC903F645FEDF8B9203EDB574664CA405EDD99997008DFC75ACBE98CDCA7FBD6911BEF7F68C392C7E09FF2A85319CE532544C424BEC393A649FEE00E692C49CC30097B488903397B824227E9A5654E51CBB40D82DA4D2030855D54279CAE065347EAF5F5C65EAD9ED0F1B372295E1738393DB08F0FA6D3EC9B51747BF640A613E5E8D44378A9E6166C3F5B280015E83CD34658251856EB797CB57104971CC5077214B667855BAA6F2922A5A6CCB587F51ABBA68E3620250B14DA43F03ABC33914F52C64E4986F9E25E7FFB654435F92654575D555F410744416B6F80B08C9241D50E3E84B23702EC80260063CBB84135A0BA00D28848D655ED056D1A7F6FB049F580B924E93EB71E33308A801ED7E118D7A430B6AF67A4D2879300F759DDAB21190A35B28061B4C3130B5ED90";
	log("BaseScene::send1=%s", sendXml.c_str());
	

	unsigned char *ciphertext;
	int outSize = Des::encrypt((unsigned char*)sendXml.c_str(), &ciphertext, sendXml.size(), (unsigned char*)DES_KEY);
	//char *output = (char * ) malloc(outSize*2 + 1);
	/*char* dst = new char[outSize*2 + 1];
	for (int i = 0; i < outSize; i++) {		
		sprintf(&dst[i*2], "%02X", ciphertext[i]);
	}*/
	char* dst = DataHelper::bytesToString(ciphertext, outSize);
	free(ciphertext);
	//log("BaseScene::send2=%s", dst);

	char* enXml;
	int enSize = gzipToEnBase64(dst, outSize*2, &enXml);
	delete []dst;
	
	httpSendData(enXml, enSize);
	free(enXml);	
}

void BaseScene::httpSendData(char * postData, unsigned int size)
{
	bool isImmediate = true;

    HttpRequest* request = new HttpRequest();	//(std::nothrow)
	request->setUrl("http://61.145.116.221:8000/LotteryAgentServer/ServiceServlet");	
    request->setRequestType(HttpRequest::Type::POST);
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/x-www-form-urlencoded; charset=utf-8");
    request->setHeaders(headers);
    request->setResponseCallback(CC_CALLBACK_2(BaseScene::onHttpRequestCompleted, this));
  
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
    
    log("BaseScene::loading...");
}

void BaseScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
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
    log("BaseScene::status=%s", statusString);

    if (!response->isSucceed()) 
    {
        log("BaseScene::response failed");        
		this->onNetError(_transaction, response);
		delete _transaction;
		_transaction = nullptr;
        return;
    }
     
    std::vector<char> *buffer = response->getResponseData();
    // log("Http Test, dump data: ");
 
	char result[65535] ;
	for (unsigned int i = 0; i < buffer->size(); i++)
    {	
		sprintf(&result[i], "%c", (*buffer)[i]);
    }
	//log("BaseScene::result1=%s", result);
	char* bytes;
	int bytesSize = DataHelper::stringToBytes(result, &bytes);

	unsigned char *outbuf;
	int outSize = Des::decrypt((unsigned char*)bytes, &outbuf, bytesSize, (unsigned char*)DES_KEY);
	//log("BaseScene::result2=%s", outbuf);
	delete []bytes;
	unsigned char *resp = DeBase64ToGunzip((char*)outbuf, outSize);
	free(outbuf);
	
	//log("BaseScene::result3=%s", (char*)resp);

    if (response->getHttpRequest()->getReferenceCount() != 2)
    {
        log("BaseScene::request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
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
	delete _transaction;
	_transaction = nullptr;
	
}

int BaseScene::gzipToEnBase64(char *data, unsigned long size, char** en)
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
		//log("BaseScene::enCompress=%s", zdata);//fprintf(stdout, "nzdata:%d %s/n", nzdata, zdata);
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


unsigned char* BaseScene::DeBase64ToGunzip(char *en, unsigned int size)
{
	#define BUF_SIZE 65535
	Bytef  odata[BUF_SIZE];
	uLong nodata = BUF_SIZE;

	unsigned char* de;
	int deSize = base64Decode((unsigned char*)en, size, &de);
	//log("DeBase64=%s", de);
	
	memset(odata, 0, BUF_SIZE);		
	if(GzipUtil::gzipDecompress(de, deSize, odata, &nodata) == 0)
	{
		log("BaseScene::deCompress=%s", odata);		
	}
	free(de);
	
	return odata;
}

void BaseScene::onOK(AbstractTransaction* transaction)
{
	log("BaseScene::onOK...");
	
}

void BaseScene::onFail(AbstractTransaction* transaction)
{
	log("BaseScene::onFail...");
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
}

void BaseScene::onNetError(AbstractTransaction* transaction, HttpResponse *response)
{	
	log("BaseScene::onNetError: %s", response->getErrorBuffer());
}