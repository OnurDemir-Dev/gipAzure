/*
 * gipAzure.h
 *
 *  Created on: Aug 4, 2021
 *      Author: Onur Demir
 */

#ifndef PLUGINS_GIPAZURE_SRC_GIPAZURE_H_
#define PLUGINS_GIPAZURE_SRC_GIPAZURE_H_


#include <stdlib.h>
#include <iostream>
#include "gBasePlugin.h"
#include "gHttpFile.h"
#include "storage_credential.h"
#include "storage_account.h"
#include "blob/blob_client.h"






class gipAzure : public gBasePlugin{
public:
	gipAzure();
	~gipAzure();

	void setup();
	void update();
	int dirExists(std::string fullpath);

	void initSettings(std::string _account_name, std::string _account_key, bool _httpsProtocol);
	void initSettings(std::string _account_name, std::string _account_key, int _connectioncount, bool _httpsProtocol);
	void initSettings(std::string _account_name, std::string _account_key, std::string _blob_endpoint, bool _httpsProtocol);
	void initSettings(std::string _account_name, std::string _account_key, std::string _blob_endpoint, int _connectioncount, bool _httpsProtocol);

	void createClient();
	std::string getUrl();
	void deleteAllContainers();

	bool containerExists(std::string containername);
	void deleteContainer(std::string containername);
	void createContainer(std::string containername);
	std::vector<std::string> listContainerNames();

	bool blobExists(std::string containername, std::string blobname);
	std::vector<std::string> listBlobNamesFromContainer(std::string containername);
	void deleteBlob(std::string containername, std::string blobname);
	void downloadBlob(std::string containername, std::string blobname, std::string fullpath);
	void uploadBlob(std::string containername, std::string fullpath);
private:

	std::shared_ptr<azure::storage_lite::blob_client> client;
	std::shared_ptr<azure::storage_lite::blob_client_wrapper> clientwrapper;

	std::string account_name;
	std::string account_key;
	std::string blob_endpoint;
	std::string currentcontainer;
	std::shared_ptr<azure::storage_lite::storage_account> storage_account;
	std::shared_ptr<azure::storage_lite::shared_key_credential> credential;
	int connection_count;
	bool httpsProtocol;

};

#endif /* PLUGINS_GIPAZURE_SRC_GIPAZURE_H_ */
