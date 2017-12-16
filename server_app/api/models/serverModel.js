
'use strict';
var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var MeasurementSchema = new Schema({
  devId: {
    type: String,
    required: 'Kindly enter id of the device used for measuring'
  },
  value: {
    type: Number,
    required: 'Kindly enter value of the measurement'
  },
  Created_date: {
    type: Date,
    default: Date.now
  }
});

module.exports = mongoose.model('Measurement', MeasurementSchema);