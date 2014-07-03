#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "soapH.h"
#include "DeviceBinding.nsmap"


const char server[] = "http://192.168.1.4:8080";


#define CHECK_FIELD(em) \
if (em == NULL) {\
	size_t size = sizeof(*(em));\
	em = soap_malloc(soap, size);\
	memset(em, 0, size);\
}

void soap_set_field_string(struct soap* soap, char ** p_field, const char* val) {
	assert(val != 0);
	*p_field = soap_malloc(soap, strlen(val) + 1);
	strcpy(*p_field, val);
}

void soap_set_field_ptr(struct soap* soap, unsigned char ** p_field, const unsigned char* val, int size) {
	assert(val != 0);
	*p_field = soap_malloc(soap, size);
	memcpy(*p_field, val, size);
}



#define ONVIF_SET_REQUEST(prefix, name) \
void onvif_set_##name##_request(struct soap* soap, struct _##prefix##__##name * req){\
	printf("enter %s\n", __FUNCTION__);\
}

#define ONVIF_GET_RESPONSE(prefix, name) \
void onvif_get_##name##_response(struct soap* soap, struct _##prefix##__##name##Response * res) {\
	printf("enter %s\n", __FUNCTION__);\
}
#define ONVIF_CLIENT(prefix,name) \
void onvif_##name() {\
	struct _##prefix##__##name in;\
	struct _##prefix##__##name##Response out;\
	struct soap* soap = soap_new1(SOAP_ENC_MTOM);\
	onvif_set_##name##_request(soap, &in);\
	int ret =  soap_call___##prefix##__##name(soap, server,  NULL,\
			&in,  &out);\
	printf("%s ret:%d\n", __FUNCTION__, ret);\
	onvif_get_##name##_response(soap, &out);\
	soap_end(soap);\
	soap_free(soap);\
}


#define ONVIF_DM(name) ONVIF_CLIENT(tds, name)
#define ONVIF_SET_REQUEST_DM(name) ONVIF_SET_REQUEST(tds, name)
#define ONVIF_GET_RESPONSE_DM(name) ONVIF_GET_RESPONSE(tds, name)

#define ONVIF_MEDIA(name) ONVIF_CLIENT(trt, name)
#define ONVIF_SET_REQUEST_MEDIA(name) ONVIF_SET_REQUEST(trt, name)
#define ONVIF_GET_RESPONSE_MEDIA(name) ONVIF_GET_RESPONSE(trt, name)


ONVIF_SET_REQUEST_MEDIA(GetProfiles)
ONVIF_GET_RESPONSE_MEDIA(GetProfiles)
ONVIF_MEDIA(GetProfiles)

ONVIF_SET_REQUEST_DM(GetDeviceInformation)
ONVIF_GET_RESPONSE_DM(GetDeviceInformation)
ONVIF_DM(GetDeviceInformation)


ONVIF_SET_REQUEST_DM(GetCapabilities)
ONVIF_GET_RESPONSE_DM(GetCapabilities)
ONVIF_DM(GetCapabilities)



unsigned char* load_file_data(const char* path, size_t* length) {
	int file_size;
	FILE* pf = fopen(path, "rb");
	unsigned char* buf;

	if (pf == NULL) {
		return NULL;
	}

	fseek(pf, 0, SEEK_END);
	file_size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	if (file_size == 0) {
		return NULL;
	}

	*length = file_size;
	buf = malloc(file_size + 1);
	fread(buf, file_size, 1, pf);

	fclose(pf);
	buf[file_size] = 0;

	return buf;
}

#define min(a,b) (a < b ? a : b)

void onvif_set_UpgradeSystemFirmware_request(struct soap* soap, struct _tds__UpgradeSystemFirmware * req){
	unsigned char* data;
	size_t size = 0;

	printf("enter %s\n", __FUNCTION__);

	memset(req, 0, sizeof(*req));
	CHECK_FIELD(req->Firmware);


	data = load_file_data("1.bin", &size);
	if (data == NULL) {
		printf("empty file\n");
		return;
	}

	printf("file size:%d\n", size);

	soap_set_field_string(soap, &req->Firmware->xmime__contentType, "binary");

	req->Firmware->xop__Include.__size = min(64*1024,size);
	req->Firmware->xop__Include.__ptr = (unsigned char*) data;
	soap_set_field_string(soap, &req->Firmware->xop__Include.id, "id");
	soap_set_field_string(soap, &req->Firmware->xop__Include.options, "option");
	soap_set_field_string(soap, &req->Firmware->xop__Include.type, "text/html");

	free(data);
}

ONVIF_GET_RESPONSE_DM(UpgradeSystemFirmware)
ONVIF_DM(UpgradeSystemFirmware)


//SOAP_FMAC5 int SOAP_FMAC6 soap_call___tds__UpgradeSystemFirmware(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct _tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware, struct _tds__UpgradeSystemFirmwareResponse *tds__UpgradeSystemFirmwareResponse)



int main(int argc, char* argv[]) {
	
	//onvif_GetCapabilities();
	//onvif_GetProfiles();
	//onvif_GetDeviceInformation();
	onvif_UpgradeSystemFirmware();




	return 0;
}
