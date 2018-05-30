
google.charts.load('current', { 'packages': ['corechart'] });

const SERVER_URL = "http://checkmytemp.herokuapp.com/"
const TEST_SERVER_URL = "http://localhost:3000"

window.addEventListener("load", () => {

    var graph_container = document.getElementById("graph_container");
    graph_container.style.height = (screen.height * 0.6) + "px";
    graph_container.style.width = (screen.width * 0.9) + "px";

    var select = document.getElementById("devicelist");
    var uri = SERVER_URL + "devices";
    $.ajax({
        url: uri,
        type: 'GET',
        data: 'jsonp',
        success: function (response) {
            console.log(response);
            console.log("success");
            var options = response;
            for (var i = 0; i < options.length; i++) {
                var opt = options[i];
                var el = document.createElement("option");
                el.textContent = opt;
                el.value = opt;
                select.appendChild(el);
            }
        },
        error: function (jqXHR, exception) {
            if (jqXHR.status === 0) {
                console.log('Not connect.\n Verify Network.');
            } else if (jqXHR.status == 404) {
                console.log('Requested page not found. [404]');
            } else if (jqXHR.status == 500) {
                console.log('Internal Server Error [500].');
            } else if (exception === 'parsererror') {
                console.log('Requested JSON parse failed.');
            } else if (exception === 'timeout') {
                console.log('Time out error.');
            } else if (exception === 'abort') {
                console.log('Ajax request aborted.');
            } else {
                console.log('Uncaught Error.\n' + jqXHR.responseText);
            }
        }
    });
});

(function () {
    var select = document.getElementById("devicelist");
    var button = document.getElementById("selectdevice");
    var URI = SERVER_URL + "devsmeasurements/";
    //var URI = TEST_SERVER_URL + 'devsmeasurements/';

    button.addEventListener("click", () => {
        if (select.selectedIndex == 0)
            return null;

        var uri = URI + select.options[select.selectedIndex].text;

        $.ajax({
            url: uri,
            type: 'GET',
            data: 'jsonp',
            success: function (response) {
                var data = new google.visualization.arrayToDataTable(new Array());
                data.addColumn('date', 'Date');
                data.addColumn('number', 'Temperature');

                response.forEach(element => {
                    data.addRow([new Date(element.Created_date), parseInt(element.value)]);
                });

                var options = {
                    title: 'Lazar room tmp: ' + select.options[select.selectedIndex].text,
                    curveType: 'function',
                    legend: { position: 'bottom' }
                };

                var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));
                chart.draw(data, options);
            }
        });
    });

})();