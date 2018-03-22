

'use strict';

var mongoose = require('mongoose'),
  Measurement = mongoose.model('Measurement');

exports.list_all_devices = function(req, res) {
  Measurement.find().distinct('devId', function(err, ids) {
    if (err)
      res.send(err);
    res.json(ids);
  });
};

exports.list_all_measurements = function(req, res) {
  Measurement.find({}, function(err, measurement) {
    if (err)
      res.send(err);
    res.json(measurement);
  });
};

exports.create_a_measurement = function(req, res) {
  var new_measurement = new Measurement(req.body);
  new_measurement.save(function(err, measurement) {
    if (err)
      res.send(err);
    res.json(measurement);
  });
};

exports.read_a_measurement = function(req, res) {
  Measurement.findById(req.params.measurementId, function(err, measurement) {
    if (err)
      res.send(err);
    res.json(measurement);
  });
};

exports.read_devices_measurements = function(req, res) {
  Measurement.find({'devId': req.params.devId}, 'Created_date value', function(err, measurements) {
    if (err){
      res.send(err);
    }
    res.json(measurements);
  });
};

exports.update_a_measurement = function(req, res) {
  Measurement.findOneAndUpdate({_id: req.params.measurementId}, req.body, {new: true}, function(err, measurement) {
    if (err)
      res.send(err);
    res.json(measurement);
  });
};

exports.delete_a_measurement = function(req, res) {
  Measurement.remove({
    _id: req.params.measurementId
  }, function(err, measurement) {
    if (err)
      res.send(err);
    res.json({ message: 'Measurement successfully deleted' });
  });
};