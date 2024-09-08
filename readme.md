Android Bluetooth Sniffer
===

* Prerequisite
  * Android Phone
    * Rooting
    * Install Termux : https://f-droid.org/en/packages/com.termux/

  * Linux
    * Android Debug Bridge(adb)
    * Install pcap library : sudo apt install libpcap-dev

* How to run
  * Run abs
```
sudo ./abs | wireshark -i - -k
```

<iframe width="560" height="315" src="https://www.youtube.com/embed/U8JoLB9B8kk?si=185wiQV8M_AgWnEg" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>