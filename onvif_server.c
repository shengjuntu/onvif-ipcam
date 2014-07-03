#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "soapH.h"

#define PORT 8080

const char *TMPDIR = ".";


struct mime_server_handle
{ char *key;	/* file name */
  FILE *fd;	/* file fd */
};

void *mime_server_write_open(struct soap *soap, void *unused_handle,
		const char *id, const char *type, const char *description,
		enum soap_mime_encoding encoding) { /* Note: the 'unused_handle' is always NULL */
	/* Return NULL without setting soap->error if we don't want to use the streaming callback for this DIME attachment */
	const char *file;
	struct mime_server_handle *handle = soap_malloc(soap,
			sizeof(struct mime_server_handle));
	if (!handle) {
		soap->error = SOAP_EOM;
		return NULL;
	}
	/* Create a new file */
	file = tempnam(TMPDIR, "data");
	/* The file name is also the key */
	handle->key = soap_strdup(soap, file);
	handle->fd = fopen(file, "wb");
	free((void*) file);
	if (!handle->fd) {
		soap->error = soap_sender_fault(soap,
				"Cannot save data to file", handle->key);
		soap->errnum = errno; /* get reason */
		return NULL;
	}
	fprintf(stderr, "Saving file %s type %s\n", handle->key,
			type ? type : "");
	return (void*) handle;
}

void mime_server_write_close(struct soap *soap, void *handle) {
	fclose(((struct mime_server_handle*) handle)->fd);
}

int mime_server_write(struct soap *soap, void *handle, const char *buf,
		size_t len) {
	FILE *fd = ((struct mime_server_handle*) handle)->fd;
	while (len) {
		size_t nwritten = fwrite(buf, 1, len, fd);
		if (!nwritten) {
			soap->errnum = errno;
			return SOAP_EOF;
		}
		len -= nwritten;
		buf += nwritten;
	}
	return SOAP_OK;
}

int main(int argc, char * argv[]) {
	SOAP_SOCKET m, s;
	struct soap soap;

	soap_init1(&soap, SOAP_ENC_MTOM);


	m = soap_bind(&soap, NULL, PORT, 100);
	if (!soap_valid_socket(m)) {
		soap_print_fault(&soap, stderr);
		exit(-1);
	}

	printf("socket bind success %d\n", m);

	soap.fmimewriteopen = mime_server_write_open;
	soap.fmimewriteclose = mime_server_write_close;
	soap.fmimewrite = mime_server_write;

	for (;;) {
		printf("socket connect %d\n", s);
		s = soap_accept(&soap);
		if (!soap_valid_socket(s)) {
			soap_print_fault(&soap, stderr);
			exit(-1);
		}
		if (soap_serve(&soap) != SOAP_OK) {
			soap_print_fault(&soap, stderr);
		}
		soap_destroy(&soap);
		soap_end(&soap);

	}

	soap_done(&soap);
	return 0;
}

