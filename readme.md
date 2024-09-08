Android Bluetooth Sniffer
===

* Prerequisite
  * Android Phone
    * Rooting
    * Install Termux : https://f-droid.org/en/packages/com.termux/

  * Linux
    * Android Debug Bridge(adb)
    * Install pcap library : sudo apt install libpcap-dev

How to run
===

* Run abs
```
sudo ./abs | wireshark -i - -k
```
