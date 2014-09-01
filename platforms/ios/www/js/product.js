angular.module('nibs.product', ['ngResource', 'openfb', 'nibs.config', 'nibs.status', 'nibs.activity', 'nibs.wishlist'])

    .config(function ($stateProvider, $urlRouterProvider) {

        $stateProvider

            .state('app.products', {
                url: "/products",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/product-list.html",
                        controller: "ProductListCtrl"
                    }
                }
            })

            .state('app.product-detail', {
                url: "/products/:productId",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/product-detail.html",
                        controller: "ProductDetailCtrl"
                    }
                }
            })

    })

    // REST resource for access to Products data
    .factory('Product', function ($resource, HOST) {
        return $resource(HOST + 'products/:productId');
    })

    .controller('ProductListCtrl', function ($scope, Product, OpenFB) {

        $scope.products = Product.query();

        $scope.doRefresh = function() {
            $scope.products = Product.query(function() {
                $scope.$broadcast('scroll.refreshComplete');
            });
        }

    })

    .controller('ProductDetailCtrl', function ($scope, $stateParams, $ionicPopup, Product, OpenFB, WishListItem, Activity, Status) {

        $scope.product = Product.get({productId: $stateParams.productId});

        $scope.shareOnFacebook = function () {
// Uncomment the lines below to support enable the actual Facebook posting.
//            var product = $scope.product;
//            OpenFB.post('/me/feed/', {name: product.name, link: product.productPage, picture: product.image, caption: 'Available Today!', description: product.description})
//                .success(function() {
//                    Status.show('Shared on Facebook!');
//                    var activity = new Activity({type: "Shared on Facebook", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image});
//                    activity.$save(Status.checkStatus);
//                })
//                .error(function() {
//                    $ionicPopup.alert({title: 'Facebook', content: 'Something went wrong while sharing this offer.'});
//                });

            // Fake Facebook posting
            Status.show('Shared on Facebook!');
            var activity = new Activity({type: "Shared on Facebook", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image});
            activity.$save(Status.checkStatus);

        };

        $scope.shareOnTwitter = function () {
            Status.show('Shared on Twitter!');
            var activity = new Activity({type: "Shared on Twitter", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image});
            activity.$save(Status.checkStatus);
        };

        $scope.shareOnGoogle = function () {
            Status.show('Shared on Google+!');
            var activity = new Activity({type: "Shared on Google+", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image});
            activity.$save(Status.checkStatus);
        };

        $scope.saveToWishList = function () {
            var item = new WishListItem({productId: $scope.product.id});
            item.$save(function() {
                Status.show('Added to your wish list!');
                var activity = new Activity({type: "Saved to Wish List", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image});
                activity.$save(Status.checkStatus);
            });
        };

    });
