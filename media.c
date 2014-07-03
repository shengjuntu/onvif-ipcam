#include "soapH.h"
#include "onvif_impl.h"

int __trt__GetVideoSources(struct soap* soap,
		struct _trt__GetVideoSources *trt__GetVideoSources,
		struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse) {


	ACCESS_CONTROL;
	trt__GetVideoSourcesResponse->__sizeVideoSources = 1;

	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Resolution)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Resolution)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Brightness)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->ColorSaturation)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Contrast)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->IrCutFilter)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Sharpness)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->BacklightCompensation)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WideDynamicRange)
	CHECK_FIELD(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WhiteBalance)


	trt__GetVideoSourcesResponse->VideoSources[0].Framerate = onvif_media_get_video_frame_rate();
	trt__GetVideoSourcesResponse->VideoSources[0].Resolution->Height = onvif_media_get_video_height();
	trt__GetVideoSourcesResponse->VideoSources[0].Resolution->Width = onvif_media_get_video_width();
	soap_set_field_string(soap, &trt__GetVideoSourcesResponse->VideoSources[0].token, onvif_media_get_video_token());

	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Brightness[0] = onvif_media_get_video_brightness();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->ColorSaturation[0] = onvif_media_get_video_color_saturation();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Contrast[0] = onvif_media_get_video_contrast();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->IrCutFilter[0] = onvif_media_get_video_ir_cut_filter();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Sharpness[0] = onvif_media_get_video_sharpness();


	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->BacklightCompensation->Mode = onvif_media_get_video_backlight_compensation_mode();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->BacklightCompensation->Level = onvif_media_get_video_backlight_compensation_level();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WideDynamicRange->Mode = onvif_media_get_video_wide_dynamic_range_mode();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WideDynamicRange->Level = onvif_media_get_video_wide_dynamic_range_level();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WhiteBalance->Mode = onvif_media_get_video_white_balance_mode();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WhiteBalance->CrGain = onvif_media_get_video_white_balance_cr_gain();
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WhiteBalance->CbGain = onvif_media_get_video_white_balance_cb_gain();

	return SOAP_OK;
}

int __trt__GetProfile(struct soap* soap,
		struct _trt__GetProfile *trt__GetProfile,
		struct _trt__GetProfileResponse *trt__GetProfileResponse) {

	ACCESS_CONTROL;

	printf("token:%s\n", trt__GetProfile->ProfileToken);

	CHECK_FIELD(trt__GetProfileResponse->Profile);

	CHECK_FIELD(trt__GetProfileResponse->Profile[0].VideoSourceConfiguration)
	CHECK_FIELD(trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->Bounds)

	soap_set_field_string(soap, &trt__GetProfileResponse->Profile[0].Name, "my_profile");
	soap_set_field_string(soap, &trt__GetProfileResponse->Profile[0].token, "token_profile");
	soap_set_field_string(soap, &trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->Name, "VS_Name");
	soap_set_field_string(soap, &trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->token, "VS_Token");
	soap_set_field_string(soap, &trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->SourceToken,onvif_media_get_video_token());

	trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->UseCount = 1;
	trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->Bounds->x = 1;
	trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->Bounds->y = 1;
	trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->Bounds->height = onvif_media_get_video_height();
	trt__GetProfileResponse->Profile[0].VideoSourceConfiguration->Bounds->width = onvif_media_get_video_width();



	CHECK_FIELD(trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration)
	CHECK_FIELD(trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->Resolution)
	CHECK_FIELD(trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->RateControl)

	soap_set_field_string(soap, &trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->Name,"VE_Name1");
	soap_set_field_string(soap, &trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->token,"VE_token1");
	trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->UseCount = 1;
	trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->Quality = 10;
	trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->Encoding = 2;//JPEG = 0, MPEG4 = 1, H264 = 2;
	trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->Resolution->Height = onvif_media_get_video_height();
	trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->Resolution->Width = onvif_media_get_video_width();
	trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->RateControl->FrameRateLimit = onvif_media_get_video_frame_rate();
	trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->RateControl->EncodingInterval = 1;
	trt__GetProfileResponse->Profile[0].VideoEncoderConfiguration->RateControl->BitrateLimit = 500;

	return SOAP_OK;
}

int __trt__GetProfiles(struct soap* soap,
		struct _trt__GetProfiles *trt__GetProfiles,
		struct _trt__GetProfilesResponse *trt__GetProfilesResponse) {

	ACCESS_CONTROL;

	trt__GetProfilesResponse->__sizeProfiles = 1;

	CHECK_FIELD(trt__GetProfilesResponse->Profiles)
	CHECK_FIELD(trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration)
	CHECK_FIELD(trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds)

	soap_set_field_string(soap, &trt__GetProfilesResponse->Profiles[0].Name, "my_profile");
	soap_set_field_string(soap, &trt__GetProfilesResponse->Profiles[0].token, "token_profile");
	soap_set_field_string(soap, &trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Name, "VS_Name");
	soap_set_field_string(soap, &trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->token, "VS_Token");
	soap_set_field_string(soap, &trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->SourceToken,onvif_media_get_video_token());

	trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->UseCount = 1;
	trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds->x = 1;
	trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds->y = 1;
	trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds->height = onvif_media_get_video_height();
	trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds->width = onvif_media_get_video_width();



	CHECK_FIELD(trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration)
	CHECK_FIELD(trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Resolution)
	CHECK_FIELD(trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->RateControl)

	soap_set_field_string(soap, &trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Name,"VE_Name1");
	soap_set_field_string(soap, &trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->token,"VE_token1");
	trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->UseCount = 1;
	trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Quality = 10;
	trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Encoding = 2;//JPEG = 0, MPEG4 = 1, H264 = 2;
	trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Resolution->Height = onvif_media_get_video_height();
	trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Resolution->Width = onvif_media_get_video_width();
	trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->RateControl->FrameRateLimit = onvif_media_get_video_frame_rate();
	trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->RateControl->EncodingInterval = 1;
	trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->RateControl->BitrateLimit = 500;

	printf("GetProfiles\n");

	return SOAP_OK;
}


/** Auto-test server operation __trt__GetStreamUri */
int __trt__GetStreamUri(struct soap *soap, struct _trt__GetStreamUri *trt__GetStreamUri, struct _trt__GetStreamUriResponse *trt__GetStreamUriResponse)
{
	/* Return incomplete response with default data values */
	ACCESS_CONTROL

	CHECK_FIELD(trt__GetStreamUriResponse->MediaUri)
	soap_set_field_string(soap, &trt__GetStreamUriResponse->MediaUri->Uri, "rtsp://192.168.1.2:8554/1.mkv");

	return SOAP_OK;
}


