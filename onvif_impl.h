#ifndef __ONVIF_IMPL_H__
#define __ONVIF_IMPL_H__

#include <time.h>

#define DBG_LINE printf("enter: %s\n", __FUNCTION__);
#define DBG_TAG(l) printf("dbg:%s %s\n", __FUNCTION__, l);

#define TRUE 1
#define FALSE 0


#define CHECK_FIELD(em) \
if (em == NULL) {\
	size_t size = sizeof(*em);\
	em = soap_malloc(soap, size);\
	memset(em, 0, size);\
}\

#define LOAD_FIELD(obj1, name1, obj2, name2) \
	(obj1).(name1) = (obj2).(name2);

#define STORE_FIELD(obj1, name1, obj2, name2) \
	 (obj2).(name2) = (obj1).(name1);



#define LOAD(val1, val2) \
	val1 = val2;

#define STORE(val1, val2) \
	 val2 = val1;


void soap_set_field_string(struct soap* soap, char ** p_field, const char* val);


const char * onvif_dm_get_ipv4_address();
const char * onvif_dm_get_wsdl_url();
const char * onvif_dm_get_service_url();
const char * onvif_dm_get_service_namespace();
void onvif_dm_get_service_version(int* major, int * minor);

const char* onvif_dm_get_manufacturer();
const char* onvif_dm_get_model();
const char* onvif_dm_get_firmware_version();
const char* onvif_dm_get_serial_number();
const char* onvif_dm_get_hardware_id();


void onvif_dm_set_system_date_time(int is_ntp, struct tm* now);
void onvif_dm_get_system_date_time(int* is_ntp, struct tm* now);

void onvif_dm_set_system_factory_default(int type);
void onvif_dm_reboot_system();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int onvif_media_get_video_frame_rate();
int onvif_media_get_video_width();
int onvif_media_get_video_height();
char* onvif_media_get_video_token();

float onvif_media_get_video_brightness();
float onvif_media_get_video_color_saturation();
float onvif_media_get_video_contrast();
int onvif_media_get_video_ir_cut_filter();
float onvif_media_get_video_sharpness();
int onvif_media_get_video_backlight_compensation_mode();
int onvif_media_get_video_backlight_compensation_level();
int onvif_media_get_video_wide_dynamic_range_mode();
int onvif_media_get_video_wide_dynamic_range_level();
int onvif_media_get_video_white_balance_mode();
int onvif_media_get_video_white_balance_cr_gain();
int onvif_media_get_video_white_balance_cb_gain();

#endif
