angular.module('nibs.chatter', ['nibs.config'])

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
        if ($rootScope.server.url.indexOf('nibs2') >= 0) {
            CHATTER_SSO = 'https://login.salesforce.com/services/auth/sso/00Do0000000aEe2EAE/Nibs2';
        } else {
            CHATTER_SSO = 'https://login.salesforce.com/services/auth/sso/00Di0000000k8FREAY/RealNibs';
        }
        //$scope.chatter_frame = CHATTER_SSO + "?startURL=%2Fone%2Fone.app";
        $scope.chatter_frame = CHATTER_SSO + "?startURL=" + encodeURIComponent('/apex/NibsChatter');
        $scope.chatter_frame = $sce.trustAsResourceUrl($scope.chatter_frame);

        window.frame_loaded = function() {
            $rootScope.loading = false;
            $rootScope.$apply();
        }
    })

