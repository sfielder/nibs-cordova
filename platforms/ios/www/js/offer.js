angular.module('nibs.offer', ['ngResource', 'openfb', 'nibs.status', 'nibs.activity', 'nibs.wallet', 'nibs.config'])

    // Routes
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.offers', {
                url: "/offers",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/offer-list.html",
                        controller: "OfferListCtrl"
                    }
                }
            })

            .state('app.offer-detail', {
                url: "/offers/:offerId",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/offer-detail.html",
                        controller: "OfferDetailCtrl"
                    }
                }
            })

            .state('app.offer-redeem', {
                url: "/offers/:offerId/redeem",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/redeem.html",
                        controller: "OfferDetailCtrl"
                    }
                }
            })

    })

    // Resources
    .factory('Offer', function ($resource, HOST) {
        return $resource(HOST + 'offers/:offerId');
    })


    //Controllers
    .controller('OfferListCtrl', function ($scope, $ionicPopup, Offer) {

        $scope.offers = Offer.query();

        $scope.doRefresh = function() {
            $scope.offers = Offer.query(function() {
                $scope.$broadcast('scroll.refreshComplete');
            });
        };

    })

    .controller('OfferDetailCtrl', function ($scope, $state, $ionicPopup, $stateParams, Offer, OpenFB, WalletItem, Activity, Status) {

        $scope.offer = Offer.get({offerId: $stateParams.offerId});
        $scope.shareOnFacebook = function (offer) {
//      Uncomment to enable actual "Share on Facebook" feature
//            OpenFB.post('/me/feed', {name: offer.name, link: offer.campaignPage, picture: offer.image, caption: 'Offer ends soon!', description: offer.description})
//                .success(function() {
//                    Status.show('Shared on Facebook!');
//                    var activity = new Activity({type: "Shared on Facebook", points: 1000, offerId: $scope.offer.sfid, name: $scope.offer.name, image: $scope.offer.image});
//                    activity.$save(Status.checkStatus);
//                })
//                .error(function() {
//                    $ionicPopup.alert({title: 'Facebook', content: 'Something went wrong while sharing this offer.'});
//                });
            Status.show('Shared on Facebook!');
            var activity = new Activity({type: "Shared on Facebook", points: 1000, offerId: $scope.offer.sfid, name: $scope.offer.name, image: $scope.offer.image});
            activity.$save(Status.checkStatus);
        };

        $scope.shareOnTwitter = function () {
            Status.show('Shared on Twitter!');
            var activity = new Activity({type: "Shared on Twitter", points: 1000, offerId: $scope.offer.sfid, name: $scope.offer.name, image: $scope.offer.image});
            activity.$save(Status.checkStatus);
        };

        $scope.shareOnGoogle = function () {
            Status.show('Shared on Google+!');
            var activity = new Activity({type: "Shared on Google+", points: 1000, offerId: $scope.offer.sfid, name: $scope.offer.name, image: $scope.offer.image});
            activity.$save(Status.checkStatus);
        };

        $scope.saveToWallet = function () {
            var walletItem = new WalletItem({offerId: $scope.offer.id});
            walletItem.$save(function() {
                Status.show('Saved to your wallet!');
                var activity = new Activity({type: "Saved to Wallet", points: 1000, offerId: $scope.offer.sfid, name: $scope.offer.name, image: $scope.offer.image});
                activity.$save(Status.checkStatus);
            });
        };

        $scope.redeem = function () {
            var activity = new Activity({type: "Redeemed Offer", points: 1000, offerId: $scope.offer.sfid, name: $scope.offer.name, image: $scope.offer.image});
            activity.$save(Status.checkStatus);
            $state.go('app.offer-redeem', {offerId: $scope.offer.id});
        }

    });
