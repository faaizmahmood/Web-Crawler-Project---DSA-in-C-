#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>

bool isValidUrl(const std::string& url) {
	
    // Basic URL validation logic
    // You can enhance this validation based on your specific requirements
    return !url.empty() && (url.find("http://") == 0 || url.find("https://") == 0);

}

void openURL(const std::string& url, const std::string& browser, int& successCount, int& errorCount) {
    std::string command;

    // Check the browser and form the command accordingly
    if (browser == "chrome") {
        command = "start chrome " + url;
        
    } else if (browser == "firefox") {
        command = "start firefox " + url;
        
    } else if (browser == "edge") {
        command = "start msedge " + url;
        
    } else {
        std::cerr << "Unsupported browser: " << browser << "\n";
        errorCount++;
        return;
        
    }

     
    int result = std::system(command.c_str());

    if (result == 0) {
    	
        std::cout << "Successfully opened " << url << " in " << browser << "\n";
        successCount++;
        
    } else {
    	
        std::cout << "Error opening " << url << " in " << browser << "\n";
        errorCount++;
        
    }
}

int main() {
	std::cout << "--------------------------------------\n";
    std::cout << "     	WEB CRAWLER			\n";
    std::cout << "--------------------------------------\n";
    
    std::queue<std::string> urlQueue;
    int successCount = 0;
    int errorCount = 0;

    // Prompt the user to enter URLs and store them in the queue
    std::cout << "Enter URLs (type 'done' to finish):\n";
    
    std::string inputUrl;
    
    while (true) {
    	
        std::cout << "URL: ";
        std::getline(std::cin, inputUrl);

        if (inputUrl == "done") {
        	
            break;
            
        }

        if (isValidUrl(inputUrl)) {
        	
            urlQueue.push(inputUrl);
            
        } else {
        	
            std::cout << "Invalid URL. Please enter a valid URL starting with 'http://' or 'https://'.\n";
        }
    }

    // Prompt the user to enter the desired browser
    std::cout << "Enter the browser to use (chrome/firefox/edge): ";
    std::string browser;
    std::cin >> browser;

    // Process each URL in the queue
    while (!urlQueue.empty()) {
        std::string currentUrl = urlQueue.front();
        urlQueue.pop();

        openURL(currentUrl, browser, successCount, errorCount);

        // You can add more functionality here, such as saving the visited URLs to a file, etc.
    }

    std::cout << "Finished processing URLs. Summary:\n";
    std::cout << "Success Count: " << successCount << "\n";
    std::cout << "Error Count: " << errorCount << "\n";

    // Log the details to a file
    
    std::ofstream logFile("crawler_log.txt", std::ios::app);
    
    if (logFile.is_open()) {
    	
        logFile << "Summary:\n";
        logFile << "Success Count: " << successCount << "\n";
        logFile << "Error Count: " << errorCount << "\n";
        logFile.close();
        
    } else {
    	
        std::cerr << "Error opening log file for writing.\n";
	}

    return 0;
}

