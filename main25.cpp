#include <iostream>
#include <string>
#include <limits>
#include <direct.h>
#include "FileUtility.h"
#include "FileManager.h"
#include "CryptoManagerPro.h"
#include "VersionManager.h"
#include "NotificationManager.h"
#include "FileProfiler.h"
#include "DiskAnalyzer.h"
#include "Auth.h"
#include "AccessController.h"
#include "Login.h"
#include "Structs.h"

std::string roleToString(UserRole r) {
    switch (r) {
        case UserRole::ADMIN: return "ADMIN";
        case UserRole::EDITOR: return "USER";
        case UserRole::VIEWER: return "GUEST";
        default: return "DENIED";
    }
}

class SessionMonitor {
    int createC=0, deleteC=0, encC=0, decC=0;
public:
    void incCreate(){createC++;}
    void incDelete(){deleteC++;}
    void incEncrypt(){encC++;}
    void incDecrypt(){decC++;}

    void report(){
        std::cout<<"\n===== SESSION REPORT =====\n";
        std::cout<<"Create: "<<createC<<"\n";
        std::cout<<"Delete: "<<deleteC<<"\n";
        std::cout<<"Encrypt: "<<encC<<"\n";
        std::cout<<"Decrypt: "<<decC<<"\n";

        int risk = deleteC*2 + encC;
        std::cout<<"Risk Score: "<<risk<<"\n";
    }
};

void showMenu(const std::string& dir) {

    std::cout << "\n====== Secure File Manager ======\n";
    std::cout << "Current Directory: " << dir << "\n\n";

    std::cout << "1. List Files\n";
    std::cout << "2. Create File\n";
    std::cout << "3. Create Folder\n";
    std::cout << "4. Delete File\n";
    std::cout << "5. Search File\n";
    std::cout << "6. Sort Files\n";
    std::cout << "7. Encrypt File\n";
    std::cout << "8. Decrypt File\n";
    std::cout << "9. List Backups\n";
    std::cout << "10. Restore Backup\n";
    std::cout << "11. Show Log\n";
    std::cout << "12. Clear Log\n";
    std::cout << "13. Show Current Directory\n";
    std::cout << "14. Session Monitor\n";
    std::cout << "15. Disk Analyzer\n";      
    std::cout << "16. File Profiler\n";      
    std::cout << "17. Exit\n";

    std::cout << "Choose option: ";
}

int main() {

    FileManager fm;
    FileUtility fu;
    VersionManager version;
    NotificationManager notifier;
    FileProfiler profiler;
    DiskAnalyzer analyzer;   
    Auth auth;
    AccessController access;
    Login logger;
    SessionMonitor monitor;

    auth.init();

    std::string user, pass;
    std::cout<<"Username: "; std::cin>>user;
    std::cout<<"Password: "; std::cin>>pass;

    User u = auth.login(user, pass);

    if (u.role == UserRole::DENIED) {
        std::cout<<"Login failed\n";
        return 0;
    }

    std::cout<<"✔ Logged in as "<<roleToString(u.role)<<"\n";

    int choice;
    std::string name, keyword, password, full;

    while (true) {

        char buffer[1024];
        _getcwd(buffer, 1024);
        std::string base = std::string(buffer) + "\\";

        showMenu(base);

        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {

        case 1: {
            auto files = fu.listFiles(base);
            for (auto &f : files)
                std::cout<<(f.isDirectory?"[DIR] ":"[FILE] ")<<f.name<<"\n";
            break;
        }

        case 2: {
            if (!access.can(u,"create")) { std::cout<<"❌ Denied\n"; break; }

            std::cout<<"File name: ";
            std::getline(std::cin,name);

            full = base + name;

            if (fm.createFile(full)) {
                version.saveVersion(full);
                notifier.addNotification("CREATE", name, "File created");
                monitor.incCreate();
                logger.log(u.username,"CREATE",name);
            }
            break;
        }

        case 3: {
            if (!access.can(u,"create")) { std::cout<<"Denied\n"; break; }

            std::cout<<"Folder name: ";
            std::getline(std::cin,name);

            full = base + name;

            if (fm.createFolder(full)) {
                notifier.addNotification("CREATE", name, "Folder created");
                monitor.incCreate();
                logger.log(u.username,"MKDIR",name);
            }
            break;
        }

        case 4: {
            if (!access.can(u,"delete")) { std::cout<<"❌ Denied\n"; break; }

            std::cout<<"File name: ";
            std::getline(std::cin,name);

            full = base + name;

            version.saveVersion(full);

            if (fm.deleteFile(full)) {
                notifier.addNotification("DELETE", name, "File deleted");
                monitor.incDelete();
                logger.log(u.username,"DELETE",name);
            }
            break;
        }

        case 5: {
            std::cout<<"Keyword: ";
            std::getline(std::cin,keyword);

            auto res = fu.searchFile(base, keyword);
            for (auto &f : res)
                std::cout<<f.name<<"\n";
            break;
        }

        case 6: {
            auto files = fu.listFiles(base);
            fu.sortByName(files,true);

            for (auto &f : files)
                std::cout<<f.name<<"\n";
            break;
        }

        case 7: {
            if (!access.can(u,"encrypt")) { std::cout<<"❌ Denied\n"; break; }

            std::cout<<"File: ";
            std::getline(std::cin,name);

            std::cout<<"Password: ";
            std::getline(std::cin,password);

            full = base + name;

            version.saveVersion(full);

            CryptoManagerPro crypto(password);
            crypto.encryptFile(full);

            notifier.addNotification("ENCRYPT", name, "File encrypted");
            monitor.incEncrypt();
            logger.log(u.username,"ENCRYPT",name);
            break;
        }

        case 8: {
            if (!access.can(u,"decrypt")) { std::cout<<"❌ Denied\n"; break; }

            std::cout<<"File: ";
            std::getline(std::cin,name);

            std::cout<<"Password: ";
            std::getline(std::cin,password);

            full = base + name;

            CryptoManagerPro crypto(password);
            crypto.decryptFile(full);

            notifier.addNotification("DECRYPT", name, "File decrypted");
            monitor.incDecrypt();
            logger.log(u.username,"DECRYPT",name);
            break;
        }

        case 9: {
            std::cout<<"File name: ";
            std::getline(std::cin,name);
            version.listVersions(base + name);
            break;
        }

        case 10: {
            std::cout<<"File name: ";
            std::getline(std::cin,name);

            int v;
            std::cout<<"Version: ";
            std::cin>>v;
            std::cin.ignore();

            version.restoreVersion(base + name, v);
            logger.log(u.username,"RESTORE",name);
            break;
        }

        case 11:
            logger.show();
            break;

        case 12:
            logger.clear();
            break;

        case 13:
            std::cout<<"Current Directory: "<<base<<"\n";
            break;

        case 14:
            monitor.report();
            break;

        case 15:
            analyzer.analyze(base);   
            break;

        case 16: {
            std::cout<<"File name: ";
            std::getline(std::cin,name);
            profiler.analyze(base + name);
            break;
        }

        case 17:
            std::cout<<"Exiting...\n";
            return 0;

        default:
            std::cout<<"Invalid option\n";
        }
    }
}