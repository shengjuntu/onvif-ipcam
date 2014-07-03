#include "soapH.h"
#include <assert.h>
#include "onvif_impl.h"

//following functions used to simplify set xxxResponse fields
void soap_set_field_string(struct soap* soap, char ** p_field, const char* val) {
	assert(val != 0);
	*p_field = soap_malloc(soap, strlen(val) + 1);
	strcpy(*p_field, val);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//an device implement can overwrite these functions.
//device management functions

#define IPV4_ADDRESS "192.168.1.2"
#define WSDL_URL "http://192.168.1.2/onvif/ver10/device/wsdl/devicemgmt.wsdl"
#define SERVICE_URL "http://192.168.1.2/onvif/services"
#define SERVICE_NAMESPACE "http://www.onvif.org/ver10/events/wsdl"

const char * onvif_dm_get_ipv4_address() {
	return IPV4_ADDRESS;
}

const char * onvif_dm_get_wsdl_url() {
	return WSDL_URL;
}

const char * onvif_dm_get_service_url() {
	return SERVICE_URL;
}

const char * onvif_dm_get_service_namespace() {
	return SERVICE_NAMESPACE;
}

void onvif_dm_get_service_version(int* major, int * minor) {
	*major = 1;
	*minor = 3;
}

const char* onvif_dm_get_manufacturer() {
	return "NewBee";
}
const char* onvif_dm_get_model() {
	return "102";
}
const char* onvif_dm_get_firmware_version() {
	return "1.1";
}
const char* onvif_dm_get_serial_number() {
	return "333-133-333";
}
const char* onvif_dm_get_hardware_id() {
	return "free_scale_333";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//media

#define VIDEO_FRAME_RATE 30
#define VIDEO_WIDTH 1280
#define VIDEO_HEIGHT 720
#define VIDEO_TOKEN "TOKEN_ONVIF_VIDEO_V4L2"
#define VIDEO_BRIGHTNESS (128)
#define VIDEO_COLOR_SATURATION (128)
#define VIDEO_CONTRAST (128)
#define VIDEO_IR_CUT_FILTER (0)
#define VIDEO_SHARPNESS (128)


int onvif_media_get_video_frame_rate() {
	return VIDEO_FRAME_RATE;
}

int onvif_media_get_video_width() {
	return VIDEO_WIDTH;
}

int onvif_media_get_video_height() {
	return VIDEO_HEIGHT;
}

char* onvif_media_get_video_token() {
	return VIDEO_TOKEN;
}

float onvif_media_get_video_brightness() {
	return VIDEO_BRIGHTNESS;
}

float onvif_media_get_video_color_saturation() {
	return VIDEO_COLOR_SATURATION;
}

float onvif_media_get_video_contrast() {
	return VIDEO_CONTRAST;
}
int onvif_media_get_video_ir_cut_filter() {
	return VIDEO_IR_CUT_FILTER;
}

float onvif_media_get_video_sharpness() {
	return VIDEO_SHARPNESS;
}

int onvif_media_get_video_backlight_compensation_mode() {
	return 0;
}

int onvif_media_get_video_backlight_compensation_level() {
	return 20;
}

int onvif_media_get_video_wide_dynamic_range_mode() {
	return 0;
}

int onvif_media_get_video_wide_dynamic_range_level() {
	return 20;
}

int onvif_media_get_video_white_balance_mode() {
	return 0;
}

int onvif_media_get_video_white_balance_cr_gain() {
	return 0;
}

int onvif_media_get_video_white_balance_cb_gain() {
	return 0;
}


void onvif_dm_set_system_date_time(int is_ntp, struct tm* now) {
}

void onvif_dm_get_system_date_time(int* is_ntp, struct tm* now) {
}

void onvif_dm_set_system_factory_default(int type) {
}

void onvif_dm_reboot_system() {
}


