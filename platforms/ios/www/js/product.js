angular.module('nibs.product', ['openfb', 'nibs.status', 'nibs.activity', 'nibs.wishlist', 'nibs.push'])

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
    .factory('Product', function ($http, $rootScope) {
        return {
            all: function() {
                return $http.get($rootScope.server.url + '/products');
            },
            get: function(productId) {
                return $http.get($rootScope.server.url + '/products/' + productId);
            }
        };
    })

    .controller('ProductListCtrl', function ($scope, Product, OpenFB) {

        Product.all().success(function(products) {
            $scope.products = products;
        });

        $scope.doRefresh = function() {
            Product.all().success(function(products) {
                $scope.products = products;
                $scope.$broadcast('scroll.refreshComplete');
            });
        }

    })

    .controller('ProductDetailCtrl', function ($scope, $rootScope, $stateParams, $ionicPopup, Product, OpenFB, WishListItem, Activity, Status, PushNotification, ET_MESSAGE_ID) {

        Product.get($stateParams.productId).success(function(product) {
            $scope.product = product;
        });

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
            Activity.create({type: "Shared on Facebook", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image})
                .success(function(status) {
                    Status.checkStatus(status);
                });

            PushNotification.send({
                messageId: ET_MESSAGE_ID,
                // subscriberKeys: [$rootScope.user.email],
                openDirect: '/app/products/' + $stateParams.productId,
                messageText: $rootScope.user.firstname + " just shared " + $scope.product.name});
        };

        $scope.shareOnTwitter = function () {
            Status.show('Shared on Twitter!');
            Activity.create({type: "Shared on Twitter", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image})
                .success(function(status) {
                    Status.checkStatus(status);
                });
        };

        $scope.shareOnGoogle = function () {
            Status.show('Shared on Google+!');
            Activity.create({type: "Shared on Google+", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image})
                .success(function(status) {
                    Status.checkStatus(status);
                });
        };

        $scope.saveToWishList = function () {
            WishListItem.create({productId: $scope.product.id}).success(function(status) {
                Status.show('Added to your wish list!');
                Activity.create({type: "Added to Wish List", points: 1000, productId: $scope.product.sfid, name: $scope.product.name, image: $scope.product.image})
                    .success(function(status) {
                        Status.checkStatus(status);
                    });
            });
        };

    });
