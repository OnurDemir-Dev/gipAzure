cmake_minimum_required (VERSION 3.10.2)


##### PLUGIN NAME #####
set(pluginname gipAzure)


##### PLUGIN PATHS #####
set(PLUGIN_DIR ${PLUGINS_DIR}/${pluginname})
set(PREBUILT_DIR ${PLUGIN_DIR}/prebuilts)


##### PLUGIN SOURCES #####
list(APPEND PLUGIN_SRCS
			${PLUGIN_DIR}/src/gipAzure.cpp
			${PLUGIN_DIR}/azure/src/blob/blob_client.cpp
			${PLUGIN_DIR}/azure/src/blob/blob_client_wrapper.cpp
			${PLUGIN_DIR}/azure/src/http/libcurl_http_client.cpp
			${PLUGIN_DIR}/azure/src/append_block_request_base.cpp
			${PLUGIN_DIR}/azure/src/base64.cpp
			${PLUGIN_DIR}/azure/src/constants.cpp
			${PLUGIN_DIR}/azure/src/copy_blob_request_base.cpp
			${PLUGIN_DIR}/azure/src/create_container_request_base.cpp
			${PLUGIN_DIR}/azure/src/delete_blob_request_base.cpp
			${PLUGIN_DIR}/azure/src/delete_container_request_base.cpp
			${PLUGIN_DIR}/azure/src/get_blob_property_request_base.cpp
			${PLUGIN_DIR}/azure/src/get_blob_request_base.cpp
			${PLUGIN_DIR}/azure/src/get_block_list_request_base.cpp
			${PLUGIN_DIR}/azure/src/get_container_property_request_base.cpp
			${PLUGIN_DIR}/azure/src/get_page_ranges_request_base.cpp
			${PLUGIN_DIR}/azure/src/hash.cpp
			${PLUGIN_DIR}/azure/src/list_blobs_request_base.cpp
			${PLUGIN_DIR}/azure/src/list_containers_request_base.cpp
			${PLUGIN_DIR}/azure/src/logging.cpp
			${PLUGIN_DIR}/azure/src/put_blob_request_base.cpp
			${PLUGIN_DIR}/azure/src/put_block_list_request_base.cpp
			${PLUGIN_DIR}/azure/src/put_block_request_base.cpp
			${PLUGIN_DIR}/azure/src/put_page_request_base.cpp
			${PLUGIN_DIR}/azure/src/set_blob_metadata_request_base.cpp
			${PLUGIN_DIR}/azure/src/set_container_metadata_request_base.cpp
			${PLUGIN_DIR}/azure/src/storage_account.cpp
			${PLUGIN_DIR}/azure/src/storage_credential.cpp
			${PLUGIN_DIR}/azure/src/storage_url.cpp
			${PLUGIN_DIR}/azure/src/tinyxml2.cpp
			${PLUGIN_DIR}/azure/src/tinyxml2_parser.cpp
			${PLUGIN_DIR}/azure/src/utility.cpp
			)


##### PLUGIN HEADERS #####
list(APPEND PLUGIN_INCLUDES
			${PLUGIN_DIR}/src
			${PREBUILT_DIR}/include
			${PLUGIN_DIR}/azure/include)


##### PLUGIN DEPENDENCY LOCATIONS (IF ANY) #####
if(WIN32)
	list(APPEND PLUGIN_LINKDIRS
				${PREBUILT_DIR}/lib/win32
				${PREBUILT_DIR}/bin
				
	)
	
	#set(PLUGIN_LIBDIRS ${PREBUILT_DIR}/lib/win32)
	list(APPEND PLUGIN_LIBDIRS
				${PREBUILT_DIR}/lib/win32
	)
elseif(LINUX)
	#Linux libs here
elseif(APPLE)
	#Macos libs here
endif(WIN32)


##### PLUGIN DEPENDENCY LINKING (IF ANY) #####					
if(WIN32)
	list(APPEND PLUGIN_LINKLIBS
	)
elseif(LINUX)
	list(APPEND PLUGIN_LINKLIBS
				#Lib names
	)
elseif(APPLE)
	list(APPEND PLUGIN_LINKLIBS
				#Lib names
	)
endif(WIN32)