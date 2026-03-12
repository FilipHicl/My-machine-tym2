#include <WiFi.h>
#include <WebServer.h>
#include "kinematics.h"

// ==========================================
// WI-FI CONFIGURATION
// ==========================================
const char* ssid = "Epson";
const char* password = "12345678";

// Initialize the web server on port 80
WebServer server(80);

// Global variable to store the current motor speed (0-100)
// Can be used inside the motor control logic to adjust power
int currentSpeed = 50; 

// ==========================================
// HTML/CSS/JS WEBPAGE
// ==========================================
// Raw string literal containing the HTML/CSS/JS code
const char INDEX_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html lang="cs">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <title>Ovládání Robota</title>
    <style>
        :root { --primary: #007bff; --bg: #e9ecef; --text: #333; }
        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background-color: var(--bg); color: var(--text); text-align: center; margin: 0; padding: 20px; user-select: none; }
        h1 { margin-bottom: 5px; color: #2c3e50; }
        .card { background: white; border-radius: 15px; padding: 30px; box-shadow: 0 8px 20px rgba(0,0,0,0.1); max-width: 400px; margin: 0 auto; }
        .slider-container { margin: 20px 0 40px 0; }
        input[type=range] { width: 100%; height: 15px; border-radius: 10px; background: #ddd; outline: none; -webkit-appearance: none; }
        input[type=range]::-webkit-slider-thumb { -webkit-appearance: none; appearance: none; width: 40px; height: 40px; border-radius: 50%; background: var(--primary); cursor: pointer; box-shadow: 0 2px 5px rgba(0,0,0,0.2); }
        .d-pad { display: grid; grid-template-columns: repeat(3, 80px); grid-template-rows: repeat(3, 80px); gap: 15px; justify-content: center; }
        .btn { background-color: var(--primary); color: white; border: none; border-radius: 15px; font-size: 30px; display: flex; align-items: center; justify-content: center; cursor: pointer; box-shadow: 0 6px 0 #0056b3; transition: all 0.1s; touch-action: manipulation; }
        .btn:active { transform: translateY(6px); box-shadow: 0 0 0 #0056b3; }
        .btn-up { grid-column: 2; grid-row: 1; }
        .btn-left { grid-column: 1; grid-row: 2; }
        .btn-stop { grid-column: 2; grid-row: 2; background-color: #dc3545; box-shadow: 0 6px 0 #a71d2a; font-size: 18px; font-weight: bold; }
        .btn-stop:active { box-shadow: 0 0 0 #a71d2a; }
        .btn-right { grid-column: 3; grid-row: 2; }
        .btn-down { grid-column: 2; grid-row: 3; }
    </style>
</head>
<body>
    <div class="card">
        <h1>🤖 MyMachine</h1>
        <p style="color: #7f8c8d; margin-top: 0;">Robot</p>
        
        <div class="slider-container">
            <label for="speed">Výkon motorů: <strong id="speedVal">50</strong> %</label><br><br>
            <input type="range" id="speed" min="0" max="100" value="50" oninput="document.getElementById('speedVal').innerText = this.value" onchange="sendSpeed(this.value)">
        </div>

        <div class="d-pad">
            <button class="btn btn-up" onmousedown="cmd('forward')" onmouseup="cmd('stop')" ontouchstart="cmd('forward')" ontouchend="cmd('stop')">▲</button>
            <button class="btn btn-left" onmousedown="cmd('left')" onmouseup="cmd('stop')" ontouchstart="cmd('left')" ontouchend="cmd('stop')">◄</button>
            <button class="btn btn-stop" onclick="cmd('stop')">STOP</button>
            <button class="btn btn-right" onmousedown="cmd('right')" onmouseup="cmd('stop')" ontouchstart="cmd('right')" ontouchend="cmd('stop')">►</button>
            <button class="btn btn-down" onmousedown="cmd('backward')" onmouseup="cmd('stop')" ontouchstart="cmd('backward')" ontouchend="cmd('stop')">▼</button>
        </div>
    </div>

    <script>
        function cmd(action) { fetch('/' + action); }
        function sendSpeed(val) { fetch('/speed?val=' + val); }
    </script>
</body>
</html>
)rawliteral";

// ==========================================
// HARDWARE CONTROL FUNCTIONS
// ==========================================
// Hardware logic (analogWrite/digitalWrite) should be implemented here.

kinematics robot; 

void stopMotors() {
    Serial.println("Action: STOP");
    robot.setSpeed(0);
    robot.setTurnRate(0);

    // TODO: Add motor stop logic
}

void moveForward() {
    Serial.println("Action: FORWARD");
    robot.setSpeed(-0.5); // Example: Scale speed to 50% of max for forward movement
    // TODO: Add forward movement logic
}

void moveBackward() {
    Serial.println("Action: BACKWARD");
    robot.setSpeed(0.5); // Example: Scale speed to 50% of max for forward movement
    //robot.setSpeed(-(currentSpeed/256) * 0.5f); // Example: Scale speed to 50% of max for forward movement
    Serial.println("Here");

    Serial.println("Here1");
    // TODO: Add backward movement logic
}

void turnLeft() {
    Serial.println("Action: LEFT");
    robot.setTurnRate(2); // Example: Scale turn rate based on speed slider
    //robot.setSpeed(-0.5); 
}

void turnRight() {
    Serial.println("Action: RIGHT");
    robot.setTurnRate(-2); // Example: Scale turn rate based on speed slider
    //robot.setSpeed(0.5); 
}


// ==========================================
// MAIN SETUP
// ==========================================

void setup() {
    Serial.begin(115200);
    Serial.println("\nInitializing...");
    robot.begin(); // Initialize kinematics and motors
    robot.start();
    Serial.println("Kinematics initialized.");

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
    Serial.print("Access the webserver at IP: ");
    Serial.println(WiFi.localIP());

    // Display the main HTML page
    server.on("/", []() {
        server.send(200, "text/html", INDEX_HTML);
    });

    // Handle speed slider value updates
    server.on("/speed", []() {
        if (server.hasArg("val")) {
            int webValue = server.arg("val").toInt();
            
            // Maps 0-100 to 0-255 for motor PWM
            currentSpeed = map(webValue, 0, 100, 0, 255); 
            
            Serial.print("New Web Speed: ");
            Serial.print(webValue);
            Serial.print("% -> PWM mapped to: ");
            Serial.println(currentSpeed);
        }
        server.send(200, "text/plain", "OK");
    });

    // Handle movement commands mapping to hardware functions
    server.on("/forward", []() {
        moveForward();
        server.send(200, "text/plain", "OK");
    });

    server.on("/backward", []() {
        moveBackward();
        server.send(200, "text/plain", "OK");
    });

    server.on("/left", []() {
        turnLeft();
        server.send(200, "text/plain", "OK");
    });

    server.on("/right", []() {
        turnRight();
        server.send(200, "text/plain", "OK");
    });

    server.on("/stop", []() {
        stopMotors();
        server.send(200, "text/plain", "OK");
    });

    // Start the server
    server.begin();
    Serial.println("Web server started.");
}

// ==========================================
// MAIN LOOP
// ==========================================

void loop() {
    // Continuously listen for incoming HTTP requests
    server.handleClient();
}