How to run
===

* Add virtual network interface
```
sudo ip link add bluetooth0 type dummy; ifconfig bluetooth0 up

```
* Add LD_PRELOAD environment variable
```
export LD_PRELOAD=$PWD/libabspcap.so
```

* Run abs
```
sudo ./abs bluetooth0
```

* Run network sniffer such as wireshark
```
sudo wireshark
```
