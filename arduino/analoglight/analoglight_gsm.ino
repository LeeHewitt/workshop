#include <GSM.h>
#include "plotly_streaming_gsm.h"

// Sign up to plotly here: https://plot.ly
// View your API key and streamtokens here: https://plot.ly/settings
#define nTraces 2
// View your tokens here: https://plot.ly/settings
// Supply as many tokens as data traces
// e.g. if you want to ploty A0 and A1 vs time, supply two tokens
char *tokens[nTraces] = {"25tm9197rz", "unbi52ww8a"};
// arguments: username, api key, streaming token, filename
plotly graph = plotly("workshop", "v6w5xlbx9j", tokens, "your_filename", nTraces);


// Setup Analog Light Sensor Pin
int sensorPin = A0;    // select the input pin for the potentiometer
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux

void gsm_connect(){
  // ...
}

void setup() {
  analogReference(EXTERNAL);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  gsm_connect();

  graph.fileopt="overwrite"; // See the "Usage" section in https://github.com/plotly/arduino-api for details
  bool success;
  success = graph.init();
  if(!success){while(true){}}
  graph.openStream();
}

unsigned long x;
int y;

void loop() {
  int rawValue = analogRead(sensorPin);

  Serial.print("Raw = ");
  Serial.print(rawValue);
  graph.plot(millis(), rawValue, tokens[0]);

  Serial.print(" - Lux = ");
  Serial.println(RawToLux(rawValue));
  graph.plot(millis(), RawToLux(rawValue), tokens[1]);


}

float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}
