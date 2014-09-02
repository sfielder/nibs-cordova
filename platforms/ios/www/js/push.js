angular.module('nibs.push', ['ngResource', 'nibs.config'])

    .factory('PushNotification', function ($resource, HOST) {
        return $resource(HOST + 'notifications', null, {
                'send': {method:'POST'}
            });
    });