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

void dump(unsigned char* p, size_t n) {
	for (size_t i = 0; i < n;) {
		fprintf(stderr, "%02X ", p[i]);
		++i;
		if (i != 0) {
			if (i % 16 == 8)
				fprintf(stderr, " ");
			if (i % 16 == 0)
				fprintf(stderr, "\n");
		}
	}
	fprintf(stderr, "\n");
}

int main() {
	FILE* fp = popen("adb shell \"su -c '/data/data/com.termux/files/usr/bin/tail -c 0 -f /data/misc/bluetooth/logs/btsnoop_hci.log'\"", "r");
	if (fp == nullptr) {
		fprintf(stderr, "can not open pipe\n");
		exit(EXIT_FAILURE);
	}
	setvbuf(fp, NULL, _IONBF, 0);

	pcap_t* pcap = pcap_open_dead(DLT_BLUETOOTH_HCI_H4_WITH_PHDR, 0);
	if (pcap == nullptr) {
		fprintf(stderr, "pcap_open_dead return null");
		return EXIT_FAILURE;
	}

	pcap_dumper_t* pcap_dumper = pcap_dump_fopen(pcap, stdout);
	if (pcap_dumper == nullptr) {
		fprintf(stderr, "pcap_dump_fopen return null");
		return EXIT_FAILURE;
	}
	pcap_dump_flush(pcap_dumper);

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

		pcap_pkthdr pkthdr;
		gettimeofday(&pkthdr.ts, nullptr);
		// strange to say buf, size must added by 4
		pkthdr.caplen = pkthdr.len = bpf_u_int32(readLen + 4);
		pcap_dump(reinterpret_cast<u_char*>(pcap_dumper), &pkthdr, buf - 4);
		pcap_dump_flush(pcap_dumper);
	}
	pclose(fp);
	pcap_close(pcap);
}
