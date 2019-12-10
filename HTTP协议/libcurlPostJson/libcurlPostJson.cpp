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
	// Ԥ��-�������п��ֽڵĳ���  
	int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
	// ��ָ�򻺳�����ָ����������ڴ�  
	wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
	// ��ʼ�򻺳���ת���ֽ�  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
	wstring ret_str = pUnicode;
	free(pUnicode);
	return ret_str;
}

string UnicodeToUtf8(const wstring& wstr) 
{
	// Ԥ��-�������ж��ֽڵĳ���  
	int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	// ��ָ�򻺳�����ָ����������ڴ�  
	char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
	// ��ʼ�򻺳���ת���ֽ�  
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

	//HTTP����ͷ  
	struct curl_slist* headers = NULL;

	char *url = "http://if.qdocument.net:705/bic/operationNote/upload";

	curl = curl_easy_init();

	if(curl)
	{
		//����json
		Json::Value item;
		item["uid"]=Json::Value("weidong0925@126.com");
		item["fileName"]=Json::Value("÷��&�����&������˹.txt");
		item["time"]=Json::Value("2017.07.31 9:55:22");
		item["type"]=Json::Value("Libcurl HTTP POST Json��");
		item["authList"]=Json::Value("weidong0925@126.com");
		std::string jsonout = item.toStyledString();

		jsonout = AsciiToUtf8(jsonout);


		//����url
		curl_easy_setopt(curl, CURLOPT_URL, url);

		//����http���͵���������ΪJSON
		//����HTTP����ͷ  
		sprintf_s(tmp_str, "Content-Length: %s", jsonout.c_str());
		headers=curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
		//headers=curl_slist_append(headers, tmp_str);

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		//curl_easy_setopt(curl,  CURLOPT_CUSTOMREQUEST, "POST");//�Զ�������ʽ
		curl_easy_setopt(curl, CURLOPT_POST, 1);//����Ϊ��0��ʾ���β���ΪPOST

		// ����ҪPOST��JSON����
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonout.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonout.size());


		// ���ý������ݵĴ������ʹ�ű���
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//���ûص�����
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);//����д����
		res = curl_easy_perform(curl);//ִ��

		string str_json = out.str();

		printf("%s",str_json.c_str());


		/* always cleanup */
		curl_easy_cleanup(curl);

	}

	return 0;
}

