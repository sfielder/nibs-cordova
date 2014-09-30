angular.module('nibs.push', [])

    .factory('PushNotification', function ($http, $rootScope) {
        return {
            send: function(notification) {
                return $http.post($rootScope.server.url + '/notifications/', notification);
            }
        };
    });
