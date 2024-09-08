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

* Add virtual network interface
```
sudo ip link add bluetooth0 type dummy; ifconfig bluetooth0 up
```

* Run abs
```
sudo ./abs bluetooth0
```

* Add LD_PRELOAD environment variable
```
export LD_PRELOAD=$PWD/libabspcap.so
```

* Run network sniffer such as wireshark
```
sudo wireshark
```
