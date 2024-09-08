/*
 * These are the types that are the same on all platforms, and that
 * have been defined by <net/bpf.h> for ages.
 */
#define DLT_NULL	0	/* BSD loopback encapsulation */
#define DLT_EN10MB	1	/* Ethernet (10Mb) */
#define DLT_EN3MB	2	/* Experimental Ethernet (3Mb) */
#define DLT_AX25	3	/* Amateur Radio AX.25 */
#define DLT_PRONET	4	/* Proteon ProNET Token Ring */
#define DLT_CHAOS	5	/* Chaos */
#define DLT_IEEE802	6	/* 802.5 Token Ring */
#define DLT_ARCNET	7	/* ARCNET, with BSD-style header */
#define DLT_SLIP	8	/* Serial Line IP */
#define DLT_PPP		9	/* Point-to-point Protocol */
#define DLT_FDDI	10	/* FDDI */

/*
 * Bluetooth HCI UART transport layer (part H:4); requested by
 * Paolo Abeni.
 */
#define DLT_BLUETOOTH_HCI_H4	187

/*
 * Bluetooth HCI UART transport layer (part H:4), with pseudo-header
 * that includes direction information; requested by Paolo Abeni.
 */
#define DLT_BLUETOOTH_HCI_H4_WITH_PHDR	201

/*
 * Bluetooth Low Energy air interface link-layer packets.
 *
 * Requested by Mike Kershaw <dragorn@kismetwireless.net>.
 */
#define DLT_BLUETOOTH_LE_LL	251

/*
 * Bluetooth Linux Monitor headers for the BlueZ stack.
 */
#define DLT_BLUETOOTH_LINUX_MONITOR	254

/*
 * Bluetooth Basic Rate/Enhanced Data Rate baseband packets, as
 * captured by Ubertooth.
 */
#define DLT_BLUETOOTH_BREDR_BB	255

/*
 * Bluetooth Low Energy link layer packets, as captured by Ubertooth.
 */
#define DLT_BLUETOOTH_LE_LL_WITH_PHDR	256

int pcap_datalink(void* p) {
    return DLT_BLUETOOTH_HCI_H4;
}
