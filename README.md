# README.md

Prerequisites: Linux kernel version >= 5.0.0

My envinonment: 

* Ubuntu 18.04.3 LTS
* gcc-4.8
* Kernel version: 5.3.0-40-generic

## 1. Enable binder driver.

### Step 1

Load the kernel modules:

```
sudo modprobe ashmem_linux
sudo modprobe binder_linux
```

### Step 2

Mount binderfs:

```
sudo mkdir /dev/binderfs
sudo mount -t binder binder /dev/binderfs
```

After those steps, two items should appear in /dev:

* /dev/ashmem
* /dev/binderfs/

## 2. Build

```
sudo apt install linux-headers-$(uname -r)
cd src
make all
```

## 3. Create binder device

```
sudo ./src/build/bin/binder_ctl /dev/binderfs/binder-control my-binder
```

## 4. Start service manager  

```
sudo ./src/build/bin/service_manager /dev/binderfs/my-binder &
```

## 5. Run test

```
sudo ./src/build/bin/test_server &
sudo ./src/build/bin/test_client
```

Should see test_client prints messages to stdout.

## Ref:

* https://github.com/hungys/binder-for-linux
* https://brauner.github.io/2019/01/09/android-binderfs.html

Sources may from those links, special thank to the author!  
