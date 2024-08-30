#include "MAPI.h"
#include <iostream>
#include <sstream>
#include <curl/curl.>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

MapAPI::MapAPI(const std::string& apiKey):apiKey(apiKey){
    std::cout<<"Map api initialized with api key"<<std::endl;
}

MapAPI::~MapAPI() {
    
    std::cout << "Map API instance destroyed." << std::endl;
}

Location MapAPI::geocode(const std::string& address){

    std::string encodedAddress = curl_easy_escape(nullptr, address.c_str(), address.length());
    std::string url = "https://maps.googleapis.com/maps/api/geocode/json?address="+address+"&key="+apiKey;
    std::string response = makeHTTPRequest(url);

    Location location = {0.0,0.0};
    try{
        auto jsonResponse = json::parse(response);

        if(jsonResponse.containse("result") && jsonResponse["result"].empty()){
            auto locationData = jsonResponse["result"][0]["geometry"]["location"];
            location.latitude = locationData["lat"].get<double>();
            location.longitude = locationData["lng"].get<double>();
            std::cout<<"geocode address "<<ddress<<std::endl;
        }else{
             std::cerr << "No results found for the address: " << address << std::endl;
        }
    }catch (const json::exception& e) {
        std::cerr << "Failed to parse JSON response: " << e.what() << std::endl;
    }
     return location;
}

std::string MapAPI::makeHTTPRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;
    curl = curl_easy_init();
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, std::string* s) -> size_t {
            size_t newLength = size * nmemb;
            try {
                s->append((char*)contents, newLength);
            } catch (std::bad_alloc& e) {
                
                return 0;
            }
            return newLength;
        });
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    
    return response;
}

std::string MapAPI::reverseGeocode(const Location& location){
    std::string url= "https://maps.googleapis.com/maps/api/geocode/json?latlng=" +
                      std::to_string(location.latitude) + "," + std::to_string(location.longitude) +
                      "&key=" + apiKey;
    
    std::string response = makeHTTPRequest(url);

    std::string address;
    try{
        auto jsonResponse = json::parse(response);

        if(jsonResponse.contains("results") && !jsonResponse["result"].empty()){
            address = jsonResponse["results"][0]["formatted_address"].get<std::string>();
             std::cout << "Reverse geocoded location (" << location.latitude << ", " << location.longitude << ") to '" << address << "'." << std::endl;
        }else {
            std::cerr << "No results found for the location: (" << location.latitude << ", " << location.longitude << ")" << std::endl;
            address = "Address not found";
        }
}catch (const json::exception& e) {
        std::cerr << "Failed to parse JSON response: " << e.what() << std::endl;
        address = "Error parsing address";
    }

    return address;

}

Route MapAPI::calculateRoute(const Location& start, Location& destination){
    std::string url = "https://maps.googleapis.com/maps/api/directions/json?origin=" +
                      std::to_string(start.latitude) + "," + std::to_string(start.longitude) +
                      "&destination=" + std::to_string(destination.latitude) + "," + std::to_string(destination.longitude) +
                      "&key=" + apiKey;
    std::string response = makeHTTPRequest(url);

    Route route;
    try{
        auto jsonResponse = json::parse(response);

        if(jsonResponse.contains["result"] && !jsonResponse["routes"].empty()){
            auto routeInfo = jsonResponse["routes"][0];

            for (const auto& leg: routeInfo["legs"]){
                for(const auto& step : leg["steps"]){
                    double lat = step["end_location"]["lat"].get<double>();
                    double lng = step["end_location"]["lng"].get<double>();
                    route.path.push_back{(lat,lng)};
                }
            }

            route.distance = routeInfo["legs"][0]["distance"]["value"].get<double>();
            route.duration = routeInfo["legs"][0]["duration"]["value"].get<double>();

            std::cout << "Calculated route from (" << start.latitude << ", " << start.longitude << ") to ("
                      << destination.latitude << ", " << destination.longitude << "). Distance: "
                      << route.distance << " km, Duration: " << route.duration << " minutes." << std::endl;
        }else {
            std::cerr << "No route found between the specified locations." << std::endl;
        }
    } catch (const json::exception& e) {
        std::cerr << "Failed to parse JSON response: " << e.what() << std::endl;
    }

    return route;
    }

    std::vector<Location> MapAPI::findNearby(const Location& location, doubel radius, const std::string& placeType){
        std::string url = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=" +
                      std::to_string(location.latitude) + "," + std::to_string(location.longitude) +
                      "&radius=" + std::to_string(radius) + "&type=" + placeType + "&key=" + apiKey;
        std::string response = makeHTTPRequest(url);
        try{
            auto jsonResponse = json::parse(response);
            if(jsonResponse.contains["results"] && !jsonResponse["results"].empty()){
                for(const auto& result:jsonResponse["results"]){
                    double lat = result["geometry"]["location"]["lat"].get<double>();
                    double lng = result["geometry"]["location"]["lng"].get<double>();
                    locations.push_back({lat, lng});
                }
                std::cout << "Found " << locations.size() << " nearby places of type '" << placeType << "' around ("
                      << location.latitude << ", " << location.longitude << ")." << std::endl;
            }else {
            std::cerr << "No nearby places found of type '" << placeType << "' around the specified location." << std::endl;
        }
        }catch (const json::exception& e) {
        std::cerr << "Failed to parse JSON response: " << e.what() << std::endl;
    }

    return locations;

    }
