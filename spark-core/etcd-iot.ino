// etcd server IP address.
byte remote[] = { 192, 168, 1, 3 };
// The name of the service the device will be advertised as.
char service[] = "test";
// Server port number
int port = 80;

TCPServer server = TCPServer(port);
TCPClient advertiser;

void setup() {
 if (advertiser.connect(remote, 4001)) {
  advertiser.print("PUT /v2/keys/services/");
  advertiser.print(service);
  advertiser.print("/");
  advertiser.print(Network.localIP());
  advertiser.println(" HTTP/1.1");
  advertiser.println("Content-type: application/x-www-form-urlencoded");
  advertiser.println("Content-length: 8");
  advertiser.println();
  advertiser.print("value=");
  advertiser.println(port);
 }
 server.begin();
}

void loop() {
 TCPClient client = server.available();
 if (client) {
  Serial.println("Client connected.");
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
