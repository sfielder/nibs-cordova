window.SalesforceSOS = function(email) {
	cordova.exec(function() {}, function(err) {alert(err);}, "SOS", "startSOS", [email]);
}