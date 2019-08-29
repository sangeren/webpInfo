#include "../include/DownLoad.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include "webp/decode.h"

FILE *fp;
using namespace std;

int write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int written = fwrite(ptr, size, nmemb, (FILE *)fp);
    return written;
}

string DownLoadFile(string url)
{
    auto postion = url.rfind('/');
    auto fileName = url.substr(postion + 1);
    const char *c = fileName.c_str();

    const char *mode = "w";
    fp = fopen(c, mode);
    curl_global_init(CURL_GLOBAL_ALL);
    CURLcode res;
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return fileName;
}

void GetWebpInfo(string filePath, int *width, int *height)
{
    ifstream image;
    image.open(filePath, std::ios_base::binary);

    if (!image.is_open())
    {
        cout << "unable to open file";
        return;
    }

    //get length of file:
    image.seekg(0, image.end);
    int n = image.tellg();
    image.seekg(0, image.beg);

    //allocate memory:
    uint8_t *res = new uint8_t[n];
    image.read((char *)res, n);

    WebPGetInfo(res, n, width, height);
    return;
}