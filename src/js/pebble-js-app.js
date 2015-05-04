var ipServer = localStorage.getItem("ar.com.lofarolabs.remote.ip");
if (!ipServer) {
  ipServer = '192.168.1.100';
}
var portServer = localStorage.getItem("ar.com.lofarolabs.remote.port");
if (!portServer) {
  portServer = '8080';
}
var base_url = "http://"+ipServer+":"+portServer;



var UI = require('ui');

var i = 0;

function sendBuffer(b) {
//  var response;
  var req = new XMLHttpRequest();
  req.open('GET', base_url+"/"+b, true);
  req.send("sendBuffer");
}

function sendi() {
//  var response;
  i = i+1;
  var req = new XMLHttpRequest();
  req.open('GET', base_url+"/"+String(i), true);
  req.send("dani");
}




// Function to send a message to the Pebble using AppMessage API
function sendMessage(a) {
  sendBuffer(a);
  //sendi();
	////Pebble.sendAppMessage({"status": 0});
	
	// PRO TIP: If you are sending more than one message, or a complex set of messages, 
	// it is important that you setup an ackHandler and a nackHandler and call 
	// Pebble.sendAppMessage({ /* Message here */ }, ackHandler, nackHandler), which 
	// will designate the ackHandler and nackHandler that will be called upon the Pebble 
	// ack-ing or nack-ing the message you just sent. The specified nackHandler will 
	// also be called if your message send attempt times out.
}


// Called when JS is ready
Pebble.addEventListener("ready",
							function(e) {
							});
												
// Called when incoming message from the Pebble is received
Pebble.addEventListener("appmessage",
							function(e) {
								//console.log("Received Status: " + e.payload.status);
                a = e.payload.message;
                //sendi();
                //a = "temp";
								sendMessage(String(a));
							});

Pebble.addEventListener('showConfiguration', function(e) {
  // Show config page
  Pebble.openURL('http://www.files.lofarolabs.com/software/pebble/Robot-Wrist-Ctrl/config.html');
});

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("configuration closed");
  // webview closed
  var options = JSON.parse(decodeURIComponent(e.response));
  ipServer = options.ip;
  portServer = options.port;
  localStorage.setItem("ar.com.lofarolabs.remote.ip", ipServer);
  localStorage.setItem("ar.com.lofarolabs.remote.port", portServer);
});