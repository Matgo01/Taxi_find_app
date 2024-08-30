#ifndef MAPAPI_H
#define MAPAPI_H

#include <string>
#include <vector>

struct Location{
    double latitude;
    double longitude;
};

struct Route{
    std::vector<Location> path;
    double distance;
    double duration;
}

class MapAPI{
    public:
      MapAPI(const std::string& apiKey);
      ~MapAPI();

      Location geocode(const std::string& address);

      std::string reverseGeocode(const Location& location);

      Route calculateRoute(const Location& start, const Location& destination);

      std::vector<Location> findNearby(const Location& location, double radius, const std::string& placeType );


    private:
      std::string apiKey;

      sts::string makeHTTPRequest(const std::string& url);

};

#endif