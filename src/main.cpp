#include <Arduino.h>
#include "CoinMarketCapApi.h"
#include <WiFi.h>
#include "WiFiClientSecure.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <litecoin.h>

#define ssid "ssid"
#define password "password"
#define apiKey "apikey"

WiFiClientSecure client;
CoinMarketCapApi api(client, apiKey);
TFT_eSPI tft = TFT_eSPI(135, 240);

void printTickerData(String ticker)
{
  CMCTickerResponse response = api.GetTickerInfo(ticker, "USD");
  if (response.error == "")
  {
    Serial.print("ID: ");
    Serial.println(response.id);
    Serial.print("Name: ");
    Serial.println(response.name);
    Serial.print("Symbol: ");
    Serial.println(response.symbol);

    Serial.print("Rank: ");
    Serial.println(response.cmc_rank);

    Serial.print("Price: ");
    Serial.println(response.price);

    Serial.print("24h Volume: ");
    Serial.println(response.volume_24h);
    Serial.print("Market Cap: ");
    Serial.println(response.market_cap);

    Serial.print("Circulating Supply: ");
    Serial.println(response.circulating_supply);
    Serial.print("Total Supply: ");
    Serial.println(response.total_supply);
    tft.drawString(String(response.price).c_str(), 88, 50, 6);

    Serial.print("Percent Change 1h: ");
    Serial.println(response.percent_change_1h);
    Serial.print("Percent Change 24h: ");
    Serial.println(response.percent_change_24h);
    Serial.print("Percent Change 7d: ");
    Serial.println(response.percent_change_7d);
    Serial.print("Last Updated: ");
    Serial.println(response.last_updated);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Boot Ticker"));

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  tft.pushImage(0, 35, 64, 64, litecoin);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // You can use any other crypto ID. BTC / ETH / BNB
  // (LTC image will remain at least you change it)
  printTickerData("LTC");
  delay(120000);
}