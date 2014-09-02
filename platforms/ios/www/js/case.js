angular.module('nibs.case', ['ngResource', 'nibs.config'])

    // Routes
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.help', {
                url: "/help",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/case.html",
                        controller: "CaseCtrl"
                    }
                }
            })

    })

    // Resources
    .factory('Case', function ($resource, HOST) {
        return $resource(HOST + 'cases', null, {
                'save':      {method:'POST'}}
        );
    })

    //Controllers
    .controller('CaseCtrl', function ($scope, $window, $ionicPopup, Case, User) {

        $scope.case = new Case();

        $scope.submit = function () {
            $scope.case.$save(function() {
                $ionicPopup.alert({title: 'Thank You', content: 'A customer representative will contact you shortly.'});
            });
        };

        $scope.sos = function() {
            User.get(function(user) {
                alert(JSON.stringify(user));
                // Available via SOS cordova plugin
                window.SalesforceSOS(user.email);
            });
        }
    });
