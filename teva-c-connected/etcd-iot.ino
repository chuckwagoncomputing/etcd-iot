#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <EthernetUdp.h>

// MAC Address. Your TI Teva C Connected has a sticker on the bottom with its MAC Address. Replace this with that.
byte mac[] = { 0x00, 0x1a, 0xb6, 0x02, 0xab, 0xf5 };
// The name of the service the device will be advertised as.
char service[] = "test";
// etcd server IP address.
IPAddress remote(192,168,1,3);
// IP Address to use if DHCP is unsuccessful.
IPAddress ip(192,168,1,8);
// Port number
EthernetServer server(80);
EthernetClient advertiser;

void setup() {
 Serial.begin(115200);
 Serial.println("Initializing.");
 if (Ethernet.begin(mac) == 0) {
  Ethernet.begin(mac, ip);
  Serial.println("Could not configure network with DHCP.");
 }
 if (advertiser.connect(remote, 4001)) {
  Serial.println("Connected.");
  advertiser.print("PUT /v2/keys/services/");
  advertiser.print(service);
  advertiser.print("/");
  advertiser.print(Ethernet.localIP());
  advertiser.println(" HTTP/1.1");
  advertiser.println("Content-type: application/x-www-form-urlencoded");
  advertiser.println("Content-length: 8");
  advertiser.println();
  advertiser.println("value=80");
  advertiser.stop();
 }
 else {
  Serial.println("Could not connect.");
 }
 Serial.print("IP Address: ");
 Serial.println(Ethernet.localIP());
 Serial.println("Starting server.");
 server.begin();
}

void loop() {
 EthernetClient client = server.available();
 if (client) {
  Serial.println("Client connected");
  boolean currentLineIsBlank = true;
  while (client.connected()) {
   if (client.available()) {
    char c = client.read();
    if (c == '\n' && currentLineIsBlank) {
     client.println("HTTP/1.1 200 OK");
     client.println("Content-Type: text/html");
     client.println("Connection: close");
     client.println();

     // *******************************************
     // This space is yours. Use it as necessary.
     client.println("<!DOCTYPE HTML>");
     client.println("<html>");
     client.println("foobar");
     client.println("</html>");
     // *******************************************

     break;
    }
    if (c == '\n') {
     currentLineIsBlank = true;
    }
    else if (c != '\r') {
     currentLineIsBlank = false;
    }
   }
  }
  delay(1);
  client.stop();
 }
}
