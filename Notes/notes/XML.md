---
tags: [TPSIT]
title: XML
created: '2019-10-01T08:55:11.146Z'
modified: '2019-10-01T09:54:18.045Z'
---

# XML

## ENCODING per l'HTTP

- **file**: usa librerie "magic" per analizzare il file indicato
_file *_

- **joe**: CTRL+K e poi X per salvare e uscire
_prova.txt: UTF-8 Unicode text, with no line terminators_
I browser trovano iso-8859-1

- **iconv**: converte un file di testo da un encoding ad un altro
_iconv -f UTF-8 -t iso-8859-1 prova.txt > prova.iso.txt_
senza nomefile legge da stdin verso stdout, altrimenti usare redirezione output
_prova.iso.txt: ISO-8859-1 text, with no line terminators_

Terminale xfce4-terminal supporta UTF-8
Browser di default usano ISO-8859-1

_hexdump -C prova.txt_

```
00000000  41 76 65 76 6f 20 75 6e  61 20 63 61 73 65 74 74  |Avevo una casett|
00000010  61 20 70 69 63 63 6f 6c  69 6e 61 20 69 6e 20 43  |a piccolina in C|
00000020  61 6e 61 64 c3 a0                                 |anad..|
00000026
```

0a = invio (CR)
c3 a0 = 16 bit (minimo 2 byte a lunghezza variabile per UTF-8)


_hexdump -C prova.iso.txt_

```
00000000  41 76 65 76 6f 20 75 6e  61 20 63 61 73 65 74 74  |Avevo una casett|
00000010  61 20 70 69 63 63 6f 6c  69 6e 61 20 69 6e 20 43  |a piccolina in C|
00000020  61 6e 61 64 e0                                    |anad.|
00000025
```

iso8859 codifica ASCII estesa (1 byte per carattere)

Gestore file: ssh://172.30.4.npc per trasferire i file da macchina virtuale ad un altra


## VBOX file = XML

```
<?xml version="1.0"?>
<VirtualBox xmlns="http://www.virtualbox.org/" version="1.16-linux">
  <Machine uuid="{827810e0-21ce-4282-bfc2-cfd981a45ce0}" name="clientbasso" OSType="Debian_64" stateFile="Snapshots/2019-09-26T10-37-22-586364000Z.sav" snapshotFolder="Snapshots" lastStateChange="2019-09-26T10:37:25Z">
    <MediaRegistry>
      <HardDisks>
        <HardDisk uuid="{a0015833-8303-4824-8dda-026fa8fa07ed}" location="clientbasso.vdi" format="VDI" type="Normal"/>
      </HardDisks>
    </MediaRegistry>
    <ExtraData>
      <ExtraDataItem name="GUI/LastCloseAction" value="SaveState"/>
      <ExtraDataItem name="GUI/LastNormalWindowPosition" value="3,24,800,649"/>
      <ExtraDataItem name="GUI/RestrictedRuntimeDevicesMenuActions" value="HardDrives"/>
      <ExtraDataItem name="GUI/RestrictedRuntimeMachineMenuActions" value="SaveState,PowerOff"/>
      <ExtraDataItem name="GUI/StatusBar/IndicatorOrder" value="HardDisks,OpticalDisks,FloppyDisks,Network,USB,SharedFolders,Display,VideoCapture,Features,Mouse,Keyboard"/>
    </ExtraData>
    <Hardware>
      <CPU>
        <PAE enabled="false"/>
        <LongMode enabled="true"/>
        <X2APIC enabled="true"/>
        <HardwareVirtExLargePages enabled="false"/>
      </CPU>
      <Memory RAMSize="1024"/>
      <HID Pointing="USBTablet"/>
      <Boot>
        <Order position="1" device="Floppy"/>
        <Order position="2" device="DVD"/>
        <Order position="3" device="HardDisk"/>
        <Order position="4" device="Network"/>
      </Boot>
      <Display VRAMSize="16"/>
      <BIOS>
        <IOAPIC enabled="true"/>
      </BIOS>
      <USB>
        <Controllers>
          <Controller name="OHCI" type="OHCI"/>
        </Controllers>
      </USB>
      <Network>
        <Adapter slot="0" enabled="true" MACAddress="080027BB3AD9" type="82540EM">
          <DisabledModes>
            <InternalNetwork name="intnet"/>
            <NATNetwork name="NatNetwork"/>
          </DisabledModes>
          <BridgedInterface name="br0"/>
        </Adapter>
        <!--Predisposti 8 interfacce di rete, contro le 4 via GUI-->
        <Adapter slot="1" type="82540EM"/>
        <Adapter slot="2" type="82540EM"/>
        <Adapter slot="3" type="82540EM"/>
        <Adapter slot="4" type="82540EM"/>
        <Adapter slot="5" type="82540EM"/>
        <Adapter slot="6" type="82540EM"/>
        <Adapter slot="7" type="82540EM"/>
      </Network>
      <AudioAdapter codec="AD1980" driver="Pulse" enabled="true"/>
      <RTC localOrUTC="UTC"/>
      <GuestProperties>
        <GuestProperty name="/VirtualBox/HostInfo/GUI/LanguageID" value="it_IT" timestamp="1569494246170988000" flags=""/>
      </GuestProperties>
    </Hardware>
    <StorageControllers>
      <StorageController name="IDE" type="PIIX4" PortCount="2" useHostIOCache="true" Bootable="true">
        <AttachedDevice passthrough="false" type="DVD" hotpluggable="false" port="1" device="0"/>
      </StorageController>
      <StorageController name="SATA" type="AHCI" PortCount="1" useHostIOCache="false" Bootable="true" IDE0MasterEmulationPort="0" IDE0SlaveEmulationPort="1" IDE1MasterEmulationPort="2" IDE1SlaveEmulationPort="3">
        <AttachedDevice type="HardDisk" hotpluggable="false" port="0" device="0">
          <Image uuid="{a0015833-8303-4824-8dda-026fa8fa07ed}"/>
        </AttachedDevice>
      </StorageController>
    </StorageControllers>
  </Machine>
</VirtualBox>
```

### Consegna

1. Ricerca nella documentazione virtualbox del DTD di clientcognome.vbox per validare l'xml (404 hehe)
1. Creare programma in C per leggere VBOX che stampa in uscita i dati contenuti in un file XML, HTML o RTF (formato morto)
1. Accetta input come comandi GNU/Linux: argv oppure stdin
1. Obbiettivo futuro: eseguibile via rete

LaTex usato per pubblicare documenti, RTF usato per creare dei documenti https://en.wikipedia.org/wiki/Rich_Text_Format

