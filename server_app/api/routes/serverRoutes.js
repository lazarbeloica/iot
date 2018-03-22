

'use strict';
module.exports = function (app) {
  var todoList = require('../controllers/serverController');

  // todoList Routes
  app.route('/devices')
    .get(todoList.list_all_devices);

  app.route('/measurements')
    .get(todoList.list_all_measurements)
    .post(todoList.create_a_measurement);

  app.route('/measurements/:measurementId')
    .get(todoList.read_a_measurement)
    .put(todoList.update_a_measurement)
    .delete(todoList.delete_a_measurement);

  app.route('/devsmeasurements/:devId')
    .get(todoList.read_devices_measurements);
};