#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "Jeekun의 iPhone";     // 여기에 WiFi 이름(SSID) 입력
const char* password = "00000000"; // 여기에 WiFi 비밀번호 입력

void setup() {
  Serial.begin(115200);
  // WiFi 연결 시작
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // 연결 성공
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  test();
}

void loop() {
  // 메인 루프는 비어있음
}

void test() {
  if(WiFi.status() == WL_CONNECTED){ // WiFi가 연결되어 있는지 확인
    HTTPClient http;  // HTTPClient 객체 생성

    Serial.println("Testing internet connection...");
    http.begin("http://httpbin.org/get"); // HTTP GET 요청을 보낼 URL
    int httpCode = http.GET();  // GET 요청 보내기

    if (httpCode > 0) { // 응답이 성공적으로 수신된 경우
      String payload = http.getString(); // 응답 받은 페이로드
      Serial.println("HTTP Response code: " + String(httpCode));
      Serial.println("Response: " + payload);
    }
    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); // HTTP 연결 종료
  }
  else {
    Serial.println("WiFi is not connected");
  }
}