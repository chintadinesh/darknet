# EE382M SOC report <!--[github link](https://github.com/CHINTADINESH/darknet.git) -->
- [Lab1 setup link](http://users.ece.utexas.edu/~gerstl/ece382m_f21/labs/lab1.htm)

## Miscellaneous points while lab setup.
1. We used screen to connect to the board instead of Minicom. Reason: not able 
    ```bash
    sudo screen -L /dev/ttyUSB1 115200
    ```
2. Login credentials:
   i. Username: ultra96
   ii. Password: ultra96

3. For a graceful shutdown, please use the fillowing command
    ```bash
    sudo halt
    ```

4. Apply the patch for mAP calculation as shown below.
    ```bash
    wget http://www.ece.utexas.edu/~gerstl/ece382m_f21/labs/lab1/darknet-map.patch
    patch -p0 -b < darknet-map.patch
    make clean
    make
    ```

## Experiments
### Where we did our experiments:
* We did experiments on two machines:
    * For functional testing: Intel CPU
      <details><summary>lshw output</summary>
      <p>
      ub18
          description: Notebook
          product: HP Pavilion Notebook (M2W75PA#ACJ)
          vendor: Hewlett-Packard
          version: Type1ProductConfigId
          serial: 5CD5263JFN
          width: 64 bits
          capabilities: smbios-2.8 dmi-2.8 smp vsyscall32
          configuration: administrator_password=disabled boot=normal chassis=notebook family=103C_5335KV G=N L=CON B=HP S=PAV X=Null sku=M2W75PA#ACJ uuid=35434435-3236-334A-464E-3CA82AB08ED6
        *-core
            description: Motherboard
            product: 8096
            vendor: Hewlett-Packard
            physical id: 0
            version: 89.11
            serial: PFDXH018J8U572
            slot: Type2 - Board Chassis Location
          *-firmware
          description: BIOS
          vendor: Insyde
          physical id: 0
          version: F.03
          date: 03/31/2015
          size: 128KiB
          capacity: 6MiB
          capabilities: pci upgrade shadowing cdboot bootselect edd int13floppynec int13floppytoshiba int13floppy360 int13floppy1200 int13floppy720 int13floppy2880 int9keyboard int10video acpi usb biosbootspecification uefi
          *-cpu
          description: CPU
          product: Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz
          vendor: Intel Corp.
          physical id: 4
          bus info: cpu@0
          version: Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz
          serial: To Be Filled By O.E.M.
          slot: U3E1
          size: 947MHz
          capacity: 2700MHz
          width: 64 bits
          clock: 100MHz
          capabilities: lm fpu fpu_exception wp vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp x86-64 constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid rdseed adx smap intel_pt xsaveopt dtherm ida arat pln pts md_clear flush_l1d cpufreq
          configuration: cores=2 enabledcores=2 threads=4
        *-cache:0
            description: L1 cache
            physical id: 6
            slot: L1 Cache
            size: 32KiB
            capacity: 32KiB
            capabilities: synchronous internal write-back instruction
            configuration: level=1
        *-cache:1
            description: L2 cache
            physical id: 7
            slot: L2 Cache
            size: 256KiB
            capacity: 256KiB
            capabilities: synchronous internal write-back unified
            configuration: level=2
        *-cache:2
            description: L3 cache
            physical id: 8
            slot: L3 Cache
            size: 3MiB
            capacity: 3MiB
            capabilities: synchronous internal write-back unified
            configuration: level=3
          *-cache
          description: L1 cache
          physical id: 5
          slot: L1 Cache
          size: 32KiB
          capacity: 32KiB
          capabilities: synchronous internal write-back data
          configuration: level=1
          *-memory
          description: System Memory
          physical id: 16
          slot: System board or motherboard
          size: 8GiB
        *-bank:0
            description: SODIMM DDR3 Synchronous 1600 MHz (0.6 ns)
            product: M471B1G73QH0-YK0
            vendor: Samsung
            physical id: 0
            serial: 18671515
            slot: Bottom-Slot 1(left)
            size: 8GiB
            width: 64 bits
            clock: 1600MHz (0.6ns)
        *-bank:1
            description: DIMM [empty]
            physical id: 1
            slot: Bottom-Slot 2(right)
          *-pci
          description: Host bridge
          product: Broadwell-U Host Bridge -OPI
          vendor: Intel Corporation
          physical id: 100
          bus info: pci@0000:00:00.0
          version: 09
          width: 32 bits
          clock: 33MHz
          configuration: driver=bdw_uncore
          resources: irq:0
        *-display
            description: VGA compatible controller
            product: HD Graphics 5500
            vendor: Intel Corporation
            physical id: 2
            bus info: pci@0000:00:02.0
            version: 09
            width: 64 bits
            clock: 33MHz
            capabilities: msi pm vga_controller bus_master cap_list rom
            configuration: driver=i915 latency=0
            resources: irq:52 memory:c3000000-c3ffffff memory:d0000000-dfffffff ioport:7000(size=64) memory:c0000-dffff
        *-multimedia:0
            description: Audio device
            product: Broadwell-U Audio Controller
            vendor: Intel Corporation
            physical id: 3
            bus info: pci@0000:00:03.0
            version: 09
            width: 64 bits
            clock: 33MHz
            capabilities: pm msi pciexpress bus_master cap_list
            configuration: driver=snd_hda_intel latency=0
            resources: irq:55 memory:c6218000-c621bfff
        *-generic
            description: Signal processing controller
            product: Broadwell-U Processor Thermal Subsystem
            vendor: Intel Corporation
            physical id: 4
            bus info: pci@0000:00:04.0
            version: 09
            width: 64 bits
            clock: 33MHz
            capabilities: msi pm bus_master cap_list
            configuration: driver=proc_thermal latency=0
            resources: irq:16 memory:c6210000-c6217fff
        *-usb
            description: USB controller
            product: Wildcat Point-LP USB xHCI Controller
            vendor: Intel Corporation
            physical id: 14
            bus info: pci@0000:00:14.0
            version: 03
            width: 64 bits
            clock: 33MHz
            capabilities: pm msi xhci bus_master cap_list
            configuration: driver=xhci_hcd latency=0
            resources: irq:47 memory:c6200000-c620ffff
          *-usbhost:0
          product: xHCI Host Controller
          vendor: Linux 5.4.0-81-generic xhci-hcd
          physical id: 0
          bus info: usb@1
          logical name: usb1
          version: 5.04
          capabilities: usb-2.00
          configuration: driver=hub slots=11 speed=480Mbit/s
              *-usb:0
            description: Generic USB device
            product: SDM660-MTP _SN:269DBF10
            vendor: Xiaomi
            physical id: 1
            bus info: usb@1:1
            version: 4.04
            serial: d9650f6
            capabilities: usb-2.00
            configuration: driver=usbfs maxpower=500mA speed=480Mbit/s
              *-usb:1
            description: Generic USB device
            product: JTAG+Serial
            vendor: Xilinx
            physical id: 2
            bus info: usb@1:2
            version: 7.00
            serial: 1234-oj1
            capabilities: usb-2.00
            configuration: driver=ftdi_sio maxpower=100mA speed=480Mbit/s
              *-usb:2
            description: Video
            product: HP Truevision HD
            vendor: Generic
            physical id: 3
            bus info: usb@1:3
            version: 19.16
            serial: 200901010001
            capabilities: usb-2.00
            configuration: driver=uvcvideo maxpower=500mA speed=480Mbit/s
              *-usb:3
            description: Keyboard
            product: 2.4G Keyboard Mouse
            vendor: MOSART Semi.
            physical id: 6
            bus info: usb@1:6
            version: 3.26
            capabilities: usb-1.10
            configuration: driver=usbhid maxpower=100mA speed=12Mbit/s
          *-usbhost:1
          product: xHCI Host Controller
          vendor: Linux 5.4.0-81-generic xhci-hcd
          physical id: 1
          bus info: usb@2
          logical name: usb2
          version: 5.04
          capabilities: usb-3.00
          configuration: driver=hub slots=4 speed=5000Mbit/s
        *-communication
            description: Communication controller
            product: Wildcat Point-LP MEI Controller #1
            vendor: Intel Corporation
            physical id: 16
            bus info: pci@0000:00:16.0
            version: 03
            width: 64 bits
            clock: 33MHz
            capabilities: pm msi bus_master cap_list
            configuration: driver=mei_me latency=0
            resources: irq:51 memory:c6222000-c622201f
        *-multimedia:1
            description: Audio device
            product: Wildcat Point-LP High Definition Audio Controller
            vendor: Intel Corporation
            physical id: 1b
            bus info: pci@0000:00:1b.0
            version: 03
            width: 64 bits
            clock: 33MHz
            capabilities: pm msi bus_master cap_list
            configuration: driver=snd_hda_intel latency=64
            resources: irq:54 memory:c621c000-c621ffff
        *-pci:0
            description: PCI bridge
            product: Wildcat Point-LP PCI Express Root Port #1
            vendor: Intel Corporation
            physical id: 1c
            bus info: pci@0000:00:1c.0
            version: e3
            width: 32 bits
            clock: 33MHz
            capabilities: pci pciexpress msi pm normal_decode bus_master cap_list
            configuration: driver=pcieport
            resources: irq:42
        *-pci:1
            description: PCI bridge
            product: Wildcat Point-LP PCI Express Root Port #2
            vendor: Intel Corporation
            physical id: 1c.1
            bus info: pci@0000:00:1c.1
            version: e3
            width: 32 bits
            clock: 33MHz
            capabilities: pci pciexpress msi pm normal_decode bus_master cap_list
            configuration: driver=pcieport
            resources: irq:43 ioport:6000(size=4096) memory:c5000000-c5ffffff ioport:c2000000(size=16777216)
          *-generic
          description: Unassigned class
          product: RTS522A PCI Express Card Reader
          vendor: Realtek Semiconductor Co., Ltd.
          physical id: 0
          bus info: pci@0000:02:00.0
          version: 01
          width: 32 bits
          clock: 33MHz
          capabilities: pm msi pciexpress bus_master cap_list
          configuration: driver=rtsx_pci latency=0
          resources: irq:48 memory:c5000000-c5000fff
        *-pci:2
            description: PCI bridge
            product: Wildcat Point-LP PCI Express Root Port #3
            vendor: Intel Corporation
            physical id: 1c.2
            bus info: pci@0000:00:1c.2
            version: e3
            width: 32 bits
            clock: 33MHz
            capabilities: pci pciexpress msi pm normal_decode bus_master cap_list
            configuration: driver=pcieport
            resources: irq:44 ioport:5000(size=4096) memory:c6100000-c61fffff
          *-network DISABLED
          description: Wireless interface
          product: RTL8723BE PCIe Wireless Network Adapter
          vendor: Realtek Semiconductor Co., Ltd.
          physical id: 0
          bus info: pci@0000:08:00.0
          logical name: wlo1
          version: 00
          serial: 70:77:81:5c:c3:ab
          width: 64 bits
          clock: 33MHz
          capabilities: pm msi pciexpress bus_master cap_list ethernet physical wireless
          configuration: broadcast=yes driver=rtl8723be driverversion=5.4.0-81-generic firmware=N/A latency=0 link=no multicast=yes wireless=IEEE 802.11
          resources: irq:18 ioport:5000(size=256) memory:c6100000-c6103fff
        *-pci:3
            description: PCI bridge
            product: Wildcat Point-LP PCI Express Root Port #4
            vendor: Intel Corporation
            physical id: 1c.3
            bus info: pci@0000:00:1c.3
            version: e3
            width: 32 bits
            clock: 33MHz
            capabilities: pci pciexpress msi pm normal_decode bus_master cap_list
            configuration: driver=pcieport
            resources: irq:45 ioport:4000(size=4096) memory:c6000000-c60fffff
          *-network
          description: Ethernet interface
          product: RTL810xE PCI Express Fast Ethernet controller
          vendor: Realtek Semiconductor Co., Ltd.
          physical id: 0
          bus info: pci@0000:09:00.0
          logical name: eno1
          version: 0a
          serial: 3c:a8:2a:b0:8e:d6
          capacity: 100Mbit/s
          width: 64 bits
          clock: 33MHz
          capabilities: pm msi pciexpress msix bus_master cap_list ethernet physical tp mii 10bt 10bt-fd 100bt 100bt-fd autonegotiation
          configuration: autonegotiation=on broadcast=yes driver=r8169 firmware=rtl8107e-2_0.0.2 02/26/15 latency=0 link=no multicast=yes port=MII
          resources: irq:19 ioport:4000(size=256) memory:c6004000-c6004fff memory:c6000000-c6003fff
        *-pci:4
            description: PCI bridge
            product: Wildcat Point-LP PCI Express Root Port #5
            vendor: Intel Corporation
            physical id: 1c.4
            bus info: pci@0000:00:1c.4
            version: e3
            width: 32 bits
            clock: 33MHz
            capabilities: pci pciexpress msi pm normal_decode bus_master cap_list
            configuration: driver=pcieport
            resources: irq:46 ioport:3000(size=4096) memory:c4000000-c4ffffff ioport:b0000000(size=301989888)
          *-display
          description: 3D controller
          product: GM108M [GeForce 940M]
          vendor: NVIDIA Corporation
          physical id: 0
          bus info: pci@0000:0a:00.0
          version: a2
          width: 64 bits
          clock: 33MHz
          capabilities: pm msi pciexpress bus_master cap_list
          configuration: driver=nouveau latency=0
          resources: irq:53 memory:c4000000-c4ffffff memory:b0000000-bfffffff memory:c0000000-c1ffffff ioport:3000(size=128)
        *-isa
            description: ISA bridge
            product: Wildcat Point-LP LPC Controller
            vendor: Intel Corporation
            physical id: 1f
            bus info: pci@0000:00:1f.0
            version: 03
            width: 32 bits
            clock: 33MHz
            capabilities: isa bus_master cap_list
            configuration: driver=lpc_ich latency=0
            resources: irq:0
        *-sata
            description: SATA controller
            product: Wildcat Point-LP SATA Controller [AHCI Mode]
            vendor: Intel Corporation
            physical id: 1f.2
            bus info: pci@0000:00:1f.2
            version: 03
            width: 32 bits
            clock: 66MHz
            capabilities: sata msi pm ahci_1.0 bus_master cap_list
            configuration: driver=ahci latency=0
            resources: irq:49 ioport:7088(size=8) ioport:7094(size=4) ioport:7080(size=8) ioport:7090(size=4) ioport:7060(size=32) memory:c6220000-c62207ff
        *-serial
            description: SMBus
            product: Wildcat Point-LP SMBus Controller
            vendor: Intel Corporation
            physical id: 1f.3
            bus info: pci@0000:00:1f.3
            version: 03
            width: 64 bits
            clock: 33MHz
            configuration: driver=i801_smbus latency=0
            resources: irq:18 memory:c6221000-c62210ff ioport:7040(size=32)
          *-pnp00:00
          product: PnP device PNP0c02
          physical id: 1
          capabilities: pnp
          configuration: driver=system
          *-pnp00:01
          product: PnP device PNP0b00
          physical id: 2
          capabilities: pnp
          configuration: driver=rtc_cmos
          *-pnp00:02
          product: PnP device HPQ8001
          vendor: HP
          physical id: 3
          capabilities: pnp
          configuration: driver=i8042 kbd
          *-pnp00:03
          product: PnP device SYN1ef2
          vendor: Synaptics Inc
          physical id: 6
          capabilities: pnp
          configuration: driver=i8042 aux
          *-pnp00:04
          product: PnP device PNP0c02
          physical id: 7
          capabilities: pnp
          configuration: driver=system
          *-scsi:0
          physical id: 8
          logical name: scsi0
          capabilities: emulated
        *-disk
            description: ATA Disk
            product: HGST HTS541010A9
            physical id: 0.0.0
            bus info: scsi@0:0.0.0
            logical name: /dev/sda
            version: A710
            serial: JA1009C03HU9GP
            size: 931GiB (1TB)
            capabilities: gpt-1.00 partitioned partitioned:gpt
            configuration: ansiversion=5 guid=812de78b-0013-494e-b929-0eddfa27d129 logicalsectorsize=512 sectorsize=4096
          *-volume:0
          description: Windows NTFS volume
          vendor: Windows
          physical id: 1
          bus info: scsi@0:0.0.0,1
          logical name: /dev/sda1
          version: 3.1
          serial: 9079-7222
          size: 648MiB
          capacity: 649MiB
          capabilities: boot precious ntfs initialized
          configuration: clustersize=4096 created=2015-06-25 19:24:32 filesystem=ntfs label=WINRE name=Basic data partition state=clean
          *-volume:1
          description: Windows FAT volume
          vendor: MSDOS5.0
          physical id: 2
          bus info: scsi@0:0.0.0,2
          logical name: /dev/sda2
          logical name: /boot/efi
          version: FAT32
          serial: 0e47-954b
          size: 245MiB
          capacity: 259MiB
          capabilities: boot fat initialized
          configuration: FATs=2 filesystem=fat mount.fstype=vfat mount.options=rw,relatime,fmask=0077,dmask=0077,codepage=437,iocharset=iso8859-1,shortname=mixed,errors=remount-ro name=EFI system partition state=mounted
          *-volume:2
          description: reserved partition
          vendor: Windows
          physical id: 3
          bus info: scsi@0:0.0.0,3
          logical name: /dev/sda3
          serial: c78bde29-a665-4db7-b603-8ef4b0b6e8a6
          capacity: 127MiB
          capabilities: nofs
          configuration: name=Microsoft reserved partition
          *-volume:3
          description: Windows NTFS volume
          vendor: Windows
          physical id: 4
          bus info: scsi@0:0.0.0,4
          logical name: /dev/sda4
          version: 3.1
          serial: 06633286-f5b1-644c-b739-f15bb9023416
          size: 416GiB
          capacity: 416GiB
          capabilities: ntfs initialized
          configuration: clustersize=4096 created=2015-04-30 01:01:09 filesystem=ntfs label=Windows name=Basic data partition state=clean
          *-volume:4
          description: EXT4 volume
          vendor: Linux
          physical id: 5
          bus info: scsi@0:0.0.0,5
          logical name: /dev/sda5
          logical name: /
          version: 1.0
          serial: ed910030-eeab-4d4a-b7e1-41d4f0462630
          size: 97GiB
          capabilities: journaled extended_attributes large_files huge_files dir_nlink recover 64bit extents ext4 ext2 initialized
          configuration: created=2018-12-28 05:09:08 filesystem=ext4 lastmountpoint=/ modified=2021-09-14 07:43:26 mount.fstype=ext4 mount.options=rw,relatime,errors=remount-ro mounted=2021-09-14 07:43:33 state=mounted
          *-volume:5
          description: EXT4 volume
          vendor: Linux
          physical id: 6
          bus info: scsi@0:0.0.0,6
          logical name: /dev/sda6
          logical name: /mnt/UB16root
          logical name: /home
          version: 1.0
          serial: 19995ab2-1b81-496e-aba4-8db3f814a4e2
          size: 182GiB
          capabilities: journaled extended_attributes large_files huge_files dir_nlink recover extents ext4 ext2 initialized
          configuration: created=2015-12-27 09:36:17 filesystem=ext4 lastmountpoint=/home modified=2021-09-14 07:44:00 mount.fstype=ext4 mount.options=rw,relatime mounted=2021-09-14 07:44:00 state=mounted
          *-volume:6
          description: Linux swap volume
          vendor: Linux
          physical id: 7
          bus info: scsi@0:0.0.0,7
          logical name: /dev/sda7
          version: 1
          serial: 0005e636-1fcd-41a9-b26f-a3add8b27e5c
          size: 8112MiB
          capacity: 8113MiB
          capabilities: nofs swap initialized
          configuration: filesystem=swap pagesize=4095
          *-volume:7
          description: Windows NTFS volume
          vendor: Windows
          physical id: 8
          bus info: scsi@0:0.0.0,8
          logical name: /dev/sda8
          version: 3.1
          serial: 9a4f-7c6a
          size: 807MiB
          capacity: 828MiB
          capabilities: boot precious ntfs initialized
          configuration: clustersize=4096 created=2015-08-29 11:32:34 filesystem=ntfs state=clean
          *-volume:8
          description: Windows NTFS volume
          vendor: Windows
          physical id: 9
          bus info: scsi@0:0.0.0,9
          logical name: /dev/sda9
          version: 3.1
          serial: 32ae1e8c-3f6c-704d-8626-abd95094444a
          size: 27GiB
          capacity: 27GiB
          capabilities: precious ntfs initialized
          configuration: clustersize=4096 created=2015-06-25 19:42:55 filesystem=ntfs label=RECOVERY name=Basic data partition state=clean
          *-volume:9
          description: EXT4 volume
          vendor: Linux
          physical id: a
          bus info: scsi@0:0.0.0,10
          logical name: /dev/sda10
          version: 1.0
          serial: e0a914f2-faea-4300-bfb0-ff3e050fa0eb
          size: 5MiB
          capabilities: journaled extended_attributes large_files huge_files dir_nlink recover extents ext4 ext2 initialized
          configuration: created=2018-05-21 01:18:05 filesystem=ext4 modified=2021-07-11 01:00:41 mounted=2021-07-11 01:00:41 state=clean
          *-volume:10
          description: Windows NTFS volume
          physical id: b
          bus info: scsi@0:0.0.0,11
          logical name: /dev/sda11
          version: 3.1
          serial: 58751de6-3651-ab47-9914-e8e52580f6a7
          size: 197GiB
          capacity: 197GiB
          capabilities: ntfs initialized
          configuration: clustersize=4096 created=2015-12-31 13:20:27 filesystem=ntfs label=ADMINISTRATION state=dirty
          *-scsi:1
          physical id: 9
          logical name: scsi1
          capabilities: emulated
        *-cdrom
            description: DVD-RAM writer
            product: DVDRW  UJ8G2A
            vendor: hp
            physical id: 0.0.0
            bus info: scsi@1:0.0.0
            logical name: /dev/cdrom
            logical name: /dev/cdrw
            logical name: /dev/dvd
            logical name: /dev/dvdrw
            logical name: /dev/sr0
            version: SGM1
            capabilities: removable audio cd-r cd-rw dvd dvd-r dvd-ram
            configuration: ansiversion=5 status=nodisc
        *-battery
            product: KI04041
            vendor: 131-24-72
            physical id: 1
            version: ManufDate
            serial: DummySerialNumber
            slot: Primary
            capacity: 32560mWh
            configuration: voltage=14.8V
        *-power UNCLAIMED
            description: OEM Define 1
            product: OEM Define 5
            vendor: OEM Define 2
            physical id: 2
            version: OEM Define 6
            serial: OEM Define 3
            capacity: 75mWh
        *-network DISABLED
            description: Ethernet interface
            physical id: 3
            logical name: virbr0-nic
            serial: 52:54:00:05:e4:fe
            size: 10Mbit/s
            capabilities: ethernet physical
            configuration: autonegotiation=off broadcast=yes driver=tun driverversion=1.6 duplex=full link=no multicast=yes port=twisted pair speed=10Mbit/s
            </p>
            </details>

    * For profiling: The provided Xilinx's Ultra96 Fpga board. log: scratch/lshw_board
      <details><summary>lshw for board</summary>
      <p>
      ee382n4
          description: Computer
          product: Avnet Ultra96 Rev1
          width: 64 bits
          capabilities: smp
        *-core
            description: Motherboard
            physical id: 0
          *-cpu:0
                description: CPU
                product: cpu
                physical id: 0
                bus info: cpu@0
                size: 1199MHz
                capacity: 1199MHz
                capabilities: fp asimd evtstrm aes pmull sha1 sha2 crc32 cpuid cpufreq
          *-cpu:1
                description: CPU
                product: cpu
                physical id: 1
                bus info: cpu@1
                size: 1199MHz
                capacity: 1199MHz
                capabilities: fp asimd evtstrm aes pmull sha1 sha2 crc32 cpuid cpufreq
          *-cpu:2
                description: CPU
                product: cpu
                physical id: 2
                bus info: cpu@2
                size: 1199MHz
                capacity: 1199MHz
                capabilities: fp asimd evtstrm aes pmull sha1 sha2 crc32 cpuid cpufreq
          *-cpu:3
                description: CPU
                product: cpu
                physical id: 3
                bus info: cpu@3
                size: 1199MHz
                capacity: 1199MHz
                capabilities: fp asimd evtstrm aes pmull sha1 sha2 crc32 cpuid cpufreq
          *-cpu:4 DISABLED
                description: CPU
                product: idle-states
                physical id: 4
                bus info: cpu@4
          *-memory
                description: System memory
                physical id: 5
                size: 1983MiB
        *-usbhost:0
            product: xHCI Host Controller
            vendor: Linux 4.14.0-xilinx-v2018.3 xhci-hcd
            physical id: 1
            bus info: usb@1
            logical name: usb1
            version: 4.14
            capabilities: usb-2.00
            configuration: driver=hub slots=1 speed=480Mbit/s
          *-usb
                description: USB hub
                product: USB2744
                vendor: Microchip Tech
                physical id: 1
                bus info: usb@1:1
                version: 2.21
                capabilities: usb-2.10
                configuration: driver=hub slots=4 speed=480Mbit/s
              *-usb UNCLAIMED
                  description: Generic USB device
                  product: Hub Controller
                  vendor: Microchip Tech
                  physical id: 4
                  bus info: usb@1:1.4
                  version: 2.00
                  capabilities: usb-2.01
                  configuration: speed=480Mbit/s
        *-usbhost:1
            product: xHCI Host Controller
            vendor: Linux 4.14.0-xilinx-v2018.3 xhci-hcd
            physical id: 2
            bus info: usb@2
            logical name: usb2
            version: 4.14
            capabilities: usb-3.00
            configuration: driver=hub slots=1 speed=5000Mbit/s
          *-usb
                description: USB hub
                product: USB5744
                vendor: Microchip Tech
                physical id: 1
                bus info: usb@2:1
                version: 2.21
                capabilities: usb-3.20
                configuration: driver=hub slots=3 speed=5000Mbit/s
        *-network:0
            description: Wireless interface
            physical id: 3
            logical name: wlan0
            serial: fa:f0:05:79:7d:a2
            capabilities: ethernet physical wireless
            configuration: broadcast=yes driver=wilc_sdio ip=192.168.1.4 multicast=yes wireless=IEEE 802.11
        *-network:1
            description: Wireless interface
            physical id: 4
            logical name: p2p0
            serial: f8:f0:05:79:7d:a2
            capabilities: ethernet physical wireless
            configuration: broadcast=yes driver=wilc_sdio multicast=yes wireless=IEEE 802.11
            </p>
            </details>
            
    
### Compiling and running darknet
* We did not cross-compile for arm platform. Instead, we used this git repo to maintain source code, which was directly compiled on the individual machines.

* Debug flag is added, and set to 1, in the Makefile.
#### Different options to run darknet
1. To test: makes predictions on the provided image. 
	i. If '-save_labels' option is also provided, a '.txt' file, with predicted bounding boxes appear. 
    ```bash
    run_type=test
    var=fpx
    ts=$(date "+%H%M%S.%d%m%Y")
    ./darknet detector $run_type cfg/coco.data \
      cfg/yolov3-tiny.cfg yolov3-tiny.weights data/dog.jpg 2>&1 \
      | tee log/arm.$run_type.$var.$ts
    ```
	ii. Note: use the predictions made with floating point as the ground truth while calculating mAP of our modified darknet code.

2. mAP calculator: makes predictions and compares the result with the ground-thuth present in 'data' directory. 
    ```bash
    run_type=map
    var=fpx
    ts=$(date "+%H%M%S.%d%m%Y")
    ./darknet detector $run_type cfg/coco.data \
      cfg/yolov3-tiny.cfg yolov3-tiny.weights data/dog.jpg 2>&1 \
      | tee log/arm.$run_type.$var.$ts
    ```

## Details
### Directory structure and new files added
You may see pointers to files in the following directories as you read through
the experiments and reports. Please feel free to open them for further
analysys

We add the following new directories:
  * log           // contains darknet run logs. 
  * perf_results  // contains gprof results of the runs
  * scratch       // any miscellaneous files

We added the following files
  * src/snr_test.c // contains the source code for calculating snrs for
   matrix multiplications.
  * src/snr_test.h

We edited the following files
  * src/darknet.c
  * src/gemm.c

## experiments and results

#### Base model (floating point) mAP results on my intel machine 
With no modifications, here are the results: as expected, we get 100% mAP.
  ```bash
  IoU threshold = 50 %, used Area-Under-Curve for each unique Recall

  mean average precision (mAP) = 1.000000, or 100.00 % (4 classes)
  Total Detection Time: 1 Seconds
  ```

#### Experiments with fixed point conversions
##### Code changes 
  ```c
  DTYPE ALPHA_con = __roundup(ALPHA * (1 << scale)); //printf("ALPHA = %d\n", ALPHA_con);

  for (i = 0; i < M; ++i) {
      for (k = 0; k < K; ++k) {
          PUT_IN_REGISTER int A_PART = ((ALPHA_con * __roundup(A[i * lda + k]
          * (1 << scale))) / ( 1 << scale));

          for (j = 0; j < N; ++j) {
              C[i*ldc + j] += ((float)((A_PART *
                                      __roundup( B[k*ldb + j] * (1 << scale))) 
                                     /(1 << scale)))    /  ( 1 << scale);

          }
      }
  }
  ```
##### Issues
We note the following issues with our fixed point implementation:
  1. Bad mAP for scale = 16 (default).  log = log/intel.fx.scale_16.initial_run

    ```bash
    ...
    for conf_thresh = 0.25, precision = -nan, recall = 0.00, F1-score = -nan
    for conf_thresh = 0.25, TP = 0, FP = 0, FN = 4, average IoU = 0.00 %

    IoU threshold = 50 %, used Area-Under-Curve for each unique Recall

    mean average precision (mAP) = 0.000000, or 0.00 % (1 classes)
    Total Detection Time: 98 Seconds
    ```
  We continued to check mAP for scales higher than 16 expecting mAP to increase.
  Interestingly, we did not find any scale that gave close to floating point
  results. 

    * log = log/intel.fx.scale_17_27.initial_run)
    * Here is a summary:

            | Scale         |     mAP %             |
            | ------------- |     -------------     |
            | 17            |     1.77 % (3 classes)|
            | 18            |     1.64 % (1 classes)|
            | 19            |     0.06 % (1 classes)|
            | 20            |     3.89 % (2 classes)|
            | 21            |     2.31 % (4 classes)|
            | 22            |     2.53 % (3 classes)|
            | 23            |     4.90 % (2 classes)|
            | 24            |     0.06 % (3 classes)|
            | 25            |     0.05 % (3 classes)|
            | 26            |     0.05 % (3 classes)|
            | 27            |     1.12 % (3 classes)|


  To get a better picture of the given data and appropriate scales, we did the
  following analysis:

  * The range of numbers present in the filters and input data (data/dog.jpg).
  By maintaining two global variables maximum and minimum, we figured the range
  of number:

    * max = 76.966393, min = -17.589060
    * However, it is unclear whether the max and min are completely from
    filters or images. For example, the filters could be in the range 10^(-20)
    to 10^(-30); and the image could be in the range 10^(+10) to 10^(+20). 
    In the above example, it is difficult to find one common range. For time
    being, we assumed that filters and inputs have similar range of numbers. If
    they follow a different distribution, we could possibly use different scales
    and further improve the performace and accuracy.

  With a common scale between the filters and numbers, we started to find the
  SNR for the given data. We first implemented code for SNR in c, and tested it
  on the given testbench. We obtained the following results:

###### SNR: 
  For the testbench provided at * [tb](http://users.ece.utexas.edu/~gerstl/ece382m_f21/labs/lab1/testbench.m),
      we got the following results for different values of scaling:
      * logfile = 'log/snr.231906.17092021'
      * results

	  | scale     snr   	|
	  | ----------- | ----------- |
	  | 10 	    |  0.244   |
          | 8       | 18.262178|
          | 9       | 25.754839|
          | 10      | 38.904385|
          | 11      | 50.432785|
          | 12      | 64.333061|
          | 13      | 78.565445|
          | 14      | 90.450508|
          | 15      | 105.698715|
          | 16      | -4.251273|
          | 17      | -0.958876|
          | 18      | -0.754522|
          | 19      | 0.000042|

  Now, with the above SNR code, we calculated SNR between floating point and
  fixed-point implementations of gemm for different scales in fixed point. We
  obtained the following results.

    * table 
      |scale  | snr |
      |---    |-------------|
      |1      | 25.368002|
      |2      | 28.792755|
      |3      | 43.377327|
      |4      | 54.751232|
      |5      | 67.387032|
      |6      | 77.842567|
      |7      | 94.654114|
      |8      | 102.631355|
      |9      | 117.446495|
      |10     | 130.757172|
      |11     | 146.535904|
      |12     | 160.423248|
      |13     | 174.414871|
      |14     | 74.169121|
      |15     | 1.698584|
      |16     | 0.076399|
      |17     | 0.178493|
      |18     | -0.167274|
      |19     | 0.012987|
      |20     | 0.009955|
      |21     | -0.004165|

  It is clear from the above table that, a common scale of 13 is a good fit. As
  specified in the document, it's SNR is well above the recommended SNR of 40.

  From here on, we took 13 as the our scaling factor for further experiments,
  wherever we use fixed point conversions.

##### Performace drop
* We noted a 8x in performance degradation after this floating to fixed
 point conversions. The following observations were made on the above code and
 further optimizations in the operations were made:
 1. The \__roundup is not doing a lot of useful work. Hence, after scaling
 and converting to fixed type, we can simply type-case to int type instead of
 using the rounding off function.
 2. While doing the fixed point operations, we need to divide the number with
 (1 << scale). In fixed-point, this is equivalent to a simple bit shifting by
 scale amount.

  ```c
  PUT_IN_REGISTER DTYPE SCALE_NUM = (1 << scale);
  PUT_IN_REGISTER DTYPE ALPHA_con = (int)(ALPHA * SCALE_NUM);

  for (i = 0; i < M; ++i) {

      for (k = 0; k < K; ++k) {
          PUT_IN_REGISTER DTYPE A_PART 
              = (ALPHA_con * (int)(A[i * lda + k] * SCALE_NUM))
                    >> scale;

          for (j = 0; j < N; ++j) {
              C[i*ldc + j] 
                  += ( (float)(
                    (A_PART * (int)(B[k*ldb + j] * SCALE_NUM)) 
                          >> scale))
                            / SCALE_NUM;
          }
      }
  }
  ```
  3. We note that one floating-point operation in our fixed-point
  implementation is unavoidable for every multiplication operation. To analyze this further, consider the below code, 

        ```c
        mAP drops to 25% when this method is used
        C[i*ldc + j] 
            += (A_PART     *   (int)(B[k*ldb + j] * (1 << scale))) >> (2*scale);
        */                                              
        ```

    * In the above code, we got rid of the final floating point division, with
    (1 << scale), by bit shifting the fixed-point number by appropriate
    bits. We noted that there is significant loss of information. To
    corroborate, we dumped the resultant matrix in a file cout.txt and
    verified that many of the numbers in the result are close to zero.
    Hence, it is not appropriate to get rid of the final division. 

    * This also has the consequense in terms of the performance upperbound for
    our fixed point implementation. In other words, we may not be able to get
    our fixed-point performance better than floating point performance.

##### Order of the for-loops
* We also experimented on the order of loops within gemm_nn code. We
 discovered that there is not much difference in the performance. Here are
 our reasons:

 1. Within gemm_nn, M=1. Hence, it is sensible to keep the out loop
 undisturbed. When tried to send the complete matrix to gemm_nn, we did not
 observe any improvement because the row and column sizes are big enough that
 it is likely that cach would reuse the repated data present in the channels.
 2. There is not much difference in by changing the order of for-loops of K,
 N as they are already present in a cache friendly manner. 
  * We can note that we use the same filter weight for all the rows in the
   tranformed input channel. This is already in a cache friendly manner.
   However, to this end, we did not implement any tiling or blocking
   algorithms for matrix multiplications.

#### Difference in programming language (c/cpp)
* There is no big difference between c/cpp in terms of performance. Both of them are taking 20 s. Their logs:
    * C:    perf_results/darknet.perf.withscale_int_round.test.172737.18092021
    * Cpp:  perf_results/darknet.perf.withscale_int_round.test.165858.18092021
 

After enabling openmp, we can notice that most of time is spent in omp
  allocation, deallocation functions. log =
  "perf_results/darknet.perf.arm.fpx.map.222848.18092021"

    * I can think of compiling gemm.c seperately and then linking it. Not sure
      how much effort does that take.
    * Though it is not explicit, it is likely that openmp's time of 13 ms is
      still in optimizing our gemm_nn function. Thus, it is not meaningful to
      compile only gemm.c with openmp. Owing to the lack of time, we make that
      assumption and go further.

#### Timing results
* On the board, here are the timing results
    * For our fixedpoint conversion: 20.94 s
    * For the native floating point: 10.49 s
    
    * With int type rounding time taken by gemm is 1.97 sec. 
        log = perf_results/darknet.perf.withscale_int_round.test.141337.18092021
    * floating point gemm takes, 1.95 seconds 

* Does scale matter?
  * The difficulty in answering this is to measure the difference in
    performance. 
  * Unfortunately, for all other scales, the mAP is too low. Also, FNs are
    high for small scale.

* Let us start with scale = 13:
    * We don't actually need our custom \__roundup function. I am directly
      type casting to int types.
    * mAP close to 100%. log = "log/map.withscale_cnative_round.133032.18092021" 
    * Time is around 2 seconds. Now, only gemm_nn is the bottleneck.
        log = "log/map.withscale_cnative_round.133032.18092021"

* For scale = 13, 
    * the mAP came to be 100%. log = "log/map.fx.124030.18092021"
    * Time taken = 13s; log =  "perf_results/darknet.perf.fx.124248.18092021"

* If the precision is not lost, we can aswell represent the data in char, 
    * as we know the max and min values to be: max = 76.966393, min = -17.589060 
    * I think it is more important to have a look at the SNR values of the
     calculations instead of mAP to decide on the scale.

##### What we did not analyze
1. Tiling/blocking techniques in matrix multiplication.
2. Two differnt scales, one each for channels and filters.  
3. What happens when we convert the numbers to ints even before sending to gemm


<!--
* With c's native round function:
    * gemm_nn still shows the same time. However, time taken round disappers.
    * Total time ~= 10 sec. log = "perf_results/darknet.perf.cnative_round.011654.18092021"
    * mAP:  mean average precision (mAP) = 0.037500, or 3.75 % (2 classes)
    * log = "log/map.cnative_round.011634.18092021"
-->
<!--
* gprof results for scale = 23 is 
    * time = 17 seconds. log = 'perf_results/darknet.perf.scale_23.234744.17092021'
    * for floating, time = 1.12 seconds. log = 'perf_results/darknet.perf.fpx.000556.18092021'
* We fix scale = 23 for performance analysis.
-->


