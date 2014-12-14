/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_HOSTPROXY_TCP_H
#define USBPROXY_HOSTPROXY_TCP_H

#include "HostProxy.h"
#include "TCP_Helper.h"

class HostProxy_TCP: public HostProxy {
private:
	bool p_is_connected;
	TCP_Helper* network;

public:
	static int debugLevel;
	HostProxy_TCP(const char* address=NULL);
	HostProxy_TCP(ConfigParser *cfg);
	virtual ~HostProxy_TCP();

	int connect(Device *device,int timeout=250);
	void disconnect();
	void reset();
	bool is_connected();

	//CLEANUP is this the best way to indicate whether there was a request?
	//return 0 in usb_ctrlrequest->brequest if there is no request
	int control_request(usb_ctrlrequest *setup_packet, int *nbytes, __u8** dataptr, int timeout=500);
	void send_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8* dataptr,int length);
	bool send_wait_complete(__u8 endpoint, int timeout=500);
	void receive_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8** dataptr, int* length, int timeout=500);
	void control_ack();
	void stall_ep(__u8 endpoint);

	void setConfig(Configuration* fs_cfg,Configuration* hs_cfg,bool hs);

	char* toString() {return (char *) "TCP host proxy";}
};

#endif /* USBPROXY_HOSTPROXY_TCP_H */
