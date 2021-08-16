/*
 * gipAzure.cpp
 *
 *  Created on: Aug 4, 2021
 *      Author: Onur Demir
 */

#include "gipAzure.h"


gipAzure::gipAzure() {
	account_name = "";
	account_key = "";
	blob_endpoint = "";
	connection_count = 2;
	currentcontainer = "";
	httpsProtocol = false;
}

gipAzure::~gipAzure() {
}

void gipAzure::initSettings(std::string _account_name, std::string _account_key, bool _httpsProtocol) {
	 account_name = _account_name;
	 account_key = _account_key;
	 httpsProtocol = _httpsProtocol;
}

void gipAzure::initSettings(std::string _account_name, std::string _account_key, int _connectioncount, bool _httpsProtocol) {
	 initSettings(_account_name, _account_key, _httpsProtocol);
	 connection_count = _connectioncount;
}

void gipAzure::initSettings(std::string _account_name, std::string _account_key, std::string _blob_endpoint, bool _httpsProtocol) {
	initSettings(_account_name, _account_key, _httpsProtocol);
	blob_endpoint = _blob_endpoint;
}

void gipAzure::initSettings(std::string _account_name, std::string _account_key, std::string _blob_endpoint,  int _connectioncount, bool _httpsProtocol) {
	initSettings(_account_name, _account_key, _blob_endpoint, _httpsProtocol);
	connection_count = _connectioncount;
}

void gipAzure::createClient() {
	credential = std::make_shared<azure::storage_lite::shared_key_credential>(account_name, account_key);
	storage_account = std::make_shared<azure::storage_lite::storage_account>(account_name, credential, httpsProtocol, blob_endpoint);
	client = std::make_shared<azure::storage_lite::blob_client>(storage_account, connection_count);
	clientwrapper = std::make_shared<azure::storage_lite::blob_client_wrapper>(client);
}

std::string gipAzure::getUrl() {
	return storage_account.get()->get_url(azure::storage_lite::storage_account::service::blob).get_domain();
}

void gipAzure::deleteAllContainers() {
	std::vector<std::string> containernames = listContainerNames();
	if (!containernames.empty()) {
		for (std::string containername : containernames) {
			deleteContainer(containername);
		}
	}
}

bool gipAzure::containerExists(std::string containername) {
	return client.get()->get_container_properties(containername).get().response().valid();
}

void gipAzure::deleteContainer(std::string containername){
		if (containerExists(containername)) {
			client.get()->delete_container(containername);
			gLogi("Azure")<< containername << " deleted..." ;
		}
		else gLogi("Azure") << "Does not exist..." ;
}

void gipAzure::createContainer(std::string containername) {
	if (client) {
		auto outcome = client.get()->create_container(containername).get();
		if (!outcome.success())
		{
			gLogi("Azure") << "Failed to create container, Error: " << outcome.error().code << ", " << outcome.error().code_name ;
		}
	}
}



std::vector<std::string> gipAzure::listContainerNames() {
	std::vector<std::string> container_names;
	auto containers = client.get()->list_containers_segmented("", "", false).get();
	if (!containers.success()){
		gLogi("Azure") << "Failed to list container names, Error: " << containers.error().code << ", " << containers.error().code_name;
	}
	else{
		for (auto name : containers.response().containers) {
			container_names.push_back(name.name);
		}
	}
	return container_names;
}

bool gipAzure::blobExists(std::string containername, std::string blobname) {
		if (containerExists(containername)) {
			return client.get()->get_blob_properties(containername, blobname).get().response().valid();
		}
		else return false;
}

std::vector<std::string> gipAzure::listBlobNamesFromContainer(std::string containername) {
	std::vector<std::string> blob_names;
	if (containerExists(containername)) {
		auto blobs = client.get()->list_blobs_segmented(containername, "/", "", "").get();
		if (!blobs.success()) {
			gLogi("Azure") << "Failed to list container names, Error: " << blobs.error().code << ", " << blobs.error().code_name;
			blob_names.push_back("Failed to list container names, Error: " + blobs.error().code + ", " + blobs.error().code_name);
		}
		else {
			for	(auto name : blobs.response().blobs) {
				blob_names.push_back(name.name);
			}
		}
	}
	else blob_names.push_back("Container does not exists");

	return blob_names;
}

void gipAzure::deleteBlob(std::string containername, std::string blobname) {
	if (blobExists(containername, blobname)) client.get()->delete_blob(containername, blobname);
	else gLogi("Azure") << "Blob or container does not exists.";
}

void gipAzure::downloadBlob(std::string containername, std::string blobname, std::string fullpath) {
	if (!dirExists(fullpath)) fs::create_directories(fullpath);
	time_t last_modified;
	clientwrapper.get()->download_blob_to_file(containername, blobname, fullpath + "/" + blobname, last_modified);
	gLogi("Azure") << "Download Blob done: " << errno;
}

void gipAzure::uploadBlob(std::string container, std::string fullpath) {
	if (containerExists(container)) {
		gLogi("Azure") << fullpath;
		std::ifstream fin(fullpath, std::ios_base::in | std::ios_base::binary);
		std::vector<std::pair<std::string, std::string>> metadata;
		metadata.emplace_back(std::make_pair("meta_key1", "meta-value1"));
		metadata.emplace_back(std::make_pair("meta_key2", "meta-value2"));
		auto value = client.get()->upload_block_blob_from_stream(container, fs::path(fullpath).filename().u8string(), fin, metadata).get();
		if (!value.success()) gLogi("Azure") << "Failed to upload blob, Error:" << value.error().code << ", " << value.error().code_name;
	}
	else gLogi("Container doesn't exists...");
}


void gipAzure::setup() {

}

void gipAzure::update() {
}

int gipAzure::dirExists (std::string fullpath) {
	struct stat info;
	if(stat( fullpath.c_str(), &info ) != 0)
		return 0;
	else if(info.st_mode & S_IFDIR)
		return 1;
	else
		return 0;
}
