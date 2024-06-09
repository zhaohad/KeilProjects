#ifndef __CODE_LIB_H__
#define __CODE_LIB_H__
#include "typedef.h"

u8 code_165_to_9239(u8 i_165, u8 d) {
	switch (i_165) {
		case 0:
			switch (d) {
				case 0x01:
					return 0x35;
				case 0x02:
					return 0x2b;
				case 0x04:
					return 0x3a;
				case 0x08:
					return 0x29;
				case 0x10:
					return 0x14;
				case 0x20:
					return 0x1e;
				case 0x40:
					return 0x1f;
				case 0x80:
					return 0x1a;
			}
			break;
		case 1:
			switch (d) {
				case 0x01:
					return 0x22;
				case 0x02:
					return 0x21;
				case 0x04:
					return 0x3c;
				case 0x08:
					return 0x3b;
				case 0x10:
					return 0x20;
				case 0x20:
					return 0x08;
				case 0x40:
					return 0x15;
				case 0x80:
					return 0x17;
			}
			break;
		case 2:
			switch (d) {
				case 0x01:
					return 0x23;
				case 0x02:
					return 0x25;
				case 0x04:
					return 0x24;
				case 0x08:
					return 0x3d;
				case 0x10:
					return 0x3e;
				case 0x20:
					return 0x1c;
				case 0x40:
					return 0x0c;
				case 0x80:
					return 0x18;
			}
			break;
		case 3:
			switch (d) {
				case 0x01:
					return 0x13;
				case 0x02:
					return 0x12;
				case 0x04:
					return 0x27;
				case 0x08:
					return 0x26;
				case 0x10:
					return 0x41;
				case 0x20:
					return 0x42;
				case 0x40:
					return 0x40;
				case 0x80:
					return 0x3f;
			}
			break;
		case 4:
			switch (d) {
				case 0x01:
					return 0x2d;
				case 0x02:
					return 0x2e;
				case 0x04:
					return 0x2f;
				case 0x08:
					return 0x30;
				case 0x10:
					return 0x46;
				case 0x20:
					return 0x45;
				case 0x40:
					return 0x44;
				case 0x80:
					return 0x43;
			}
			break;
		case 5:
			switch (d) {
				case 0x01:
					return 0x4c;
				case 0x02:
					return 0x4d;
				case 0x04:
					return 0x4e;
				case 0x08:
					return 0x47;
				case 0x10:
					return 0x48;
				case 0x20:
					return 0x4b;
				case 0x40:
					return 0x4a;
				case 0x80:
					return 0x49;
			}
			break;
		case 6:
			switch (d) {
				case 0x01:
					return 0xe5; // shift r
				case 0x02:
					return 0x65; // APP
				case 0x04:
					return 0xe4; // ctrl r
				case 0x08:
					return 0x58;
				case 0x10:
					return 0x50;
				case 0x20:
					return 0x51;
				case 0x40:
					return 0x52;
				case 0x80:
					return 0x4f;
			}
			break;
		case 7:
			switch (d) {
				case 0x01:
					return 0x31; // keycode 29
				case 0x02:
					return 0x2a;
				case 0x04:
					return 0x34;
				case 0x08:
					return 0x33;
				case 0x10:
					return 0x38;
				case 0x20:
					return 0x37;
				case 0x40:
					return 0x0; // fn
				case 0x80:
					return 0xe6;
			}
			break;
		case 8:
			switch (d) {
				case 0x01:
					return 0x0e;
				case 0x02:
					return 0x0d;
				case 0x04:
					return 0x0b;
				case 0x08:
					return 0x36;
				case 0x10:
					return 0x0f;
				case 0x20:
					return 0x10;
				case 0x40:
					return 0x11;
				case 0x80:
					return 0x05;
			}
			break;
		case 9:
			switch (d) {
				case 0x01:
					return 0xe2;
				case 0x02:
					return 0x2c;
				case 0x04:
					return 0x16;
				case 0x08:
					return 0x06;
				case 0x10:
					return 0x19;
				case 0x20:
					return 0x0a;
				case 0x40:
					return 0x09;
				case 0x80:
					return 0x07;
			}
			break;
		case 10:
			switch (d) {
				case 0x01:
					return 0x00; // ext
				case 0x02:
					return 0xe1;
				case 0x04:
					return 0xe0;
				case 0x08:
					return 0x39;
				case 0x10:
					return 0x1b;
				case 0x20:
					return 0x1d;
				case 0x40:
					return 0x04;
				case 0x80:
					return 0xe3;
			}
			break;
	}
	return 0;
}

#endif