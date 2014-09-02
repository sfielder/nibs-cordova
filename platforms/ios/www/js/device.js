angular.module('nibs.device', ['ngResource', 'nibs.config'])

    // Resources
    .factory('Device', function ($resource, HOST) {
        return $resource(HOST + 'devices');
    });

