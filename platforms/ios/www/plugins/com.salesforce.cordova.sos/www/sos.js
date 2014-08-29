cordova.define("com.salesforce.cordova.sos.sos", function(require, exports, module) { window.SalesforceSOS = function(email) {
	cordova.exec(function() {}, function(err) {alert(err);}, "SOS", "startSOS", [email]);
}
});
