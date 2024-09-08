#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>


#pragma pack(push, 1)
struct btsnoop_packet_header {
	uint32_t org_len_;
	uint32_t inc_len_;
	uint32_t flags_;
	uint32_t drops_;
	uint64_t ts_;

	uint32_t org_len() { return ntohl(org_len_); }
	uint32_t inc_len() { return ntohl(inc_len_); }
	uint32_t flags() { return ntohl(flags_); }
	uint32_t drops() { return ntohl(drops_); }
	uint64_t ts() { return htobe64(ts_); }
};
#pragma pack(pop)

int main() {
	//FILE* fp = popen("adb exe/data/misc/bluetooth/logs/btsnoop_hci.logc-out su -c '/system/bin/tail -c 0 -f /data/misc/bluetooth/logs/btsnoop_hci.log'", "r");
	//FILE* fp = popen("adb exec-out su -c '/data/data/com.termux/files/usr/bin/tail -c 0 -f /data/misc/bluetooth/logs/btsnoop_hci.log'", "r");
	FILE* fp = popen("adb shell \"su -c '/data/data/com.termux/files/usr/bin/tail -c 0 -f /data/misc/bluetooth/logs/btsnoop_hci.log'\"", "r");
	if (fp == nullptr) {
		fprintf(stderr, "can not open pipe\n");
		exit(EXIT_FAILURE);
	}
	setvbuf(fp, NULL, _IONBF, 0);

	while (true) {
		btsnoop_packet_header header;
		memset(&header, 0, sizeof(header));
		int readLen = fread(&header, 1, sizeof(header), fp);
		if (readLen != sizeof(header)) {
			fprintf(stderr, "fread return %d\n", readLen);
			break;
		}
		fprintf(stderr, "\nlen : %u %u %08x\n", header.org_len(), header.inc_len(), header.flags());

		uint32_t payloadLen = header.inc_len();
		static constexpr int BufSize = 65536;
		if (payloadLen >= BufSize) {
			fprintf(stderr, "Too big paylodLen(%d)\n", payloadLen);
			break;
		}

		uint8_t buf[BufSize];
		readLen = fread(buf, 1, payloadLen, fp);
		if (readLen != int(payloadLen)) {
			fprintf(stderr, "readLen=%d payloadLen=%u\n", readLen, payloadLen);
			break;
		}

		for (int i = 0; i < readLen;) {
			printf("%02X ", buf[i]);
			++i;
			if (i != 0) {
				if (i % 16 == 8)
					printf(" ");
				if (i % 16 == 0)
					printf("\n");
			}
		}
		printf("\n");
	}
	pclose(fp);
}
