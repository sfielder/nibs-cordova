angular.module('nibs.chatter', ['ngResource', 'openfb', 'nibs.config', 'nibs.status', 'nibs.activity', 'nibs.wishlist'])

    .config(function ($stateProvider, $urlRouterProvider) {

        $stateProvider

            .state('app.chatter', {
                url: "/chatter",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/chatter.html",
                        controller: "ChatterCtrl"
                    }
                }
            })
        })

    .controller('ChatterCtrl', function ($rootScope, $scope, $sce, CHATTER_SSO) {
        $rootScope.loading = true;
        //$scope.chatter_frame = CHATTER_SSO + "?startURL=%2Fone%2Fone.app";
        $scope.chatter_frame = CHATTER_SSO + "?startURL=" + encodeURIComponent('/apex/NibsChatter');
        $scope.chatter_frame = $sce.trustAsResourceUrl($scope.chatter_frame);

        window.frame_loaded = function() {
            $rootScope.loading = false;
            $rootScope.$apply();
        }
    })

