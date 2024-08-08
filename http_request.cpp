#include <iostream>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://yuantsy.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            std::cout << "HTTP Response Body: " << response << std::endl;

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}
