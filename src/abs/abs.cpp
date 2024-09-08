#include <arpa/inet.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

struct Param {
	char *intfName_{nullptr};

	bool parse(int argc, char** argv) {
		if (argc != 2) {
			usage();
			return false;
		}

		intfName_ = argv[1];

		return true;
	}

	static void usage() {
		printf("syntax: abs <interface>\n");
		printf("sample: abs bluetooth0\n");

	}
};

void dump(unsigned char* p, size_t n) {
	for (size_t i = 0; i < n;) {
		printf("%02X ", p[i]);
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

int main(int argc, char* argv[]) {
	Param param;
	if (!param.parse(argc, argv)) return EXIT_FAILURE;

	FILE* fp = popen("adb shell \"su -c '/data/data/com.termux/files/usr/bin/tail -c 0 -f /data/misc/bluetooth/logs/btsnoop_hci.log'\"", "r");
	if (fp == nullptr) {
		fprintf(stderr, "can not open pipe\n");
		exit(EXIT_FAILURE);
	}
	setvbuf(fp, NULL, _IONBF, 0);

	char* dev = argv[1];
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* pcap = pcap_open_live(dev, 0, 0, 0, errbuf);
	if (pcap == nullptr) {
		fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
		return EXIT_FAILURE;
	}
	printf("datalink=%d\n", pcap_datalink(pcap));

	while (true) {
		btsnoop_packet_header header;
		memset(&header, 0, sizeof(header));
		size_t readLen = fread(&header, 1, sizeof(header), fp);
		if (readLen != sizeof(header)) {
			fprintf(stderr, "fread return %lu\n", readLen);
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
		if (readLen != payloadLen) {
			fprintf(stderr, "readLen=%lu payloadLen=%u\n", readLen, payloadLen);
			break;
		}
		dump(buf, readLen);

		int res = pcap_inject(pcap, buf, readLen);
		printf("pcap_inject return %d\n", res);
		// int res = pcap_sendpacket(pcap, reinterpret_cast<const u_char*>(buf), readLen+50);
		// if (res != 0) {
		// 	fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(pcap));
		// 	break;
		// }
	}
	pclose(fp);
	pcap_close(pcap);
}
