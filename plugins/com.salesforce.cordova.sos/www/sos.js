window.SalesforceSOS = {
	setup: function() {
		cordova.exec(function() {}, function(err) {alert(err);}, "SOS", "setup", [email]);
	},

	startSession: function(email) {
		cordova.exec(function() {}, function(err) {alert(err);}, "SOS", "startSOS", [email]);
	}
}