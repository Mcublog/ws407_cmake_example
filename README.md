# ws407_cmake_example

STM32 Cmake example

![building](/doc/Peek_2022-10-25_21-34.gif)

## Installing toolchaine

Download tar.bz2 with toolchaine from [Arm site](https://developer.arm.com/downloads/-/gnu-rm)
Unzip it to /usr/share

```bash
# unzip bz2
sudo tar xjf gcc-arm-none-eabi-your-version.bz2 -C /usr/share/
```

```bash
# setting simlink
sudo ln -s /usr/share/gcc-arm-none-eabi-your-version/bin/* /usr/bin/
```

```bash
# installing ncurses for GDB
sudo apt install libncurses5
```
