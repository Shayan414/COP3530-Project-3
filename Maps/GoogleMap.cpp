#include <iostream>
#include <string>
#include <curl/curl.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

// Callback function writes data to a string, and then returns the size written

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *data) 
{
    size_t newLength = size * nmemb;
    try 
    {
        data->append((char*)contents, newLength);
        return newLength;
    } catch(bad_alloc &e) 
    {
        return 0;
    }
}

void geocodeAddress(const string& address, const string& apiKey) 
{
string readBuffer;
CURL *curl;
CURLcode res;

curl = curl_easy_init();
if(curl) 
{
    char* escaped_address = curl_easy_escape(curl, address.c_str(), address.length());
    if (escaped_address) 
    {
        // Build the URL with the escaped address
        string url = "https://maps.googleapis.com/maps/api/geocode/json?address=";
        url += escaped_address;  // Append the escaped address
        url += "&key=" + apiKey; // Append the API key

        // Set the cURL options
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        // Perform the cURL request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) 
        {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n';
        }
        
        else 
        {
            cout << readBuffer << endl;
        }

        curl_free(escaped_address);
    } 
    
    else 
        {
            cerr << "Failed to escape address" << '\n';
        }

    curl_easy_cleanup(curl);
    } 
    
    else 
    {
        cerr << "Failed to initialize cURL" << '\n';
    }
}

int main() 
{
string address = "1600 Amphitheatre Parkway, Mountain View, CA";
string apiKey = "AIzaSyDGGVZCBmJySquYQPkvMMO_rKCi6zGR8ho";

geocodeAddress(address, apiKey);

return 0;
}