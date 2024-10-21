#include <iostream>
#include <string>
#include <map>
#include <windows.h>
#include <wininet.h>
#include <regex>
#include <fstream>
#include <set>

#pragma comment(lib, "wininet.lib")

class SocialMediaFinder {
public:
    void displayBanner() {
        std::cout << R"(
          Made by @znlv for research purposes
        )" << std::endl;
    }

    void displayMenu() {
        std::cout << "Choose an option:\n";
        std::cout << "1. Search for Facebook accounts\n";
        std::cout << "2. Search for Twitter accounts\n";
        std::cout << "3. Search for Instagram accounts\n";
        std::cout << "4. Search for YouTube accounts\n";
        std::cout << "5. Search for all accounts\n";
        std::cout << "6. Exit\n";
    }

    void findAccounts(const std::string& name, bool exportToFile, const std::set<std::string>& platforms) {
        std::map<std::string, std::string> results;

        if (platforms.empty() || platforms.count("Facebook")) {
            results["Facebook"] = "https://www.facebook.com/search/top?q=" + name;
        }
        if (platforms.empty() || platforms.count("Twitter")) {
            results["Twitter"] = "https://twitter.com/search?q=" + name;
        }
        if (platforms.empty() || platforms.count("Instagram")) {
            results["Instagram"] = "https://www.instagram.com/" + name + "/";
        }
        if (platforms.empty() || platforms.count("YouTube")) {
            results["YouTube"] = "https://www.youtube.com/results?search_query=" + name;
        }

        std::ofstream outFile;
        if (exportToFile) {
            outFile.open("social_media_accounts.txt");
            if (!outFile) {
                std::cerr << "Error opening file for writing." << std::endl;
                return;
            }
            outFile << "[+] " << name << std::endl;
        }

        for (const auto& pair : results) {
            if (checkAccountExists(pair.second)) {
                if (exportToFile) {
                    outFile << "[+] " << pair.first << ": " << pair.second;
                } else {
                    std::cout << "[+] " << pair.first << ": " << pair.second;
                }
                if (pair.first == "Facebook") {
                    std::string fbId = getFacebookID(pair.second);
                    if (!fbId.empty()) {
                        if (exportToFile) {
                            outFile << " (Account exists, ID: " << fbId << ")" << std::endl;
                        } else {
                            std::cout << " (Account exists, ID: " << fbId << ")" << std::endl;
                        }
                    } else {
                        if (exportToFile) {
                            outFile << " (Account exists, ID not found)" << std::endl;
                        } else {
                            std::cout << " (Account exists, ID not found)" << std::endl;
                        }
                    }
                } else {
                    if (exportToFile) {
                        outFile << " (Account exists)" << std::endl;
                    } else {
                        std::cout << " (Account exists)" << std::endl;
                    }
                }
            } else {
                if (exportToFile) {
                    outFile << "[+] " << pair.first << ": " << pair.second << " (Account does not exist)" << std::endl;
                } else {
                    std::cout << "[+] " << pair.first << ": " << pair.second << " (Account does not exist)" << std::endl;
                }
            }
        }

        if (exportToFile) {
            outFile.close();
            std::cout << "Results written to social_media_accounts.txt" << std::endl;
        }
    }

private:
    bool checkAccountExists(const std::string& url) {
        HINTERNET hInternet, hConnect;
        DWORD response_code = 0;

        hInternet = InternetOpenA("SocialMediaFinder", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (hInternet) {
            hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
            if (hConnect) {
                DWORD size = sizeof(response_code);
                if (HttpQueryInfoA(hConnect, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &response_code, &size, NULL)) {
                    InternetCloseHandle(hConnect);
                    InternetCloseHandle(hInternet);
                    return (response_code == 200);
                }
                InternetCloseHandle(hConnect);
            }
            InternetCloseHandle(hInternet);
        }

        return false;
    }

    std::string getFacebookID(const std::string& url) {
        HINTERNET hInternet, hConnect;
        std::string content;
        const int bufferSize = 8192;

        hInternet = InternetOpenA("SocialMediaFinder", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (hInternet) {
            hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
            if (hConnect) {
                char buffer[bufferSize];
                DWORD bytesRead;

                while (InternetReadFile(hConnect, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    content += buffer;
                }

                InternetCloseHandle(hConnect);
            }
            InternetCloseHandle(hInternet);
        }

        std::regex idRegex("id=([0-9]+)");
        std::smatch match;
        if (std::regex_search(content, match, idRegex) && match.size() > 1) {
            return match.str(1);
        }

        return "";
    }
};

int main() {
    SocialMediaFinder finder;
    finder.displayBanner();
    std::string name;
    bool exportToFile = false;

    while (true) {
        finder.displayMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 6) {
            std::cout << "Exiting program." << std::endl;
            break;
        }

        std::cout << "Enter the name to search for social media accounts: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::set<std::string> platforms;
        switch (choice) {
        case 1: platforms.insert("Facebook"); break;
        case 2: platforms.insert("Twitter"); break;
        case 3: platforms.insert("Instagram"); break;
        case 4: platforms.insert("YouTube"); break;
        case 5: platforms.insert("Facebook"); platforms.insert("Twitter");
            platforms.insert("Instagram"); platforms.insert("YouTube"); break;
        default: std::cout << "Invalid choice. Please try again." << std::endl; continue;
        }

        char exportChoice;
        std::cout << "Do you want to export the results to a text file? (y/n): ";
        std::cin >> exportChoice;
        exportToFile = (exportChoice == 'y' || exportChoice == 'Y');

        finder.findAccounts(name, exportToFile, platforms);
    }

    return 0;
}
