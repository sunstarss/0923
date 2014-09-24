#include "Timestamp.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
using namespace std;


Timestamp::Timestamp()
	:value_(0)
{

}

Timestamp::Timestamp(int64_t value)
	:value_(value)
{

}

string Timestamp::toString() const
{
	//1411373695.488096
	int64_t sec = value_ / (1000 * 1000);
	int64_t usec = value_ % (1000 * 1000);
	// %06lld
	char text[32] = {0};
	snprintf(text, sizeof text, "%lld.%06lld", sec, usec);

	return string(text);
}

string Timestamp::toFormatString() const
{
	//20140922 08:14:55.488096
	time_t sec = value_ / (1000 * 1000);
	int64_t usec = value_ % (1000 * 1000);
	struct tm st;
	//gmtime_r(&sec, &st);
	localtime_r(&sec, &st);

	char text[100] = {0};
	snprintf(text, sizeof text, "%04d%02d%02d %02d:%02d:%02d.%06lld", st.tm_year + 1900, st.tm_mon + 1, st.tm_mday, st.tm_hour, st.tm_min, st.tm_sec, usec);
	return string(text);
}

Timestamp Timestamp::now()
{
	struct timeval tv;
	memset(&tv, 0, sizeof tv);
	gettimeofday(&tv, NULL);

	int64_t val = 0;
	val += static_cast<int64_t>(tv.tv_sec) * 1000 * 1000;
	val += tv.tv_usec;

	return Timestamp(val);
}
