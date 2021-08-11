/*
 * gipAzure.cpp
 *
 *  Created on: Aug 4, 2021
 *      Author: Onur Demir
 */

#include "gipAzure.h"


gipAzure::gipAzure(){
	account_name = "";
	account_key = "";
	blob_endpoint = "";
	connection_count = 2;
	currentcontainer = "";
}

gipAzure::~gipAzure() {
}

void gipAzure::initSettings(std::string _account_name, std::string _account_key){
	 account_name = _account_name;
	 account_key = _account_key;
}

void gipAzure::initSettings(std::string _account_name, std::string _account_key, int _connectioncount){
	 initSettings(_account_name, _account_key);
	 connection_count = _connectioncount;
}

void gipAzure::initSettings(std::string _account_name, std::string _account_key, std::string _blob_endpoint){
	initSettings(_account_name, _account_key);
	blob_endpoint = _blob_endpoint;
}

void gipAzure::initSettings(std::string _account_name, std::string _account_key, std::string _blob_endpoint,  int _connectioncount){
	initSettings(_account_name, _account_key, _blob_endpoint);
	connection_count = _connectioncount;
}

void gipAzure::createClient(){
	credential = std::make_shared<azure::storage_lite::shared_key_credential>(account_name, account_key);
	storage_account = std::make_shared<azure::storage_lite::storage_account>(account_name, credential, true, blob_endpoint);
	client = new azure::storage_lite::blob_client(storage_account, connection_count);
	clientwrapper = new azure::storage_lite::blob_client_wrapper(client);
}

bool gipAzure::containerExists(std::string containername) {
	return client->get_container_properties(containername).get().response().valid();
}

void gipAzure::deleteContainer(std::string containername){
	if (client) {
		if (containerExists(containername)) {
			client->delete_container(containername);
			gLogi("Azure") << "Deleted..." ;
		}
		else gLogi("Azure") << "Does not exist..." ;
	}
}

void gipAzure::createContainer(std::string containername){
	if (client) {
		auto outcome = client->create_container(containername).get();
		if (!outcome.success())
		{
				gLogi("Azure") << "Failed to create container, Error: " << outcome.error().code << ", " << outcome.error().code_name ;
		}
	}
}

void gipAzure::setCurrentContainer(std::string containername){
	if (client) {
		if (containerExists(containername)) currentcontainer = containername;
	}
}


std::vector<std::string> gipAzure::listContainerNames() {
	if (client){
		auto containers = client->list_containers_segmented("", "", false);
		std::vector<std::string> container_names;
		for (auto name : containers.get().response().containers) {
			container_names.push_back(name.name);
		}
		return container_names;
	}
}



void gipAzure::setup() {

}

void gipAzure::update() {
}
