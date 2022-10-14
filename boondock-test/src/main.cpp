/**
 * @file streams-url_mp3-audiokit.ino
 * @author Phil Schatzmann
 * @brief decode MP3 stream from url and output it on I2S on audiokit
 * @version 0.1
 * @date 2021-96-25
 * 
 * @copyright Copyright (c) 2021
 */

// install https://github.com/pschatzmann/arduino-libhelix.git
#define AUDIOKIT_BOARD 5
#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"
#include "AudioLibs/AudioKit.h"
/* I2C gpios */
#define IIC_CLK 23
#define IIC_DATA 18

URLStream url("XXXX","XXXX");  // or replace with ICYStream to get metadata
AudioKitStream i2s; // final output of decoded stream
EncodedAudioStream dec(&i2s, new MP3DecoderHelix()); // Decoding stream
StreamCopy copier(dec, url); // copy url to decoder


void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);  

  // setup i2s
  auto config = i2s.defaultConfig(TX_MODE);
  config.channels =1;
  i2s.setVolume(0.7);
  i2s.begin(config);


  // setup I2S based on sampling rate provided by decoder
  dec.begin();
  // mp3 radio
  url.begin("https://app.boondock.live/audio/welcome.mp3","audio/mp3");

}

void loop(){
  copier.copy();
}