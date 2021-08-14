var x, y, speed, heading;
var adhocURL = "http://192.168.1.93/move?";
var xmlHttp = new XMLHttpRequest();

var joystick = new VirtualJoystick({
    container: document.getElementById('joystick-container'),
    mouseSupport: true,
    strokeStyle: '#000',
    stationaryBase: true,
    baseX: (window.innerWidth / 2),
    baseY: (window.innerHeight / 2),
    limitStickTravel: true,
});

joystick.addEventListener('touchStart', function () {
    console.log('pressed')
    drive();
});
joystick.addEventListener('touchMove', function () {
    console.log('moving')
    drive();
});
joystick.addEventListener('touchEnd', function () {
    console.log('released')
    stop();
});


setInterval(function () {
    x = Math.round(joystick.deltaX());
    y = -(Math.round(joystick.deltaY()));
    calculateHeading();
    calculateSpeed();
});

function calculateHeading() {
    if (x == 0 && y == 0) {
        heading = 0;
    }
    else {
        heading = Math.round(Math.atan2(x, y) * 180.0 / Math.PI);
        if (heading < 0) {
            heading = heading + 360;
        }
    }
}

function calculateHeading() {
    if (x == 0 && y == 0) {
        heading = 0;
    }
    else {
        heading = Math.round(Math.atan2(x, y) * 180.0 / Math.PI);
        if (heading < 0) {
            heading = heading + 360;
        }
    }
}

function calculateSpeed() {
    var pyth = (x * x) + (y * y);
    speed = Math.round(Math.sqrt(pyth));
    return speed;
}

window.addEventListener("resize", function () {
    window.location.reload();
});

function drive() {
    xmlHttp.open('POST', adhocURL + "&heading=" + heading + "&speed=" + speed, true);
    xmlHttp.send();
}

function stop() {
    xmlHttp.open('POST', adhocURL + "&heading=" + 0 + "&speed=" + 0, true);
    xmlHttp.send();
}