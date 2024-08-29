#include "CloudManager.h"
#include <iostream>

CloudManager::CloudManager(const std::string& apiKey, const std::string& projectId)
:apiKey(apiKey),projectId(projectId){
    initializeCloudService();
}

CloudManager::~CloudManager(){

}

void CloudManager::initializeCloudService(){
    std::cout << "Initializing cloud service with Project ID: " << projectId << std::endl;
    
    try {
        // Check if the service is initialized and ready
        bool initialized = true;  // Replace with actual initialization check
        if (initialized) {
            std::cout << "Cloud service initialized successfully!" << std::endl;
        } else {
            throw std::runtime_error("Failed to initialize cloud service.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error during cloud service initialization: " << e.what() << std::endl;
        throw;
    }
}

bool CloudManager::uploadData(const std::string& data, const std::string& remotPath){
    
}std::cout << "Uploading data to " << remotePath << "..." << std::endl;

    try {
        bool success = true;  

        if (success) {
            std::cout << "Data uploaded successfully!" << std::endl;
            return true;
        } else {
            throw std::runtime_error("Upload failed due to a cloud service error.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error uploading data: " << e.what() << std::endl;
        return false;
    }

std::string CloudManager::downloadData(const std::string& remotePath){
    std::cout<<"downloading data from"<<remotePath<<"..."<<std::endl;

    try{
        std::string downloadData = cloudService.dowload(remotePath);
        if (!downloadedData.empty()) {
            std::cout << "Data downloaded successfully!" << std::endl;
            return downloadedData;
        } else {
            throw std::runtime_error("Download failed or no data found.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error downloading data: " << e.what() << std::endl;
        return "";
    }
}

bool CloudManager::deleteData(const std::string& remotePath) {
    std::cout << "Deleting data at " << remotePath << "..." << std::endl;

    try { 
        
        cloudService.delete(remotePath);
        
        if (success) {
            std::cout << "Data deleted successfully!" << std::endl;
            return true;
        } else {
            throw std::runtime_error("Deletion failed due to a cloud service error.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error deleting data: " << e.what() << std::endl;
        return false;
    }
}

// List all files in a remote directory
std::vector<std::string> CloudManager::listFiles(const std::string& remoteDirectory) {
    std::cout << "Listing files in " << remoteDirectory << "..." << std::endl;

    try {
        std::vector<std::string> files = cloudService.list(remoteDirectory);

        if (!files.empty()) {
            std::cout << "Files listed successfully!" << std::endl;
        } else {
            throw std::runtime_error("Failed to list files or directory is empty.");
        }

        return files;
    } catch (const std::exception& e) {
        std::cerr << "Error listing files: " << e.what() << std::endl;
        return {};
    }
}