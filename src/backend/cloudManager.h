#ifndef CLUDMANAGER_H
#define CLOUDMANAGER_H

#include <string>
#include <vector>

class CloudManager{
    public:
      CloudManager(const std::string& apiKey, const std::string& projectId);
      ~CloudManager();

      bool updateData(const std::string& data, const std::string& remotePath);

      std::string downloadData(const std::string& remotePath);

      bool deleteData(const std::string& remotePath);

      std::vector<std::string> listFiles(const std::string& remoteDirectory);

    private:
      std::string apiKey;
      std::string projectId;

      void initializeCloudService();
};

#endif