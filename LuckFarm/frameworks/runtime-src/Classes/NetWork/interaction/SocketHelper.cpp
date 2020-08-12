#include "SocketHelper.h"
#include "GzipUtil.h"
#include "Des.h"
#include "DataHelper.h"

SocketHelper::SocketHelper():_posting(false), _transaction(nullptr),
	_onOKCallback(nullptr),
	_onFailCallback(nullptr),
	_onNetErrorCallback(nullptr),
	_onFinishedCallback(nullptr)
{

}
SocketHelper::~SocketHelper()
{
	log("~SocketHelper()");
}

void SocketHelper::post(AbstractTransaction* transaction)
{
	if (_posting == true)
		return;
	_posting = true;
	_transaction = transaction;
	string sendXml = transaction->getSendContent();
	//char* sendXml1 = "BD0F42ED9ACBCE3436125199285BB9C853C999D23693AD74494C7E8A42AC51008284AC8540771618E493586B3C57CB3FA57926B32E43BA77B15EDF7BC903F645FEDF8B9203EDB574664CA405EDD99997008DFC75ACBE98CDCA7FBD6911BEF7F68C392C7E09FF2A85319CE532544C424BEC393A649FEE00E692C49CC30097B488903397B824227E9A5654E51CBB40D82DA4D2030855D54279CAE065347EAF5F5C65EAD9ED0F1B372295E1738393DB08F0FA6D3EC9B51747BF640A613E5E8D44378A9E6166C3F5B280015E83CD34658251856EB797CB57104971CC5077214B667855BAA6F2922A5A6CCB587F51ABBA68E3620250B14DA43F03ABC33914F52C64E4986F9E25E7FFB654435F92654575D555F410744416B6F80B08C9241D50E3E84B23702EC80260063CBB84135A0BA00D28848D655ED056D1A7F6FB049F580B924E93EB71E33308A801ED7E118D7A430B6AF67A4D2879300F759DDAB21190A35B28061B4C3130B5ED90";
	log("SocketHelper::send1=%s", sendXml.c_str());
	

	unsigned char *ciphertext;
	int outSize = Des::encrypt((unsigned char*)sendXml.c_str(), &ciphertext, sendXml.size(), (unsigned char*)DES_KEY);
	
	char* dst = DataHelper::bytesToString(ciphertext, outSize);
	free(ciphertext);
	//log("SocketHelper::send2=%s", dst);

	char* enXml;
	int enSize = gzipToEnBase64(dst, outSize*2, &enXml); // dst size = 2 * outSize
	delete []dst;
	
	log("thread.main=%d", std::this_thread::get_id());
	//httpSendData(enXml, enSize);
	//char* hello = "hello";std::thread t1(&SocketHelper::httpSendData, this, hello, 5);  
	std::thread t1(&SocketHelper::httpSendData, this, enXml, enSize);  
	t1.detach();

	//free(enXml);	
	log("SocketHelper::loading...");
}

void SocketHelper::httpSendData(char * postData, unsigned int size)
{	
	char* recvDataBuf = nullptr;
	int recvSize = 0;
	int errorCode = 0;
	char* errorReason = nullptr;

	int test = size;
	log("thread.SOCKET=%d", std::this_thread::get_id());
	ODSocket mSocket;
	mSocket.Init();
	bool status = mSocket.Create(AF_INET,SOCK_STREAM,0);
	if (status == true) {
		log("SocketHelper::create ok...");
		bool flag = mSocket.Connect("61.145.116.221", 9988);
		//bool flag = mSocket.Connect("192.168.1.53", 57958);
		if (flag == true) {
			 log("SocketHelper::connect ok...size=%d", size);
			 char buf[4];   
			 memcpy(buf, &size, 4);				 
			 mSocket.Send(buf, 4, 0);		 
			 mSocket.Send(postData, size, 0);
			 
			 log("SocketHelper::send ok....");		
			 char recvSizeBuf[4];			
			 mSocket.Recv(recvSizeBuf, 4);
			 memcpy(&recvSize, recvSizeBuf, 4);  
			 log("recvSize=%d", recvSize);

			 recvDataBuf = new char[recvSize];
			 mSocket.Recv(recvDataBuf, recvSize, 0);
			 //log("recvData=%s", recvDataBuf);
			 free(postData);
			// onHttpRequestCompleted(recvDataBuf, recvSize, 0, nullptr);
			 log("recvOK");
	
		} else {
			 log("SocketHelper::connect fail...");
			 errorCode = 1;
			 errorReason = "connect fail";
			 //onHttpRequestCompleted(nullptr, 0, 1, "connect fail");
		}
		mSocket.Close();
	} else {
		log("SocketHelper::socket create fail...");
		errorCode = 2;
		errorReason = "socket create fail";
		//onHttpRequestCompleted(nullptr, 0, 2, "socket create fail");
	}

    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->performFunctionInCocosThread([=](){
		log("thread.scheduler=%d", std::this_thread::get_id());
		onHttpRequestCompleted(recvDataBuf, recvSize, errorCode, errorReason);
    });
}

void SocketHelper::onHttpRequestCompleted(char * result, unsigned int inSize, int errorCode, char* errorReason)
{
	_posting = false;
   
	if (errorCode != 0) 
    {
        log("SocketHelper::response failed");        
		this->onNetError(_transaction->getType(), errorCode, errorReason);
		this->onFinished(_transaction);
        return;
    }
       
	//log("SocketHelper::result1=%s", result);
	char* bytes;
	int bytesSize = DataHelper::stringToBytes(result, &bytes, inSize);
	delete []result;
	unsigned char *outbuf;
	int outSize = Des::decrypt((unsigned char*)bytes, &outbuf, bytesSize, (unsigned char*)DES_KEY);
	//log("SocketHelper::result2=%s", outbuf);
	delete []bytes;
	unsigned char *resp = DeBase64ToGunzip((char*)outbuf, outSize);
	free(outbuf);
	
	log("SocketHelper::result3=%s", (char*)resp);

   

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

int SocketHelper::gzipToEnBase64(char *data, unsigned long size, char** en)
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
		//log("SocketHelper::enCompress=%s", zdata);//fprintf(stdout, "nzdata:%d %s/n", nzdata, zdata);
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


unsigned char* SocketHelper::DeBase64ToGunzip(char *en, unsigned int size)
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
		//log("SocketHelper::deCompress=%s", odata);
	}
	free(de);
	
	return odata;
}

void SocketHelper::onOK(AbstractTransaction* transaction)
{
	log("SocketHelper::onOK...");
	if(_onOKCallback)
		_onOKCallback(transaction);
}

void SocketHelper::onFail(AbstractTransaction* transaction)
{
	log("SocketHelper::onFail...");
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

void SocketHelper::onNetError(string type, int errorCode, char* errorReason)
{	
	log("SocketHelper::onNetError: %s", errorReason);
	if(_onNetErrorCallback)
		_onNetErrorCallback(type, errorCode, errorReason);
}

void SocketHelper::onFinished(AbstractTransaction* transaction)
{
	log("SocketHelper::onFinished...");
	if(_onFinishedCallback)
		_onFinishedCallback(transaction);

	delete _transaction;
	_transaction = nullptr;
	
	delete this;
}