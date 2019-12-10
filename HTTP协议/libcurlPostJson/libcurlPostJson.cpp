// libcurlPostJson.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
//json
#include "json\json.h"
using namespace std;


//http://blog.csdn.net/wyansai/article/details/50764315
wstring AsciiToUnicode(const string& str) 
{
	// 预算-缓冲区中宽字节的长度  
	int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
	// 给指向缓冲区的指针变量分配内存  
	wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
	// 开始向缓冲区转换字节  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
	wstring ret_str = pUnicode;
	free(pUnicode);
	return ret_str;
}

string UnicodeToUtf8(const wstring& wstr) 
{
	// 预算-缓冲区中多字节的长度  
	int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	// 给指向缓冲区的指针变量分配内存  
	char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
	// 开始向缓冲区转换字节  
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
	string ret_str = pAssii;
	free(pAssii);
	return ret_str;
}


string AsciiToUtf8(const string& str) 
{
	return UnicodeToUtf8(AsciiToUnicode(str));
}


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
{
	string data((const char*) ptr, (size_t) size * nmemb);

	*((stringstream*) stream) << data << endl;

	return size * nmemb;
}

//POST json
int main()
{
	CURL *curl;
	CURLcode res;
	char tmp_str[256] = { 0 };
	std::stringstream out;

	//HTTP报文头  
	struct curl_slist* headers = NULL;

	char *url = "http://if.qdocument.net:705/bic/operationNote/upload";

	curl = curl_easy_init();

	if(curl)
	{
		//构建json
		Json::Value item;
		item["uid"]=Json::Value("weidong0925@126.com");
		item["fileName"]=Json::Value("梅西&内马尔&苏亚雷斯.txt");
		item["time"]=Json::Value("2017.07.31 9:55:22");
		item["type"]=Json::Value("Libcurl HTTP POST Json串");
		item["authList"]=Json::Value("weidong0925@126.com");
		std::string jsonout = item.toStyledString();

		jsonout = AsciiToUtf8(jsonout);


		//设置url
		curl_easy_setopt(curl, CURLOPT_URL, url);

		//设置http发送的内容类型为JSON
		//构建HTTP报文头  
		sprintf_s(tmp_str, "Content-Length: %s", jsonout.c_str());
		headers=curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
		//headers=curl_slist_append(headers, tmp_str);

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		//curl_easy_setopt(curl,  CURLOPT_CUSTOMREQUEST, "POST");//自定义请求方式
		curl_easy_setopt(curl, CURLOPT_POST, 1);//设置为非0表示本次操作为POST

		// 设置要POST的JSON数据
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonout.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonout.size());


		// 设置接收数据的处理函数和存放变量
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//设置回调函数
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);//设置写数据
		res = curl_easy_perform(curl);//执行

		string str_json = out.str();

		printf("%s",str_json.c_str());


		/* always cleanup */
		curl_easy_cleanup(curl);

	}

	return 0;
}

