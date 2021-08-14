
var adhocURL = "http://192.168.1.51/";
//var adhocURL = "http://192.168.1.119/";
var l_event, l_distance, l_angle, l_direction, r_event, r_distance, r_angle, r_direction;
var actuators;
var xhttp = new XMLHttpRequest();

// $(document).ready(function () {
//     buildActuatorTable();
// });

$(document).ready(function () {
    var refresh = setInterval(function () {
        buildActuatorTable();
    }, 200);
});


//ACTUATOR JSON
function buildActuatorTable() {
    $.getJSON("data/actuator.json", function (data) {

        actuators = data;
        console.log(actuators);
        var leg_1_table_data = "";
        var leg_2_table_data = "";
        var leg_3_table_data = "";
        var leg_4_table_data = "";


        $.each(data, function (key, value) {
            if (value.leg === "1") {
                leg_1_table_data += "<tr>";
                leg_1_table_data += "<td>" + value.id + "</td>";
                leg_1_table_data += "<td>" + value.joint_name + "</td>";
                leg_1_table_data += "<td>" + value.voltage + " V</td>";
                leg_1_table_data += "<td>" + value.temperature + " &#8451;</td>";
                leg_1_table_data += "<td>" + value.position + " &#176;</td>";
                leg_1_table_data += "<td><button class='btn' id='settings_" + value.id + "' data-toggle='modal' data-target='#configWindow' data-id='" + value.id + "'><i class='fas fa-cog'></i></button></td>";
                leg_1_table_data += "</tr>";
            }

            if (value.leg === "2") {
                leg_2_table_data += "<tr>";
                leg_2_table_data += "<td>" + value.id + "</td>";
                leg_2_table_data += "<td>" + value.joint_name + "</td>";
                leg_2_table_data += "<td>" + value.voltage + " V</td>";
                leg_2_table_data += "<td>" + value.temperature + " &#8451;</td>";
                leg_2_table_data += "<td>" + value.position + " &#176;</td>";
                leg_2_table_data += "<td><button class='btn' id='settings_" + value.id + "' data-toggle='modal' data-target='#configWindow' data-id='" + value.id + "'><i class='fas fa-cog'></i></button></td>";
                leg_2_table_data += "</tr>";
            }

            if (value.leg === "3") {
                leg_3_table_data += "<tr>";
                leg_3_table_data += "<td class='align-middle'>" + value.id + "</td>";
                leg_3_table_data += "<td class='align-middle'>" + value.joint_name + "</td>";
                leg_3_table_data += "<td class='align-middle'>" + value.voltage + " V</td>";
                leg_3_table_data += "<td class='align-middle'>" + value.temperature + " &#8451;</td>";
                leg_3_table_data += "<td class='align-middle'>" + value.position + " &#176;</td>";
                leg_3_table_data += "<td class='align-middle'><button class='btn' id='settings_" + value.id + "' data-toggle='modal' data-target='#configWindow' data-id='" + value.id + "'><i class='fas fa-cog'></i></button></td>";
                leg_3_table_data += "</tr>";
            }

            if (value.leg === "4") {
                leg_4_table_data += "<tr>";
                leg_4_table_data += "<td class='align-middle'>" + value.id + "</td>";
                leg_4_table_data += "<td class='align-middle'>" + value.joint_name + "</td>";
                leg_4_table_data += "<td class='align-middle'>" + value.voltage + " V</td>";
                leg_4_table_data += "<td class='align-middle'>" + value.temperature + " &#8451;</td>";
                leg_4_table_data += "<td class='align-middle'>" + value.position + " &#176;</td>";
                leg_4_table_data += "<td class='align-middle'><button class='btn' id='settings_" + value.id + "' data-toggle='modal' data-target='#configWindow' data-id='" + value.id + "'><i class='fas fa-cog'></i></button></td>";
                leg_4_table_data += "</tr>";
            }
        });

        $("#leg_1_table").html(leg_1_table_data);
        $("#leg_2_table").html(leg_2_table_data);
        $("#leg_3_table").html(leg_3_table_data);
        $("#leg_4_table").html(leg_4_table_data);

    }.bind(this));
};

//MODAL JS
$('#configWindow').on('show.bs.modal', function (event) {
    var button = $(event.relatedTarget);
    var id = button.data('id');
    console.log(actuators[id - 1].id);
    var modal = $(this);

    var max_pos = actuators[id - 1].max_position;
    var min_pos = actuators[id - 1].min_position;

    modal.find('.modal-title').text("Actuator Config: " + id);
    modal.find('#config_min_pos').html("<div class='input-group'><div class='input-group-prepend'><button class='btn btn-dark' onclick='decrease_min_pos(" + id + ")'>-</button></div><input onpropertychange='adjustSliderRange(" + id + ") type='number' id='min_pos_" + id + "' type='text' class='form-control' value='" + min_pos + "' min='0' max='1024'><div class='input-group-append'><button class='btn btn-dark' onclick='increase_min_pos(" + id + ")'>+</button></div></div>");
    modal.find('#config_max_pos').html("<div class='input-group'><div class='input-group-prepend'><button class='btn btn-dark' onclick='decrease_max_pos(" + id + ")'>-</button></div><input onchange='adjustSliderRange(" + id + ") type='number' id='max_pos_" + id + "' type='text' class='form-control' value='" + max_pos + "' min='0' max='1024'><div class='input-group-append'><button class='btn btn-dark' onclick='increase_max_pos(" + id + ")'>+</button></div></div>");
    modal.find('#current_pos').html("<input type='range' class='form-control-range' id='slider_" + id + "' oninput='move(" + id + ")' min='" + min_pos + "' max='" + max_pos + "'></input>");
    modal.find("#save_button").attr("onclick", "saveConfig(" + id + ")");
})

function decrease_min_pos(id) {
    var value = parseInt(document.getElementById('min_pos_' + id).value, 10);
    var min_value = parseInt(document.getElementById('min_pos_' + id).min, 10);
    value = isNaN(value) ? 0 : value;
    value <= min_value ? value = min_value + 1 : '';
    --value;
    document.getElementById('min_pos_' + id).value = value;
    adjustSliderRange(id);
}

function increase_min_pos(id) {
    var value = parseInt(document.getElementById('min_pos_' + id).value, 10);
    var max_value = parseInt(document.getElementById('max_pos_' + id).value, 10);
    value = isNaN(value) ? 0 : value;
    value >= max_value ? value = max_value - 1 : '';
    ++value;
    document.getElementById('min_pos_' + id).value = value;
    adjustSliderRange(id);
}

function decrease_max_pos(id) {
    var value = parseInt(document.getElementById('max_pos_' + id).value, 10);
    var min_value = parseInt(document.getElementById('min_pos_' + id).value, 10);
    value = isNaN(value) ? 0 : value;
    value <= min_value ? value = min_value + 1 : '';
    --value;
    document.getElementById('max_pos_' + id).value = value;
    adjustSliderRange(id);
}

function increase_max_pos(id) {
    var value = parseInt(document.getElementById('max_pos_' + id).value, 10);
    var max_value = parseInt(document.getElementById('max_pos_' + id).max, 10);
    value = isNaN(value) ? 0 : value;
    value >= max_value ? value = max_value - 1 : '';
    ++value;
    document.getElementById('max_pos_' + id).value = value;
    adjustSliderRange(id);
}

function adjustSliderRange(id) {
    var min_pos = parseInt(document.getElementById('min_pos_' + id).value, 10);
    var max_pos = parseInt(document.getElementById('max_pos_' + id).value, 10);
    document.getElementById('slider_' + id).min = min_pos;
    document.getElementById('slider_' + id).max = max_pos;
}

function move(id) {
    var pos = document.getElementById("slider_" + id);
    xhttp.open('POST', adhocURL + "move?id=" + id + "&pos=" + pos.value);
    xhttp.send();
}

function saveConfig(id) {
    var min_pos = parseInt(document.getElementById('min_pos_' + id).value, 10);
    var max_pos = parseInt(document.getElementById('max_pos_' + id).value, 10);
    xhttp.open('POST', adhocURL + "save?id=" + id + "&min_pos=" + min_pos + "&max_pos=" + max_pos);
    xhttp.send();
}

//CONTROLLERS JS

var joystickL = nipplejs.create({
    zone: document.getElementById("left-controller"),
    mode: "static",
    position: { left: "50%", top: "50%" },
    color: "black",
    size: 200,
});

var joystickR = nipplejs.create({
    zone: document.getElementById("right-controller"),
    mode: "static",
    position: { left: "50%", top: "50%" },
    color: "black",
    size: 200,
});



joystickL.on('start', function (evt, data) {
    l_event = evt.type;
    document.getElementById("l-event").innerHTML = l_event;
}).on('end', function (evt, data) {
    l_event = evt.type;
    l_distance = 0;
    l_angle = 0;
    l_direction = "none";
    document.getElementById("l-event").innerHTML = l_event;
    document.getElementById("l-distance").innerHTML = l_distance;
    document.getElementById("l-angle-deg").innerHTML = l_angle;
    document.getElementById("l-direction").innerHTML = l_direction;
    xhttp.open('POST', adhocURL + "gait?dir=" + l_direction + "&speed=" + l_distance);
    xhttp.send();
}).on('move', function (evt, data) {
    l_distance = Math.round(data.distance);
    l_angle = Math.round(data.angle.degree);
    l_direction = getDirection(l_angle);
    document.getElementById("l-distance").innerHTML = l_distance;
    document.getElementById("l-angle-deg").innerHTML = l_angle;
    document.getElementById("l-direction").innerHTML = l_direction;
    xhttp.open('POST', adhocURL + "gait?dir=" + l_direction + "&speed=" + l_distance);
    xhttp.send();
});

joystickR.on('start', function (evt, data) {
    r_event = evt.type;
    document.getElementById("r-event").innerHTML = r_event;
}).on('end', function (evt, data) {
    r_event = evt.type;
    r_distance = 0;
    r_angle = 0;
    r_direction = "stop";
    document.getElementById("r-event").innerHTML = r_event;
    document.getElementById("r-distance").innerHTML = r_distance;
    document.getElementById("r-angle-deg").innerHTML = r_angle;
    document.getElementById("r-direction").innerHTML = r_direction;
    xhttp.open('POST', adhocURL + "gait?dir=" + r_direction + "&speed=" + r_distance);
    xhttp.send();
}).on('move', function (evt, data) {
    r_event = evt.type;
    r_distance = Math.round(data.distance);
    r_angle = Math.round(data.angle.degree);
    r_direction = getDirection(r_angle);
    document.getElementById("r-event").innerHTML = r_event;
    document.getElementById("r-distance").innerHTML = r_distance;
    document.getElementById("r-angle-deg").innerHTML = r_angle;
    document.getElementById("r-direction").innerHTML = r_direction;
    xhttp.open('POST', adhocURL + "gait?dir=" + r_direction + "&speed=" + r_distance);
    xhttp.send();
});


function getDirection(angle) {
    if (angle >= 45 && angle < 135) return "up";
    else if (angle >= 135 && angle < 225) return "left";
    else if (angle >= 225 && angle < 315) return "down";
    else return "right";
}

//XYZ Position

function setPos(leg){
    var x = document.getElementById("x-data-" + leg).value;
    var y = document.getElementById("y-data-" + leg).value;
    var z = document.getElementById("z-data-" + leg).value;
    xhttp.open('POST', adhocURL + "pos?id=" + leg +  "&x=" + x + "&y=" + y);
    xhttp.send();
}