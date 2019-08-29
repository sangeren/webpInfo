#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;
int write_data(void *ptr, size_t size, size_t nmemb, void *stream);
string DownLoadFile(string url);
void GetWebpInfo(string filePath, int *width, int *height);
#endif