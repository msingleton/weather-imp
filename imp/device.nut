led <- hardware.pin1;
led.configure(DIGITAL_OUT);

cubeWire <- hardware.i2c89;
cubeWire.configure(CLOCK_SPEED_100_KHZ);

function showWeather(weatherState) {
    if (regexp("^rain.*").match(weatherState)) {
        local res = cubeWire.write((0x53 << 1), weatherState);
        server.log("Sending rain to cube: " + res);
    } else if(regexp("^snow.*").match(weatherState)) {
        local res = cubeWire.write((0x53 << 1), weatherState);
        server.log("Sending snow to cube: " + res);
    }
}

function heartbeat() {
    server.log("Heartbeat");
    led.write(1);
    imp.wakeup(0.1, turnoffLight);
    imp.wakeup(5, heartbeat);
}

function turnoffLight() {
    led.write(0);
}

heartbeat();
agent.on("weather", showWeather);
