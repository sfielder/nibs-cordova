cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "file": "plugins/org.apache.cordova.inappbrowser/www/inappbrowser.js",
        "id": "org.apache.cordova.inappbrowser.inappbrowser",
        "clobbers": [
            "window.open"
        ]
    },
    {
        "file": "plugins/com.salesforce.cordova.sos/www/sos.js",
        "id": "com.salesforce.cordova.sos.sos",
        "clobbers": [
            "window.sos"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "org.apache.cordova.inappbrowser": "0.5.1",
    "com.salesforce.cordova.sos": "0.0.1"
}
// BOTTOM OF METADATA
});