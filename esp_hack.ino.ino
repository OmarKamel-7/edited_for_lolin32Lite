#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Ksoa";
const char* password = "KSOA@7310";

WebServer server(80);

const char* prank_html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>😈 You've Been Hacked!</title>
  <style>
    body { text-align: center; font-size: 2em; background: black; color: lime; }
    .flash { animation: flash 0.2s infinite; }
    @keyframes flash {
      0% { background: red; }
      50% { background: blue; }
      100% { background: green; }
    }
  </style>
</head>
<body class="flash">
  <h1>😱 WARNING!</h1>
  <p>Your device has been compromised!</p>
  <audio autoplay loop>
    <source src="https://www.soundjay.com/button/beep-07.wav" type="audio/wav">
  </audio>
  <script>
    if (navigator.vibrate) {
      setInterval(() => navigator.vibrate([200, 100, 200]), 2000);
    }
    alert("Your device has been accessed 😈");
  </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", prank_html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
