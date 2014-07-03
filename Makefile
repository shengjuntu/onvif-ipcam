CFLAGS=-I/usr/local/include -I.-g -O0 -DWITH_DOM -DWITH_OPENSSL 
LDFLAGS=-lm -lssl -lcrypto 
all:onvif_server
onvif_client:onvif_client.o soapC.o stdsoap2.o soapClient.o duration.o
onvif_server:onvif_server.o soapC.o stdsoap2.o soapServer.o soapTester.o wsseapi.o mecevp.o smdevp.o dom.o wsaapi.o duration.o onvif_impl.o
clean:
	rm *.o
	rm onvif_server
	rm onvif_client
 

