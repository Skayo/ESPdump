# ESPdump

Text dump service, similar to PrivateBin, running on an ESP8266/NodeMCU

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