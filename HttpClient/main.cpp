#include "include/HttpClient.h"

void progress_callback(void *userdata, double download_speed, double remaining_time, double progress_percentage)
{
	//qDebug()<<download_speed<<remaining_time<<progress_percentage;
	int hours = 0, minutes = 0, seconds = 0;

	if (download_speed != 0)
	{
		hours = remaining_time / 3600;
		minutes = (remaining_time - hours * 3600) / 60;
		seconds = remaining_time - hours * 3600 - minutes * 60;
	}

	string unit = "B";
	if (download_speed > 1024 * 1024 * 1024)
	{
		unit = "G";
		download_speed /= 1024 * 1024 * 1024;
	}
	else if (download_speed > 1024 * 1024)
	{
		unit = "M";
		download_speed /= 1024 * 1024;
	}
	else if (download_speed > 1024)
	{
		unit = "kB";
		download_speed /= 1024;
	}

	char speedFormat[15] = { 0 };
	char timeFormat[10] = { 0 };
	char progressFormat[8] = { 0 };

#ifdef _WIN32
	sprintf_s(speedFormat, sizeof(speedFormat), "%.2f%s/s", download_speed, unit.c_str());
	sprintf_s(timeFormat, sizeof(timeFormat), "%02d:%02d:%02d", hours, minutes, seconds);
	sprintf_s(progressFormat, sizeof(progressFormat), "%.2f", progress_percentage);
#else
	sprintf(speedFormat, "%.2f%s/s", download_speed, unit.c_str());
	sprintf(timeFormat, "%02d:%02d:%02d", hours, minutes, seconds);
	sprintf(progressFormat, "%.2f", progress_percentage);
#endif

	//AnyClass *eg = static_cast<AnyClass *>(userdata);
	//eg->func(speedFormat, timeFormat, progressFormat);
}

int main()
{	
	HttpClient::getInstance()->HttpGet("http://speedtest.wdc01.softlayer.com/downloads/test10.zip", "test10.zip", NULL, NULL);

	return 0;
}
