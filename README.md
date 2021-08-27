# gipAzure
Azure storage plugin for [GlistEngine](https://github.com/GlistEngine/GlistEngine).
### Requirements
- [GlistEngine](https://github.com/GlistEngine/GlistEngine).
- Azure account or local azure storage.
- Windows, Linux, or MacOS operating system.

## Installation
### 1. Open file explorer and create necessary folders:
- On Windows:
  - C:\dev\glist\glistplugins
- On macOS
  - ~/dev/glist/glistplugins
- On Linux
  - ~/dev/glist/glistplugins
### 2. Clone Plugin :
 First of all fork this repo at right up corner.  
   
Open command line(cmd.exe or bash) and go to the glistplugins folder by the command.
- On Windows:
  > cd C:\dev\glist\glistplugins
- On macOS:
  > cd ~/dev/glist/glistplugins
- On macOS:
  > cd ~/dev/glist/glistplugins
  
 Clone the gipAzure repo by writing this commands on command line:
 > git clone https://github.com/yourgithubusername/gipAzure.git

### 3. Set Up Plugin
 Add "gipAzure" in GlistApp's CMakelists.txt's line where it write "set(PLUGINS)" (Like "set(PLUGINS gipAzure)").
## How to Use
First of all have to createClient after call two function initSettings.
### Functions
- bool containerExists(string containername) :
  > Checks for container.
- void deleteAllContainers() :
  > Deletes all containers and blobs.
- void deleteContainer(string containername) :
  > Deletes the typed container.
- void createContainer(string containername) :
  > Creates the typed container.
- vector<string> listContainerNames() :
  > Gets all container names.
- bool blobExists(std::string containername, std::string blobname)
  > Checks the typed blob from typed container.
- std::vector<std::string> listBlobNamesFromContainer(std::string containername)
  > Gets all blob names from the typed container.
- void deleteBlob(std::string containername, std::string blobname)
  > Deletes the typed blob from the typed container.
- void downloadBlob(std::string containername, std::string blobname, std::string fullpath);
  > Downloads blob file from typed container name to typed path.
- void uploadBlob(std::string containername, std::string fullpath)
  > Uploads file to container from typed path.