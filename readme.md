Android Bluetooth Sniffer
===

* Prerequisite
  * Android Phone
    * Rooting
    * Install Termux : https://f-droid.org/en/packages/com.termux/
    * Settings - Developer options - Enable Bluetooth HCP snoop log

  * Linux
    * Android Debug Bridge(adb)
    * Install pcap library : sudo apt install libpcap-dev

* How to run
  * Run abs
```
sudo ./abs | wireshark -i - -k
```

Youtube
===
https://youtu.be/U8JoLB9B8kk?si=Yn3Vk5vswYBSrCua
