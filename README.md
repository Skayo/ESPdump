# ESPdump

Text dump service, similar to PrivateBin, running on an ESP8266/NodeMCU

## Setup

- SD Card with the content of `site` and a directory named `dumps` on it
- SD Card Reader connected to NodeMCU
- Edit `DDNS.h`, `WiFi.h`, `WiFi.cpp` and `MDNS.h` to fit your needs
- Build and Upload with Platform.IO

## Notes

```
FILE:
- Filename is a generated 8 character string
- File extension is: <p (Plain text) | m (Markdown) | s (Source Code)><y (Self-delete) | n (No Self-delete)><y (Password) | n (No Password)>

API:
/					Homepage (create dump)
/<filename>			View Dump
/admin				Administrator Page (Delete Dumps, View System Information)
/create				Create dump (POST)
/dumps/<filename>	Raw Text File Output (takes ?password=)
```