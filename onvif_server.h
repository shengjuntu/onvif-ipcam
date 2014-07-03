#ifndef __ONVIF_SERVER_H__
#define __ONVIF_SERVER_H__

/*
int onvif__trt__GetVideoSources(struct soap* soap,
		struct _trt__GetVideoSources *trt__GetVideoSources,
		struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse);

	{"tds", "http://www.onvif.org/ver10/device/wsdl", NULL, NULL},
	{"tev", "http://www.onvif.org/ver10/events/wsdl", NULL, NULL},
	{"timg", "http://www.onvif.org/ver20/imaging/wsdl", NULL, NULL},
	{"tmd", "http://www.onvif.org/ver10/deviceIO/wsdl", NULL, NULL},
	{"trt", "http://www.onvif.org/ver10/media/wsdl", NULL, NULL},

*/

#define DECLARE_SOAP_SERVICE(prefix,name) \
int __##prefix##__##name(struct soap *, struct _##prefix##__##name *, struct _##prefix##__##name##Response *);


#define IMPL_SOAP_SERVICE(prefix,name) \
void __##prefix##__##name(struct soap * soap, struct _##prefix##__##name * req, struct _##prefix##__##name##Response * response) {\
	DBG_LINE;\
	return SOAP_OK;\
}



#endif
