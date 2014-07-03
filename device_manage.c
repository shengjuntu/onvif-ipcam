#include "soapH.h"
#include <assert.h>
#include "wsseapi.h"
#include "onvif_impl.h"

int access_control(struct soap* soap) {
	const char *username = soap_wsse_get_Username(soap);
      const char *password;
      if (!username)
        return soap->error; // no username: return FailedAuthentication

      password = "123456"; // lookup password of username
      if (soap_wsse_verify_Password(soap, password))
        return soap->error; // password verification failed: return FailedAuthentic

      return SOAP_OK;
}

#define ACCESS_CONTROL \
{\
	DBG_LINE;\
	int ret = access_control(soap);\
	if (ret != SOAP_OK) return ret;\
}

int save_file_data(const char* path, void const* buffer, int length) {
	FILE* pf = fopen(path, "wb");
	if (pf != NULL) {
		fwrite(buffer, length, 1, pf);
		fclose(pf);
		return 1;
	} else {
		printf("open file failed %s\n", path);
	}
	return 0;
}
//******************************************************************************************************************************************************************
int __tds__GetServices(struct soap* soap,
		struct _tds__GetServices *tds__GetServices,
		struct _tds__GetServicesResponse *tds__GetServicesResponse) {
	int major, minor;


	ACCESS_CONTROL;

	onvif_dm_get_service_version(&major, &minor);

	tds__GetServicesResponse->__sizeService = 1;

	CHECK_FIELD(tds__GetServicesResponse->Service)
	CHECK_FIELD(tds__GetServicesResponse->Service[0].Version)

	soap_set_field_string(soap, &tds__GetServicesResponse->Service[0].XAddr, onvif_dm_get_service_url());
	soap_set_field_string(soap, &tds__GetServicesResponse->Service[0].Namespace, onvif_dm_get_service_namespace());
	tds__GetServicesResponse->Service[0].Version->Major = major;
	tds__GetServicesResponse->Service[0].Version->Minor = minor;

	return SOAP_OK;
}

int __tds__GetDeviceInformation(struct soap* soap,
		struct _tds__GetDeviceInformation *tds__GetDeviceInformation,
		struct _tds__GetDeviceInformationResponse *tds__GetDeviceInformationResponse) {
	ACCESS_CONTROL;


	soap_set_field_string(soap, &tds__GetDeviceInformationResponse->FirmwareVersion,
			onvif_dm_get_firmware_version());
	soap_set_field_string(soap, &tds__GetDeviceInformationResponse->HardwareId,
			onvif_dm_get_hardware_id());
	soap_set_field_string(soap, &tds__GetDeviceInformationResponse->Manufacturer,
			onvif_dm_get_manufacturer());
	soap_set_field_string(soap, &tds__GetDeviceInformationResponse->Model,
			onvif_dm_get_model());
	soap_set_field_string(soap, &tds__GetDeviceInformationResponse->SerialNumber,
			onvif_dm_get_serial_number());
	return SOAP_OK;
}

int __tds__UpgradeSystemFirmware(struct soap* soap,
		struct _tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware,
		struct _tds__UpgradeSystemFirmwareResponse *tds__UpgradeSystemFirmwareResponse) {
	ACCESS_CONTROL;

	if (tds__UpgradeSystemFirmware->Firmware == NULL) {
		printf("Firmware is NULL\n");
	} else {
		printf("mimeType:%s\n", tds__UpgradeSystemFirmware->Firmware->xmime__contentType);
		//printf("", ds__UpgradeSystemFirmware->

		printf("id:%s\n", tds__UpgradeSystemFirmware->Firmware->xop__Include.id);
		printf("options:%s\n", tds__UpgradeSystemFirmware->Firmware->xop__Include.options);
		printf("type:%s\n", tds__UpgradeSystemFirmware->Firmware->xop__Include.type);
		printf("size:%d\n", tds__UpgradeSystemFirmware->Firmware->xop__Include.__size);
		if (tds__UpgradeSystemFirmware->Firmware->xop__Include.__size > 0) {
			int ret = save_file_data("./firmware.bin",
					tds__UpgradeSystemFirmware->Firmware->xop__Include.__ptr,
					tds__UpgradeSystemFirmware->Firmware->xop__Include.__size);
			if (ret) {
				printf("*************save firmware OK\n");
			}

		}

	}


	return SOAP_OK;
}


int __tds__GetWsdlUrl(struct soap* soap,
		struct _tds__GetWsdlUrl *tds__GetWsdlUrl,
		struct _tds__GetWsdlUrlResponse *tds__GetWsdlUrlResponse) {
	ACCESS_CONTROL;

	soap_set_field_string(soap,  &tds__GetWsdlUrlResponse->WsdlUrl, onvif_dm_get_wsdl_url());

	return SOAP_OK;
}


int __tds__GetCapabilities(struct soap* soap,
		struct _tds__GetCapabilities *tds__GetCapabilities,
		struct _tds__GetCapabilitiesResponse *tds__GetCapabilitiesResponse) {

	DBG_LINE;

	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Media)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Extension)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Device)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Device->System)
	CHECK_FIELD(tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions)


	soap_set_field_string(soap, &tds__GetCapabilitiesResponse->Capabilities->Media->XAddr, onvif_dm_get_ipv4_address());
	*tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast = xsd__boolean__false_;
	*tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP = xsd__boolean__true_;
	*tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP = xsd__boolean__true_;
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->VideoSources = TRUE;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->FirmwareUpgrade =  xsd__boolean__true_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions->Major = 2;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions->Minor = 0;


	return SOAP_OK;
}



/** Auto-test server operation __tds__SetSystemDateAndTime */
int __tds__SetSystemDateAndTime(struct soap *soap, struct _tds__SetSystemDateAndTime *tds__SetSystemDateAndTime, struct _tds__SetSystemDateAndTimeResponse *tds__SetSystemDateAndTimeResponse)
{
	struct tm now;


	LOAD(now.tm_year , tds__SetSystemDateAndTime->UTCDateTime->Date->Year);
	LOAD(now.tm_mon , tds__SetSystemDateAndTime->UTCDateTime->Date->Month);
	LOAD(now.tm_mday , tds__SetSystemDateAndTime->UTCDateTime->Date->Day);
	LOAD(now.tm_hour , tds__SetSystemDateAndTime->UTCDateTime->Time->Hour);
	LOAD(now.tm_min , tds__SetSystemDateAndTime->UTCDateTime->Time->Minute);
	LOAD(now.tm_sec , tds__SetSystemDateAndTime->UTCDateTime->Time->Second);
	LOAD(now.tm_zone , tds__SetSystemDateAndTime->TimeZone->TZ);
	LOAD(now.tm_isdst , tds__SetSystemDateAndTime->DaylightSavings);

	onvif_dm_set_system_date_time(tds__SetSystemDateAndTime->DateTimeType, &now);

	return SOAP_OK;
}


/** Auto-test server operation __tds__GetSystemDateAndTime */
int __tds__GetSystemDateAndTime(struct soap *soap, struct _tds__GetSystemDateAndTime *tds__GetSystemDateAndTime, struct _tds__GetSystemDateAndTimeResponse *tds__GetSystemDateAndTimeResponse)
{
	/* Return incomplete response with default data values */
	struct tm now;
	int ntp;

	onvif_dm_get_system_date_time(&ntp, &now);

	CHECK_FIELD(tds__GetSystemDateAndTimeResponse->SystemDateAndTime);
	CHECK_FIELD(tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime);
	CHECK_FIELD(tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Date);
	CHECK_FIELD(tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Time);

	tds__GetSystemDateAndTimeResponse->SystemDateAndTime->DateTimeType = ntp;
	STORE(now.tm_year , tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Date->Year);
	STORE(now.tm_mon , tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Date->Month);
	STORE(now.tm_mday , tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Date->Day);
	STORE(now.tm_hour ,tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Time->Hour);
	STORE(now.tm_min , tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Time->Minute);
	STORE(now.tm_sec , tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Time->Second);
	tds__GetSystemDateAndTimeResponse->SystemDateAndTime->DaylightSavings = now.tm_isdst;

	if (now.tm_zone != NULL) {
		soap_set_field_string(soap, &tds__GetSystemDateAndTimeResponse->SystemDateAndTime->TimeZone->TZ, now.tm_zone);
	}

	return SOAP_OK;
}


/** Auto-test server operation __tds__SetSystemFactoryDefault */
int __tds__SetSystemFactoryDefault(struct soap *soap,
		struct _tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault,
		struct _tds__SetSystemFactoryDefaultResponse *tds__SetSystemFactoryDefaultResponse)
{
	onvif_dm_set_system_factory_default(tds__SetSystemFactoryDefault->FactoryDefault);
	return SOAP_OK;
}


/** Auto-test server operation __tds__SystemReboot */
int __tds__SystemReboot(struct soap *soap,
		struct _tds__SystemReboot *tds__SystemReboot,
		struct _tds__SystemRebootResponse *tds__SystemRebootResponse)
{
	/* Return incomplete response with default data values */
	onvif_dm_reboot_system();
	return SOAP_OK;
}


/** Auto-test server operation __tds__GetAccessPolicy */
int __tds__GetAccessPolicy(struct soap *soap, struct _tds__GetAccessPolicy *tds__GetAccessPolicy, struct _tds__GetAccessPolicyResponse *tds__GetAccessPolicyResponse)
{
	/* Return incomplete response with default data values */
	DBG_LINE
	return SOAP_OK;
}


/** Auto-test server operation __tds__SetAccessPolicy */
int __tds__SetAccessPolicy(struct soap *soap, struct _tds__SetAccessPolicy *tds__SetAccessPolicy, struct _tds__SetAccessPolicyResponse *tds__SetAccessPolicyResponse)
{
	DBG_LINE
	return SOAP_OK;
}








