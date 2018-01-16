var Graph = Graph || {};

(function () {
    var canvas = document.getElementById("graph");
    var select = document.getElementById("devicelist");
    var button = document.getElementById("selectdevice");
    var url = "http://checkmytemp.fr.openode.io/measurements";


    button.addEventListener("click" , () => {
        $.ajax({
            "url": url,
            "dataType": "jsonp",
            success: function (response) {
                console.log(response);
            }
        });
    });

})();