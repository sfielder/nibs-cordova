angular.module('nibs.activity', ['ngResource', 'nibs.config'])

    // Routes
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.activity', {
                url: "/activity",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/activity-list.html",
                        controller: "ActivityCtrl"
                    }
                }
            })

    })

    // Resources
    .factory('Activity', function ($resource, HOST) {
        return $resource(HOST + 'activities/:activityId');
    })


    //Controllers
    .controller('ActivityCtrl', function ($scope, $state, Activity) {
        $scope.activities = Activity.query();

        $scope.doRefresh = function() {
            $scope.activities = Activity.query(function() {
                $scope.$broadcast('scroll.refreshComplete');
            });
        }

        $scope.popupDialog = function() {

            if (navigator.notification) {
                navigator.notification.alert(
                    'You have a new message!',  // message
                    function() {                // callback
                        $state.go('app.messages');
                    },
                    'Nibs',                     // title
                    'Open Inbox'             // buttonName
                );
            } else {
                alert('You have a new message!');
                $state.go('app.messages');
            }

        }

    });