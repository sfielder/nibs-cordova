cordova.define("com.salesforce.cordova.sos.sos", function(require, exports, module) {
    window.SalesforceSOS = {
        setup: function(account, app, email, retry, expire) {
               var args = [];
               if (account) {
                 args.push(account);
               }
               if (app) {
                 args.push(app);
               }
               if (email) {
               args.push(email);
               }
               if (retry) {
               args.push(retry);
               }
               if (expire) {
               args.push(expire);
               }
               cordova.exec(function() {}, function(err) {alert(err);}, "SOS", "setup", args);
        },

        setupMessages: function(alertTitle, connectMessage, disconnectMessage, agentDisconnectMessage,
                                retrySeconds, timeoutSeconds) {
               var args = [];
               if (alertTitle) {
               args.push(alertTitle);
               }
               if (connectMessage) {
               args.push(connectMessage);
               }
               if (disconnectMessage) {
               args.push(disconnectMessage);
               }
               if (agentDisconnectMessage) {
               args.push(agentDisconnectMessage);
               }
               if (retrySeconds) {
               args.push(retrySeconds);
               }
               if (timeoutSeconds) {
               args.push(timeoutSeconds);
               }
            cordova.exec(function() {}, function(err) {alert(err);}, "SOS", "setupMessages", args);
        },

        startSession: function(email) {
            cordova.exec(function() {}, function(err) {alert(err);}, "SOS", "startSOS", [email]);
        }
    }
});
