var app = angular.module('nibs', ['ionic', 'openfb', 'nibs.config', 'nibs.profile', 'nibs.auth', 'nibs.product', 'nibs.offer', 'nibs.store-locator', 'nibs.gallery', 'nibs.settings', 'nibs.case', 'nibs.chatter', 'nibs.journeybuilder'])

    .run(function ($window, $location, $rootScope, $state, $ionicPlatform, $http, OpenFB, FB_APP_ID, JourneyBuilder, JBSurvey) {

        var user = JSON.parse($window.localStorage.getItem('user'));

        $rootScope.user = user;
        $rootScope.server = {url: $window.localStorage.getItem('serverURL') || "http://nibs2.herokuapp.com"};

        // Intialize OpenFB Facebook library
        OpenFB.init(FB_APP_ID, $window.localStorage);

        $ionicPlatform.ready(function() {
            if(window.StatusBar) {
                StatusBar.styleDefault();
            }

            if (typeof(ETPush) != "undefined") {

                function onMessage(payload) {
                    console.log(payload);
                    alert('got message: ' + JSON.stringify(payload));
                }

                ETPush.registerForNotifications(
                    function() {
                        console.log('registerForNotifications: success');
                    },
                    function(error) {
                        alert('Error registering for Push Notification');
                        console.log('registerForNotifications: error - ' + JSON.stringify(error));
                    },
                    "onNotification"
                );

                ETPush.resetBadgeCount();

                if (user && user.email) {
                    console.log('Subscribing for Push as ' + user.email);
                    ETPush.setSubscriberKey(
                        function() {
                            console.log('setSubscriberKey: success');
                        },
                        function(error) {
                            alert('Error setting Push Notification subscriber');
                        },
                        user.email
                    );
                }

            }

        });

        // Re-route to welcome street if we don't have an authenticated token
        $rootScope.$on('$stateChangeStart', function(event, toState) {
            if (toState.name !== 'app.login' && toState.name !== 'app.signup' && toState.name !== 'app.welcome' && toState.name !== 'app.logout' && !$window.localStorage.getItem('token')) {
                console.log('Aborting state ' + toState.name + ': No token');
                $location.path('/app/welcome');
                event.preventDefault();
            }
        });

        $rootScope.poller = setInterval(function() {
            if ($window.localStorage.getItem('token')) {
                JourneyBuilder.load_survey()
                    .success(function(survey) {
                        if (survey != "false") {
                            console.log('load_survey success');
                            console.log(survey);
                            $rootScope.openSurveyDialog(survey);
                            //JBSurvey(survey, $rootScope);
                        }
                    }).catch(function() {});
            }

        }, 10000);


        $state.go('app.profile');
    })

    .config(function ($stateProvider, $urlRouterProvider) {

        $stateProvider

            .state('app', {
                url: "/app",
                abstract: true,
                templateUrl: "templates/menu.html",
                controller: "AppCtrl"
            })

            .state('app.welcome', {
                url: "/welcome",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/welcome.html"
                    }
                }
            })


        // if none of the above states are matched, use this as the fallback
//        $urlRouterProvider.otherwise('/app/profile');

    })


    .controller('AppCtrl', function ($scope, $rootScope, $state, $window, $location, $ionicViewService, $ionicPopup, $ionicModal) {

        $ionicModal.fromTemplateUrl('templates/survey.html', {
            scope: $scope,
            animation: 'slide-in-up'
        }).then(function(modal) {
            $scope.modal = modal;
        });
        $scope.openSurveyDialog = function(survey) {
            $scope.questions = [{question: survey.q1_text, choices:survey.q1_choices.split(',')},
                                {question: survey.q2_text, choices:survey.q2_choices.split(',')}];
            $scope.modal.show();
        };

        $rootScope.openSurveyDialog = $scope.openSurveyDialog;
        $scope.$on('modal.hidden', function(event) {

        });


    })

    // XMLHTTPRequest Interceptor.
    // Outbound: Adds access token to HTTP requests before they are sent to the server.
    // Inbound: Handles 401 (Not Authorized) errors by loading the Login page
    .factory('AuthInterceptor', function ($rootScope, $window, $q, $location) {

        return {
            request: function (config) {
                //TODO: Remove test
                if (config.url.indexOf('load_survey')<0) $rootScope.loading = true;
                config.headers = config.headers || {};
                if ($window.localStorage.getItem('token')) {
                    config.headers.authorization = $window.localStorage.getItem('token');
                }
                return config || $q.when(config);
            },
            requestError: function (request) {
                console.log('request error');
                $rootScope.loading = false;
                return $q.reject(request);
            },
            response: function (response) {
                $rootScope.loading = false;
                return response || $q.when(response);
            },
            responseError: function (response) {
                console.log(JSON.stringify(response));
                $rootScope.loading = false;
                if (response && response.status === 401) {
                    // TODO: broadcast event instead.
                    $location.path('/app/welcome');
                } else if (response && response.status !== 404) {
                    console.log(response);
                    // alert(response.data);
                }
                return $q.reject(response);
            }
        };
    })

    // Add the AuthInterceptor declared above
    .config(function ($httpProvider) {
        $httpProvider.interceptors.push('AuthInterceptor');
    });
