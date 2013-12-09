/*
 * Copyright 2013 Dominic Spill
 * Copyright 2013 Adam Stasiak
 *
 * This file is part of USBProxy.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 *
 * Injector.h
 *
 * Created on: Nov 12, 2013
 */
#ifndef USBPROXY_INJECTOR_H
#define USBPROXY_INJECTOR_H

#include <mqueue.h>
#include <boost/atomic.hpp>

#include "Manager.h"
#include "Packet.h"
#include "Criteria.h"

class Manager;

class Injector {
private:
	mqd_t outQueues[16];
	mqd_t inQueues[16];

protected:
	virtual Packet* get_packets()=0;
	virtual void start_injector() {}
	virtual void stop_injector() {}

public:
	struct criteria_endpoint endpoint;
	struct criteria_interface interface;
	struct criteria_configuration configuration;
	struct criteria_device device;

	boost::atomic_bool halt;

	Injector();
	virtual ~Injector() {}

	void set_queue(__u8 epAddress,mqd_t queue);

	void listen();

	static void *listen_helper(void* context);

	virtual const char* toString() {return "Injector";}

};

#endif /* USBPROXY_INJECTOR_H */