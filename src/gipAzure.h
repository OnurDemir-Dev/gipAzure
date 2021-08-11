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

	void initSettings(std::string _account_name, std::string _account_key);
	void initSettings(std::string _account_name, std::string _account_key, int _connectioncount);
	void initSettings(std::string _account_name, std::string _account_key, std::string _blob_endpoint);
	void initSettings(std::string _account_name, std::string _account_key, std::string _blob_endpoint, int _connectioncount);

	void createClient();
	bool containerExists(std::string containername);
	void deleteContainer(std::string containername);
	void createContainer(std::string containername);
	void setCurrentContainer(std::string containername);
	std::vector<std::string> listContainerNames();

private:

	azure::storage_lite::blob_client* client;
	azure::storage_lite::blob_client_wrapper* clientwrapper;

	std::string account_name;
	std::string account_key;
	std::string blob_endpoint;
	int connection_count;
	std::string currentcontainer;
	std::shared_ptr<azure::storage_lite::storage_account> storage_account;
	std::shared_ptr<azure::storage_lite::shared_key_credential> credential;
};

#endif /* PLUGINS_GIPAZURE_SRC_GIPAZURE_H_ */
