angular.module('nibs.wallet', ['ngResource', 'nibs.config'])

    // Routes
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.wallet', {
                url: "/wallet",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/wallet.html",
                        controller: "WalletCtrl"
                    }
                }
            })

    })

    // Resources
    .factory('WalletItem', function ($resource, HOST) {
        return $resource(HOST + 'wallet/:id');
    })


    //Controllers
    .controller('WalletCtrl', function ($scope, WalletItem) {

        $scope.walletItems = WalletItem.query();

        $scope.deleteItem = function(offer) {
            offer.$delete({id: offer.id}, function() {
                $scope.walletItems = WalletItem.query();
            });
        };

    })
