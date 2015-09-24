#ifndef __HTTPCLIENT_H__
#define __HTTPCLIENT_H__

#include <iostream>
#include "include/curl/curl.h"

#define Z_DEBUG

using namespace std;

#define ZLOG(str) HttpClient::getInstance()->zlog(__DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__, str);

#ifdef _WIN32
typedef _off_t p_off_t;
#else
typedef off_t p_off_t;
#endif

typedef void(*progress_info_callback)(void *userdata, double downloadSpeed, double remainingTime, double progressPercentage);

typedef struct
{
    void *sender;
	CURL *handle;
	progress_info_callback cb;
}Progress_User_Data;

typedef enum
{
	HTTP_REQUEST_OK = CURLE_OK,

	HTTP_REQUEST_ERROR = -999,

}Http_Client_Response;

class HttpClient
{
public:
	
	~HttpClient();

	static HttpClient *getInstance();
	static void destroyInstance();

    int HttpGet(const string requestURL, const string saveTo, void *sender, progress_info_callback cb);
    void zlog(const char *date, const char *time, const char *file, const int line, const char *func, const char* str);

private:
	HttpClient();

	bool init();
	
	static size_t write_callback(char *buffer, size_t size, size_t nmemb, void *userdata);
    static int progress_callback(void *userdata, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);

	// Get the local file size
	p_off_t getLocalFileLength(string path);

	// Get the file size on the server
	double getDownloadFileLength(string url);

private:
	static HttpClient *instance;

	static double downloadFileLength;
	static curl_off_t resumeByte;

	// Call frequency of the callback function
	static time_t lastTime;

    static bool stopCurl;
};

#endif		// __HTTPCLIENT_H__
