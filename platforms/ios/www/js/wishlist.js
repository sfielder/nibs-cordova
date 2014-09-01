angular.module('nibs.wishlist', ['ngResource', 'nibs.config'])

    // Routes
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.wishlist', {
                url: "/wishlist",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/wishlist.html",
                        controller: "WishListCtrl"
                    }
                }
            })

    })

    // REST resources
    .factory('WishListItem', function ($resource, HOST) {
        return $resource(HOST + 'wishlist/:id');
    })

    // Controllers
    .controller('WishListCtrl', function ($scope, WishListItem) {

        $scope.products = WishListItem.query();

        $scope.deleteItem = function(product) {
            product.$delete({id: product.id}, function() {
                $scope.products = WishListItem.query();
            });
        };

    });