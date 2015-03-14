/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_LIBUSB_H
#define USBPROXY_DEVICEPROXY_LIBUSB_H

#ifndef LIBUSB_HOTPLUG_MATCH_ANY
#define LIBUSB_HOTPLUG_MATCH_ANY -1
#endif

#include <libusb-1.0/libusb.h>
#include "DeviceProxy.h"

class DeviceProxy_LibUSB:public DeviceProxy {
private:
	libusb_context* context;
	libusb_hotplug_callback_handle callback_handle;
	libusb_device_handle* dev_handle;
	bool privateContext;
	bool privateDevice;
	int desired_vid;
	int desired_pid;
	bool desired_hubs;

public:
	DeviceProxy_LibUSB(int vendorId=LIBUSB_HOTPLUG_MATCH_ANY,int productId=LIBUSB_HOTPLUG_MATCH_ANY,bool includeHubs=false);
	DeviceProxy_LibUSB(ConfigParser *cfg);
	~DeviceProxy_LibUSB();

	int connect(int timeout=250);
	int connect(int vendorId,int productId,bool includeHubs);
	int connect(libusb_device* dvc, libusb_context* _context=NULL);
	int connect(libusb_device_handle* devh,libusb_context* _context=NULL);
	void disconnect();
	void reset();
	bool is_connected();
	bool is_highspeed();


	int control_request(const usb_ctrlrequest *setup_packet, int *nbytes, __u8* dataptr,int timeout=500);
	void send_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8* dataptr,int length);
	void receive_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8** dataptr, int* length,int timeout=500);

	void setConfig(Configuration* fs_cfg,Configuration* hs_cfg,bool hs) {}

	void claim_interface(__u8 interface);
	void release_interface(__u8 interface);

	__u8 get_address();
	char* toString();
};

#endif /* USBPROXY_DEVICEPROXY_LIBUSB_H */
