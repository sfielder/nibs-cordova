angular.module('nibs.auth', ['ngResource', 'openfb', 'nibs.config'])

    /*
     * Routes
     */
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.login', {
                url: "/login",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/login.html",
                        controller: "LoginCtrl"
                    }
                }
            })

            .state('app.logout', {
                url: "/logout",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/welcome.html",
                        controller: "LogoutCtrl"
                    }
                }
            })

            .state('app.signup', {
                url: "/signup",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/signup.html",
                        controller: "SignupCtrl"
                    }
                }
            })

    })

    /*
     * REST Resources
     */
    .factory('Auth', function ($http, $window, $rootScope, HOST) {
        return {
            login: function (user) {
                return $http.post(HOST + 'login', user)
                    .success(function (data) {
                        $rootScope.user = data.user;
                        $window.localStorage.user = JSON.stringify(data.user);
                        $window.localStorage.token = data.token;

                        console.log('Subscribing for Push as ' + data.user.email);
                        ETPush.setSubscriberKey(
                            function() {
                                console.log('setSubscriberKey: success');
                            },
                            function(error) {
                                alert('Error setting Push Notification subscriber');
                            },
                            data.user.email
                        );

                    });
            },
            fblogin: function (fbUser) {
                console.log(JSON.stringify(fbUser));
                console.log(HOST);
                return $http.post(HOST + 'fblogin', {user:fbUser, token: $window.localStorage['fbtoken']})
                    .success(function (data) {
                        $rootScope.user = data.user;
                        $window.localStorage.user = JSON.stringify(data.user);
                        $window.localStorage.token = data.token;

                        console.log('Subscribing for Push as ' + data.user.email);
                        ETPush.setSubscriberKey(
                            function() {
                                console.log('setSubscriberKey: success');
                            },
                            function(error) {
                                alert('Error setting Push Notification subscriber');
                            },
                            data.user.email
                        );

                    });
            },
            logout: function () {
                $rootScope.user = undefined;
                var promise = $http.post(HOST + 'logout');
                $window.localStorage.clear();
                return promise;
            },
            signup: function (user) {
                return $http.post(HOST + 'signup', user);
            }
        }
    })

    /*
     * Controllers
     */
    .controller('LoginCtrl', function ($scope, $state, $window, $location, $ionicViewService, $ionicPopup, Auth, OpenFB) {

        $window.localStorage.clear();

        $scope.user = {};

        $scope.login = function () {

            Auth.login($scope.user)
                .success(function (data) {
                    $state.go("app.profile");
                })
                .error(function (err) {
                    $ionicPopup.alert({title: 'Oops', content: err});
                });
        };

        $scope.facebookLogin = function () {

            OpenFB.login('email,read_stream,publish_stream').then(
                function () {
                    OpenFB.get('/me', {fields: 'id,first_name,last_name,email,picture,birthday,gender'})
                        .success(function (fbUser) {
                            Auth.fblogin(fbUser)
                                .success(function (data) {
                                    $state.go("app.profile");
                                    setTimeout(function () {
                                        $ionicViewService.clearHistory();
                                    });
                                })
                                .error(function (err) {
                                    console.log(JSON.stringify(err));
                                    $ionicPopup.alert({title: 'Oops', content: err});
                                })
                        })
                        .error(function () {
                            $ionicPopup.alert({title: 'Oops', content: "The Facebook login failed"});
                        });
                },
                function () {
                    $ionicPopup.alert({title: 'Oops', content: "The Facebook login failed"});
                });
        };

    })

    .controller('LogoutCtrl', function ($rootScope, $window) {
        console.log("Logout");
        $rootScope.user = null;
        $window.localStorage.clear();

    })

    .controller('SignupCtrl', function ($scope, $state, $ionicPopup, Auth, OpenFB) {

        $scope.user = {};

        $scope.signup = function () {
            if ($scope.user.password !== $scope.user.password2) {
                $ionicPopup.alert({title: 'Oops', content: "passwords don't match"});
                return;
            }
            Auth.signup($scope.user)
                .success(function (data) {
                    $state.go("app.login");
                });
        };

        $scope.facebookLogin = function () {

            OpenFB.login('email,read_stream,publish_stream').then(
                function () {
                    OpenFB.get('/me', {fields: 'id,first_name,last_name,email,picture,birthday,gender'})
                        .success(function (fbUser) {
                            Auth.fblogin(fbUser)
                                .success(function (data) {
                                    $state.go("app.profile");
                                    setTimeout(function () {
                                        $ionicViewService.clearHistory();
                                    });
                                })
                                .error(function (err) {
                                    $ionicPopup.alert({title: 'Oops', content: err});
                                })
                        })
                        .error(function () {
                            $ionicPopup.alert({title: 'Oops', content: "The Facebook login failed"});
                        });
                },
                function () {
                    $ionicPopup.alert({title: 'Oops', content: "The Facebook login failed"});
                });
        };

    });
