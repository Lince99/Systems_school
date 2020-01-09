## NAT
Le Regole devono ancora essere aggiornate all'ultima versione

| If | Proto | Ext. port range | NAT IP | Int. port range | Description |
| --- | --- | --- | --- | --- | --- |
| WAN | TCP | 22 (SSH) | host-server | 22 (SSH) | Server in SSH |
| DMZ | TCP | 22 (SSH) | host-client | 8888 | "Block" DMZ to LAN via port 22 |
| WAN | TCP | 80 (HTTPP) | host-server | 80 (HTTP) | Rendirizzamento al server "apache" |
| WAN | TCP | 443 (HTTPS) | host-server | 443 (HTTPS) | Allow HTTPS connection |
| DMZ | TCP | 5022 | host-client | 22 (SSH) | DMZ to LAN in SSH via port 5022 |
| WAN | TCP | 8080 | host-router | 80 (HTTP) | Rendirizzamento al router m0n0wall dalla porta 8080 |

## 1:1

| Interface | External IP | Internal IP | Description |
| --- | --- | --- | --- |
| DMZ | 192.168.2.100/32 | 192.168.3.100/32 | Block DMZ to LAN via 192.168.2.100 |

[↑](#indice)
# LAN
IP Address: 192.168.`2`.1/24[^lan]
[^lan]: Il `2` si riferisce all'indirizzo del mio PC nel laboratorio

## Firewall Rules
| Proto | Source | Port | Destination | Port | Description |
| --- | --- | --- | --- | --- | --- |
| TCP/UDP | LAN net | * | ! host-router-lan | 53 (DNS) | Block richieste DNS che non sono al router |
| * | LAN net | * | * | * | Default LAN -> any |

## DHCP Server
Range: 192.168.2.100 to 192.168.2.199

[↑](#indice)
# WAN
IP Address: 172.30.4.110

- Username: admin
- Password: lasolita
## Firewall Rules
| Proto | Source | Port | Destination | Port | Description |
| --- | --- | --- | --- | --- | --- |
| TCP | * | * | host-server | 443 (HTTPS) | Allow HTTPS connection |
| TCP | host-pcospitante | * | WAN address | 80 (HTTP) | Allow: accesso web al m0n0wall dal PC ospitante |
| TCP | host-pcospitante | * | host-server | 22(SSH) | NAT Server in SSH |
| ICMP | * | * | WAN address | * | Allow ping to WAN |
| TCP | * | * | host-server | 80 (HTTP) | Allow accesso al WebServer(index.html) dalla porta 80 |
[↑](#indice)

# IPsec VPN

## Firewall Rules
| Proto | Source | Port | Destination | Port | Description |
| --- | --- | --- | --- | --- | --- |
| * | * | * | * | * | Default IPsec VPN |

[↑](#indice)
# DMZ
IP Address: 192.168.`102`.1/24[^dmz]
[^dmz]: Il`102` si riferisce all'indirizzo del mio PC nel laboratorio sommato a `100`

## Firewall Rules
| Proto | Source | Port | Destination | Port | Description |
| --- | --- | --- | --- | --- | --- |
| TCP | DMZ net | * | host-client | 22 (SSH) | Allow DMZ to LAN via SSH (Normally disable) |
| * | DMZ net | * | LAN net | * | Block DMZ to LAN |
| ICMP | DMZ net | * | * | * | Allow ping to any |
| UDP | DMZ net | * | * | 53(DNS) | Allow DNS to any |
| UDP | DMZ net | * | * | 123(NTP | Allow NTP to any |
| TCP | DMZ net | * | apt-cacher | 3142 | Allow only update from server apt-cacher |
| * | DMZ net | * | * | * | Allow: DMZ to any (Normally disable) |

## DHCP Server
Range: 192.168.102.100 to 192.168.102.199

#### Reservations
| MAC address | IP address | Description |
| --- | --- | --- |
| 08:00:27:78:8e:2b | 192.168.102.250 | IP statico del Server |
