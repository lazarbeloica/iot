


var express = require('express'),
app = express(),
port = process.env.PORT || 80,
mongoose = require('mongoose'),
Task = require('./api/models/serverModel'), //created model loading here
bodyParser = require('body-parser');
var DbCredentials = {
  schema: "mongodb://",
  user: "beloica",
  pass: "Aa12345678",
  host: "ds251737.mlab.com",
  port: 51737,
  db : "checkmytmp"
};

var URI = DbCredentials.schema +
          DbCredentials.user +
          ":" +
          DbCredentials.pass +
          "@"
          + DbCredentials.host
          + ":"
          + DbCredentials.port
          + "/"
          + DbCredentials.db;
console.log(URI);

// mongoose instance connection url connection
mongoose.Promise = global.Promise;
mongoose.connect(URI);

var db = mongoose.connection;

db.on('error', console.error.bind(console, 'connection error:'));

db.once('open', function callback () {
  console.log("Connection open!");
  });

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// Add headers
app.use(function (req, res, next) {
  // Website you wish to allow to connect
  res.setHeader('Access-Control-Allow-Origin', '*');

  // Request methods you wish to allow
  res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

  // Request headers you wish to allow
  res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');

  // Set to true if you need the website to include cookies in the requests sent
  // to the API (e.g. in case you use sessions)
  res.setHeader('Access-Control-Allow-Credentials', false);

  // Pass to next layer of middleware
  next();
});

var routes = require('./api/routes/serverRoutes'); //importing route
routes(app); //register the route

app.use(function(req, res) {
    res.status(404).send({url: req.originalUrl + ' not found'})
  });

app.listen(port);

console.log('Lazar\'s measurements server started on: ' + port);
